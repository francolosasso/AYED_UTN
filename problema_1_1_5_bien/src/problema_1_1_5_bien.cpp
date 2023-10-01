#ifndef _MAIN
#define _MAIN
#include <iostream>
#include "../../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/funciones/files.hpp"
#include <stdlib.h>
#include <strings.h>
#include "problema_1_1_5_bien.hpp"
using namespace std;

void inicializarContadores(Coll<int> &c)
{
    for (int i = 0; i < 5; i++)
    {
        collAdd<int>(c, 0, intToString);
    }
}

Coll<RCuento> subirCuento()
{
    Coll<RCuento> ret = coll<RCuento>();
    FILE *f = fopen("CUENTOS.dat", "r+b");

    Coll<int> cCont = coll<int>(',');
    inicializarContadores(cCont);

    Cuento c = read<Cuento>(f);
    while (!feof(f))
    {
        RCuento rc = rCuento(c, cCont);
        collAdd<RCuento>(ret, rc, rCuentoToString);
        c = read<Cuento>(f);
    }

    fclose(f);
    return ret;
}
Coll<RRelator> subirRelator()
{
    Coll<RRelator> ret = coll<RRelator>();
    FILE *f = fopen("RELATORES.dat", "r+b");

    Relator c = read<Relator>(f);
    while (!feof(f))
    {
        RRelator rc = rRelator(c, 0);
        collAdd<RRelator>(ret, rc, rRelatorToString);
        c = read<Relator>(f);
    }

    fclose(f);
    return ret;
}

int cmpIdCuento(RCuento c, int id)
{
    return c.c.idCuento - id;
}

void aumentarContador(Coll<int> &duracion, int pos)
{
    int n = collGetAt<int>(duracion, pos, stringToInt);
    n++;
    collSetAt<int>(duracion, n, pos, intToString);
}
void procesarReproduccion(Reproduccion r, Coll<RCuento> &cCuentos, Coll<RRelator> &cRelator)
{
    int pos = collFind<RCuento, int>(cCuentos, r.idCuento, cmpIdCuento, rCuentoFromString);
    RCuento cuento = collGetAt<RCuento>(cCuentos, pos, rCuentoFromString);

    int duracion = cuento.c.duracion;
    int reproducido = r.minutos;
    double porcentaje = (100 * reproducido) / duracion;

    if (porcentaje < 25)
    {
        aumentarContador(cuento.cDuracion, 0);
    }
    else
    {
        if (25 <= porcentaje && porcentaje < 50)
        {
            aumentarContador(cuento.cDuracion, 1);
        }
        else
        {
            if (50 <= porcentaje && porcentaje < 75)
            {
                aumentarContador(cuento.cDuracion, 2);
            }
            else
            {
                if (75 <= porcentaje && porcentaje < 100)
                {
                    aumentarContador(cuento.cDuracion, 3);
                }
                else
                {
                    aumentarContador(cuento.cDuracion, 4);
                }
            }
        }
    }
    collSetAt<RCuento>(cCuentos, cuento, pos, rCuentoToString);
}

int main()
{
    Coll<RCuento> cCuentos = subirCuento();
    Coll<RRelator> cRelator = subirRelator();

    FILE *f = fopen("REPRODUCCIONES.dat", "r+b");

    Reproduccion r = read<Reproduccion>(f);

    while (!feof(f))
    {
        procesarReproduccion(r, cCuentos, cRelator);
        r = read<Reproduccion>(f);
    }

    collReset<RCuento>(cCuentos);
    while (collHasNext(cCuentos))
    {
        RCuento rc = collNext<RCuento>(cCuentos, rCuentoFromString);

        collReset<int>(rc.cDuracion);
        while (collHasNext(rc.cDuracion))
        {
            int dur = collNext<int>(rc.cDuracion, stringToInt);
            cout << dur;
        }
        cout << endl;
    }

    fclose(f);

    return 0;
}
#endif
