//
// Created by fran on 21/06/15.
//

#include "HashRelacionesTriples.h"

void HashRelacionesTriples::agregar(string palabra1, string palabra2, string palabra3, int valor) {
    TernaPalabras terna;
    terna.pal1 = palabra1;
    terna.pal2 = palabra2;
    terna.pal3 = palabra3;
    if (hash.count(terna) > 0) {
        if (valor == 0) {
            hash.at(terna).negativa += 1;
        } else {
            hash.at(terna).positiva += 1;
        }
    } else {
        CalificacionT calificacion;
        hash.insert({terna, calificacion});
        if (valor == 0) {
            hash.at(terna).negativa += 1;
        } else {
            hash.at(terna).positiva += 1;
        }
    }
}

TDatosRelacion HashRelacionesTriples::getDatos(string palabra1, string palabra2, string palabra3) {
    TDatosRelacion datosRelacion;
    TernaPalabras terna;
    terna.pal1 = palabra1;
    terna.pal2 = palabra2;
    terna.pal3 = palabra2;
    datosRelacion.cantRelaciones = 0;
    datosRelacion.valorRelacion = 0;
    datosRelacion.cantPos = 0;
    if (hash.count(terna) > 0) {
        datosRelacion.cantRelaciones = hash.at(terna).cantRel();
        datosRelacion.valorRelacion = (double) (hash.at(terna).difPosNeg()) / (double) (hash.at(terna).cantRel());
    }
    return datosRelacion;
}