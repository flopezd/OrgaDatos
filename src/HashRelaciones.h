//
// Created by fran on 09/06/15.
//

#ifndef ORGADATOS_HASHRELACIONES_H
#define ORGADATOS_HASHRELACIONES_H

#include "Common.h"
#include "TDatosRelacion.h"
#include <string>
#include <unordered_map>

using namespace std;

class HashRelaciones {
private:
    struct ParPalabras{
        string pal1;
        string pal2;

        bool operator==(const ParPalabras& b) const
        {
            bool comp1 = pal1 == b.pal1;
            comp1 = comp1 && pal2 == b.pal2;
            bool comp2 = pal1 == b.pal2;
            comp2 = comp2 && pal2 == b.pal1;

            return ( comp1 || comp2 );
        }
    };

    struct Calificacion {
        long int positiva = 0;
        long int negativa = 0;

        size_t cantRel() {
            return (positiva + negativa);
        }

        long int difPosNeg() {
            return (positiva - negativa);
        }
    };

    struct KeyHasher {
        std::size_t operator()(const ParPalabras &par) const {
            size_t h = 0;
            string aux;
            if (par.pal1.compare(par.pal2)<0) {
                aux = par.pal1 + par.pal2;
            } else {
                aux = par.pal2 + par.pal1;
            }
            size_t len = aux.length();
            for (size_t i = 0; i < len; ++i) {
                h += aux[i];
                h += (h << 10);
                h ^= (h >> 6);
            }
            h += (h << 3);
            h ^= (h >> 11);
            h += (h << 15);
            return h;
        }
    };
    unordered_map<ParPalabras, Calificacion, KeyHasher> hash;

public:
    void agregar(string palabra1, string palabra2, int valor);

    TDatosRelacion getDatos(string palabra1, string palabra2);
};


#endif //ORGADATOS_HASHRELACIONES_H
