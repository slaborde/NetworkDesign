#if !defined(KeyTree_h)
#define KeyTree_h

#include "Graph.h"

class Graph;
class Path;
class KeyTree
{
public:
	KeyTree(Graph * graph);
	virtual ~KeyTree(void);
	void AddKeyPath(Path * path);
	//Obtiene el costo de un keytree.
	double GetCost();
	//Retorna una colección de nodos (Integers)
	Collection * GetNodes();
	//Retorna una colección de aristas (EdgeType)
	Collection * GetEdges();
	//Retorna los nodos que e encuentran el las hojas del arbol
	Collection * GetEndNodes();
	//Elimina las aristas que tienen grado 1
	void RemoveEdgesWithDegreeOne();
	void Show();
	static KeyTree * GetKeyTree(Graph * graph, int node);
private:
	Graph * graph;
	Collection * keyPaths;
};
#endif
