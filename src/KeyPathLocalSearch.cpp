#include <iostream>
using namespace std;
#include "KeyPathLocalSearch.h"


KeyPathLocalSearch::KeyPathLocalSearch(){
	
}

KeyPathLocalSearch::~KeyPathLocalSearch(){
	
}

Graph * KeyPathLocalSearch::LocalSearchMethod(Graph * g, MatrixP *p) {
	
	return KeyPathLS(g);
	
}

//El algoritmo toma como entrada el grafo factible solucion encontrado.
//Retorna el grafo solucion optimizado mediante busqueda local basada en key-paths.
Graph* KeyPathLocalSearch::KeyPathLS(Graph *graph){
	
	//Hago una copia para trabajar en el algoritmo
	Graph * gsol = graph->Copy();
	
	bool improve = true; 
	//seteo la semilla
	srand((unsigned)time(0));
	//genero el grafo original antes de la construccion greedy
	Graph *G = gsol->Copy();
	G->EnableAll();
	Path *p, *shortest;
	int index,x,y;
	Collection *nodes;
	
	//buscamos soluciones vecinas analizando cada key-path en gsol y remplazando
	//los mismos por otro para mejorar los costos sin perder la factibilidad.
	while (improve){
		improve = false;
		//descomposicion en key-paths del grafo
		Collection *K = KeyPathDecomp(gsol);
		//genero coleccion de flags para marcar key-paths ya analizados
		Collection *analized = new Collection();
		for (int i = 0; i<K->Size(); i++)
			analized->Add((Object*) new Boolean(false));
			
		
		while (not(improve) and NotAnalizedKP(analized)){
			//sorteo key-path a analizar
			index = GetRandomIndex(analized);
			((Boolean*)analized->GetItem(index))->SetValue(true);
			//obtengo el key-path a analizar
			p = (Path*)K->GetItem(index); 
			//quito del grafo original los nodos del grafo solucion y las aristas adyacentes
			Graph *mu = G->Copy();
			Collection *enabled = gsol->GetEnabledNodes();
			mu->Rest(enabled);
			enabled->Destroy(); 
			nodes = mu->GetEnabledNodes();
			//habilito los nodos del key-path examinado y las aristas correspondientes
			for(int ind = 0; ind < p->Length(); ind++){
				mu->EnableNode(p->GetNode(ind)); 
				x = p->GetNode(ind);
				for (int j = 0; j<nodes->Size(); j++){
					y = ((Integer*)nodes->GetItem(j))->GetValue();
					if (mu->ExistEdge(x,y))
						mu->EnableEdge(x,y);
				}
			}
			nodes->Destroy();
			for(int ind = 0; ind < p->Length()-1; ind++)
				mu->EnableEdge(p->GetNode(ind),p->GetNode(ind+1));				
			//obtengo el camino mas corto entre los extremos del key-path
			shortest = Algorithms::Dijkstra(mu,p->GetNode(0),p->GetNode(p->Length()-1));
			if (shortest != NULL){
				//comparo los costos
				if((shortest->GetCost()) < (p->GetCost())){
					//quito los nodos del key-path del grafo solucion y sus aristas adyacentes, los extremos los dejo
					if (p->Length() > 2){
						for(int ind = 1; ind < p->Length()-1; ind++){
							Collection * adyacents = gsol->GetAdyacents(p->GetNode(ind));
							for (int j = 0; j < adyacents->Size(); j++)
								gsol->DisableEdge(p->GetNode(ind),((Integer*)adyacents->GetItem(j))->GetValue());
							gsol->DisableNode(p->GetNode(ind)); 
							adyacents->Destroy();
						}
					}
					else //key-path de dos nodos
						gsol->DisableEdge(p->GetNode(0),p->GetNode(1));
					//agrego los nodos del camino mas corto encontrado y las aristas de este, los extremos ya estan
					for (int ind = 0; ind < shortest->Length()-1; ind++){
						x = shortest->GetNode(ind);
						y = shortest->GetNode(ind+1);
						if (gsol->ExistEdge(x,y))
							gsol->EnableEdge(x,y);
						gsol->EnableNode(x);
						gsol->EnableNode(y); 
					}
					//encontre una mejora para el grafo solucion
					improve = true;
				}
			}
			delete shortest;
			delete mu;
		}
		analized->Destroy();
		K->Destroy();
	}
	delete G;
	return gsol;
}

//Retorna la descomposicion en key-path del grafo pasado por parametro
Collection* KeyPathLocalSearch::KeyPathDecomp(Graph *g){
	
		Graph *grafo = g->Copy();
		Collection *K = new Collection();
		//nodos que pueden ser extremos de los key-path, son terminales o key-nodes
		Collection * terminals =  g->GetTerminals();
		Collection * key_nodes = g->GetKeyNodes(true);
		Collection * end_nodes = terminals->Union(key_nodes);
		
		int node, currentNode, lastIdentifier, degree;
		bool isTerminal, isKeyNode;
		
		//para cada posible nodo extremo de key-path
		for (int i=0; i<end_nodes->Size(); i++){
			node = ((Integer*)end_nodes->GetItem(i))->GetValue();
			Collection * end_node_adyacents = grafo->GetAdyacents(node);
			//para cada adyacente al nodo extremo
			for (int j = 0; j < end_node_adyacents->Size(); j++){
				lastIdentifier = node;
				//creo el camino
				Path * aux = new Path(g);
				//agrego el extremo
				aux->Add(node);
				//calculo el nodo siguiente del camino
				currentNode = ((Integer*)end_node_adyacents->GetItem(j))->GetValue();
				degree = grafo->GetNodeDegree(currentNode);
				if (grafo->IsNodeEnabled(currentNode) && degree != 0){
					do
					{
						//agrego nodo al camino
						aux->Add(currentNode);
						Collection * adyacents = grafo->GetAdyacents(currentNode);
						//calculo si es terminal y si es key-node
						isTerminal = g->IsTerminal(currentNode);
						isKeyNode = g->IsKeyNode(currentNode);
						//si es nodo intermedio actualizo el currentNode
						if(! isTerminal && ! isKeyNode){
							if(((Integer*)adyacents->GetItem(0))->GetValue() == lastIdentifier){
								lastIdentifier = currentNode;
								currentNode = ((Integer*)adyacents->GetItem(1))->GetValue();
							}
							else{
								lastIdentifier = currentNode;
								currentNode = ((Integer*)adyacents->GetItem(0))->GetValue();
							}
						}
						adyacents->Destroy();
					}while(! isTerminal && ! isKeyNode); //mientras este en nodos intermedios
					K->Add((Object*)aux);
					//apago aristas y nodos del path, dejo prendidos los extremos
					if (aux->Length() > 2)
					{
						for (int ind=1; ind<aux->Length()-1; ind++){
							Collection *adyacents = grafo->GetAdyacents(aux->GetNode(ind));
							//apago aristas si es que existen
							for (int iter=0; iter<adyacents->Size();iter++){
								if (grafo->ExistEdge(aux->GetNode(ind),((Integer*)adyacents->GetItem(iter))->GetValue()))
									grafo->DisableEdge(aux->GetNode(ind),((Integer*)adyacents->GetItem(iter))->GetValue());
							}
							grafo->DisableNode(aux->GetNode(ind));	
							adyacents->Destroy();
						}
					}
					else //key-path de dos nodos
					{
						grafo->DisableEdge(aux->GetNode(0),aux->GetNode(1));
					}
				}
				else{
					delete aux;
				}
			}
			end_node_adyacents->Destroy();
		}
		terminals->Destroy();
		key_nodes->Destroy();
		delete end_nodes;
		delete grafo;
		return K;
}

//Corrobora si quedan key-paths por analizar, para ello examina
//las flags de la coleccion pasada por parametro.
bool KeyPathLocalSearch::NotAnalizedKP(Collection *analized){
	bool aux;
	
	for(int i = 0; i<analized->Size(); i++){
		aux = ((Boolean*)analized->GetItem(i))->GetValue();
		//queda al menos uno sin analizar
		if (aux == false)
			return true;
	}
	return false;
}

//Retorna un indice que indica el key-path a analizar.
//Pre: debe existir algun key-path sin analizar, sino queda en loop.
int KeyPathLocalSearch::GetRandomIndex(Collection *analized){
	int index;
	bool used = true;
	
	while (used){
		index = rand() % (analized->Size());
		if (((Boolean*)analized->GetItem(index))->GetValue() == false)
			used = false;
	} 
	return index;
}


