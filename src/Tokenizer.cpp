#include "Tokenizer.h"
#include "../strtk/strtk.hpp"

// Toma una linea de datos y la separa por palabras, guardando tambien su valor.
TLineaDato Tokenizer::tokenizeDato(string linea) {
    TLineaDato lineaDato = TLineaDato();
    vector<string> IDValorReview;
    vector<string> bloques;

    // Parsea el id, valor y review
    static const std::string delimiters1 = "\t";
    strtk::parse(linea,delimiters1,IDValorReview);
    lineaDato.id = IDValorReview[0];
    if(IDValorReview[1]=="1") lineaDato.valor = 1;
    else lineaDato.valor = 0;

    // Parsea el review por bloques
    static const std::string delimiters2 = ".";
    strtk::parse(IDValorReview[2],delimiters2,bloques);

    // Parsea los bloques en palabras
    static const std::string delimiters3 = "[]<>\t\"\r\n ;:!@#$^&*/-=+`~";
    for(int i = 0; i < bloques.size();i++) {
        vector<string> bloque;
        strtk::parse(bloques[i],delimiters3,bloque);
        lineaDato.bloques.push_back(bloque);
    }
    return lineaDato;
}

// Toma una linea de datos y la separa por palabras, guardando tambien su valor.
TLineaDato Tokenizer::tokenizeDatoTest(string linea) {
    TLineaDato lineaDato = TLineaDato();
    vector<string> IDValorReview;
    vector<string> bloques;

    // Parsea el id, valor y review
    static const std::string delimiters1 = "\t";
    strtk::parse(linea,delimiters1,IDValorReview);
    lineaDato.id = IDValorReview[0];

    // Parsea el review por bloques
    static const std::string delimiters2 = ".";
    strtk::parse(IDValorReview[1],delimiters2,bloques);

    // Parsea los bloques en palabras
    static const std::string delimiters3 = "[]<>\t\"\r\n ;:!@#$^&*/-=+`~";
    for(int i = 0; i < bloques.size();i++) {
        vector<string> bloque;
        strtk::parse(bloques[i],delimiters3,bloque);
        lineaDato.bloques.push_back(bloque);
    }
    return lineaDato;
}