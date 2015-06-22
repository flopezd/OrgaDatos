//
// Created by fran on 21/06/15.
//

#ifndef ORGADATOS_HASHRELACIONESTRIPLES_H
#define ORGADATOS_HASHRELACIONESTRIPLES_H


#include "Common.h"
#include "TDatosRelacion.h"
#include <string>
#include <unordered_map>
using namespace std;

class HashRelacionesTriples  {
private:
    struct TernaPalabras{
        string pal1;
        string pal2;
        string pal3;

        bool operator==(const TernaPalabras& b) const
        {
            bool comp1 = pal1 == b.pal1;
            comp1 = comp1 && pal2 == b.pal2;
            comp1 = comp1 && pal3 == b.pal3;
            bool comp2 = pal1 == b.pal1;
            comp2 = comp2 && pal2 == b.pal3;
            comp2 = comp2 && pal3 == b.pal2;
            bool comp3 = pal1 == b.pal2;
            comp3 = comp3 && pal2 == b.pal1;
            comp3 = comp3 && pal3 == b.pal3;
            bool comp4 = pal1 == b.pal2;
            comp4 = comp4 && pal2 == b.pal3;
            comp4 = comp4 && pal3 == b.pal1;
            bool comp5 = pal1 == b.pal3;
            comp5 = comp5 && pal2 == b.pal1;
            comp5 = comp5 && pal3 == b.pal2;
            bool comp6 = pal1 == b.pal3;
            comp6 = comp6 && pal2 == b.pal2;
            comp6 = comp6 && pal3 == b.pal1;

            return ( comp1 || comp2 || comp3 || comp4 || comp5 || comp6);
        }
    };

    struct CalificacionT {
        long int positiva = 0;
        long int negativa = 0;

        size_t cantRel() {
            return (positiva + negativa);
        }

        long int difPosNeg() {
            return (positiva - negativa);
        }
    };

    struct KeyHasherT {
        std::size_t operator()(const TernaPalabras &terna) const {
            size_t h = 0;
            string aux;
            if (terna.pal1.compare(terna.pal2)<0) {
                if (terna.pal2.compare(terna.pal3)<0) {
                    aux = terna.pal1+ terna.pal2 + terna.pal3;
                } else if (terna.pal1.compare(terna.pal3)<0) {
                    aux = terna.pal1 + terna.pal3 + terna.pal2;
                } else {
                    aux = terna.pal3 + terna.pal1 + terna.pal2;
                }
            } else {
                if (terna.pal2.compare(terna.pal3)<0) {
                    if (terna.pal1.compare(terna.pal3)<0) {
                        aux = terna.pal2 + terna.pal1 + terna.pal3;
                    } else {
                        aux = terna.pal2 + terna.pal3 + terna.pal1;
                    }
                } else {
                    aux = terna.pal3 + terna.pal2 + terna.pal1;
                }
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
    unordered_map<TernaPalabras, CalificacionT, KeyHasherT> hash;

public:
    void agregar(string palabra1, string palabra2, string palabra3, int valor);
    TDatosRelacion getDatos(string palabra1, string palabra2, string palabra3);
};


#endif //ORGADATOS_HASHRELACIONESTRIPLES_H
