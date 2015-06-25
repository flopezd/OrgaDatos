#ifndef ORGADATOS_PARSER_H
#define ORGADATOS_PARSER_H
#include <vector>
#include <iostream>

class Parser {
public:
	static void parse(std::string linea, const char* separador, std::vector<std::string> &resultados);
};

#endif /* ORGADATOS_PARSER_H */
