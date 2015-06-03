/*
 * HashMap.cpp
 *
 *  Created on: 10/05/2015
 *      Author: emanuel
 */

#include "HashMap.h"
#include <iostream>
#include <map>
using namespace std;

HashMap::HashMap() {
	this->mapa= new map<int, Vertice*>();
}

void HashMap::put(int clave, Vertice* valor){
	this->mapa->insert(make_pair(clave,valor));
}

Vertice* HashMap::get(int clave){
	map<int,Vertice*>::iterator p = this->mapa->find(clave);
	if (p != this->mapa->end()){
		return p->second;
	}else return 0;
}

int HashMap::size(){
	return this->mapa->size();
}

HashMap::~HashMap() {
	map<int, Vertice*>::iterator p = this->mapa->begin();
	while (p != this->mapa->end()){
		Vertice *vertice = p->second;
		p++;
		delete vertice;
	}
}
void HashMap::clear(){
	map<int, Vertice*>::iterator p = this->mapa->begin();
	while (p != this->mapa->end()){
		Vertice *vertice = p->second;
		p++;
		delete vertice;
	}

	this->mapa= new map<int, Vertice*>();
}

