#include <iostream>
#include <string>
#include <vector>
#include "Common.h"
#include "Tokenizer.h"

static const string TRAIN_DATA = "resources/labeledTrainData.tsv";
static const string TEST_DATA = "resources/testData.tsv";

// Procesa la informacion del archivo pasado por parametros y la
// devuelve ya procesada.
TInfo aprender(string archivoParaAprender) {
    TInfo info;
    char *buffer;
    TLineaDato linea;

    // Se abre el archivo
    //fopen...

    // Se lee linea a linea, cada linea se separa en palabras cada una se guarda en el
    // hash de palabras y cada combinacion de par de palabras en el hash de relaciones
    //for each line
        //fgets(---);7
        linea = Tokenizer::tokenizeDato(buffer);
        for(int i = 0; i < linea.palabras.size();i++) {
            info.palabras.agregar(linea.palabras[i]);
            for (int j = i+1; j < linea.palabras.size(); i++) {
                info.relaciones.agregar(linea.palabras[i], linea.palabras[j], linea.valor);
            }
        }

    return info;
}

// Con la info pasada por parametro analiza los datos a testear.
void resolver(TInfo info,string datosATestear) {
    char *buffer;
    vector<TOracion> oraciones;
    Grafo grafo;
    TDatosArista datosArista;
    float resultado;

    // Se abre el archivo a testear y el de salida
    //fopen...
    //fopen...

    // Se lee linea a linea cada review.
    //for each line
        //fgets(---);7
       // Se inicia el resultado en cero, se separa en oraciones y las oraciones en palabras.
        resultado = 0;
        oraciones = Tokenizer::tokenizeTest(buffer);
        // Se agrega cada palabra como nodo y cada relacion como arista
        for(int z = 0; z < oraciones.size();z++) {
            for(int i = 0; i < oraciones[z].palabras.size();i++) {
                grafo.agregarNodo(oraciones[z].palabras[i]);
            }
            for(int i = 0; i < oraciones[z].palabras.size();i++) {
                for (int j = i+1; j < oraciones[z].palabras.size(); i++) {
                    // usar (pr)/(pi+pj-pr)
                    datosArista.cantPalabrasI = info.palabras.getCantidad(oraciones[z].palabras[i]);
                    datosArista.cantPalabrasJ = info.palabras.getCantidad(oraciones[z].palabras[j]);
                    datosArista.datosRelacion = info.relaciones.getDatos(oraciones[z].palabras[i], oraciones[z].palabras[j]);
                    grafo.agregarArista(oraciones[z].palabras[i], oraciones[z].palabras[j], datosArista);
                }
            }
            // Se completa el grafo con aristas en cero para las palabras no relacionadas
            grafo.completar();
            // Se resuelve el ciclco mas probable para cada oracion y se van sumando los resultados
            resultado = resultado + grafo.resolverCicloMasProbable();
        }
        // Si el resultado final es positivo la review se considera positiva, en caso contrario se toma como negativa
        if (resultado>0) {
            //escriibir review positiva
        } else {
            //escriibir review negativa
        }
}

int main(int argc, char **argv) {
    resolver(aprender(TRAIN_DATA), TEST_DATA);
}