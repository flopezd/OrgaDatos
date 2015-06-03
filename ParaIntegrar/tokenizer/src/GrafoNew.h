/*
 * grafoNew.h
 *
 *  Created on: 29/5/2015
 *      Author: sebastian
 */

#ifndef GRAFONEW_H_
#define GRAFONEW_H_
#include "Vertice.h"
#include "HashMap.h"
#include "Jenkins.h"
#include <vector>
#include "Common.h"
#include <algorithm>

class GrafoNew {
private:
	void cicloMayorPeso ( Vertice* , double& );

public:
	Vertice* vertice;
	HashMap hash;
	Jenkins *fHash;

	vector < Vertice* > verticesRecorridos;
	vector < Vertice* > verticesCicloMax;
	vector <double> ponderadoRecorridos;
	vector <double> ponderadoMax;
	double pesoMaximo = 0;

	size_t iteracion=0;

	unordered_map <string,int> *cantPalHash;
	unordered_map < parPalabras ,calificacion ,KeyHasher>  *parHash;
	vector < Vertice* >vertices;
	void guardarVertice ( Vertice* );
	void cicloMayor();
	double probaBloque();
	double valorBloque();
	GrafoNew( unordered_map < string , int >* , unordered_map < parPalabras ,calificacion ,KeyHasher >* );
	virtual ~GrafoNew();
	void clear();
};



#endif /* GRAFONEW_H_ */
