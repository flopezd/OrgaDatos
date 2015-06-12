//
// Created by fran on 09/06/15.
//

#ifndef ORGADATOS_TINFO_H
#define ORGADATOS_TINFO_H

#include "Common.h"

class TInfo {
public:
    HashPalabras palabras;
    HashRelaciones relaciones;
    //cantBloquesMax*(1+cantRelacionesMax)
    double wPerceptron[10010];
};


#endif //ORGADATOS_TINFO_H
