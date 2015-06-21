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
    static TRelacion procesarDatosRelacion(TDatosRelacion datosRelacion,double cantPal1,double cantPal2);
    static TBloque procesarDatosBloque(vector<TRelacion> bloque);
    static vector<double> ajustarW(vector<TBloque> review, vector<double> wPerceptron,double valorEsperado);
    static double resolverReview(vector<TBloque> review, vector<double> wPerceptron);
};


#endif //ORGADATOS_PERCEPTRON_H
