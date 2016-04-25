#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "Graph.h"
#include "time.h"

class Utilities
{
public:
	static Graph * GenerateGraph(int nodeCount, int edgeCount, int terminalCount);
	static Graph * GenerateGraph2(int nodeCount, int edgePercentage, int terminalCount);
	static Graph * GenerateGraph3(int nodeCount, int edgeCount, int terminalCount);
	static Graph * GenerateGraph4(int nodeCount, int nodesDegree, int terminalCount);
};

#endif /*UTILITIES_H_*/
