#include "Common.h"
#include "TInfo.h"
#include "Perceptron.h"

TRelacion Perceptron::procesarDatosRelacion(string palabra1,string palabra2,TInfo *info) {
    TDatosRelacion datosRelacion = info->relaciones.getDatos(palabra1,palabra2);
    double cantPal1 = info->palabras.getCantidad(palabra1);
    double cantPal2 = info->palabras.getCantidad(palabra2);
    TRelacion relacion;
    relacion.probabilidad = 0;
    relacion.valorRelacion = 0;
    if (datosRelacion.cantRelaciones > 0) {
        relacion.probabilidad = (double)(2*datosRelacion.cantRelaciones)/(cantPal1+cantPal2);
        relacion.valorRelacion = datosRelacion.valorRelacion;
    }
    return relacion;
}

int partition(vector<TRelacion> *bloque, int low, int high) {
    int pivotIndex = (low + high) / 2;
    double pivotValue = bloque->at(pivotIndex).probabilidad;
    TRelacion tmp;

    // put the chosen pivot at A[hi]
    tmp = bloque->at(pivotIndex);
    bloque->at(pivotIndex) = bloque->at(high);
    bloque->at(high) = tmp;

    int storeIndex = low;
    // Compare remaining array elements against pivotValue = A[hi]
    for (int i = low; i < high; i++) {
        if(bloque->at(i).probabilidad<pivotValue) {
            tmp = bloque->at(storeIndex);
            bloque->at(storeIndex) = bloque->at(i);
            bloque->at(i) = tmp;
            storeIndex = storeIndex + 1;
        }
    }
    // Move pivot to its final place
    tmp = bloque->at(storeIndex);
    bloque->at(storeIndex) = bloque->at(high);
    bloque->at(high) = tmp;

    return storeIndex;
}

void ordenarBloque(vector<TRelacion> *bloque, int low, int high) {
    if (low < high){
        int p = partition(bloque, low, high);
        ordenarBloque(bloque, low, p-1 );
        ordenarBloque(bloque, p +1, high);
    }
}

TBloque Perceptron::procesarDatosBloque(vector<TRelacion> bloque) {
    TBloque bloqueAux;
    double probTotal = 0;
    ordenarBloque(&bloque,0,bloque.size());
    while(bloque.size()>cantBloquesMax) {
        bloque.pop_back();
    }
    while(bloque.size()<cantBloquesMax) {
        TRelacion relacion;
        relacion.probabilidad = 0;
        relacion.valorRelacion = 0;
        bloque.push_back(relacion);
    }
    for (int i = 0; i < bloque.size(); i++) {
        probTotal = probTotal + bloque[i].probabilidad;
    }
    bloqueAux.probabilidad = probTotal / bloque.size();
    bloqueAux.relaciones = bloque;
    return bloqueAux;
}

void Perceptron::ajustarW(vector<TBloque> review, TInfo *info,double valorEsperado) {

}

double Perceptron::resolverReview(vector<TBloque> vector, TInfo *info) {
    return 0 ;
}