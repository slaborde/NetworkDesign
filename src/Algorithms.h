#if !defined(Algorithms_h)
#define Algorithms_h

#include "Graph.h"
#include "BinaryHeap.h"
#include "Path.h"

class Graph;
class Algorithms
{
public:
	//encuentra el camino menos costoso entre dos nodos de un grafo.
	static Path * Dijkstra(Graph * g,int node1, int node2);
	//Retorna true si el grafo es conectado
	static bool IsConnected(Graph * g);
	static double FFAlgorithm(DirectedGraph *,int,int);
	static Collection * KSP(Graph * g, int s, int t, int k);
};

//Esta clase se utiliza en el algoritmo de dijkstra, 
//y representa un registro de una tabla.
class DijkstraTableEntry : Object
{
public:
	DijkstraTableEntry(bool known, double distance, int predecessor);
	bool Equals(Object*);
	bool known;
	double distance;
	int predecessor;
};

//Esta clase se utiliza en el algoritmo de dijkstra.
class Association : INumerable
{
public:
	Association(int node, double cost);
	double GetValue();
	int GetNode();
private:
	int node;
	double cost;
};

class FFEdge{
public:
	FFEdge(double capacity);
	virtual ~FFEdge();
	double GetCapacity();
	double GetFlow();
	void SetFlow(double);
private:
	double capacity;
	double flow;
};

class FFTableEntry{
public:
	FFTableEntry();
	virtual ~FFTableEntry();
	bool IsMarked();
	int GetPredecessor();
	bool IsPlus();
	double GetFullnes();
	void SetPredecessor(int);
	void SetPlus(bool);
	void SetMarked(bool);
	void SetFullnes(double);
private:
	bool marked;
	int predecessor;
	bool plus;
	double fullnes;
};

//Esta clase se utiliza en el algoritmo de dijkstra.
class FFAssociation : INumerable
{
public:
	FFAssociation(int node, double cost, double flow);
	virtual ~FFAssociation();
	double GetValue();
	double GetFlow();
	int GetNode();
private:
	int node;
	double cost;
	double flow;
};

//Esta clase se utiliza en el algoritmo de KSP.
//Representa el k camino mas corto encontrado, con su nodo de dispersion. 
class Ksp_record : Object
{
public:
	Ksp_record();
	virtual ~Ksp_record();
	Path * camino;
	Collection * edges_removed;
	int dp;	
};

#endif
