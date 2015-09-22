#ifndef RELIAVILITY_H_
#define RELIAVILITY_H_

#include "Graph.h"
#include "ResultRVR.h"

class Reliability{
	public:
		//Configura para calcular Rst, probabilidad de existencia de por lo menos
		//un camino entre los nodos s y t
		void SetForRst(int, int, Graph * g);
		//Configura para calcular Rk, probabilidad de existencia de por lo menos
		//un camino entre todo par de nodos del subconjunto K (nodos terminales)
		void SetForRk(Graph * g);
		//Configura para calcular Rv, probabilidad de existencia de por lo menos
		//un camino entre todo par de nodos del grafo
		void SetForRv(Graph * g);
		virtual ResultRVR ConfMethod(int sem, long reps, Graph *gsol)=0;
	protected:
		double terminales;
};

#endif /*RELIAVILITY_H_*/
