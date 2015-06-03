/*
 * grafoNew.cpp
 *
 *  Created on: 29/5/2015
 *      Author: sebastian
 */

#include "GrafoNew.h"
#include "Common.h"

GrafoNew::GrafoNew(unordered_map <string,int> * cantH,unordered_map < parPalabras ,calificacion ,KeyHasher>*parH ) {
	fHash=new Jenkins(1000000007);
	this->parHash=parH;
	this->cantPalHash=cantH;
}

GrafoNew::~GrafoNew() {
	// TODO Auto-generated destructor stub
}

void GrafoNew::guardarVertice(Vertice* vertice){

	unsigned clave=fHash->hash(vertice->palabra);

	if ( !hash.get(clave) ){

		hash.put(clave,vertice);

		for ( size_t i = 0  ; i < vertices.size() ; i++ ){
			parPalabras parP;
			parP.pal1 = vertices.at(i)->palabra;
			parP.pal2 = vertice->palabra;

			double pesoP = 0;
			double valorP = 0;
			if ( parHash->count(parP) && cantPalHash->count(parP.pal1)
			&& cantPalHash->count(parP.pal2) ) {

				size_t cantRelP = parHash->at(parP).cantRel();
				size_t cantPal1P = cantPalHash->at(parP.pal1);
				size_t cantPal2P = cantPalHash->at(parP.pal2);
				pesoP = (double)( 2 * cantRelP ) / (double) ( cantPal1P + cantPal2P );
				valorP = (double) parHash->at(parP).difPosNeg() / (double) cantRelP;
			}

			vertice->conectar ( vertices.at(i) , pesoP , valorP);
		}

		for ( size_t i = 0 ; i < vertices.size() ; i++ ){

			parPalabras par;
			par.pal1 = vertices.at(i)->palabra;
			par.pal2 = vertice->palabra;

			double peso = 0;
			double valor = 0;
			if ( parHash->count(par) && cantPalHash->count(par.pal1)
			&& cantPalHash->count(par.pal2) ) {

				size_t cantRel = parHash->at(par).cantRel();
				size_t cantPal1 = cantPalHash->at(par.pal1);
				size_t cantPal2 = cantPalHash->at(par.pal2);
				peso = (double)( 2 * cantRel ) / (double) ( cantPal1 + cantPal2 );
				valor = (double) parHash->at(par).difPosNeg() / (double) cantRel;
			}

			vertices.at(i)->conectar ( vertice , peso , valor );
		}

		vertices.push_back(vertice);

	}
}

void GrafoNew::cicloMayor(){
	double sumatoria = 0;
	iteracion=0;
	cicloMayorPeso( vertices.at(0) , sumatoria);
}

void GrafoNew::cicloMayorPeso ( Vertice* raiz , double& sumatoria ) {

	verticesRecorridos.push_back(raiz);
	vector < Vertice* >::iterator it;
	iteracion++;
	cout<<"en la iteracion: "<<iteracion<<endl;
	for ( size_t i = 0 ; i < raiz->aristas.size() ; i++ ) {

		it = find ( verticesRecorridos.begin() , verticesRecorridos.end() , raiz->aristas.at(i).verticeFinal );

		if ( ! ( it != verticesRecorridos.end() ) ){
			Vertice* sigVertice = raiz->aristas.at(i).verticeFinal;
			sumatoria += raiz->aristas.at(i).peso;
			double ponderado = (double)raiz->aristas.at(i).valor * raiz->aristas.at(i).peso;
			ponderadoRecorridos.push_back(ponderado);
			cicloMayorPeso(sigVertice,sumatoria);
			sumatoria -=  raiz->aristas.at(i).peso;
			ponderadoRecorridos.pop_back();
		}
	}

	if ( verticesRecorridos.size() == vertices.size() ) {

		size_t i = 0;
		while( raiz->aristas.at(i).verticeFinal->palabra != vertices.at(0)->palabra || i >  raiz->aristas.size() )
			i++;

		if( (i+1)>=raiz->aristas.size())
			cout<<"entra Mal arista"<<endl;

		sumatoria +=  raiz->aristas.at(i).peso;
		float ponderado = raiz->aristas.at(i).valor * raiz->aristas.at(i).peso;
		ponderadoRecorridos.push_back(ponderado);

		if ( sumatoria > pesoMaximo ) {
			pesoMaximo = sumatoria;
			verticesCicloMax = verticesRecorridos;
			ponderadoMax = ponderadoRecorridos;
		}

		ponderadoRecorridos.pop_back();
		sumatoria -=  raiz->aristas.at(i).peso;

	}

	verticesRecorridos.pop_back();


}

double GrafoNew::valorBloque(){

	double sumatoria=0;

	for ( size_t i = 0 ; i < ponderadoMax.size() ; i++ ) {
		sumatoria += ponderadoMax.at(i);
	}

	return sumatoria;
}

double GrafoNew::probaBloque() {
	return ( (double) pesoMaximo / (double) vertices.size() );
}

void GrafoNew::clear(){
	verticesRecorridos.clear();
	verticesCicloMax.clear();
	ponderadoRecorridos.clear();
	ponderadoMax.clear();
	pesoMaximo = 0;
	iteracion=0;
	vertices.clear();
	hash.clear();
}

