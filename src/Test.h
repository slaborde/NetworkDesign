#ifndef TEST_H_
#define TEST_H_

#include "Greedy.h"
#include "KeyPathLocalSearch.h"
#include "KeyTreeLocalSearch.h"
#include "SwapKeyPathLocalSearch.h"
#include "Number.h"
#include "Utilities.h"
#include "Survivability.h"
#include "Reliability.h"
#include "RVR.h"

class Test
{
public:
	static void TestKeyTreeLocalSearch(string s);
	static void TestKeyPathLocalSearch(string s);
	static void TestKeyPathLocalSearch();
	static void TestKeyPathDecomp();
	static void TestSwapEdgeLocalSearch(string s);
	static void TestGreedy(string input);
	static void TestGreedyPerformance();
	static void GenerateGraphs(int startNode, int endNode);
	static void TestBinaryHeap();
	static void TestVNS();
	static void TestKsp();
};

#endif /*TEST_H_*/
