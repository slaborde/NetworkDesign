//Implementacion del algoritmo de calculo de la confiabilidad de una red 
//mediante el metodo de Reduccion Recursiva de la Varianza (RVR).

#ifndef RVR_H_
#define RVR_H_

#include "Graph.h"
#include "Boolean.h"
#include "ExtendedCut.h"
#include "Reliability.h"

class RVR : public Reliability {
	public:
		RVR();
		virtual ~RVR();
		ResultRVR ConfMethod(int sem, long reps, Graph *gsol);
		//Calcula la confiabilidad de una red mediante RVR.
		//Parte de una semilla y un numero de iteraciones pasados por parametro. 
		//Retorna el tiempo de referencia.
		ResultRVR Conf(int, long, Graph*);
		// Devuelve el resultado del ultimo calculo realizado.
		ResultRVR GetResult();
		
	private:
		//Coleccion auxiliar de booleanos para la funcion fi
		Collection * mark;
		//Atributo que indica los terminales alcanzados por dfs
		int reached; 
		// Resultado del ultimo calculo de confiabilidad
		ResultRVR res;
		
		//Quita n elementos del corte extendido del grafo
		void Remove(Graph *, ExtendedCut &, int);
		//Agrega con probabilidad uno el componente parametro al grafo
		void Add(Graph *, Component);
		// Ejecuta una replicacion para obtener un valor de la medida
		// de la anti-confiabilidad (1 - confiabilidad).
		double Rvr(Graph *);
		//Sortea un elemento del corte
		int GetRandomItem(ExtendedCut &);
		//Chequea si la estructura esta operativa. 
		//Para estar operativa deben estar operativos todos los nodos terminales y además
		//existir al menos un camino entre todo par de nodos terminales.
	public:
		bool Fi(Graph *);
		//Recorrida dfs para fi
		void Dfs(Graph *,int);
};

#endif
