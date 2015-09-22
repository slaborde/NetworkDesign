//Implementacion del grafo

#ifndef DIRECTED_GRAFO_H_
#define DIRECTED_GRAFO_H_

#include <fstream>
#include <string>
#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>

#include "Collection.h"
#include "Integer.h"
#include "Node.h"
#include "Edge.h"

class DirectedGraph {
	public:
		DirectedGraph();
		DirectedGraph(int);
		virtual ~DirectedGraph(void);

		//Obtiene la cantidad de nodos del grafo
		int GetNodesCount();
		//Obtiene la cantidad de aristas del grafo
		int GetEdgesCount();
		//Activa un nodo
		void EnableNode(int);
		//Desactiva un nodo
		void DisableNode(int);
		void DisableNode(int,bool);
		//Activa una arista
		void EnableEdge(int, int);
		//Desactiva una arista
		void DisableEdge(int, int);
		//Agrega una arista al grafo
		void AddEdge(int, int);
		void AddEdge(int, int, double);
		//Obtiene el costo de una arista
		double GetEdgeCost(int x, int y);
		//Seta el costo de una arista
		void SetEdgeCost(int, int, double);
		//Obtiene la coleccion de nodos adyacentes entrantes al que se le pasa como parámetro
		//No se tiene en cuenta los nodos inactivos
		//El resultado es una coleccion de Objetos de tipo "Integer"
		Collection * GetInAdyacents(int);
		Collection * GetOutAdyacents(int);
		//Pregunta se existe una arista entre un par de nodos especificados como parámetros
		bool ExistEdge(int, int);
		//Pregunta si un nodo se encuentra activado
		bool IsNodeEnabled(int);
		//Pregunta si una arista se encuentra activada
		bool IsEdgeEnabled(int, int);
		//Muestra en la consola un resumen de los nodos y aristas activos
		void ShowEnableds();
		//Activa todos los nodos y aristas del grafo
		void EnableAll();
		//Desactiva todos los nodos y aristas del grafo
		void DisableAll();
		//Obtiene los nodos activos
		Collection * GetEnabledNodes();
		//Obtiene las aristas activas
		//Retorna una collección de "EdgeTypes"
		Collection * GetEnabledEdges();
		
		//Obtiene el costo de un grafo
		double GetCost();

	private:
		Node ** nodes;//dos asteriscos porque es un array de punteros a nodos, tambien se podría haber hecho como un arreglo de nodos
		Edge *** edges;
		int nodesCount, edgesCount;

};

#endif /*DIRECTED_GRAFO_H_*/
