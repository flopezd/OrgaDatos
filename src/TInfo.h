#ifndef ORGADATOS_TINFO_H
#define ORGADATOS_TINFO_H

#include "Common.h"
#include "HashRelacionesTriples.h"

class TInfo {
public:
    TInfo();
    HashPalabras palabras;
    HashRelaciones relaciones;
    HashRelacionesTriples relacionesTriples;
    //cantBloquesMax*(1+cantRelacionesMax)
    vector<double> wPerceptron;
};


#endif //ORGADATOS_TINFO_H
