#include "biblioteca/funciones/files.hpp"
#include "biblioteca/tads/parte2/Map.hpp"
#include "ejercicio_1_1_15.hpp"
#include <iostream>
using namespace std;

Map<int, RConsorcio> subirConsorcio()
{
    Map<int, RConsorcio> ret = map<int, RConsorcio>();
    FILE *f = fopen("CONSORCIOS.dat", "r+b");
    Consorcio co = read<Consorcio>(f);

    while (!feof(f))
    {
        RConsorcio rc = rConsorcio(co, 0);
        mapPut<int, RConsorcio>(ret, co.idCons, rc);
        co = read<Consorcio>(f);
    }
    fclose(f);
    return ret;
}

void procesarPunto(Map<int, RConsorcio> &rcon, Gasto g)
{
    RConsorcio *con = mapGet<int, RConsorcio>(rcon, g.idCons);
    con->acum += g.importe;
}

double mtsPorcentuales(int idCons, int depto);

int cmpMts(double a, double b)
{
    return b - a;
}

void mostrarDepartamentos(RConsorcio *rc, Map<int, double> mts)
{

    int i = 1;
    while (i <= rc->c.dtosPorPiso)
    {
        double metros = mtsPorcentuales(rc->c.idCons, i);
        mapPut<int, double>(mts, i, metros);
        i++;
    }

    // no me dejaba ponerle nombre cmpDouble a cmpDbl
    mapSortByValues<int, double>(mts, cmpMts);

    cout << "dpto          mts.2        totalAPagar" << endl;

    mapReset<int, double>(mts);
    while (mapHasNext<int, double>(mts))
    {
        int dp = mapNextKey<int, double>(mts);
        double *porc = mapGet<int, double>(mts, dp);
        double totalPagar = rc->acum * (*porc) / rc->c.cantPisos;
        double porcentaje = (*porc) * 100;
        cout << dp << "    " << porcentaje << "    " << totalPagar;
    }
}

void mostrarPunto(Map<int, RConsorcio> rcon, Map<int, double> mts)
{
    mapReset<int, RConsorcio>(rcon);
    while (mapHasNext<int, RConsorcio>(rcon))
    {
        // no lo tengo que pasar a string?
        RConsorcio *rc = mapNextValue<int, RConsorcio>(rcon);
        string nombre = rc->c.direccion;
        cout << "Consorcio calle: " << nombre << "   Gastos totales:" << rc->acum;
        mostrarDepartamentos(rc, mts);
    }
}

int main()
{
    Map<int, RConsorcio> rcon = subirConsorcio();
    Map<int, double> mts = Map<int, double>();

    FILE *f = fopen("GASTOS.dat", "r+b");
    Gasto g = read<Gasto>(f);
    while (!feof(f))
    {
        procesarPunto(rcon, g);
        g = read<Gasto>(f);
    }
    mostrarPunto(rcon, mts);

    fclose(f);
    return 0;
}