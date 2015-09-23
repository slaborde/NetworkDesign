#include "Keyree.h"

KeyTree::KeyTree(Graph * pgraph)
{
	graph = pgraph;
	keyPaths = new Collection();
}

KeyTree::~KeyTree(void)
{
	for(int i=0; i < keyPaths->Size() ; i++)
	{
		delete ((Path*)keyPaths->GetItem(i));
	}
	delete keyPaths;
}

void KeyTree::AddKeyPath(Path * path)
{
	keyPaths->Add((Object *)path);
}
//Obtiene el costo de un keytree.
double KeyTree::GetCost()
{
	double cost = 0;
	for(int i=0; i < keyPaths->Size() ; i++)
	{
		cost += ((Path*)keyPaths->GetItem(i))->GetCost();
	}
	return cost;
}

Collection * KeyTree::GetNodes()
{
	Collection * result = new Collection();
	for(int i=0; i< keyPaths->Size(); i++)
	{
		Path * path = (Path*)keyPaths->GetItem(i);
		for(int j=0; j < path->Length(); j++)
		{
			if(i == 0 || j > 0)
			{
				Integer * node = new Integer(path->GetNode(j));
				if(!result->Contains((Object*)node)){
					result->Add((Object*)node);
				}
				else
				{
					delete node;
				}
			}
		}
	}
	return result;
}

Collection * KeyTree::GetEdges()
{
	Collection * result = new Collection();
	for(int i=0; i< keyPaths->Size(); i++)
	{
		Path * path = (Path*)keyPaths->GetItem(i);
		if(path->Length() > 1)
		{
			for(int j=1; j < path->Length(); j++)
			{
				int v1 = path->GetNode(j-1);
				int v2 = path->GetNode(j);
				EdgeType * edge = new EdgeType(v1,v2);
				result->Add((Object*)edge);
			}
		}
	}
	return result;
}

Collection * KeyTree::GetEndNodes()
{
	Collection * result = new Collection();
	for(int i=0; i< keyPaths->Size(); i++)
	{
		Path * path = (Path*)keyPaths->GetItem(i);
		Integer * node = new Integer(path->GetNode(path->Length()-1));
		if(!result->Contains((Object*)node)){
			result->Add((Object*)node);
		}
		else
		{
			delete node;
		}
	}
	return result;
}

void KeyTree::RemoveEdgesWithDegreeOne()
{
	bool end = false;
	while(! end)
	{
		int node;
		for(int j=0; j < keyPaths->Size();j++)
		{
			Path * path = (Path*)keyPaths->GetItem(j);
			if(path->Length() <= 1){
				end = true;
				break;
			}
			if(j==0){
				node = path->GetNode(1);
			}
			else{
				if(path->GetNode(1) != node){
					end = true;
					break;
				}
			}
		}
		if(!end)
		{
			for(int j=0; j < keyPaths->Size();j++)
			{
				Path * path = (Path*)keyPaths->GetItem(j);
				path->Remove(0);
			}
		}
	}	
}

void KeyTree::Show()
{
	for(int i=0; i< keyPaths->Size(); i++)
	{
		Path * path = (Path*)keyPaths->GetItem(i);
		path->Show();
	}
}

//Obtiene un keytree a partir de un nodo y un grafo
//el nodo debe ser un keyNode
KeyTree * KeyTree::GetKeyTree(Graph * graph, int node)
{
	KeyTree * tree = new KeyTree(graph);
	Collection * c = graph->GetAdyacents(node);
	for(int i=0; i < c->Size(); i++)
	{
		int lastIdentifier = node;
		Path * aux = new Path(graph);
		aux->Add(node);
		int currentNode = ((Integer*)c->GetItem(i))->GetValue();
		int degree;
		bool isTerminal;
		do
		{
			aux->Add(currentNode);
			Collection * adyacents = graph->GetAdyacents(currentNode);
			degree = adyacents->Size();
			isTerminal = graph->IsTerminal(currentNode);
			if(degree == 2 && ! isTerminal)
			{
				if(((Integer*)adyacents->GetItem(0))->GetValue() == lastIdentifier)
				{
					lastIdentifier = currentNode;
					currentNode = ((Integer*)adyacents->GetItem(1))->GetValue();
				}
				else
				{
					lastIdentifier = currentNode;
					currentNode = ((Integer*)adyacents->GetItem(0))->GetValue();
				}
			}
			adyacents->Destroy();
		}while(degree == 2 && ! isTerminal);
		tree->AddKeyPath(aux);
	}
	c->Destroy();
	return tree;
}
