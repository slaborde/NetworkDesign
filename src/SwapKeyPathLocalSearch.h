#ifndef SWAPKEYPATHLOCALSEARCH_H_
#define SWAPKEYPATHLOCALSEARCH_H_

#include "Greedy.h"
#include "KeyPathLocalSearch.h"

class SwapKeyPathLocalSearch : public LocalSearch
{
public:
	SwapKeyPathLocalSearch();
	virtual ~SwapKeyPathLocalSearch();
	static Graph * SwapEdgeLS(Graph * &g, MatrixP * &p);
	Graph * LocalSearchMethod(Graph * g, MatrixP *p);
	
private:
	static bool  FindSubstituteKeyPath(Graph * &g, Path * path, MatrixP * &p);
	
};

#endif /*SWAPEDGELOCALSEARCH_H_*/
