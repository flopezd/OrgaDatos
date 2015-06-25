#include "HashPalabras.h"
using namespace std;


void HashPalabras::agregar(string palabra) {
    if (hash.count(palabra) > 0)
        hash.at(palabra) += 1;
    else
        hash.insert({palabra, 1});
}

int HashPalabras::getCantidad(string palabra) {
    if (hash.count(palabra) > 0)
        return hash.at(palabra);
    return 0;
}
