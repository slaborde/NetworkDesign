//Implementacion del grafo

#ifndef GRAFO_H_
#define GRAFO_H_

#include <fstream>
#include <string>
#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>

#include "Adyacence.h"
#include "Collection.h"
#include "Integer.h"
#include "Node.h"
#include "KeyTree.h"
#include "Path.h"
#include "DirectedGraph.h"
#include "Algorithms.h"
#include "ExtendedCut.h"

class KeyTree;
class Path;
class Algorithms;
class Graph {
	public:
		Graph();
		Graph(int);
		Graph * Copy();
		virtual ~Graph(void);

		//Obtiene la cantidad de nodos del grafo
		int GetNodesCount();
		//Obtiene la cantidad de aristas del grafo
		int GetEdgesCount();
		//Muestra el grafo en la consola
		void Show();
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
		//Obtiene la probabilidad de falla de un nodo
		double GetNodeProbability(int);
		//Obtiene la probabilidad de falla de una arista
		double GetEdgeProbability(int, int);
		//Obtiene el costo de una arista
		double GetEdgeCost(int x, int y);
		//Setea la probabilidad de falla de un nodo
		void SetNodeProbability(int, double);
		//Setea la probabilidad de falla de una arista
		void SetEdgeProbability(int, int, double);
		//Seta el costo de una arista
		void SetEdgeCost(int, int, double);
		//Marca a un nodo como terminal
		void MarkTerminal(int);
		//Marca un nodo como No terminal
		void MarkNoTerminal(int);
		//Pregunta si un nodo es terminal
		bool IsTerminal(int);
		//Obtiene la coleccion de nodos adyacentes al que se le pasa como par�metro
		//No se tiene en cuenta los nodos inacivos
		//El resultado es una coleccion de Objetos de tipo "Integer"
		Collection * GetAdyacents(int);
		//Obtiene la coleccion de nodos terminales
		//El resultado es una coleccion de Objetos de tipo "Integer"
		Collection * GetTerminals();
		//Obtiene la cantidad de nodos terminales
		int GetTerminalsCount();
		//Obtiene un nodo terminal
		int GetTerminal();
		//Obtiene la colleci�n de los nodos de steiner
		Collection * GetSteinerNodes();
		//Setea la confiabilidad de los nodos de Steiner
		void SetSteinerNodesProb(double r);
		//Pregunta se existe una arista entre un par de nodos especificados como par�metros
		bool ExistEdge(int, int);
		//Pregunta si un nodo se encuentra activado
		bool IsNodeEnabled(int);
		//Pregunta si una arista se encuentra activada
		bool IsEdgeEnabled(int, int);
		//Obtiene el grado de un nodo
		int GetNodeDegree(int);
		//Muestra en la consola un resumen de los nodos y aristas activos
		void ShowEnableds();
		//Activa todos los nodos y aristas del grafo
		void EnableAll();
		//Desactiva todos los nodos y aristas del grafo
		void DisableAll();
		//Activa todos los nodos Terminales
		void EnableAllTerminals();
		//Desactiva todos los nodos Terminales
		void DisableAllTerminals();
		//Obtiene los nodos activos
		Collection * GetEnabledNodes();
		//Obtiene las aristas activas
		//Retorna una collecci�n de "EdgeTypes"
		Collection * GetEnabledEdges();
		//Setea la probabilidad de las aristas habilitadas
		void SetEnabledEdgesProb(double r);
		
		//Obtiene el grafo resultado de aplicar la opraci�n \ entre un grafo y un conjunto de nodos
		//PRE: los elementos de la colecci�n son de tipo "Integer"
		void Rest(Collection *);
		//Agrega un keyTree al grafo
		void Union(KeyTree * T);
		//Agrega un camino al grafo
		void Union(Path * path);
		// devueve true si el nodo es un keynode, false en caso contrario
		bool IsKeyNode(int);		
		//Obtiene los key nodes
		//Retorna una colecci�n de "Integers"
		Collection * GetKeyNodes();
		Collection * GetKeyNodes(bool);
		//Elimina los costos del camino en el grafo, pero no lo desactiva
		void SetCostZero(Path* path);
		
		//Obtiene el req de conexion entre un par de terminales
		int GetConnReq(int, int);
		void SetConnReq(int, int, int);
		//Obtiene el costo de un grafo
		double GetCost();

		//Retorna true si el grafo cumple con las condiciones de factibilidad
		bool IsFactible();
		
		//Convierte un grafo no dirigido a otro dirigido
		DirectedGraph * ToDirectedGraph();

		//Setea las coordenadas de un nodo
		void SetX(int,int);
		void SetY(int,int);

		//Carga un grafo
		static Graph * LoadGraph(string);
		static void SaveGraph(string,Graph *);
		
		/*******RVR*******/
		//Contrae si es posible todo el grafo
		void Contract();
		//Contrae por una arista
		int Contract(int, int);
		//Da un corte extendido
		ExtendedCut GetKExtendedCut();
		//Retorna la probabilidad de que fallen todos
		double AllFailedProb(ExtendedCut &d);
		//Retorna el valor del atributo terminales del grafo
		int GetTCount();
		/*****************/
		
	private:
		Node ** nodes;//dos asteriscos porque es un array de punteros a nodos, tambien se podr�a haber hecho como un arreglo de nodos
		Adyacence  * edges;
		int nodesCount, edgesCount;
		int ** connectionReqs;

	protected:
		int terminalsCount;	
};

#endif /*GRAFO_H_*/
