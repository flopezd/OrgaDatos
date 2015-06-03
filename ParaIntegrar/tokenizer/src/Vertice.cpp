/*
 * Vertice.cpp
 *
 *  Created on: 29/5/2015
 *      Author: sebastian
 */

#include "Vertice.h"

Vertice::Vertice(){}

Vertice::Vertice(string pal) {

	palabra=pal;
	visitado=false;
}
void Vertice::conectar(Vertice* vertice,double peso, double valor){
	arista_t aristaAux;		//conectar con su mismo vertice
	aristaAux.verticeFinal=vertice;
	ostringstream s;
	s<<aristas.size()+1;
	aristaAux.nombre=s.str();
	aristaAux.peso=peso;
	aristaAux.valor=valor;
	aristas.push_back(aristaAux);

}

Vertice::~Vertice() {
}


