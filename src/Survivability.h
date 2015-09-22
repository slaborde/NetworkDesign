#ifndef SURVIVABILITY_H_
#define SURVIVABILITY_H_

#include "Construction.h"

//Esta clase representa una interfaz para objetos de tipo Optimizaciòn
class Survivability
{
public:
	virtual Graph * Optim(Graph * g, Collection * cls, MatrixP * p)=0;
};

#endif /*SURVIVAVILITY_H_*/


