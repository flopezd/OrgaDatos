/*
 * Vertice.h
 *
 *  Created on: 29/5/2015
 *      Author: sebastian
 */

#ifndef VERTICE_H_
#define VERTICE_H_
#include <string.h>
#include <vector>
#include <sstream>
using namespace std;

class Vertice {
	typedef struct arista {
		    string nombre;
		    double peso;
		    double valor;
		    Vertice *verticeFinal;
		} arista_t;
public:
	string palabra;
	vector<arista> aristas;
	bool visitado;
	Vertice();
	Vertice(string);
	void conectar(Vertice*,double,double);
	virtual ~Vertice();
};



#endif /* VERTICE_H_ */
