#include "Construction.h"

/*********** Clase que representa la matriz P ************/
MatrixP::MatrixP()
{
}

MatrixP::MatrixP(Graph * g)
{
	size = g->GetNodesCount();
	p = new (Collection**[size]);
	for(int i=0; i <size; i++)
	{
		p[i] = new (Collection*[size]);
		for(int j=i+1; j <size ;j++)
		{
			if (g->IsTerminal(i) && g->IsTerminal(j))
			{
				p[i][j]= new Collection();
			}
			else
			{
				p[i][j]= NULL;
			}		
		}
	}
}

MatrixP::~MatrixP()
{
	for(int i=0; i <size; i++)
	{
		for(int j=i+1; j <size ;j++)
		{
			if (p[i][j] != NULL)
			{
				((Collection *)p[i][j])->Destroy();
			}
		}
		delete [] p[i];
	}
	delete [] p;
}

MatrixP * MatrixP::Copy()
{
	MatrixP * temp = new MatrixP();
	temp->size = this->size;
	temp->p = new (Collection**[temp->size]);
	
	for(int i=0; i <temp->size; i++)
	{
		temp->p[i] = new (Collection(*[temp->size]));
		for(int j=i+1; j <temp->size ;j++)
		{
			if (this->p[i][j] != NULL)
			{
				temp->p[i][j]= new Collection();
				for(int k=0; k < GetCell(i,j)->Size(); k++)
				{
					temp->p[i][j]->Add((Object*)((Path *)GetCell(i,j)->GetItem(k))->Copy());
				}
			}
			else
			{
				temp->p[i][j]= NULL;
			}		
		}
	}
	return temp;
}

Collection * MatrixP::GetCell(int i, int j)
{
	if(i<j)
	{
		return p[i][j];
	}
	else
	{
		return p[j][i];
	}
}

void MatrixP::SetCell(int i, int j, Collection * c)
{
	if(i<j)
	{
		p[i][j]= c;
	}
	else
	{
		p[j][i]= c;
	}
}

void MatrixP::Show()
{
	for(int i=0; i <size; i++)
	{
		for(int j=i+1; j <size ;j++)
		{
			if (p[i][j] != NULL)
			{
				((Collection *)p[i][j])->Show();
				cout << endl;
			}
		}
	}
}
