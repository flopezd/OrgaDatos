//============================================================================
// Name        : tokenizer.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <unordered_map>
#include <iostream>
#include "Common.h"
#include "GrafoNew.h"

#include "strtk.hpp"
using namespace std;

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool condicion(string pal,string sigPal,bool review){
	return((pal=="1"|| pal=="0") && sigPal!="\"" && !review);
}
int aNum(string num){
	if(num=="1")
		return 1;
	else
		return 0;
}

int main() {

	std::deque<std::string> word_list;
	strtk::for_each_line("/home/sebastian/datos.tsv",[&word_list](const std::string& line)
	                        {
	                           static const std::string delimiters = "()[]{}<>"
	                                                                 "\t\r\n ,,;:'"
	                                                                 "!@#$^&*/-=+`~";

	                           strtk::parse(line,delimiters,word_list);
	                        });


	int result=5;
	bool review=false;

	unordered_map <string,int> general;
	unordered_map < parPalabras ,calificacion ,KeyHasher> parMap;

	for(unsigned int i=0; i<(word_list.size()-2);i++){

		//entra si hay un 1 o 0, y si la sigPalbra es distinto de 0,1,""
		size_t size=word_list.at(i).size();
		if( word_list.at(i)[size-1] == '\"' && word_list.at(i)[0] == '\"' && isdigit(word_list.at(i)[size-2]) && ( isdigit(word_list.at(i)[size-3]) || word_list.at(i)[size-3] == '_' ) && ( isdigit(word_list.at(i)[size-4]) || word_list.at(i)[size-4] == '_' ) ){
			result=aNum(word_list.at(i+1));

			review=true;

			//cout<<word_list.at(i)<<"entra"<<endl;
		}
		else {
			//Entra solo si es una palabra
			if(review){
				review=true;
				//cout<<word_list.at(i+1)<<endl;
				calificacion calificacion;
				parPalabras par;

				//agregar palabra actual y siguiente al hash del bloque.
				string pal1=word_list.at(i+1);
				par.pal1=word_list.at(i+1);
				par.pal2=word_list.at(i+2);

				if(general.count(pal1)>0)
					general.at(pal1)+=1;
				else
					general.insert({pal1,1});

				if(result==1)
					if(parMap.count(par)>0)
						parMap.at(par).positiva+=1;
					else{
						parMap.insert( { par , calificacion } );
						parMap.at(par).positiva=1;
					}
				else
					if(parMap.count(par)>0)
						parMap.at(par).negativa+=1;
					else{
						parMap.insert( { par , calificacion } );
						parMap.at(par).negativa=1;
					}

				if(word_list.at(i+1)[size-1]=='\"'&&isdigit(word_list.at(i+1)[size-2])&&(isdigit(word_list.at(i+1)[size-3])||word_list.at(i+1)[size-3]=='_')&&isdigit(word_list.at(i+1)[size-4])){
					review=false;
				}
			}
		}
	}

	word_list.clear();

	GrafoNew* grafo  = new GrafoNew(&general , &parMap);

	string archiv ="/home/sebastian/resultado.txt";
	ofstream salida(archiv, std::ios::out | std::ios::app);
	salida << '\"' << "id"<<'\"'<<','<<'\"'<<"sentiment" << '\"' << "\n";
	salida.close();
	std::deque<std::string> word_test;
	strtk::for_each_line("/home/sebastian/testC.tsv",[&word_test](const std::string& lin)
							{
	                             static const std::string delimiter = "()[]{}<>"
	                                                                   "\t\r\n ,,;:'"
	                                                                   "!@#$^&*/-=+`~";
		                             strtk::parse(lin,delimiter,word_test);
	                          });

	bool estoyReview=false;
	vector < double > bloquesPonderados;
	cout<<"termino parsear"<<endl;
	string userId;
	for ( size_t i = 0 ; i < word_test.size() ; i++ ) {

		size_t size = word_test.at(i).size();

		if( word_test.at(i)[size-1] == '\"' && word_test.at(i)[0] == '\"'
		&& isdigit(word_test.at(i)[size-2]) && ( isdigit(word_test.at(i)[size-3])
		|| word_test.at(i)[size-3] == '_' ) && ( isdigit(word_test.at(i)[size-4])
		|| word_test.at(i)[size-4] == '_' ) ){
			userId =  word_test.at(i);
			estoyReview = true;

		} else
			if ( estoyReview ) {
				Vertice* vertice = new Vertice(word_test.at(i));
				grafo->guardarVertice(vertice);

				size_t size2 =  word_test.at( i+1 ).size();

				if ( word_test.at(i)[size-1] == '.' || ( word_test.at( i+1 )[ size2-1 ] == '\"'
				&& isdigit ( word_test.at( i+1 )[ size2-2 ] ) && ( isdigit( word_test.at( i+1 )[ size2-3 ] )
				|| word_test.at( i+1 )[ size2-3 ] == '_' ) && isdigit( word_test.at( i+1 )[ size2-4 ] ) ) ) {
					cout<<"empieza un cicloMax"<<endl;
					grafo->cicloMayor();
					cout<<"termina un cicloMax"<<endl;
					bloquesPonderados.push_back( grafo->valorBloque() * grafo->probaBloque() );
					grafo->clear();
				}

				if ( word_test.at( i+1 )[ size2-1 ] == '\"' && isdigit ( word_test.at( i+1 )[ size2-2 ] )
				&& ( isdigit( word_test.at( i+1 )[ size2-3 ] ) || word_test.at( i+1 )[ size2-3 ] == '_' )
				&& isdigit( word_test.at( i+1 )[ size2-4 ] ) ) {
					float sumatoria = 0;
					for ( size_t i = 0 ; i < bloquesPonderados.size() ; i++) {
						sumatoria += bloquesPonderados.at(i);
					}
					bloquesPonderados.clear();
					grafo->clear();
					ofstream salida(archiv, std::ios::out | std::ios::app);
					salida<<userId<<","<<sumatoria<<"\n";
					salida.close();
					estoyReview = false;
				}

			}

	}

	salida.close();

	return 0;

	}

