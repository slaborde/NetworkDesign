#if !defined(Path_h)
#define Path_h

#include "Graph.h"

class Graph;
class Path : Object
{
public:
	
	Path();
	Path(Graph * graph);
	virtual ~Path(void);
	Path * Copy();
	void Add(int node);
	int Length();
	int GetNode(int index);
	void Reverse();
	void Remove(int index);
	void Remove(Integer *);
	//Obtiene el costo del Path.
	double GetCost();
	void Show();
	//devuelve la coleccion de nodos
	Collection * GetNodes();
	void SetNodes(Collection *);
	void SetGraph(Graph * graph);
	int GetNextNode(int);
	int GetPreviousNode(int);
	Path * SubPath(int, int);
	Path * Concat(Path*);
	bool ExistsTram(int, int);
	bool Contains(int);
	bool Contains(Path * p);
	
private:
	Graph * graph;
	Collection * nodes;
};
#endif
