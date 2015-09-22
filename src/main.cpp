#include <iostream>
using namespace std;

#include "NetworkDesign.h"

int main(int numArgs, char *args[]){

int k,cantiter,simiter, rp;
double umbral;
string graph;
	
	if (numArgs == 7) {
		
		if (args[1] != "") {
	
			graph.assign(args[1]);
			cantiter = atoi(args[2]);
			k = atoi(args[3]);
			umbral = atof(args[4]);
			simiter = atoi(args[5]);
			rp = atoi(args[6]);
			cout << "NetworkDesignAlgorithm se ejecutará con los siguientes parametros: " << graph << "|" << cantiter << "|" << k << "|" << umbral << "|" << simiter << "|" << rp << endl;
			if (rp == 1) NetworkDesign::NetworkDesignAlgorithm(graph,cantiter,k,umbral,simiter);
			else NetworkDesign::NetworkDesignAlgorithm2(graph,cantiter,k);
			cout << "NetworkDesignAlgorithm ha finalizado su ejecución: "; 
		}
		else cout << "El nombre del archivo no es correcto \n";
	}
	
	else cout << "La cantidad de parametros no es correcta \n";	
	
	return 0;
}
