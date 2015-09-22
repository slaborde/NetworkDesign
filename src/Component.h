//Clase para el almacenamiento de informacion referente a un componente 
//de un corte extendido (un nodo o una arista).

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "Edge.h"

typedef enum {ARISTA, NODO} ComponentType;

class Component {
	public:
		Component();
		Component(ComponentType, int, EdgeType, double);
		ComponentType GetType();
		int GetNode();
		EdgeType GetEdge();
		double GetProb();
		bool operator==(Component);
		void SetProb(double);
		void Show();
				
	private:
		ComponentType tipo;
		int nodo;
		EdgeType arista;			
		double prob;
};

#endif
