#include "VNS.h"

VNS::VNS(){
	
}

VNS::~VNS(){
	
}

Graph * VNS::Optim(Graph * g, Collection * cls, MatrixP * p) {
	
	return VNS::VNSAlgorithm(g,cls,p);

}

Graph * VNS::VNSAlgorithm(Graph * g, Collection * cls, MatrixP * p)
{		
	int kMax = cls->Size();
	int k=0;
	double cost = g->GetCost();

	Graph * temp = SwapKeyPathLocalSearch::SwapEdgeLS(g, p);
	
	delete g;
	delete p;
	g = temp;
	cost = g->GetCost();

	int notImprove = 0;
	while(notImprove < kMax)
	{	
		Graph * g2 = Search(g,k,cls);
		cost = g->GetCost();
		double newCost = g2->GetCost();
		if(newCost < cost)
		{
			cost = newCost;
			notImprove = 0;
			delete g;
			g = g2;
		}
		else
		{
			delete g2;
			notImprove++;
		}
		k = (k+1)%kMax;
	}
	return g; 
}

void VNS::VNSAlgorithm2(Collection * cls)
{
	FILE  * f = fopen("result.txt", "w");
	for(int i=10;i <= 266; i++)
	{
		//Cargar el grafo
		Graph * g;
		string fileName;
		fileName.assign("");
		char * s;
		sprintf(s,"%i",i);
		fileName.append(s);
		fileName.append(".xml");
		g = Graph::LoadGraph(fileName);
		int ok = 0;
		///////////////////

		int kMax=cls->Size();
		int k=0;
		double cost = g->GetCost();
		cout << i << "\t"<< cost;
		fprintf(f,"%i\t%f",i,cost);

		//Greedy	
		MatrixP * p;
		Graph * temp = Greedy::GreedyConstruction(g, p, 5,ok);
		delete g;
		g = temp;
		double lastCost = cost;
		cost = g->GetCost();
		cout << cost << "\t" << lastCost - cost << "\t";
		fprintf(f,"%f\t%f\t",cost,lastCost - cost);
	
		temp = SwapKeyPathLocalSearch::SwapEdgeLS(g, p);
		delete g;
		delete p;
		g = temp;
		lastCost = cost;
		cost = g->GetCost();
		cout << cost << "\t" << lastCost - cost << "\t";
		fprintf(f,"%f\t%f\t",cost,lastCost - cost);
	
		int notImprove = 0;
		lastCost = cost;
		string improvements = "";
		while(notImprove < kMax)
		{
			Graph * g2 = Search(g,k,cls);
			double newCost = g2->GetCost();
			if(newCost < cost)
			{
				cost = newCost;
				notImprove = 0;
				delete g;
				g = g2;
				char * sk;
				sprintf(sk,"%i",k);
				improvements += sk;
			}
			else
			{
				delete g2;
				notImprove++;
			}
			k = (k+1)%kMax;
		}
		cout << cost << "\t" << lastCost - cost << "\t" << improvements << endl;
		fprintf(f,"%f\t%f\t\n",cost,lastCost - cost);
	}
	fclose(f);
}

Graph * VNS::Search(Graph * g, int k,Collection * cls){
	
	MatrixP * p;
	
	return ((LocalSearch *)cls->GetItem(k))->LocalSearchMethod(g,p);	
	
}
