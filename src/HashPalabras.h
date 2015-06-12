//
// Created by fran on 09/06/15.
//

#ifndef ORGADATOS_HASHPALABRAS_H
#define ORGADATOS_HASHPALABRAS_H

#include "Common.h"
#include <string>
#include <unordered_map>

using namespace std;

class HashPalabras {
private:
    unordered_map <string,long int> hash;
public:
    void agregar(string palabra);
    int getCantidad(string palabra);
};


#endif //ORGADATOS_HASHPALABRAS_H
