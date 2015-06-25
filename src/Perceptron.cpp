#include "Common.h"
#include "TInfo.h"
#include "Perceptron.h"

TRelacion Perceptron::procesarDatosRelacion(TDatosRelacion datosRelacion,double cantPal1,double cantPal2) {
    TRelacion relacion;
    relacion.probabilidad = 0;
    relacion.valorRelacion = 0;
    if (datosRelacion.cantRelaciones > 0) {
        relacion.probabilidad = (double)(2*datosRelacion.cantRelaciones)/(cantPal1+cantPal2);
        relacion.valorRelacion = datosRelacion.valorRelacion;
    }
    return relacion;
}

TRelacion Perceptron::procesarDatosRelacionTriple(TDatosRelacion datosRelacion,double cantPal1,double cantPal2,double cantPal3) {
    TRelacion relacion;
    relacion.probabilidad = 0;
    relacion.valorRelacion = 0;
    if (datosRelacion.cantRelaciones > 0) {
        relacion.probabilidad = (double)(3*datosRelacion.cantRelaciones)/(cantPal1+cantPal2+cantPal3);
        relacion.valorRelacion = datosRelacion.valorRelacion;
    }
    return relacion;
}

int partition(vector<TRelacion> *bloque, int low, int high) {
    int pivotIndex = (low + high) / 2;
    double pivotValue = bloque->at(pivotIndex).probabilidad;
    TRelacion tmp;

    tmp = bloque->at(pivotIndex);
    bloque->at(pivotIndex) = bloque->at(high);
    bloque->at(high) = tmp;

    int storeIndex = low;
    for (int i = low; i < high; i++) {
        if(bloque->at(i).probabilidad>pivotValue) {
            tmp = bloque->at(storeIndex);
            bloque->at(storeIndex) = bloque->at(i);
            bloque->at(i) = tmp;
            storeIndex = storeIndex + 1;
        }
    }
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
    ordenarBloque(&bloque,0,bloque.size()-1);
    while(bloque.size()>cantRelacionesMax) {
        bloque.pop_back();
    }
    while(bloque.size()<cantRelacionesMax) {
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

double productoWX(vector<double> valores, vector<double> pesos) {
    double resultado = 0;
    for (int i = 0; i < tamVectorPerceptron; i++) {
        resultado = resultado + valores[i]*pesos[i];
    }
    return resultado;
}

int partition2(vector<TBloque> *bloque, int low, int high) {
    int pivotIndex = (low + high) / 2;
    double pivotValue = bloque->at(pivotIndex).probabilidad;
    TBloque tmp;

    tmp = bloque->at(pivotIndex);
    bloque->at(pivotIndex) = bloque->at(high);
    bloque->at(high) = tmp;

    int storeIndex = low;
    for (int i = low; i < high; i++) {
        if(bloque->at(i).probabilidad>pivotValue) {
            tmp = bloque->at(storeIndex);
            bloque->at(storeIndex) = bloque->at(i);
            bloque->at(i) = tmp;
            storeIndex = storeIndex + 1;
        }
    }
    tmp = bloque->at(storeIndex);
    bloque->at(storeIndex) = bloque->at(high);
    bloque->at(high) = tmp;

    return storeIndex;
}

void ordenarReview(vector<TBloque> *review, int low, int high) {
    if (low < high){
        int p = partition2(review, low, high);
        ordenarReview(review, low, p-1 );
        ordenarReview(review, p +1, high);
    }
}

vector<double> generarVector(vector<TBloque> review) {
    vector<double> vector;
    ordenarReview(&review,0,review.size()-1);
    while(review.size()<cantBloquesMax) {
        TBloque bloque = TBloque();
        review.push_back(bloque);
    }
    for (int i = 0; i < cantBloquesMax; i++) {
        for (int j = 0; j < cantRelacionesMax; j++) {
            vector.push_back(review[i].relaciones[j].valorRelacion);
        }
    }

    return vector;
}

vector<double> Perceptron::ajustarW(vector<TBloque> review, vector<double> wPerceptron,double valorEsperado) {
    vector<double> entrada = generarVector(review);
    double learningRate = 0.0025;

    double resultadoEsperado = valorEsperado;
    if (valorEsperado == 0) resultadoEsperado=-1;
    double resultado = productoWX(entrada,wPerceptron);
    //if ((resultadoEsperado <0 && resultado>=0) ||(resultadoEsperado >0 && resultado<=0)) {
        double error = resultadoEsperado - resultado;
        double modEntradaCuad = 0;
        for (int i = 0; i < tamVectorPerceptron; i++) {
            double xi = entrada.at(i);
            if(xi<1E-150) xi =0;
            modEntradaCuad = modEntradaCuad +( xi*xi);
        }
        if (modEntradaCuad == 0) modEntradaCuad=1;
        for (int i = 0; i < tamVectorPerceptron; i++) {
            double xi = entrada.at(i);
            if(xi<1E-150) xi =0;
            wPerceptron.at(i) = wPerceptron.at(i)+ learningRate * error * xi/modEntradaCuad;
            if (i == 73) {
                int a =5;
            }
        }
    //}
    return wPerceptron;
}

double Perceptron::resolverReview(vector<TBloque> review, vector<double> wPerceptron) {
    vector<double> entrada = generarVector(review);
    return productoWX(entrada,wPerceptron);
}