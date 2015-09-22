#include "Path.h"

using namespace std;
#include <stdio.h>
#include <iostream>

Path::Path()
{
	graph = NULL;
	nodes = new Collection();
}

Path::Path(Graph * pgraph)
{
	graph = pgraph;
	nodes = new Collection();
}

Path::~Path(void)
{
	nodes->Destroy();
}
Path * Path::Copy()
{
	Path * result= new Path();
	result->graph = this->graph;
	for(int i=0 ; i < this->nodes->Size(); i++)
	{
		int node=((Integer*)this->nodes->GetItem(i))->GetValue();
		result->Add(node);
	}
	return result;
}

void Path::Add(int node)
{
	nodes->Add((Object*) new Integer(node));
}

void Path::Remove(Integer *node)
{	
	int i=0;
	bool encontre = false;
	while (! encontre && i < this->nodes->Size()) {
		
		if (((Integer*)(nodes->GetItem(i)))->GetValue() == node->GetValue())
			encontre = true;
		else i++;
	}
	if (encontre) {
		delete (Integer*)nodes->GetItem(i);
		nodes->Remove(i);
	}
}

int Path::Length()
{
	return nodes->Size();
}

int Path::GetNode(int index)
{
	return ((Integer *) nodes->GetItem(index))->GetValue();
}

void Path::Reverse()
{
	nodes->Reverse();
}

void Path::Remove(int index)
{
	delete (Integer*)nodes->GetItem(index);
	nodes->Remove(index);
}

//Obtiene el costo del Path.
double Path::GetCost()
{
	double cost = 0;
	int node1 = GetNode(0);
	int node2;
	for(int i= 1; i < Length(); i++)
	{
		node2 = GetNode(i);
		cost += graph->GetEdgeCost(node1, node2);
		node1 = node2;
	}
	return cost;
}

void Path::Show()
{
	cout << "[";
	if(nodes->Size() > 0)
	{
		cout << ((Integer*)nodes->GetItem(0))->GetValue();
	}
	for(int i=1; i < nodes->Size();i++)
	{
		cout << ", " << ((Integer*)nodes->GetItem(i))->GetValue();
	}
	cout << "]";
}

Collection * Path::GetNodes()
{
	return nodes;
}

void Path::SetNodes(Collection *c)
{
	this->nodes = c;
}

void Path::SetGraph(Graph * pgraph)
{
	this->graph = pgraph;
}

int Path::GetNextNode(int node)
{	
	Integer * x = new Integer(node);
	int i = nodes->IndexOf((Object*)x);
	delete x;
	return this->GetNode(i+1);
}

int Path::GetPreviousNode(int node)
{	
	Integer * x = new Integer(node);
	int i = nodes->IndexOf((Object*)x);
	delete x;
	if (i>0) return this->GetNode(i-1);
	else return -1;
}

Path * Path::SubPath(int node1, int node2)
{
	Path *p = new Path(this->graph); 
	
	Integer * x = new Integer(node1);
	int i = nodes->IndexOf((Object*)x);
	Integer * y = new Integer(node2);
	int j = nodes->IndexOf((Object*)y);
	
	for (int k=i;k<=j;k++) {
		p->Add(this->GetNode(k));
	}
	
	delete x;
	delete y;
	return p;
}

Path * Path::Concat(Path * p)
{
	int node;
	Path * path = new Path(this->graph);
	for (int i = 0; i < this->nodes->Size(); i++) {
		node = ((Integer *)(this->nodes->GetItem(i)))->GetValue();
		path->Add(node);
	}
	for (int i = 0; i < p->nodes->Size(); i++) {
		node = ((Integer *)(p->nodes->GetItem(i)))->GetValue();
		path->Add(node);
	}
	return path;
}

bool Path::ExistsTram(int node1, int node2) 
{
	Collection * temp = this->GetNodes();
	bool encontre = false;
	int n,next,i = 0;
	while ((!encontre) && (i < temp->Size())) {
		n = ((Integer*)temp->GetItem(i))->GetValue();
		if (n == node1) {
			// si el node1 no es el ultimo
			if (i < (temp->Size()-1)) {
				next = ((Integer*)temp->GetItem(i+1))->GetValue();
				if (next == node2)	encontre = true;
			}
		}
		i++;
	}
	return encontre;
}

bool Path::Contains(int node)
{
	for(int i=1; i < nodes->Size();i++)
	{
		if(((Integer*)nodes->GetItem(i))->GetValue() == node){
			return true;
		}
	}
	return false;
}

bool Path::Contains(Path * p)
{
	int firstNode = p->GetNode(0);
	int lastNode = p->GetNode(p->Length()-1);
	Path * temp = NULL;
	for(int i=0; i < nodes->Size();i++)
	{
		int node = ((Integer*)nodes->GetItem(i))->GetValue();
		if(node == firstNode)
		{
			temp = p->Copy();
		}
		if(node == lastNode)
		{
			temp = p->Copy();
			temp->Reverse();
		}
		if(temp != NULL)
		{
			for(int j=0; j < temp->Length(); j++)
			{
				int x = temp->GetNode(j);
				if(i+j < nodes->Size())
				{
					int y = GetNode(i+j);
					if(x != y)
					{
						delete temp;
						return false;
					}
				}
				else
				{
					delete temp;
					return false;
				}
			}
			delete temp;
			return true;
		}
	}
	return false;
}
