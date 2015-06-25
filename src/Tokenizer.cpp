#include "Tokenizer.h"
#include "../strtk/strtk.hpp"

bool pertenece(vector<string> usados,string palabra) {
    bool seUsa = false;
    for (int i = 0; i < usados.size(); i++) {
        if (usados[i] == palabra) {
            seUsa =true;
        }
    }
    return seUsa;
}

// Toma una linea de datos y la separa por palabras, guardando tambien su valor.
TLineaDato Tokenizer::tokenizeDato(string linea, vector<string> stopWords) {
    TLineaDato lineaDato = TLineaDato();
    vector<string> IDValorReview;
    vector<string> IDValorReviewA;
    vector<string> bloques;

    // Parsea el id, valor y review
    static const std::string delimiters1 = "\t";
    static const char delimiters1A []= "\t";
    strtk::parse(linea,delimiters1,IDValorReview);
    lineaDato.id = IDValorReview[0];
    if(IDValorReview[1]=="1") lineaDato.valor = 1;
    else lineaDato.valor = 0;

    // Parsea el review por bloques
    static const std::string delimiters2 = ".";
    strtk::parse(IDValorReview[2],delimiters2,bloques);

    // Parsea los bloques en palabras
    static const std::string delimiters3 = "[]<>\t\"\r\n ;:!@#$^&*/-=+`~,";
    for(int i = 0; i < bloques.size();i++) {
        vector<string> bloque;
        vector<string> bloqueAux;
        strtk::parse(bloques[i],delimiters3,bloque);
        while (!bloque.empty()) {
            string palabraAux = bloque.back();
            if (palabraAux != "" && !pertenece(bloqueAux,palabraAux) && !pertenece(stopWords,palabraAux)) {
                bloqueAux.push_back(palabraAux);
            }
            bloque.pop_back();
        }
        lineaDato.bloques.push_back(bloqueAux);
    }

    return lineaDato;
}

// Toma una linea de datos y la separa por palabras, guardando tambien su valor.
TLineaDato Tokenizer::tokenizeDatoTest(string linea,vector<string> stopWords) {
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
    static const std::string delimiters3 = "[]<>\t\"\r\n ;:!@#$^&*/-=+`~,";
    for(int i = 0; i < bloques.size();i++) {
        vector<string> bloque;
        vector<string> bloqueAux;
        strtk::parse(bloques[i],delimiters3,bloque);
        while (!bloque.empty()) {
            string palabraAux = bloque.back();
            if (palabraAux != "" && !pertenece(bloqueAux,palabraAux) && !pertenece(stopWords,palabraAux)) {
                bloqueAux.push_back(palabraAux);
            }
            bloque.pop_back();
        }
        lineaDato.bloques.push_back(bloqueAux);
    }
    return lineaDato;
}