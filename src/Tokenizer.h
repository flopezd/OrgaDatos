#ifndef ORGADATOS_TOKENIZER_H
#define ORGADATOS_TOKENIZER_H
#include "Common.h"

class Tokenizer {
public:
    // Toma una linea de datos y la separa por palabras, guardando tambien su valor.
    static TLineaDato tokenizeDato(char *buffer);

    // Toma una linea de texto y la separa por palabras.
    static vector<TOracion> tokenizeTest(char *buffer);
};


#endif //ORGADATOS_TOKENIZER_H
