// #include "../biblioteca/funciones/files.hpp"
#include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/funciones/files.hpp"
#include "avion.hpp"
#include <iostream>
using namespace std;

Coll<RVuelo> subirVuelos()
{

    Coll<RVuelo> ret = coll<RVuelo>();
    FILE *f = fopen("VUELOS.dat", "r+b");

    Vuelo rv = read<Vuelo>(f);
    while (!feof(f))
    {

        RVuelo vue = rVuelo(rv, 0, 0);
        collAdd<RVuelo>(ret, vue, rVueloToString);
        rv = read<Vuelo>(f);
    }
    fclose(f);
    return ret;
}

Coll<RCiudad> subirCiudad()
{
    Coll<RCiudad> ret = coll<RCiudad>();
    FILE *f = fopen("CIUDADES.dat", "r+b");

    Ciudad ciu = read<Ciudad>(f);
    while (!feof(f))
    {
        RCiudad rciu = rCiudad(ciu, 0);
        collAdd<RCiudad>(ret, rciu, rCiudadToString);
        ciu = read<Ciudad>(f);
    }

    fclose(f);
    return ret;
}

int cmpRVueloidVue(RVuelo rv, int id)
{
    return rv.v.idVue - id;
}

int cmpRCiudadIdDes(RCiudad rc, int id)
{
    return rc.c.idCiu - id;
}
void procesarPunto1(Reserva r, Coll<RVuelo> vue, Coll<RCiudad> &ciu)
{
    int pos = collFind<RVuelo, int>(vue, r.idVue, cmpRVueloidVue, rVueloFromString);
    RVuelo rv = collGetAt<RVuelo>(vue, pos, rVueloFromString);

    pos = collFind<RCiudad, int>(ciu, rv.v.idDes, cmpRCiudadIdDes, rCiudadFromString);
    RCiudad rc = collGetAt<RCiudad>(ciu, pos, rCiudadFromString);

    rc.cont++;
    collSetAt<RCiudad>(ciu, rc, pos, rCiudadToString);
}

bool rechazada(Coll<RVuelo> vue, Reserva r)
{
    bool ret = true;
    int pos = collFind<RVuelo, int>(vue, r.idVue, cmpRVueloidVue, rVueloFromString);
    RVuelo rv = collGetAt<RVuelo>(vue, pos, rVueloFromString);
    if (r.cant <= rv.v.cap)
    {
        ret = false;
    }
    return ret;
}

void procesarPunto2(Reserva r, Coll<RVuelo> &vue)
{
    int pos = collFind<RVuelo, int>(vue, r.idVue, cmpRVueloidVue, rVueloFromString);
    RVuelo rv = collGetAt<RVuelo>(vue, pos, rVueloFromString);

    if (rechazada(vue, r))
    {
        rv.cpr += r.cant;
    }
    else
    {
        rv.cpa += r.cant;
    }

    collSetAt<RVuelo>(vue, rv, pos, rVueloToString);
}

int cmpRClienteIdCli(RCliente rc, int id)
{
    // dudas aca de si es rc.acum o idcli
    return rc.idCli - id;
}

int calcularMillas(Coll<RVuelo> vue, Reserva r)
{
    int pos = collFind<RVuelo, int>(vue, r.idVue, cmpRVueloidVue, rVueloFromString);
    RVuelo rv = collGetAt<RVuelo>(vue, pos, rVueloFromString);

    return abs(rv.v.idDes - rv.v.idOri) * r.cant;
}
void procesarPunto3(Reserva r, Coll<RCliente> &cli, Coll<RVuelo> vue)
{
    int pos = collFind<RCliente, int>(cli, r.idCli, cmpRClienteIdCli, rClienteFromString);

    if (pos < 0)
    {
        RCliente rc = rCliente(r.idCli, 0);
        pos = collAdd<RCliente>(cli, rc, rClienteToString);
    }

    if (!rechazada(vue, r))
    {
        RCliente rcli = collGetAt<RCliente>(cli, pos, rClienteFromString);
        rcli.acum += calcularMillas(vue, r);
        collSetAt<RCliente>(cli, rcli, pos, rClienteToString);
    }
}

void mostrarPunto1(Coll<RCiudad> ciu)
{
    collReset(ciu);
    while (collHasNext<RCiudad>(ciu))
    {
        RCiudad rc = collNext<RCiudad>(ciu, rCiudadFromString);
        cout << rc.cont << endl;
    }
}

void mostrarPunto2(Coll<RVuelo> vue)
{

    // revisar por algo mas que pide el punto
    collReset(vue);
    while (collHasNext<RVuelo>(vue))
    {
        RVuelo rv = collNext<RVuelo>(vue, rVueloFromString);
        cout << "rechazados" << rv.cpr << endl;
    }
}

void mostrarPunto3(Coll<RCliente> cli)
{
    collReset(cli);
    while (collHasNext<RCliente>(cli))
    {
        RCliente rc = collNext<RCliente>(cli, rClienteFromString);
        cout << rc.acum << endl;
    }
}
int main()
{

    Coll<RVuelo> rvue = subirVuelos();
    Coll<RCiudad> rciu = subirCiudad();
    Coll<RCliente> rcli = coll<RCliente>();

    FILE *f = fopen("RESERVAS.dat", "r+b");

    Reserva r = read<Reserva>(f);
    while (!feof(f))
    {

        procesarPunto1(r, rvue, rciu);
        // ver eso de si sale completo o no en la funcion de mostrar
        procesarPunto2(r, rvue);
        procesarPunto3(r, rcli, rvue);
        r = read<Reserva>(f);
    }
    mostrarPunto1(rciu);
    mostrarPunto2(rvue);
    mostrarPunto3(rcli);
    fclose(f);
    return 0;
}