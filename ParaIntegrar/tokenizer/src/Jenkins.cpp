/*
 * Jenkins.cpp
 *
 *  Created on: 21/05/2015
 *      Author: emanuel
 */

#include "Jenkins.h"
#include <stdint.h>
using namespace std;

Jenkins::Jenkins(unsigned primo) {
	this->primo = primo;
}

unsigned Jenkins::hash(string word){
	uint32_t h = 0;
	for (unsigned i = 0; i < word.length(); i++){
		h += word[i];
		h += (h<<10);
	    h ^= (h>>6);
	}
	h += (h<<3);
	h ^= (h>>11);
	h += (h<<15);
	return h;
}

Jenkins::~Jenkins() {
	// TODO Auto-generated destructor stub
}

