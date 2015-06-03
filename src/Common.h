/**
 * Estructuras que se comparten entre las distintas clases
 */

#ifndef _ORGADATOS_COMMON_H_
#define _ORGADATOS_COMMON_H_

#include <string>
#include <vector>
using namespace std;

struct TInfo {
    HashPalabras palabras;
    HashRelaciones relaciones;
};

struct TLineaDato {
    vector<string> palabras;
    int valor;
};

struct TLineaTest {
    vector<vector<string>> oraciones;
    int id;
};

struct TDatosRelacion {
    int cantRelaciones,valorRelacion;;
};

struct TDatosArista {
    int cantPalabrasI,cantPalabrasJ;
    TDatosRelacion datosRelacion;
};

#endif //_ORGADATOS_COMMON_H_
