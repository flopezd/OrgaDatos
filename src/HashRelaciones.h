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
            string aux1=this->pal1+this->pal2;
            string aux2=b.pal1+b.pal2;
            string aux3=this->pal2+this->pal1;
            string aux4=b.pal2+b.pal1;

            return ( !strcmp(aux1.c_str(),aux2.c_str()) || !strcmp(aux3.c_str(),aux4.c_str())  );
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

        long int cantPos() {
            return (positiva);
        }
    };

    struct KeyHasher {
        std::size_t operator()(const ParPalabras &par) const {
            size_t h = 0;
            string aux = par.pal1 + par.pal2;
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
