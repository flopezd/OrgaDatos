#ifndef ORGADATOS_TOKENIZER_H
#define ORGADATOS_TOKENIZER_H
#include "Common.h"

class Tokenizer {
public:
    // Toma una linea de datos y la separa por palabras, guardando tambien su valor.
    static TLineaDato tokenizeDato(string buffer);

    // Toma una linea de texto y la separa por palabras.
    static TLineaTest tokenizeTest(string buffer);
};


#endif //ORGADATOS_TOKENIZER_H
