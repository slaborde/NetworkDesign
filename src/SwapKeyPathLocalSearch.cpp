#include "SwapKeyPathLocalSearch.h"

SwapKeyPathLocalSearch::SwapKeyPathLocalSearch(){
	
}
	
SwapKeyPathLocalSearch::~SwapKeyPathLocalSearch(){
	
}

Graph * SwapKeyPathLocalSearch::LocalSearchMethod(Graph * g, MatrixP *p) {

	return SwapKeyPathLocalSearch::SwapEdgeLS(g,p);
	
}

bool SwapKeyPathLocalSearch::FindSubstituteKeyPath(Graph * &g, Path * keyPath, MatrixP * &p)
{
	//inicializo 
	Graph * gsol = g->Copy();
	double cost = g->GetCost();
	MatrixP * psol = p->Copy();

	Greedy::DisablePath(gsol, keyPath);
	
	// Setea la semilla para el generador de numeros seudo-aleatorios.
	srand((unsigned)time(0));

	//Elimino todos los caminos de P que se intersecten con el path eliminado
	Collection * terminals = gsol->GetTerminals();
	int x,y;
	for(int i=0; i < terminals->Size(); i++)
	{
		x = ((Integer*)terminals->GetItem(i))->GetValue();
		for(int j=i+1; j < terminals->Size(); j++)
		{
			y = ((Integer*)terminals->GetItem(j))->GetValue();
			Collection * paths = psol->GetCell(x,y);
			for(int k=0;k <paths->Size(); k++)
			{
				Path * path = (Path *)paths->GetItem(k);
				//si el path se intersecta con el keyPath pasado por parámetro lo elimino de P
				if(path->Contains(keyPath))
				{
					paths->Remove((Object*)path);
					delete path;
				}
			}
		}
	}
	terminals->Destroy();
	
	MatrixA * a = new MatrixA(gsol);
	MatrixM * m = MatrixM::GetMatrixM(gsol, psol);
	
	// mientras exista un par de terminales (i,j) con mij>0
	// y el nro de intentos aij < MAX_ATTEMPT 
	Collection * pairs = Greedy::PairTerm(m,gsol);
	while ((pairs->Size() != 0) && (Greedy::Intentos(pairs,a)) && (gsol->GetCost() < cost))
	{
		// Sorteo el par i,j 
		Pair * pairij = Greedy::Sortea(pairs);
		int i = pairij->GetI();
		int j = pairij->GetJ();

		// Armo el grafo Gtecho quitando los nodos de los caminos de nodos 
		// disjuntos entre ij, para encontrar nuevos caminos
		Graph * gtecho = g->Copy();
		gtecho->EnableAll();
		Greedy::DisablePathsPij(gtecho,psol,i,j);
		Greedy::DisablePath(gtecho, keyPath);
		
		//Calculo la matriz Ctecho en Gtecho las aristas que ya estan en gsol
		// tienen costo 0 el resto su costo original
		Greedy::ActualizarCostos(gtecho,gsol);
		Path * path = Algorithms::Dijkstra(gtecho,i,j);
		delete gtecho;
		//Si encontre un camino lo agrego a Gsol y actualizo
		if (path != NULL) {
			gsol->Union(path);
			Greedy::GeneralUpdateMatrix(gsol,psol,m,path,i,j);
			delete path;
		}
		// Sino el grafo quedo disconexo, reseteo y actualizo 
		else {
			m->SetCell(i,j,g->GetConnReq(i,j));
			a->SetCell(i,j,a->GetCell(i,j)+1);
			psol->GetCell(i,j)->Destroy();
			psol->SetCell(i,j,new Collection());
		}
		pairs->Destroy();
		pairs = Greedy::PairTerm(m,gsol);
	}
	bool factible = (pairs->Size() == 0);
	pairs->Destroy();
	delete a;
	delete m;
	bool improve;
	if(factible)
	{
		if(gsol->GetCost() < cost)
		{
			delete g;
			delete p;
			g = gsol;
			p = psol;
			improve = true;
		}
		else
		{
			delete gsol;
			delete psol;
			improve = false;
		}
	}
	else
	{
		delete gsol;
		delete psol;
		improve = false;
	}
	return improve;
}

Graph * SwapKeyPathLocalSearch::SwapEdgeLS(Graph * &g, MatrixP * &p)
{
	bool improve = true;
	Graph * gsol = g->Copy();
	KeyPathLocalSearch * kpls = new KeyPathLocalSearch();
	while(improve)
	{
		improve = false;
		//armo una lista con todos los keypath's de la solución
		Collection * keyPaths = kpls->KeyPathDecomp(gsol);
		//por cada keyPath (elegido aleatoriamente)
		while(keyPaths->Size() > 0 && ! improve)
		{
			int randomIndex = rand() % keyPaths->Size();
			Path * selected = (Path*)keyPaths->GetItem(randomIndex);
			//intento quitar el keyPath y reconstruir el grafo
			improve = FindSubstituteKeyPath(gsol, selected, p);
			delete selected;
			keyPaths->Remove(randomIndex);
		}
		keyPaths->Destroy();
	}
	delete kpls;
	return gsol;
}
