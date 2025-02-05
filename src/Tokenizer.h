#ifndef ORGADATOS_TOKENIZER_H
#define ORGADATOS_TOKENIZER_H
#include "Common.h"

class Tokenizer {
public:
    // Toma una linea de datos y la separa por palabras, guardando tambien su valor.
    static TLineaDato tokenizeDato(string buffer, vector<string> stopWords);
    static TLineaDato tokenizeDatoTest(string buffer, vector<string> stopWords);
};


#endif //ORGADATOS_TOKENIZER_H
