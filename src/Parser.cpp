#include <string.h>
#include "Parser.h"
using namespace std;

void Parser::parse(std::string linea, const char* separador, std::vector<std::string> &resultados){
	char lineaArray[linea.size()];
	strcpy(lineaArray,linea.c_str());
	char *pointer = strtok(lineaArray,separador);
	while (pointer != NULL){
		resultados.push_back(pointer);
		pointer = strtok(NULL,separador);
	}
}
