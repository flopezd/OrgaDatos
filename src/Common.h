/**
 * Estructuras que se comparten entre las distintas clases
 */

#ifndef _ORGADATOS_COMMON_H_
#define _ORGADATOS_COMMON_H_

#include <string>
#include <vector>
#include <string.h>
#include "HashRelaciones.h"
#include "HashPalabras.h"

using namespace std;
static const int cantBloquesMax = 4;
static const int cantRelacionesMax = 19;
static const int tamVectorPerceptron = cantBloquesMax*(1+cantRelacionesMax);


struct TLineaDato {
    vector<vector<string>> bloques;
    int valor;
    string id;
};

struct TRelacion {
    double probabilidad,valorRelacion,probPositivo;
};

struct TBloque {
    double probabilidad;
    vector<TRelacion> relaciones;

    TBloque(){
        while (relaciones.size()<cantRelacionesMax/2) {
            TRelacion relacion;
            relacion.probabilidad = 0;
            relacion.valorRelacion = 0;
            relaciones.push_back(relacion);
        }
    }
};

#endif //_ORGADATOS_COMMON_H_
