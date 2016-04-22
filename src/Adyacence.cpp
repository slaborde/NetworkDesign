#include "Adyacence.h"
#include <iostream>
using namespace std;

Adyacence::Adyacence(void){
	dimension = 0;
	edges = NULL;
}

Adyacence::Adyacence(int cantNodes) {
	dimension = cantNodes;
	edges = new (Edge**[dimension]);
	for(int j=0; j <dimension; j++)
	{
		edges[j] = new (Edge*[dimension]);
		for(int k=0; k <dimension ;k++)
		{
			edges[j][k]= NULL;
		}
	}
}

Adyacence::~Adyacence() {
	for(int i=0; i < dimension ; i++)
	{
		for(int j=0; j< dimension ; j++)
		{
			if(this->edges[i][j]!= NULL)
				delete this->edges[i][j];
		}
		delete this->edges[i];
	}
	delete this->edges;
}

//Crea una copia de la matriz de adyacencia
Adyacence * Adyacence::Copy()
{
	Adyacence * temp = new Adyacence(dimension);
	for(int i=0; i < dimension ; i++)
	{
		for(int j=0; j< dimension ; j++)
		{
			if(this->edges[i][j] != NULL)
			{
				temp->edges[i][j] = this->edges[i][j]->Copy();
			}
		}
	}
	return temp;
}

Edge * Adyacence::GetEdge(int i, int j)
{
	if(i < j)
	{
		return this->edges[i][j];
	}
	else
	{
		return this->edges[j][i];
	}
}

void Adyacence::SetEdge(int i, int j, Edge * edge)
{
	if(i < j)
	{
		this->edges[i][j] = edge;
	}
	else
	{
		this->edges[j][i] = edge;
	}
}

void Adyacence::Show() {
	int i, j;
	for (i=0; i<dimension; i++)
		for (j=0; j<dimension; j++) {
			if (i < j)
				if (GetEdge(i, j) != NULL)
					if (GetEdge(i,j)->IsEnabled()) {
						cout << "Arista " << i << "," << j << "\n";			
						GetEdge(i, j)->Show();
					}
		}
}


