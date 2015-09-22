#include "SwapNodeLocalSearch.h"

Graph * SwapNodeLocalSearch::SwapNodeLS(Graph * graph)
{
	bool improve = true;
	Graph * gsol = graph->Copy();
	//mientras queden mejoras
	while(improve)
	{
		improve = false;
		Collection * steinerNodes = gsol->GetSteinerNodes();
		//mientras queden nodos por intercambiar
		for(int i =0; i < steinerNodes->Size() && ! improve ; i++)
		{
			//cambio el nodo
			Integer * steinerNode = (Integer*) steinerNodes->GetItem(i);
			improve = SwapNode(gsol,steinerNode->GetValue());
		}
		steinerNodes->Destroy();
	}
	return gsol;
}

bool SwapNodeLocalSearch::SwapNode(Graph * graph, int node)
{
	double cost = graph->GetCost();
	Graph * temp = graph->Copy();

	//Obtiene
	//si el costo del nuevo grafo es menor
	double newCost = temp->GetCost();
	bool improve;
	if(newCost < cost)
	{
		improve = true;
	}
	else
	{
		improve = false;
	}
	return improve;
}
