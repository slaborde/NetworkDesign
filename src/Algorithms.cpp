#include <iostream>
using namespace std;
#include "Algorithms.h"

DijkstraTableEntry::DijkstraTableEntry(bool pknown, double pdistance, int ppredecessor)
{
	known = pknown;
	distance = pdistance;
	predecessor = ppredecessor;
}

Ksp_record::Ksp_record() 
{
	this->camino = NULL;
	this->dp = 0;
	this->edges_removed = NULL;
}

Ksp_record::~Ksp_record()
{
	delete this->camino;
	edges_removed->Destroy();
}

//encuentra el camino menos costoso entre dos nodos de un grafo.
Path * Algorithms::Dijkstra(Graph * g,int node1, int node2)
{
	Collection * table = new Collection();
	for(int i= 0 ;i < g->GetNodesCount();i++){
		table->Add((Object*)new DijkstraTableEntry(false,9999999,9999999));
	}
	//le pongo distancia cero al nodo de comienzo
	((DijkstraTableEntry *)table->GetItem(node1))->distance = 0;

	//creo la cola vacia y le agrego el primer nodo
	BinaryHeap * heap = new BinaryHeap(g->GetNodesCount()*4);
	heap->Enqueue((INumerable *)new Association(node1,0));

	bool founded = false;
	while(!heap->IsEmpty() && !founded)
	{
		//Obtengo la primera asociación
		Association * association = (Association*)heap->DequeueFirst();
		int node = association->GetNode();

		//si el nodo es el destino, termino la busqueda
		if(node != node2){
			//si no es un nodo conocido
			if(! ((DijkstraTableEntry *)table->GetItem(node))->known)
			{
				//lo marco como conocido
				((DijkstraTableEntry *)table->GetItem(node))->known = true;
				
				//Obtengo los nodos adyacentes
				Collection * adyacents = g->GetAdyacents(node);
				//Por cada nodo adyacente
				for(int i=0 ; i < adyacents->Size(); i++)
				{
					int adyacent = ((Integer *)adyacents->GetItem(i))->GetValue();
					double d = ((DijkstraTableEntry *)table->GetItem(node))->distance + g->GetEdgeCost(node,adyacent);
					//si la distancia encontrada es menor que la guardada, actualizo la tabla
					if(((DijkstraTableEntry *)table->GetItem(adyacent))->distance > d)
					{
						((DijkstraTableEntry *)table->GetItem(adyacent))->distance = d;
						((DijkstraTableEntry *)table->GetItem(adyacent))->predecessor = node;
						heap->Enqueue((INumerable *)new Association(adyacent,d));
					}
				}
				adyacents->Destroy();
			}
		}
		else
		{
			founded = true;
			//vacio la cola para que no quede en memoria.
			while(!heap->IsEmpty())
			{
				delete (Association*)heap->DequeueFirst();
			}
		}
		delete association;
	}
	delete heap;

	//si se encontró el camino
	if(founded)
	{
		//Construye el camino
		Path * path = new Path(g);
		int lastNode = node2;
		path->Add(lastNode);
		while(lastNode != node1)
		{
			lastNode = ((DijkstraTableEntry *)table->GetItem(lastNode))->predecessor;
			path->Add(lastNode);
		}
		path->Reverse();
		table->Destroy();
		
		return path;
	}
	else
	{
		table->Destroy();
		return NULL;
	}
}

//Retorna true si el grafo es conectado
bool Algorithms::IsConnected(Graph * g)
{
	bool * visited= new bool[g->GetNodesCount()];

	//inicializo todos los nodos en false, menos los desactivados
	//para no tenerlos en cuenta
	for(int i=0; i < g->GetNodesCount(); i++)
	{
		if(g->IsNodeEnabled(i))
		{
			visited[i] = false;
		}
		else
		{
			visited[i] = true;
		}
	}

	//creo un heap, le agrego el primer nodo, y lo marco como visitado.
	BinaryHeap * heap = new BinaryHeap(g->GetNodesCount());
	heap->Enqueue((INumerable *)new Association(0,0));
	visited[0] = true;
	while(! heap->IsEmpty())
	{
		//Obtengo la primera asociación
		Association * association = (Association*)heap->DequeueFirst();
		int node = association->GetNode();
		Collection * adyacents = g->GetAdyacents(node);
		//Por cada nodo adyacente
		for(int i=0 ; i < adyacents->Size(); i++)
		{
			int adyacent = ((Integer *)adyacents->GetItem(i))->GetValue();
			//si ya no fue visitado, lo marco como visitado, 
			//y lo encolo para que posteriormente sea procesado
			if(! visited[adyacent])
			{
				visited[adyacent] = true;
				heap->Enqueue((INumerable *)new Association(adyacent,0));
			}
		}
		delete adyacents;
		delete association;
	}
	delete heap;

	//si hay algún nodo que no fué visitado retorno false
	bool connected = true;
	for(int j=0; j < g->GetNodesCount();j++)
	{
		if(! visited[j])
		{
			connected = false;
		}
	}
	delete [] visited;
	return connected;
}

Association::Association(int pnode, double pcost)
{
	node = pnode;
	cost = pcost;
}

double Association::GetValue()
{
	return cost;
}

int Association::GetNode()
{
	return node;
}

/********************** KSP **********************/

void RemoveNodes(Graph *g, Path *p)
{
	Collection * temp = p->GetNodes();
	for(int i=0;i<temp->Size();i++) {
		int node = ((Integer*)temp->GetItem(i))->GetValue();
		g->DisableNode(node);
	}
}

Collection * Copiar(Collection * c) {

	EdgeType * e;
	Collection * temp = new Collection(); 
	for (int i=0; i < c->Size(); i++) {
		e = (EdgeType *)c->GetItem(i);
		temp->Add((Object *)new EdgeType(e->GetV1(),e->GetV2()));
	}
	return temp;
}

Collection * RemoveEdges(Graph *g,Collection * e,int vik,int nvik) {
	Collection * temp = new Collection();
	EdgeType * edge;
	temp->Add((Object *)new EdgeType(vik,nvik));
	
	for (int i=0; i < e->Size(); i++) {
		edge =  (EdgeType *)e->GetItem(i);
		if (edge->GetV1() == vik) {
			temp->Add((Object *)new EdgeType(vik,edge->GetV2()));
			g->DisableEdge(vik,edge->GetV2());
		}
	}
	
	return temp;

}

int GetMenorCosto (Collection *c) {

	int pos;
	double costo,costo_aux;
	Path * p;
	
	if (c->Size() != 0) {
		pos = 0;
		p = ((Ksp_record *)c->GetItem(pos))->camino;
		costo = p->GetCost();
		for(int i=1; i < c->Size(); i++) {
			p = ((Ksp_record *)c->GetItem(i))->camino;
			costo_aux = p->GetCost();
			if (costo_aux < costo) {
				pos = i;
				costo = costo_aux; 
			}
		}
		return pos;
	}
	else return -1;
}

Collection * Algorithms::KSP(Graph * g, int s, int t, int k)
{
	// nodo del camino pk a analizar en la iteración i
	int vik;
	int nvik,bvik;
	// nodo de desviación del camino pk con respecto a los p1...pk-1 caminos ya calculados 
	int dpk;
	int kaux,pos;
	Path * p;
	// el k camino mas corto en la iteración k
	Path * pk;
	Path * subpk, * subpk_aux, * p_aux;
	// los k caminos mas cortos devueltos como solución
	Collection * ksp = new Collection();
	// los caminos mas cortos en orden de costo, de menor a mayor candidatos para ser incluidos en ksp 
	Collection * X = new Collection();
	Collection * edges = NULL, * edges_aux;
	Ksp_record * ksp_r, * ksp_r_aux;
	Graph * gtecho;
	
	// El camino mas corto entre s y t (es el primer camino que encuentro)
	p = Algorithms::Dijkstra(g,s,t);
	
	// Si no existe camino entre s y t devuelvo el camino vacio y termino
	if (p != NULL) {
		
		ksp_r = new Ksp_record();
		ksp_r->camino = p->Copy();
		delete p;
		ksp_r->dp = s;
		ksp_r->edges_removed = new Collection();
		X->Add((Object *)ksp_r);
		kaux = 0;
		
		while ((X->Size() != 0) && (kaux<k))
		{
			kaux++;
			// Obtiene el camino mas corto en X
			pos = GetMenorCosto(X);
			pk = ((Ksp_record *)X->GetItem(pos))->camino->Copy();
			dpk = ((Ksp_record *)X->GetItem(pos))->dp;
			
			// Copiar la coleccion
			edges = Copiar(((Ksp_record *)X->GetItem(pos))->edges_removed);
			
			// Quito el camino de X y lo agrego en ksp
			ksp_r_aux = (Ksp_record *)X->GetItem(pos);
			X->Remove(pos);
			ksp->Add((Object *)pk);
			delete ksp_r_aux;
			// Si ya encontre los k caminos termina el algoritmo
			if (kaux < k) {
				
				gtecho = g->Copy();
				bvik = pk->GetPreviousNode(dpk);
				//Si no estoy en el caso que dpk = s
				if (bvik != -1) {
					// Deshabilito en Gtecho los nodos desde s hasta el nodo anterior a dpk
					subpk = pk->SubPath(s,bvik);
					RemoveNodes(gtecho,subpk);
				}
				// Si dpk = s creo un camino vacio
				else subpk = new Path(gtecho);
				
				vik = dpk;
				// Itero en el camino pk
				while (vik != t) {
					
					// Deshabilito en Gtecho la arista de vik al siguiente nodo vik+1
					nvik = pk->GetNextNode(vik);
					gtecho->DisableEdge(vik,nvik);
					
					// Deshabilito en Gtecho las aristas desde vik, que fueron quitadas en el camino pk
					edges_aux = RemoveEdges(gtecho,edges,vik,nvik);
					
					// Obtengo el camino mas corto de vik a t				
					p = Algorithms::Dijkstra(gtecho,vik,t);
					if (p != NULL) {
						// Armo p concatenando el camino (s,vik-1) con al camino (vik,t) 
						subpk_aux = subpk->Copy(); 
						p_aux = subpk_aux->Concat(p);
						// libero memoria
						delete subpk_aux;
						
						// Agrego el camino candidato encontrado a X
						ksp_r = new Ksp_record();
						ksp_r->camino = p_aux->Copy();
						ksp_r->camino->SetGraph(g);
						ksp_r->dp = vik;
						ksp_r->edges_removed = Copiar(edges_aux);
						X->Add((Object *)ksp_r);
						delete p;
						delete p_aux;
					}// endif 
					// Deshabilito el nodo vik ya analizado
					gtecho->DisableNode(vik);
					// Actualizo el vik
					subpk->Add(vik);
					vik = nvik;
					edges_aux->Destroy();
				} // end 2do while 
				delete subpk;
				delete gtecho;
				edges->Destroy();
				edges = NULL; 
			} //endif
		}//end 1er while 
	}//endif 
	
	if (edges != NULL) edges->Destroy();
	X->Destroy();
	return ksp;
}

/************* FFEdge ****************/
FFEdge::FFEdge(double pcapacity){
	capacity = pcapacity;
	flow = 0;
}
FFEdge::~FFEdge()
{
}
double FFEdge::GetCapacity()
{
	return capacity;
}
double FFEdge::GetFlow()
{
	return flow;
}
void FFEdge::SetFlow(double pflow)
{
	flow = pflow;
}
/************* FFTableEntry ****************/
FFTableEntry::FFTableEntry(){
	predecessor = -1;
	plus = false;
	marked = false;
}
FFTableEntry::~FFTableEntry(){
}
bool FFTableEntry::IsMarked()
{
	return marked;
}
int FFTableEntry::GetPredecessor()
{
	return predecessor;
}
bool FFTableEntry::IsPlus()
{
	return plus;
}
double FFTableEntry::GetFullnes()
{
	return fullnes;
}
void FFTableEntry::SetPredecessor(int ppredecessor)
{
	predecessor = ppredecessor;
}
void FFTableEntry::SetPlus(bool pplus)
{
	plus = pplus;
}
void FFTableEntry::SetMarked(bool pmarked)
{
	marked = pmarked;
}
void FFTableEntry::SetFullnes(double pfullnes)
{
	fullnes = pfullnes;
}

/************* FFAsociation ****************/
FFAssociation::FFAssociation(int pnode, double pcost, double pflow)
{
	node = pnode;
	cost = pcost;
	flow = pflow;
}
FFAssociation::~FFAssociation()
{
}
double FFAssociation::GetValue()
{
	return cost;
}

int FFAssociation::GetNode()
{
	return node;
}

double FFAssociation::GetFlow()
{
	return flow;
}
/************** Ford Fulkerson Class implementation **************/
double Algorithms::FFAlgorithm(DirectedGraph * g, int x, int y)
{
	int nodesCount = g->GetNodesCount();
	//construyo un array que determina si un nodo fué visitado
	Collection * nodes = new Collection(nodesCount);
	for(int i=0; i <nodesCount; i++)
	{
		nodes->Add((Object *)new FFTableEntry());
	}
	//construye una matriz con la información de los nodos
	FFEdge *** edges = new (FFEdge(**[nodesCount]));
	for(int i=0; i < nodesCount;i++)
	{
		edges[i] = new (FFEdge(*[nodesCount]));
		for(int j=0; j < nodesCount;j++)
		{
			if(g->ExistEdge(i,j))
			{
				edges[i][j] = new FFEdge(g->GetEdgeCost(i,j));
			}
			else
			{
				edges[i][j]= NULL;
			}
		}
	}

	//mientras no se haya encontrado el corte minimal
	bool MinCutFounded = false;
	double capacity = 0;
	while(! MinCutFounded)
	{
		//creo un heap vacio para ir agregando los nodos que están para ser procesados
		BinaryHeap * heap = new BinaryHeap(nodesCount* 4);
		heap->Enqueue((INumerable *)new FFAssociation(x,0,999999));

		//Seteo todos los nodos como no marcados
		for(int i=0; i <nodesCount; i++)
		{
			((FFTableEntry*)nodes->GetItem(i))->SetMarked(false);
		}
		
	
		bool founded = false;
		//mientras queden nodos por examinar y no se haya llegado al destino
		while(!heap->IsEmpty() && !founded)
		{
			FFAssociation * association = (FFAssociation*)heap->DequeueFirst();
			int currentNode = association->GetNode();
	
			//si el nodo es el destino, termino la busqueda
			if(currentNode != y){
				//Si no está marcado
				if(! ((FFTableEntry*)nodes->GetItem(currentNode))->IsMarked())
				{
					((FFTableEntry*)nodes->GetItem(currentNode))->SetMarked(true);
					
					//Obtengo todos los nodos conectados por aristas salientes
					Collection * outAdyacents = g->GetOutAdyacents(currentNode);
					for(int i=0; i < outAdyacents->Size();i++){
						int node = ((Integer*)outAdyacents->GetItem(i))->GetValue();
						if(! ((FFTableEntry*)nodes->GetItem(node))->IsMarked())
						{
							double previousFullnes = association->GetFlow();
							double nextFullnes = edges[currentNode][node]->GetCapacity() - edges[currentNode][node]->GetFlow();
							double fullness = (previousFullnes < nextFullnes ? previousFullnes : nextFullnes);
							if(fullness > 0)
							{
								((FFTableEntry*)nodes->GetItem(node))->SetPredecessor(currentNode);
								((FFTableEntry*)nodes->GetItem(node))->SetPlus(true);
								((FFTableEntry*)nodes->GetItem(node))->SetFullnes(fullness);
								heap->Enqueue((INumerable *)new FFAssociation(node,association->GetValue()+1,fullness));
							}
						}
					}
					outAdyacents->Destroy();

					//Obtengo todos los nodos conectados por aristas salientes
					Collection * inAdyacents = g->GetInAdyacents(currentNode);
					for(int i=0; i < inAdyacents->Size();i++){
						int node = ((Integer*)inAdyacents->GetItem(i))->GetValue();
						if(! ((FFTableEntry*)nodes->GetItem(node))->IsMarked())
						{
							double backFlow = edges[node][currentNode]->GetFlow();
							if(backFlow > 0)
							{
								double previousFullnes = association->GetFlow();
								double fullness = (previousFullnes < backFlow ? previousFullnes : backFlow);
								((FFTableEntry*)nodes->GetItem(node))->SetPredecessor(currentNode);
								((FFTableEntry*)nodes->GetItem(node))->SetPlus(false);
								((FFTableEntry*)nodes->GetItem(node))->SetFullnes(fullness);
								heap->Enqueue((INumerable *)new FFAssociation(node,association->GetValue()+1,fullness));
							}
						}
					}
					inAdyacents->Destroy();
				}
			}
			else
			{
				founded = true;
				//vacio la cola para que no quede en memoria.
				while(!heap->IsEmpty())
				{
					delete (FFAssociation*)heap->DequeueFirst();
				}
			}
			delete association;
		}
		delete heap;
		if(founded)
		{
			//aumentar el flujo al grafo
			double fullnes = ((FFTableEntry*)nodes->GetItem(y))->GetFullnes();
			int nodeInit, nodeEnd = y;
			while(nodeEnd != x)
			{
				nodeInit = ((FFTableEntry*)nodes->GetItem(nodeEnd))->GetPredecessor();
				if(((FFTableEntry*)nodes->GetItem(nodeEnd))->IsPlus())
				{
					edges[nodeInit][nodeEnd]->SetFlow(edges[nodeInit][nodeEnd]->GetFlow()+fullnes);
				}
				else
				{
					edges[nodeEnd][nodeInit]->SetFlow(edges[nodeEnd][nodeInit]->GetFlow()-fullnes);
				}
				nodeEnd = nodeInit;
			}
			capacity = capacity + fullnes;
		}
		else{
			MinCutFounded = true;
		}
	}
	//Destruyo lo que sobra en memoria
	nodes->Destroy();
	for(int i=0; i < nodesCount;i++)
	{
		for(int j=0; j < nodesCount;j++)
		{
			if(edges[i][j] != NULL)
				delete edges[i][j];
		}
		delete [] edges[i];
	}
	delete [] edges;
	return capacity;
}
