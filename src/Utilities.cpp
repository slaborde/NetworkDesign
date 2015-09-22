#include "Utilities.h"

Graph * Utilities::GenerateGraph(int nodeCount, int edgeCount, int terminalCount)
{
	Graph * graph = new Graph(nodeCount);
	int edges=0,terminals=0;
	srand((unsigned)time(0));
	for(int i=0; i <nodeCount; i++)
	{
		graph->SetX(i,rand() % 800);
		graph->SetY(i,rand() % 600);
	}
	while(terminals < terminalCount)
	{
		int node = rand() % nodeCount;
		if(! graph->IsTerminal(node))
		{
			graph->MarkTerminal(node);
			terminals++;
		}
	}
	int * degrees = new int[3];
	degrees[0]=0;
	degrees[1]=0;
	degrees[2]=0;
	while(edges < edgeCount)
	{
		int node1,node2,node1Degree,node2Degree;
		bool fin = false;
		do{
			node1 = rand() % nodeCount;
			node1Degree = graph->GetNodeDegree(node1);
			switch(node1Degree){
				case 0 :{
					fin = true;
					break;
				}
				case 1 :{
					if(degrees[0]>=nodeCount)
					{
						fin = true;
					}
					break;
				}
				case 2 :{
					if(degrees[1]>=nodeCount)
					{
						fin = true;
					}
					break;
				}
				default :{
					if(degrees[2]>=nodeCount)
					{
						fin = true;
					}
					break;
				}
			}
		}while(! fin);
		fin = false;
		do{
			node2 = rand() % nodeCount;
			if(node2 != node1)
			{
				node2Degree = graph->GetNodeDegree(node2);
				switch(node2Degree){
					case 0 :{
						fin = true;
						break;
					}
					case 1 :{
						if((degrees[0]+(node1Degree==0?1:0))>=nodeCount)
						{
							fin = true;
						}
						break;
					}
					case 2 :{
						if((degrees[1]+(node1Degree==1?1:0))>=nodeCount)
						{
							fin = true;
						}
						break;
					}
					default :{
						if((degrees[2]+(node1Degree==2?1:0))>=nodeCount)
						{
							fin = true;
						}
						break;
					}
				}
			}
		}while(! fin);
		if(! graph->ExistEdge(node1,node2))
		{
			graph->AddEdge(node1,node2,(rand() % 10) +1);
			if(node1Degree<3){
				degrees[node1Degree]++;
			}
			if(node2Degree<3){
				degrees[node2Degree]++;
			}
			edges++;
		}
	}
	Collection * terminals2 = graph->GetTerminals();
	for(int i=0; i < terminals2->Size();i++)
	{
		int node1 = ((Integer*)terminals2->GetItem(i))->GetValue();
		for(int j=0; j < terminals2->Size();j++)
		{
			int node2 = ((Integer*)terminals2->GetItem(j))->GetValue();
			graph->SetConnReq(node1,node2,2);
		}
	}
	return graph;
}

Graph * Utilities::GenerateGraph2(int nodeCount, int edgePercentage, int terminalCount)
{
	Graph * graph = new Graph(nodeCount);
	srand((unsigned)time(0));
	for(int i=0; i <nodeCount; i++)
	{
		graph->SetX(i,rand() % 800);
		graph->SetY(i,rand() % 600);
		for(int j=i+1; j <nodeCount; j++)
		{
			if((rand() % 100) < edgePercentage)
			{
				graph->AddEdge(i,j,(rand() % 10) +1);
			}
		}
	}
	int terminals=0;
	while(terminals < terminalCount)
	{
		int node = rand() % nodeCount;
		if(! graph->IsTerminal(node))
		{
			graph->MarkTerminal(node);
			terminals++;
		}
	}
	Collection * terminals2 = graph->GetTerminals();
	for(int i=0; i < terminals2->Size();i++)
	{
		int node1 = ((Integer*)terminals2->GetItem(i))->GetValue();
		for(int j=0; j < terminals2->Size();j++)
		{
			int node2 = ((Integer*)terminals2->GetItem(j))->GetValue();
			graph->SetConnReq(node1,node2,2);
		}
	}
	return graph;
}

Graph * Utilities::GenerateGraph3(int nodeCount, int edgeCount, int terminalCount)
{
	Graph * graph = new Graph(nodeCount);
	int edges=0,terminals=0;
	srand((unsigned)time(0));
	double aumento = 100 / nodeCount;
	for(int i=0; i <nodeCount; i++)
	{
		graph->SetX(i,rand() % 800);
		graph->SetY(i,rand() % 600);
	}
	while(terminals < terminalCount)
	{
		int node = rand() % nodeCount;
		if(! graph->IsTerminal(node))
		{
			graph->MarkTerminal(node);
			terminals++;
		}
	}
	double * probabilities = new double[4];
	probabilities[0]=100;
	probabilities[1]=0;
	probabilities[2]=0;
	probabilities[3]=0;
	while(edges < edgeCount)
	{
		int node1,node2,node1Degree,node2Degree;
		bool fin = false;
		do{
			node1 = rand() % nodeCount;
			node1Degree = graph->GetNodeDegree(node1);
			double probability1 = rand() % 100;
			int index1 = (node1Degree > 2 ? 3:node1Degree);
			if(probabilities[index1] > probability1)
			{
				fin = true;
			}
		}while(! fin);
		fin = false;
		do{
			node2 = rand() % nodeCount;
			node2Degree = graph->GetNodeDegree(node2);
			double probability2 = rand() % 100;
			int index2 = (node2Degree > 2 ? 3:node2Degree);
			if(probabilities[index2] > probability2)
			{
				fin = true;
			}
		}while(! fin);
		if(! graph->ExistEdge(node1,node2))
		{
			graph->AddEdge(node1,node2,(rand() % 10) +1);
			if(node1Degree<3){
				probabilities[node1Degree + 1] = probabilities[node1Degree + 1] + aumento;
			}
			if(node2Degree<3){
				probabilities[node2Degree + 1] = probabilities[node2Degree + 1] + aumento;
			}
			edges++;
		}
	}
	Collection * terminals2 = graph->GetTerminals();
	for(int i=0; i < terminals2->Size();i++)
	{
		int node1 = ((Integer*)terminals2->GetItem(i))->GetValue();
		for(int j=0; j < terminals2->Size();j++)
		{
			int node2 = ((Integer*)terminals2->GetItem(j))->GetValue();
			graph->SetConnReq(node1,node2,2);
		}
	}
	return graph;
}

Graph * Utilities::GenerateGraph4(int nodeCount, int nodesDegree, int terminalCount)
{
	Graph * graph = new Graph(nodeCount);
	int terminals=0;
	srand((unsigned)time(0));
	for(int i=0; i <nodeCount; i++)
	{
		graph->SetX(i,rand() % 800);
		graph->SetY(i,rand() % 600);
		graph->SetNodeProbability(i,0.99);		//todos los nodos en 0.99
	}
	while(terminals < terminalCount)
	{
		int node = rand() % nodeCount;
		if(! graph->IsTerminal(node))
		{
			graph->MarkTerminal(node);
			graph->SetNodeProbability(node,1);	//valor de confiabilidad de terminal en 1
			terminals++;
		}
	}
	for(int node1=0; node1 < nodeCount; node1++)
	{
		int j=graph->GetNodeDegree(node1);
		while(j < nodesDegree)
		{
			int node2 = rand() % nodeCount;
			if(node1 != node2 && ! graph->ExistEdge(node1,node2))
			{
				graph->AddEdge(node1,node2,(rand() % 10) +1);
				graph->SetEdgeProbability(node1,node2,0.90);	//todas las aristas en 0.90
				j++;
			}
		}
	}
	Collection * terminals2 = graph->GetTerminals();
	for(int i=0; i < terminals2->Size();i++)
	{
		int node1 = ((Integer*)terminals2->GetItem(i))->GetValue();
		for(int j=0; j < terminals2->Size();j++)
		{
			int node2 = ((Integer*)terminals2->GetItem(j))->GetValue();
			graph->SetConnReq(node1,node2,2);
		}
	}
	return graph;
}
