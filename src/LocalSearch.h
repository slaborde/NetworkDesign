#ifndef LOCALSEARCH_H_
#define LOCALSEARCH_H_

#include "Graph.h"
#include "Construction.h"


//Esta clase representa una interfaz para objetos de tipo Busqueda Local
class LocalSearch : public Object
{
public:
	virtual Graph * LocalSearchMethod(Graph * g, MatrixP * p)=0;
};

#endif /*LOCALSEARCH_H_*/
