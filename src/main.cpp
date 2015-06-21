#include <iostream>
#include <vector>
#include <fstream>
#include "Common.h"
#include "Tokenizer.h"
#include "Perceptron.h"
#include "ProbCondicional.h"

using namespace std;

static const string TRAIN_DATA = "resources/labeledTrainData.tsv";
static const string TEST_DATA = "resources/testData.tsv";


// Procesa la informacion del archivo pasado por parametros y la
// devuelve ya procesada.
TInfo aprender(string archivoParaAprender) {
    TInfo info = TInfo();
    string buffer;
    TLineaDato linea;
    string line;
    int l = 0;

    int p1 = 0;
    int p2 = 0;
    int r = 0;

    // Se abre el archivo
    ifstream datos(archivoParaAprender);
    if (datos.is_open()) getline(datos, buffer);
    if (datos.is_open()) {
        // Se lee linea a linea, cada linea se separa en bloques y cada bloque en palabras
        // cada una se guarda en el hash de palabras y cada combinacion de par de palabras
        // en el hash de relaciones
        while (datos.good() && l < 100) {
            getline(datos, buffer);
            if (buffer != "") {
                linea = Tokenizer::tokenizeDato(buffer);
                for (int z = 0; z < linea.bloques.size(); z++) {
                    for (int i = 0; i < linea.bloques[z].size(); i++) {
                        info.palabras.agregar(linea.bloques[z].at(i));
                        for (int j = i + 1; j < linea.bloques[z].size(); j++) {
                            info.relaciones.agregar(linea.bloques[z].at(i), linea.bloques[z].at(j), linea.valor);
                        }
                    }
                }
            }
            l = l + 1;
        }
        datos.close();
    }

    return info;
}

// Con la info procesada va aprendiendo para el perceptron
void aprender2(string archivoParaAprender, TInfo *info) {
    string buffer;
    TLineaDato linea;
    string line;
    int l = 0;

    // Se abre el archivo
    ifstream datos(archivoParaAprender);
    if (datos.is_open()) getline(datos, buffer);
    if (datos.is_open()) {
        // Se lee linea a linea, cada linea se separa en palabras cada una se guarda en el
        // hash de palabras y cada combinacion de par de palabras en el hash de relaciones
        //for each line
        while (datos.good() && l < 10) {
            getline(datos, buffer);
            if (buffer != "") {
                // Se separa en bloques y las bloques en palabras.
                linea = Tokenizer::tokenizeDato(buffer);
                // Se agrega cada palabra como nodo y cada relacion como arista
                vector<TBloque> review = vector<TBloque>();
                for (int z = 0; z < linea.bloques.size(); z++) {
                    TBloque bloque;
                    for (int i = 0; i < linea.bloques[z].size(); i++) {
                        string palabra1 = linea.bloques[z].at(i);
                        if (linea.bloques[z].at(i) != "") {
                            for (int j = i + 1; j < linea.bloques[z].size(); j++) {
                                string palabra2 = linea.bloques[z].at(j);
                                bloque.relaciones.push_back(
                                        Perceptron::procesarDatosRelacion(info->relaciones.getDatos(palabra1, palabra2),
                                                              info->palabras.getCantidad(palabra1),
                                                              info->palabras.getCantidad(palabra2)));
                            }
                        }
                    }
                    bloque = Perceptron::procesarDatosBloque(bloque.relaciones);
                    review.push_back(bloque);
                }
                Perceptron::ajustarW(review, info, linea.valor);
            }
            if (l == 1999) {
                int a = 2;
            }
            l = l + 1;
            cout << l << endl;
        }
        datos.close();
    }
}


// Con la info pasada por parametro analiza los datos a testear.
void resolver(TInfo *info, string datosATestear) {
    string buffer;
    TLineaDato lineaDato;
    string line;
    double resultado;
    int l = 0;

    // Se abre el archivo
    ifstream datos(datosATestear);
    ofstream savefile("resources/submission.csv");
    savefile << "\"id\",\"sentiment\"" << endl;
    if (datos.is_open()) getline(datos, buffer);
    if (datos.is_open()) {
        // Se lee linea a linea, cada linea se separa en palabras cada una se guarda en el
        // hash de palabras y cada combinacion de par de palabras en el hash de relaciones
        //for each line
        while (datos.good() && l < 2000) {
            getline(datos, buffer);

            if (buffer != "") {
                // Se separa en bloques y las bloques en palabras.
                lineaDato = Tokenizer::tokenizeDatoTest(buffer);
                resultado = 0;
                vector<TBloque> review = vector<TBloque>();
                // Se agrega cada palabra como nodo y cada relacion como arista
                for (int z = 0; z < lineaDato.bloques.size(); z++) {
                    TBloque bloque;
                    for (int i = 0; i < lineaDato.bloques[z].size(); i++) {
                        if (lineaDato.bloques[z].at(i) != "") {
                            string palabra1 = lineaDato.bloques[z].at(i);
                            for (int j = i + 1; j < lineaDato.bloques[z].size(); j++) {
                                string palabra2 = lineaDato.bloques[z].at(j);
                                bloque.relaciones.push_back(
                                        Perceptron::procesarDatosRelacion(info->relaciones.getDatos(palabra1, palabra2),
                                                                          info->palabras.getCantidad(palabra1),
                                                                          info->palabras.getCantidad(palabra2)));
                            }
                        }
                    }
                    bloque = Perceptron::procesarDatosBloque(bloque.relaciones);
                    review.push_back(bloque);
                }
                resultado = Perceptron::resolverReview(review, info);
                savefile << lineaDato.id << ",";
                // Si el resultado final es positivo la review se considera positiva, en caso contrario se toma como negativa
                if (resultado > 0) {
                    savefile << "1" << endl;
                } else {
                    savefile << "0" << endl;
                }
            }
            l = l + 1;
        }
        datos.close();
        savefile.close();
    }
}


// Con la info pasada por parametro analiza los datos a testear.
void resolver2(TInfo *info, string datosATestear) {
    string buffer;
    TLineaDato lineaDato;
    string line;
    double resultado;

    // Se abre el archivo
    ifstream datos(datosATestear);
    ofstream savefile("resources/submission.csv");
    savefile << "\"id\",\"sentiment\"" << endl;
    if (datos.is_open()) getline(datos, buffer);
    if (datos.is_open()) {
        // Se lee linea a linea, cada linea se separa en palabras cada una se guarda en el
        // hash de palabras y cada combinacion de par de palabras en el hash de relaciones
        //for each line
        while (datos.good()) {
            getline(datos, buffer);

            if (buffer != "") {
                // Se separa en bloques y las bloques en palabras.
                lineaDato = Tokenizer::tokenizeDatoTest(buffer);
                resultado = 0;
                vector<TBloque> review = vector<TBloque>();
                // Se agrega cada palabra como nodo y cada relacion como arista
                for (int z = 0; z < lineaDato.bloques.size(); z++) {
                    TBloque bloque;
                    for (int i = 0; i < lineaDato.bloques[z].size(); i++) {
                        for (int j = i + 1; j < lineaDato.bloques[z].size(); j++) {
                            bloque.relaciones.push_back(
                                    ProbCondicional::procesarDatosRelacion(lineaDato.bloques[z].at(i),
                                                                           lineaDato.bloques[z].at(j),
                                                                           info));
                        }
                    }
                    review.push_back(bloque);
                }
                resultado = ProbCondicional::resolverReview(review, info);
                savefile << lineaDato.id << ",";
                // Si el resultado final es positivo la review se considera positiva, en caso contrario se toma como negativa
                if (resultado > 0.5) {
                    savefile << "1" << endl;
                } else {
                    savefile << "0" << endl;
                }
            }
        }
        datos.close();
        savefile.close();
    }
}

int main(int argc, char **argv) {
    TInfo info = aprender(TRAIN_DATA);
    cout << "pasoaca1" << endl;
    aprender2(TRAIN_DATA, &info);
    cout << "pasoaca2" << endl;/*
    resolver(info, TEST_DATA);*/
    //resolver2(info, TEST_DATA);
}