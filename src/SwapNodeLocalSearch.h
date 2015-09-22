#ifndef SWAPNODELOCALSEARCH_H_
#define SWAPNODELOCALSEARCH_H_

#include "Graph.h"

class SwapNodeLocalSearch
{
public:
	static Graph * SwapNodeLS(Graph * graph);
private:
	static bool SwapNode(Graph * graph, int node);
};

#endif /*SWAPNODELOCALSEARCH_H_*/
