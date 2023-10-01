#ifndef _MAINHPP
#define _MAINHPP
#include <iostream>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "biblioteca/funciones/strings.hpp"
#include "biblioteca/funciones/tokens.hpp"
using namespace std;

struct Gasto
{
    int idCons;
    int fecha;
    double importe;
    char categoria[20];
};

struct Consorcio
{
    int idCons;
    char direccion[50];
    int cantPisos;
    int dtosPorPiso;
};

struct RConsorcio
{
    Consorcio c;
    int acum;
};

string gastoToString(Gasto x)
{
    char sep = 1;
    string sIdCons = to_string(x.idCons);
    string sFecha = to_string(x.fecha);
    string sImporte = to_string(x.importe);
    string sCategoria = x.categoria;
    return sIdCons + sep + sFecha + sep + sImporte + sep + sCategoria;
}

Gasto gastoFromString(string s)
{
    char sep = 1;
    Gasto x;
    string t0 = getTokenAt(s, sep, 0);
    x.idCons = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.fecha = stoi(t1);
    string t2 = getTokenAt(s, sep, 2);
    x.importe = stod(t2);
    string t3 = getTokenAt(s, sep, 3);
    strcpy(x.categoria, t3.c_str());
    return x;
}

string gastoToDebug(Gasto x)
{
    stringstream sout;
    sout << "[";
    sout << x.idCons;
    sout << ",";
    sout << x.fecha;
    sout << ",";
    sout << x.importe;
    sout << ",";
    sout << x.categoria;
    sout << "]";
    return sout.str();
}

string gastoToDebug(string mssg, Gasto x)
{
    stringstream sout;
    sout << mssg << ":[";
    sout << x.idCons;
    sout << ",";
    sout << x.fecha;
    sout << ",";
    sout << x.importe;
    sout << ",";
    sout << x.categoria;
    sout << "]";
    return sout.str();
}

Gasto gasto(int idCons, int fecha, double importe, string categoria)
{
    Gasto a;
    a.idCons = idCons;
    a.fecha = fecha;
    a.importe = importe;
    strcpy(a.categoria, categoria.c_str());
    return a;
}

bool gastoEquals(Gasto a, Gasto b)
{
    if (a.idCons != b.idCons)
        return false;
    if (a.fecha != b.fecha)
        return false;
    if (a.importe != b.importe)
        return false;
    return true;
}

string consorcioToString(Consorcio x)
{
    char sep = 2;
    string sIdCons = to_string(x.idCons);
    string sDireccion = x.direccion;
    string sCantPisos = to_string(x.cantPisos);
    string sDtosPorPiso = to_string(x.dtosPorPiso);
    return sIdCons + sep + sDireccion + sep + sCantPisos + sep + sDtosPorPiso;
}

Consorcio consorcioFromString(string s)
{
    char sep = 2;
    Consorcio x;
    string t0 = getTokenAt(s, sep, 0);
    x.idCons = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    strcpy(x.direccion, t1.c_str());
    string t2 = getTokenAt(s, sep, 2);
    x.cantPisos = stoi(t2);
    string t3 = getTokenAt(s, sep, 3);
    x.dtosPorPiso = stoi(t3);
    return x;
}

string consorcioToDebug(Consorcio x)
{
    stringstream sout;
    sout << "[";
    sout << x.idCons;
    sout << ",";
    sout << x.direccion;
    sout << ",";
    sout << x.cantPisos;
    sout << ",";
    sout << x.dtosPorPiso;
    sout << "]";
    return sout.str();
}

string consorcioToDebug(string mssg, Consorcio x)
{
    stringstream sout;
    sout << mssg << ":[";
    sout << x.idCons;
    sout << ",";
    sout << x.direccion;
    sout << ",";
    sout << x.cantPisos;
    sout << ",";
    sout << x.dtosPorPiso;
    sout << "]";
    return sout.str();
}

Consorcio consorcio(int idCons, string direccion, int cantPisos, int dtosPorPiso)
{
    Consorcio a;
    a.idCons = idCons;
    strcpy(a.direccion, direccion.c_str());
    a.cantPisos = cantPisos;
    a.dtosPorPiso = dtosPorPiso;
    return a;
}

bool consorcioEquals(Consorcio a, Consorcio b)
{
    if (a.idCons != b.idCons)
        return false;
    if (a.cantPisos != b.cantPisos)
        return false;
    if (a.dtosPorPiso != b.dtosPorPiso)
        return false;
    return true;
}

string rConsorcioToString(RConsorcio x)
{
    char sep = 3;
    string sC = consorcioToString(x.c);
    string sAcum = to_string(x.acum);
    return sC + sep + sAcum;
}

RConsorcio rConsorcioFromString(string s)
{
    char sep = 3;
    RConsorcio x;
    string t0 = getTokenAt(s, sep, 0);
    x.c = consorcioFromString(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.acum = stoi(t1);
    return x;
}

string rConsorcioToDebug(RConsorcio x)
{
    stringstream sout;
    sout << "[";
    sout << consorcioToDebug(x.c);
    sout << ",";
    sout << x.acum;
    sout << "]";
    return sout.str();
}

string rConsorcioToDebug(string mssg, RConsorcio x)
{
    stringstream sout;
    sout << mssg << ":[";
    sout << consorcioToDebug(x.c);
    sout << ",";
    sout << x.acum;
    sout << "]";
    return sout.str();
}

RConsorcio rConsorcio(Consorcio c, int acum)
{
    RConsorcio b;
    b.c = c;
    b.acum = acum;
    return b;
}

bool rConsorcioEquals(RConsorcio a, RConsorcio b)
{
    if (!consorcioEquals(a.c, b.c))
        return false;
    if (a.acum != b.acum)
        return false;
    return true;
}

#endif
