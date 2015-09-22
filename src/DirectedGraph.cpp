#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(){
	nodes = NULL;
	edges = NULL;
	nodesCount = 0;
	edgesCount = 0;
}

DirectedGraph::DirectedGraph(int cant){
	nodes = new (Node(*[cant]));

	for(int i=0; i< cant; i++)
	{
		nodes[i]= new Node();
	}
	edges = new (Edge(**[cant]));
	for(int j=0; j <cant; j++)
	{
		edges[j] = new (Edge(*[cant]));
		for(int k=0; k <cant ;k++)
		{
			edges[j][k]= NULL;
		}
	}
	nodesCount = cant;
	edgesCount = 0;
}

DirectedGraph::~DirectedGraph(void)
{
	for(int i=0; i< nodesCount; i++)
	{
		delete nodes[i];
	}
	delete [] nodes;
	for(int i=0; i< nodesCount; i++)
	{
		for(int j=0; j< nodesCount; j++)
		{
			if(edges[i][j] != NULL)
				delete edges[i][j];
		}
		delete [] edges[i];
	}
	delete [] edges;
}

int DirectedGraph::GetNodesCount() {
	return (nodesCount);
}

int DirectedGraph::GetEdgesCount() {
	return (edgesCount);
}

void DirectedGraph::EnableNode(int x) {
	nodes[x]->Enable();
} 

void DirectedGraph::DisableNode(int x) {
	nodes[x]->Disable();
}

void DirectedGraph::DisableNode(int x, bool disableAdyacentEdges) {
	nodes[x]->Disable();
	if(disableAdyacentEdges)
	{
		for(int i=0; i < nodesCount; i++)
		{
			if(ExistEdge(x,i))
			{
				DisableEdge(x,i);
			}
		}
	}
}

void DirectedGraph::EnableEdge(int x, int y) {
	edges[x][y]->Enable();
}

void DirectedGraph::DisableEdge(int x, int y) {
	edges[x][y] ->Disable();
}

void DirectedGraph::AddEdge(int x, int y) {
	edgesCount++;
	edges[x][y]= new Edge();
}

void DirectedGraph::AddEdge(int x, int y, double cost)
{
	edgesCount++;
	edges[x][y] = new Edge(true,1.0,cost);
}

double DirectedGraph::GetEdgeCost(int x, int y) {
	return (edges[x][y]->GetCost());
}

void DirectedGraph::SetEdgeCost(int x, int y, double cost)
{
	edges[x][y]->SetCost(cost);
}

//Retorna una colección de nodos representados por Integers.
Collection * DirectedGraph::GetInAdyacents(int i) { 
	int j;
	Collection * result = new Collection();
	for (j=0; j<nodesCount; j++) {
		if (i!=j)
			if (ExistEdge(j,i))
				if (IsEdgeEnabled(j,i))
					if (IsNodeEnabled(j))
					{
						result->Add((Object*)new Integer(j));
					}
	}
	return (result);
}

Collection * DirectedGraph::GetOutAdyacents(int i) { 
	int j;
	Collection * result = new Collection();
	for (j=0; j<nodesCount; j++) {
		if (i!=j)
			if (ExistEdge(i,j))
				if (IsEdgeEnabled(i,j))
					if (IsNodeEnabled(j))
					{
						result->Add((Object*)new Integer(j));
					}
	}
	return (result);
}

bool DirectedGraph::ExistEdge(int i, int j) {
	if (i != j)
		if (edges[i][j] != NULL)
			return true;
		else
			return false;
	else
		return false;
}

bool DirectedGraph::IsNodeEnabled(int x) {
	return (nodes[x]->IsEnabled());
}

bool DirectedGraph::IsEdgeEnabled(int x, int y) {
	return (edges[x][y]->IsEnabled());
}

void DirectedGraph::ShowEnableds() {
	for (int i=1; i<=nodesCount; i++) {
		if (IsNodeEnabled(i)){
			cout << "Nodo " << i << " existe" << endl;
		}
	}
	for (int i=0; i<nodesCount; i++) {
		for (int j=i+1; j<nodesCount; j++) {
			if (ExistEdge(i, j))
				if (IsEdgeEnabled(i, j))
					cout << "Arista " << i << " , " << j << " existe" << endl;
		}		
	}
}


void DirectedGraph::EnableAll() {
	int i, j;
	// Habilita todos los nodes.
	for (i=0; i<nodesCount; i++) {
		EnableNode(i);
	}
	// Habilita todas las edges.
	for (i=0; i<nodesCount; i++) {
		for (j=i+1; j<nodesCount; j++) {
			if (ExistEdge(i, j))
				EnableEdge(i, j);
		}
	}
}
void DirectedGraph::DisableAll()
{
	int i, j;
	// DesHabilita todos los nodes.
	for (i=0; i<nodesCount; i++) {
		DisableNode(i);
	}
	// DesHabilita todas las edges.
	for (i=0; i<nodesCount; i++) {
		for (j=i+1; j<nodesCount; j++) {
			if (ExistEdge(i, j))
				DisableEdge(i, j);
		}
	}
}

Collection * DirectedGraph::GetEnabledNodes() {
	Collection * result = new Collection();
	for (int i=0; i<nodesCount; i++) {
		if (IsNodeEnabled(i))
		{
			result->Add((Object*)new Integer(i));
		}
	}
	return result;
}

Collection * DirectedGraph::GetEnabledEdges() {
	int i, j;
	Collection * result = new Collection();
	for (i=0; i<nodesCount; i++) {
		for (j=i+1; j<nodesCount; j++) {
			if (ExistEdge(i,j))
				if (IsEdgeEnabled(i, j))
					result->Add((Object*)new EdgeType(i,j));
		}
	
	}
	return result;
}

double DirectedGraph::GetCost()
{
	double cost = 0;
	for(int i=0 ; i < nodesCount; i++)
	{
		for(int j=i;j < nodesCount;j++)
		{
			if(ExistEdge(i,j) && IsEdgeEnabled(i,j))
			{
				cost += GetEdgeCost(i,j);
			}
		}
	}
	return cost;
}
