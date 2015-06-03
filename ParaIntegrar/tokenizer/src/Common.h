/*
 * Common.h
 *
 *  Created on: 1/6/2015
 *      Author: sebastian
 */

#ifndef _TOKENIZER_COMMON_H_
#define _TOKENIZER_COMMON_H_

#include <string.h>
#include <unordered_map>
#include <iostream>
using namespace std;

struct parPalabras{
	string pal1;
	string pal2;

	bool operator==(const parPalabras& b) const
	{
		string aux1=this->pal1+this->pal2;
		string aux2=b.pal1+b.pal2;
		string aux3=this->pal2+this->pal1;
		string aux4=b.pal2+b.pal1;
	   return (strcmp(aux1.c_str(),aux2.c_str())==0||strcmp(aux3.c_str(),aux4.c_str())==0);
	}
};

  struct KeyHasher
  {
    std::size_t operator()(const parPalabras& par) const
    {
    size_t h = 0;
    string aux=par.pal1+par.pal2;
    size_t len=aux.length();
    for (size_t i=0; i <len; ++i){
    	h+=aux[i];
    	h+=(h<<10);
    	h^=(h>>6);
    }
    h+=(h<<3);
    h^=(h>>11);
    h+=(h<<15);
    return h;
}
  };

  struct calificacion{
	  int positiva=0;
	  int negativa=0;

	  int cantRel() {
		  return (positiva + negativa);
	  }

	  int difPosNeg() {
		  return (positiva - negativa);
	  }
  };


#endif // _TOKENIZER_COMMON_H_
