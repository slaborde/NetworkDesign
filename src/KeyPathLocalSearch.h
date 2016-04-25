#ifndef KEYPATHLOCALSEARCH_H_
#define KEYPATHLOCALSEARCH_H_

#include "Algorithms.h"
#include "Boolean.h"
#include "LocalSearch.h"
#include "time.h"

class KeyPathLocalSearch : public LocalSearch {

	public:
		KeyPathLocalSearch();
		virtual ~KeyPathLocalSearch();
		//busqueda local por key-path
		Graph* KeyPathLS(Graph *gsol);
		//retorna la descomposicion de un grafo en key-paths
		Collection* KeyPathDecomp(Graph *g);
		Graph * LocalSearchMethod(Graph * g, MatrixP *p);
		
	private:
		//chequea si restan por analizar key-paths de la coleccion
		bool NotAnalizedKP(Collection *K);
		//sortea un indice de key-path que no haya sido analizado 
		int GetRandomIndex(Collection *analized);
};

#endif /*KEYPATHLOCALSEARCH_H_*/
