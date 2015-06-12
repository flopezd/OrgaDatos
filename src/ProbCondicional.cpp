//
// Created by fran on 11/06/15.
//

#include "ProbCondicional.h"

double ProbCondicional::resolverReview(vector<TBloque> review, TInfo *info) {
    double probTotal = 0;
    double contador = 0;
    for(int i = 0; i < review.size();i++) {
        for(int j = 0; j < review[i].relaciones.size();j++) {
            probTotal= probTotal+review[i].relaciones[j].probabilidad*review[i].relaciones[j].probPositivo;
            contador = contador+1;
        }
    }
    return probTotal/contador;
}

// Devuelve los valores de la relacion
TRelacion ProbCondicional::procesarDatosRelacion(string palabra1,string palabra2,TInfo *info) {
    TRelacion relacion;
    int cantPalabrasI = info->palabras.getCantidad(palabra1);
    int cantPalabrasJ = info->palabras.getCantidad(palabra2);
    TDatosRelacion datosRelacion = info->relaciones.getDatos(palabra1, palabra2);
    if (datosRelacion.cantRelaciones != 0) {
        relacion.valorRelacion = (datosRelacion.valorRelacion)/(double)(datosRelacion.cantRelaciones);
        relacion.probabilidad = (double)(2*datosRelacion.cantRelaciones)/(double)(cantPalabrasI+cantPalabrasJ);
        relacion.probPositivo = (datosRelacion.cantPos)/(double)(datosRelacion.cantRelaciones);
    }else {
        relacion.valorRelacion = 0;
        relacion.probabilidad = 0;
        relacion.probPositivo = 0;
    }
    return relacion;
}