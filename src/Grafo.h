#ifndef ORGADATOS_GRAFO_H
#define ORGADATOS_GRAFO_H
#include "Common.h"
#include <string>

class Grafo {
public:
    void agregarNodo(string nodo);
    void agregarArista(string nodo1,string nodo2, TDatosArista datosArista);
    void completar();
    float resolverCicloMasProbable();
};


#endif //ORGADATOS_GRAFO_H
