#include <iostream>
#include <vector>
#include <fstream>
#include "Common.h"
#include "Tokenizer.h"
#include "Grafo.h"

static const string TRAIN_DATA = "resources/labeledTrainData.tsv";
static const string TEST_DATA = "resources/testData.tsv";

// Procesa la informacion del archivo pasado por parametros y la
// devuelve ya procesada.
TInfo aprender(string archivoParaAprender) {
    TInfo info;
    string buffer;
    TLineaDato linea;
    string line;

    // Se abre el archivo
    ifstream datos(archivoParaAprender);
    if (datos.is_open()) {
        // Se lee linea a linea, cada linea se separa en palabras cada una se guarda en el
        // hash de palabras y cada combinacion de par de palabras en el hash de relaciones
        //for each line
        while (datos.good()) {
            getline(datos,buffer);
            linea = Tokenizer::tokenizeDato(buffer);
            for(int i = 0; i < linea.palabras.size();i++) {
                info.palabras.agregar(linea.palabras[i]);
                for (int j = i+1; j < linea.palabras.size(); i++) {
                    info.relaciones.agregar(linea.palabras[i], linea.palabras[j], linea.valor);
                }
            }
        }
        datos.close();
    }

    return info;
}

// Con la info pasada por parametro analiza los datos a testear.
void resolver(TInfo info,string datosATestear) {
    string buffer;
    TLineaTest lineaTest;
    Grafo grafo;
    TDatosArista datosArista;
    float resultado;

    // Se abre el archivo a testear y el de salida
    ifstream datos(datosATestear);
    ofstream savefile("resources/submission.tsv");
    savefile<<"\"id\",\"sentiment\""<<endl;
    if (datos.is_open()) {
        // Se lee linea a linea cada review.
        while (datos.good()) {
            getline(datos,buffer);
            // Se inicia el resultado en cero, se separa en oraciones y las oraciones en palabras.
            resultado = 0;
            lineaTest = Tokenizer::tokenizeTest(buffer);
            // Se agrega cada palabra como nodo y cada relacion como arista
            for(int z = 0; z < lineaTest.oraciones.size();z++) {
                for(int i = 0; i < lineaTest.oraciones[z].size();i++) {
                    grafo.agregarNodo(lineaTest.oraciones[z].at(i));
                }
                for(int i = 0; i < lineaTest.oraciones[z].size();i++) {
                    for (int j = i+1; j < lineaTest.oraciones[z].size(); i++) {
                        // TODO: usar (pr)/(pi+pj-pr)
                        datosArista.cantPalabrasI = info.palabras.getCantidad(lineaTest.oraciones[z].at(i));
                        datosArista.cantPalabrasJ = info.palabras.getCantidad(lineaTest.oraciones[z].at(j));
                        datosArista.datosRelacion = info.relaciones.getDatos(lineaTest.oraciones[z].at(i), lineaTest.oraciones[z].at(j));
                        grafo.agregarArista(lineaTest.oraciones[z].at(i), lineaTest.oraciones[z].at(j), datosArista);
                    }
                }
                // Se completa el grafo con aristas en cero para las palabras no relacionadas
                grafo.completar();
                // Se resuelve el ciclco mas probable para cada oracion y se van sumando los resultados
                resultado = resultado + grafo.resolverCicloMasProbable();
            }
            savefile<<"\""<<lineaTest.id<<"\",";
            // Si el resultado final es positivo la review se considera positiva, en caso contrario se toma como negativa
            if (resultado>0) {
                savefile<<"1"<<endl;
            } else {
                savefile<<"0"<<endl;
            }
            datos.close();
            savefile.close();
        }
    }
}

int main(int argc, char **argv) {
    resolver(aprender(TRAIN_DATA), TEST_DATA);
}