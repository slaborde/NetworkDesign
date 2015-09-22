#ifndef KEYTREELOCALSEARCH_H_
#define KEYTREELOCALSEARCH_H_

#include "Algorithms.h"
#include "LocalSearch.h"

class KeyTreeLocalSearch : public LocalSearch
{
public:
	KeyTreeLocalSearch();
	virtual ~KeyTreeLocalSearch();
	//Busqueda local basada en la estructra de vecindario key-tree
	static Graph * KeyTreeLS(Graph * g);
	static Graph * SubGraphInducedBySGorro(Graph * g, Collection * Z, Collection * SGorro);
	static Collection * GetNonSolutionNodes(Graph * g);
	static bool FindSubstituteKeyTree(Graph * g, int v, Collection * STecho);
	
	Graph * LocalSearchMethod(Graph * g, MatrixP *p);
};

#endif /*KEYTREELOCALSEARCH_H_*/
