//
// Created by fran on 09/06/15.
//

#ifndef ORGADATOS_PERCEPTRON_H
#define ORGADATOS_PERCEPTRON_H

#include "Common.h"
#include "TInfo.h"
#include <vector>

class Perceptron {
public:
    static TRelacion procesarDatosRelacion(string palabra1,string palabra2,TInfo *info);
    static TBloque procesarDatosBloque(vector<TRelacion> bloque);
    static void ajustarW(vector<TBloque> review, TInfo *info,double valorEsperado);
    static double resolverReview(vector<TBloque> vector, TInfo *info);
};


#endif //ORGADATOS_PERCEPTRON_H
