/*
 * HashMap.h
 *
 *  Created on: 10/05/2015
 *      Author: emanuel
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_
#include "Vertice.h"
#include <map>

class HashMap {
private:
	std::map<int,Vertice*>* mapa;

public:
	HashMap();
	void put(int clave, Vertice* valor);
	Vertice* get(int clave);
	int size();
	virtual ~HashMap();
	void clear();
};

#endif /* HASHMAP_H_ */
