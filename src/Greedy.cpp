#include <iostream> 
using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib> 
#include <ctime> 
#include "Greedy.h"

/*********** Clase que representa la matriz M ************/
MatrixM::MatrixM(Graph * g)
{
	size = g->GetNodesCount();
	m = new (int*[size]);
	for(int i=0; i <size; i++)
	{
		m[i] = new (int[size]);
		for(int j=i+1; j <size ;j++)
		{
			if (g->IsTerminal(i) && g->IsTerminal(j))
			{
				m[i][j]= g->GetConnReq(i,j);
			}
			else
			{
				m[i][j]= 0;
			}
		}
	}
}

MatrixM::~MatrixM()
{
	for(int i=0; i <size; i++)
	{
		delete [] m[i];
	}
	delete [] m;
}

int MatrixM::GetCell(int i, int j)
{
	if(i<j)
	{
		return m[i][j];
	}
	else
	{
		return m[j][i];
	}
}

void MatrixM::SetCell(int i, int j, int value)
{
	if(i<j)
	{
		m[i][j]= value;
	}
	else
	{
		m[j][i]= value;
	}
}

MatrixM * MatrixM::GetMatrixM(Graph * g, MatrixP * p)
{
	MatrixM * result = new MatrixM(g);
	for(int i=0; i <result->size; i++)
	{
		for(int j=i+1; j <result->size ;j++)
		{
			if(p->GetCell(i,j) != NULL)
			{
				result->m[i][j]= g->GetConnReq(i,j) - p->GetCell(i,j)->Size();
			}
		}
	}
	return result;
}
void MatrixM::Show()
{
	for(int i=-1; i <size; i++)
	{
		if(i > -1)
			cout << i;
		else
			cout << " ";
		for(int j=i+1; j <size ;j++)
		{
			if(i > -1)
				cout << " " << m[i][j];
			else
				cout << " " << j;
		}
		cout << endl;
	}
}

/*********** Clase que representa la matriz A ************/
MatrixA::MatrixA(Graph * g)
{
	size = g->GetNodesCount();
	a = new (int*[size]);
	for(int i=0; i <size; i++)
	{
		a[i] = new (int[size]);
		for(int j=i+1; j <size ;j++)
		{
			if (g->IsTerminal(i) && g->IsTerminal(j))
			{
				a[i][j] = 0;
			}
		}
	}
}

MatrixA::~MatrixA()
{
	for(int i=0; i <size; i++)
	{
		delete [] a[i];
	}
	delete [] a;
}

int MatrixA::GetCell(int i, int j)
{
	if(i<j)
	{
		return a[i][j];
	}
	else
	{
		return a[j][i];
	}
}

void MatrixA::SetCell(int i, int j, int value)
{
	if(i<j)
	{
		a[i][j]= value;
	}
	else
	{
		a[j][i]= value;
	}
}

/************** Greedy ****************/
Greedy::Greedy(){
	
}

Greedy::~Greedy(){
	
}

Graph * Greedy::Construct(Graph * g, MatrixP *& p, int k, int & ok){

	return Greedy::GreedyConstruction(g,p,k,ok);
	
}

Graph * Greedy::GreedyConstruction(Graph * g, MatrixP *& p, int k, int & ok)
{
	//inicializo 
	//gsol es el grafo solo con los terminales activos
	Graph * gsol = g->Copy();
	gsol->DisableAll();
	gsol->EnableAllTerminals();
	
	Collection * ksp_paths;
	MatrixA * a = new MatrixA(gsol);
	MatrixM * m = new MatrixM(gsol);
	p = new MatrixP(gsol);
	
	// Setea la semilla para el generador de numeros seudo-aleatorios.
	srand((unsigned)time(0));

	// Mientras exista un par de terminales (i,j) con mij>0
	// y el nro de intentos aij < MAX_ATTEMPT 
	Collection * pairs = PairTerm(m,gsol);
	while ((pairs->Size() != 0) && (Intentos(pairs,a))) {
		
		// Sorteo el par i,j
		Pair * pairij = Sortea(pairs);
		int i = pairij->GetI();
		int j = pairij->GetJ();
		// Obtengo el conjunto de nodos de todos los caminos nodos disjuntos
		// encontrados hasta el momento

		// Armo el grafo Gtecho quitando los nodos de los caminos de nodos 
		// disjuntos entre ij, para encontrar nuevos caminos
		Graph * gtecho = g->Copy();
		DisablePathsPij(gtecho,p,i,j);
		//Calculo la matriz Ctecho en Gtecho las aristas que ya estan en gsol
		// tienen costo 0 el resto su costo original
		ActualizarCostos(gtecho,gsol);
		//Se calculan los K caminos mas cortos entre i,j en Gtecho
		ksp_paths = Algorithms::KSP(gtecho,i,j,k);
		Path * path = SorteaPath(ksp_paths);
		delete gtecho;

		//Si encontre un camino lo agrego a Gsol y actualizo
		if (path != NULL) {
			gsol->Union(path);
			GeneralUpdateMatrix(gsol,p,m,path,i,j);
		}
		// Sino el grafo quedo disconexo, reseteo y actualizo 
		else {
			m->SetCell(i,j,g->GetConnReq(i,j));
			a->SetCell(i,j,a->GetCell(i,j)+1);
			p->GetCell(i,j)->Destroy();
			p->SetCell(i,j,new Collection());
		}
		pairs->Destroy();
		ksp_paths->Destroy();
		pairs = PairTerm(m,gsol);
	} 
	
	// Si pudo construir el grafo ok = 0 sino ok = -1
	if ((pairs->Size() != 0)&&(!Intentos(pairs,a))) ok = -1;
	else ok = 0;
	
	pairs->Destroy();
	delete a;
	delete m;
	return gsol;
}

void Greedy::DisablePathsPij(Graph * g, MatrixP * p, int i, int j)
{
	Collection * paths = p->GetCell(i,j);
	for (int i = 0; i < paths->Size(); i++)
	{
		Path * path = (Path *)paths->GetItem(i);
		DisablePath(g, path);
	}
}

void Greedy::DisablePath(Graph * g, Path * p)
{
	//Desactivo las aristas y nodos intermedios del path a borrar
	for(int i = 0; i < p->Length() - 1; i++)
	{
		int x = p->GetNode(i);
		int y = p->GetNode(i+1);
		g->DisableEdge(x,y);
		if(i > 0)
		{
			g->DisableNode(x);
		}
	}
}

Collection * Greedy::PairTerm(MatrixM * m,Graph * g)
{
	int dimension = g->GetNodesCount();
	Collection * temp = new Collection();
	for (int i= 0; i < dimension; i++)
	{
		for (int j = i+1; j < dimension; j++)
		{
			if (g->IsTerminal(i) && g->IsTerminal(j)) 
			{
				if (m->GetCell(i,j) > 0)
				{
					Pair *p = new Pair(i,j);
					temp->Add((Object *)p);
				}
			}	
		}
	}
	return temp;
}

bool Greedy::Intentos(Collection *c, MatrixA * a)
{
	int i,j;
	for (int k = 0; k < c->Size(); k++) {
		Pair * p = (Pair *)c->GetItem(k);
		i = p->GetI();
		j = p->GetJ();
		if (a->GetCell(i,j)<=MAX_ATTEMPTS) {
			return true;
		}
	}
	return false;
		
}

Pair * Greedy::Sortea(Collection * c)
{
	int sorteo = rand(); 
	int r = sorteo % c->Size();
	return (Pair *)c->GetItem(r);	
}

Path * Greedy::SorteaPath(Collection * c)
{
	if (c->Size() > 0) {
		
		int sorteo = rand(); 
		int r = sorteo % c->Size();
		return (Path *)c->GetItem(r);	
	}
	return NULL;
}

void Greedy::ActualizarCostos(Graph * gtecho,Graph * gsol)
{
	Collection * ca = gsol->GetEnabledEdges();
	for (int i = 0; i < ca->Size(); ++i)
	{
		EdgeType * e = (EdgeType *)ca->GetItem(i);
		int v1 = e->GetV1();
		int v2 = e->GetV2(); 
		if (gtecho->IsEdgeEnabled(v1,v2))
		{
			gtecho->SetEdgeCost(v1,v2,0);
		}
	}
	ca->Destroy();
}

//Retorna true si el path es disjunto a todos los path guardados en P
bool IsDisjointInP(MatrixP * p, int i, int j, Path * path)
{
	for(int m=0; m < p->GetCell(i,j)->Size(); m++)
	{
		Path * p2 = (Path *)p->GetCell(i,j)->GetItem(m);
		if(path->Length() > 2)
		{
			for(int n= 1 ; n < path->Length()-1; n++)
			{
				if(p2->Contains(path->GetNode(n)))
				{
					return false;
				}
			}
		}
		else
		{
			if(p2->Length() == 2)
			{
				return false;
			}
		}
	}
	return true;
}

void Greedy::GeneralUpdateMatrix(Graph * gsol, MatrixP * p, MatrixM * m, Path *path, int i, int j)
{
	// Agrego el nuevo camino en la matriz de caminos
	p->GetCell(i,j)->Add((Object *)path->Copy());
	m->SetCell(i,j,m->GetCell(i,j)-1);

	Collection * visitedTerminals = new Collection();
	visitedTerminals->Add((Object*)new Integer(i));

	//Por cada nodo que pertenece al path a actualizar, 
	//exepto los extremos
	for (int x = 1; x < path->Length() -1; x++) {
		
		int k = path->GetNode(x);
		
		if (gsol->IsTerminal(k)) 
		{
			for(int y = 0; y < visitedTerminals->Size(); y++)
			{
				int v = ((Integer*)visitedTerminals->GetItem(y))->GetValue();
				if (m->GetCell(v,k)>0)
				{
					Path * pathVK = path->SubPath(v,k);
					if (IsDisjointInP(p,v,k,pathVK))
					{
						// encontre un nuevo camino nodo disjunto
						p->GetCell(v,k)->Add((Object *)pathVK);
						m->SetCell(v,k,m->GetCell(v,k)-1);
					}
					else
					{
						delete pathVK;
					}
				}
			}
			
			visitedTerminals->Add((Object*)new Integer(k));

			if (m->GetCell(k,j)>0)
			{
				Path * pathKJ = path->SubPath(k,j);
				if (IsDisjointInP(p,k,j,pathKJ))
				{
					// encontre un nuevo camino nodo disjunto
					p->GetCell(k,j)->Add((Object *)pathKJ);
					m->SetCell(k,j,m->GetCell(k,j)-1);
				}
				else
				{
					delete pathKJ;
				}
			}
		}
	}
	visitedTerminals->Destroy();
}

