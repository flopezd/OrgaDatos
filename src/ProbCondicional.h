//
// Created by fran on 11/06/15.
//

#ifndef ORGADATOS_PROBCONDICIONAL_H
#define ORGADATOS_PROBCONDICIONAL_H


#include "Common.h"
#include "TInfo.h"

class ProbCondicional {
public:
    static double resolverReview(vector<TBloque> review, TInfo *info);
    static TRelacion procesarDatosRelacion(string palabra1,string palabra2,TInfo *info);
};


#endif //ORGADATOS_PROBCONDICIONAL_H
