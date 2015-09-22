#include "KeyTreeLocalSearch.h"

KeyTreeLocalSearch::KeyTreeLocalSearch(){
	
}
	
KeyTreeLocalSearch::~KeyTreeLocalSearch(){
	
}

Graph * KeyTreeLocalSearch::LocalSearchMethod(Graph * g, MatrixP *p) {
	
	return KeyTreeLocalSearch::KeyTreeLS(g);
	
}



/*****************Local KeyTree Search*****************************/

//Obtiene el subgrafo inducido por el conjunto de nodos finales del arbol,
//y el conjunto de nodos SGorro.
Graph * KeyTreeLocalSearch::SubGraphInducedBySGorro(Graph * g, Collection * Z, Collection * SGorro)
{
	Graph * temp = g->Copy();
	//Desactiva todo el grafo
	temp->DisableAll();
	//Activa los nodos finales del arbol
//	for(int j=0; j < Z->Size();j++)
//	{
//		int m = ((Integer*)Z->GetItem(j))->GetValue();
//		temp->EnableNode(m);
//	}
	//Activa todos los nodos de SGorro
	for(int i=0; i< SGorro->Size();i++)
	{
		int n = ((Integer*)SGorro->GetItem(i))->GetValue();
		temp->EnableNode(n);
		//Activa todas las aristas entre SGorro y Z (Conjunto de nodos finales)
		for(int j=0; j < Z->Size();j++)
		{
			int m = ((Integer*)Z->GetItem(j))->GetValue();
			if(temp->ExistEdge(n,m))
			{
				temp->EnableEdge(n,m);
			}
		}
		//Activa todas las aristas entre los elementos de SGorro
		for(int k=0; k < SGorro->Size();k++)
		{
			int m = ((Integer*)SGorro->GetItem(k))->GetValue();
			if(temp->ExistEdge(n,m))
			{
				temp->EnableEdge(n,m);
			}
		}
	}
	return temp;
}

//Busca un Arbol Sustituto de menor costo
//Si lo encuentra retorna true, 
//y realiza el cambio en el arbol pasado por parámetro.
bool KeyTreeLocalSearch::FindSubstituteKeyTree(Graph * g, int v, Collection * STecho)
{
	KeyTree * currentKeyTree = KeyTree::GetKeyTree(g,v);
	double cost = currentKeyTree->GetCost();
	Collection * Y = currentKeyTree->GetNodes();//Todos los nodos del arbol
	Collection * Z = currentKeyTree->GetEndNodes();//Nodos finales del arbol
	Collection * YMenosZ = Y->Remove(Z);
	Collection * SGorro = YMenosZ->Union(STecho);// Son los nodos del arbol, más los que no pertenecen a la solución, menos los nodos finales del arbol.
	delete currentKeyTree;
	
	Graph * HTecho = SubGraphInducedBySGorro(g,Z,SGorro);//subgrafo inducido por SGorro
	//Graph::SaveGraph("HTecho.xml",HTecho);
	delete SGorro;

	//Contruye un arbol vacio.	
	KeyTree * T = new KeyTree(g);
	
	//Por cada nodo final del arbol, busco un camino desde la raiz del arbol, hasta el nodo final
	while(Z->Size() >0)
	{
		srand((unsigned)time(0));
		int randomIndex = rand() % Z->Size();
		Integer * selected = (Integer*)Z->GetItem(randomIndex);
		int u = selected->GetValue();
		Z->Remove((Object*)selected);
		delete selected;
		HTecho->EnableNode(u);
		Path * p = Algorithms::Dijkstra(HTecho,v,u);
		//p->Show();
		//cout << endl;
		HTecho->DisableNode(u);
		p->SetGraph(g);
		T->AddKeyPath(p);
		HTecho->SetCostZero(p);
	}
	// remover todas las aristas con grado 1
	T->RemoveEdgesWithDegreeOne();
	bool improve;
	//Si el costo del arbol encontrado es menor que el actual
	if(T->GetCost() < cost)
	{
		//Actualizo el grafo solución
		//Gsol <- (GSol \ (Y\Z))U T
		g->Rest(YMenosZ);
		g->Union(T);
		improve = true;
	}
	else
	{
		improve = false;
	}
	delete HTecho;
	delete YMenosZ;
	delete T;
	Z->Destroy();
	Y->Destroy();
	return improve;
}

//Retorna todos los nodos que no pertenecen a la solución.
Collection * KeyTreeLocalSearch::GetNonSolutionNodes(Graph * g)
{
	Collection * temp = new Collection();
	for(int i=0 ;i < g->GetNodesCount();i++)
	{
		//Si el nodo no esta activado y no es terminal
		if(!g->IsNodeEnabled(i) && ! g->IsTerminal(i))
		{
			temp->Add((Object*)new Integer(i));
		}
	}
	return temp;
}

//Retorna un grafo con el óptimo local con repecto al vecindario KeyTree
Graph * KeyTreeLocalSearch::KeyTreeLS(Graph * g)
{
	bool improve = true;
	Graph * gsol = g->Copy();
	while(improve)
	{
		improve = false;
		Collection * keyNodes = gsol->GetKeyNodes(true);//Obtiene los keyNodes de la solución actual
		Collection * solutionNodes = gsol->GetEnabledNodes();//Obtiene los nodos que pertenecen a la solución.
		Collection * STecho = GetNonSolutionNodes(gsol);//Retorna los nodos que no pertenecen a la solución
		//mientras quede algún keyNode para revisar, y no se haya encontrado una mejora
		for(int i =0; i < keyNodes->Size() && ! improve ; i++)
		{
			Integer * keyNode = (Integer*) keyNodes->GetItem(i);
			improve = FindSubstituteKeyTree(gsol,keyNode->GetValue(),STecho);
			if(improve)
			{
				//Graph::SaveGraph("temp.xml",gsol);
			}
		}
		keyNodes->Destroy();
		solutionNodes->Destroy();
		STecho->Destroy();
	}
	return gsol;
}
