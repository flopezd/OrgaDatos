#include "HashRelaciones.h"

void HashRelaciones::agregar(string palabra1, string palabra2, int valor) {
    ParPalabras par;
    par.pal1 = palabra1;
    par.pal2 = palabra2;
    if (hash.count(par) > 0) {
        if (valor == 0) {
            hash.at(par).negativa += 1;
        } else {
            hash.at(par).positiva += 1;
        }
    } else {
        Calificacion calificacion;
        hash.insert({par, calificacion});
        if (valor == 0) {
            hash.at(par).negativa += 1;
        } else {
            hash.at(par).positiva += 1;
        }
    }
}

TDatosRelacion HashRelaciones::getDatos(string palabra1, string palabra2) {
    TDatosRelacion datosRelacion;
    ParPalabras par;
    par.pal1 = palabra1;
    par.pal2 = palabra2;
    datosRelacion.cantRelaciones = 0;
    datosRelacion.valorRelacion = 0;
    datosRelacion.cantPos = 0;
    if (hash.count(par) > 0) {
        datosRelacion.cantRelaciones = hash.at(par).cantRel();
        datosRelacion.valorRelacion = (double) (hash.at(par).difPosNeg()) / (double) (hash.at(par).cantRel());

    }
    return datosRelacion;
}
