//Clase que implementa una arista de un grafo.

#ifndef EDGE_H_
#define EDGE_H_
#include "Object.h"

class Edge {
	public:
		//Por defecto esta habilitada, con probabilidad de operacion 1 y costo 0.
		Edge();
		Edge(bool, double, double);
		Edge(const Edge &);
		Edge &operator=(const Edge &);
		~Edge();
		Edge * Copy();
		void Enable();
		void Disable();
		void SetProbability(double);
		void SetCost(double);
		bool IsEnabled();
		double GetProbability();
		double GetCost();
		void Show();
	private:
		double costo;		//costo de la arista
		bool enabled;	//Esta habilitada o no
		double r;			//probabilidad de operacion
};

class EdgeType : Object
{
	public:
		EdgeType(){};
		EdgeType(int v1, int v2);
		virtual ~EdgeType();
		int GetV1();
		int GetV2();
		bool Equal(Object*);
	private:
		int v1;
		int v2;
};
#endif /*EDGE_H_*/
