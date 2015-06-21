//
// Created by fran on 09/06/15.
//

#include "HashPalabras.h"
using namespace std;


void HashPalabras::agregar(string palabra) {
    if (hash.count(palabra) > 0)
        hash.at(palabra) += 1;
    else
        hash.insert({palabra, 1});
    if (palabra == "to") {
        a = a+1;
        if (hash.at(palabra) != a) {
            int s =5;
        }
    }
}

int HashPalabras::getCantidad(string palabra) {
    if (hash.count(palabra) > 0)
        return hash.at(palabra);
    return 0;
}
