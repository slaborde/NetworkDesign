#include "Graph.h"

Graph::Graph(){
	nodesCount = 0;
	edgesCount = 0;
	terminalsCount = 0;
}

Graph::Graph(int cant){
	nodes = new (Node(*[cant]));
	connectionReqs = new (int(*[cant]));
	
	for(int i=0; i< cant; i++)
	{
		nodes[i]= new Node();
		connectionReqs[i] = new (int[cant]);
		
		for (int j = 0; j < cant; j++) {
			connectionReqs[i][j] = 0;
		}
	}
	edges = new Adyacence(cant);
	nodesCount = cant;
	edgesCount = 0;
	terminalsCount = 0;
}

Graph * Graph::Copy()
{
	Graph * temp = new Graph();
	temp->nodes = new (Node(*[nodesCount]));
	for(int i=0; i< nodesCount; i++)
	{
		temp->nodes[i]= this->nodes[i]->Copy();
	}
	temp->edges = edges->Copy();
	temp->edgesCount = edgesCount;
	temp->nodesCount = nodesCount;
	temp->terminalsCount = terminalsCount;
	
	// Agrego copia de la Matriz de Reqs
	temp->connectionReqs = new (int(*[nodesCount]));
	for (int i = 0; i < nodesCount; i++) {
		temp->connectionReqs[i] = new (int[nodesCount]);
		for (int j = 0; j < nodesCount; j++) {
			temp->connectionReqs[i][j] = connectionReqs[i][j]; 
		}
	}
	
	return temp;
}
Graph::~Graph(void)
{
	for(int i=0; i< nodesCount; i++)
	{
		delete nodes[i];
	}
	delete [] nodes;
	delete edges;
	for (int i = 0; i < nodesCount; i++) {
		delete [] connectionReqs[i]; 
	}
	delete [] connectionReqs;
}

int Graph::GetNodesCount() {
	return (nodesCount);
}

int Graph::GetEdgesCount() {
	return (edgesCount);
}

void Graph::Show() {
	cout << "Nodos: (hay" << nodesCount << ")" << endl ;
	for (int i=0; i<nodesCount; i++) {
		if (IsNodeEnabled(i)) {
			cout << "Nodo " << i << endl;
			nodes[i]->Show();
		}
	}
	cout << "Aristas:" << endl;
	edges->Show();
	cout << "Cantidad de terminales :" << terminalsCount << endl;
}

void Graph::EnableNode(int x) {
	nodes[x]->Enable();
} 

void Graph::DisableNode(int x) {
	nodes[x]->Disable();
}

void Graph::DisableNode(int x, bool disableAdyacentEdges) {
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

void Graph::EnableEdge(int x, int y) {
	edges->GetEdge(x,y) ->Enable();
}

void Graph::DisableEdge(int x, int y) {
	edges->GetEdge(x,y) ->Disable();
}

void Graph::AddEdge(int x, int y) {
	edgesCount++;
	edges->SetEdge(x,y, new Edge());
}

void Graph::AddEdge(int x, int y, double cost)
{
	edgesCount++;
	edges->SetEdge(x,y, new Edge(true,1.0,cost));
}

double Graph::GetNodeProbability(int x) {
	return (nodes[x]->GetProbability());
}

double Graph::GetEdgeProbability(int x, int y) {
	return (edges->GetEdge(x,y)->GetProbability());
}

double Graph::GetEdgeCost(int x, int y) {
	return (edges->GetEdge(x,y)->GetCost());
}

void Graph::SetNodeProbability(int x, double p) {
	nodes[x]->SetProbability(p);
}

void Graph::SetEdgeProbability(int x, int y, double p) {
	edges->GetEdge(x,y)->SetProbability(p); 
}

void Graph::SetEdgeCost(int x, int y, double cost)
{
	edges->GetEdge(x,y)->SetCost(cost);
}

void Graph::MarkTerminal(int x) {
	nodes[x]->MarkTerminal();
	terminalsCount++;
}

void Graph::MarkNoTerminal(int x) {
	terminalsCount--;
	nodes[x]->MarkNoTerminal();
}

bool Graph::IsTerminal(int x) {
	return (nodes[x]->IsTerminal());
}

//Retorna una colección de nodos representados por Integers.
Collection * Graph::GetAdyacents(int i) { 
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

Collection * Graph::GetTerminals() {
	Collection * result = new Collection();
	for (int i=0; i<nodesCount; i++) {
		if (IsTerminal(i))
			if (IsNodeEnabled(i))
			{
				result->Add((Object*)new Integer(i));
			}
	}
	return (result);
}


int Graph::GetTerminalsCount() {
	int i, cant = 0;
	for (i=0; i<nodesCount; i++) {
		if(IsTerminal(i))
			if (IsNodeEnabled(i))
				cant++;
	}
	return (cant);	
}

int Graph::GetTerminal() {
	for (int i=0; i<nodesCount; i++) {
		if (IsTerminal(i))
			if (IsNodeEnabled(i))
				return i;
	}
	return -1;
}

//Obtiene la colleción de los nodos de stiner
Collection * Graph::GetSteinerNodes()
{
	Collection * result = new Collection();
	for (int i=0; i<nodesCount; i++) {
		if (! IsTerminal(i))
			if (IsNodeEnabled(i))
			{
				result->Add((Object*)new Integer(i));
			}
	}
	return (result);
}

bool Graph::ExistEdge(int i, int j) {
	if (i != j)
		if (edges->GetEdge(i, j) != NULL)
			return true;
		else
			return false;
	else
		return false;
}

bool Graph::IsNodeEnabled(int x) {
	return (nodes[x]->IsEnabled());
}

bool Graph::IsEdgeEnabled(int x, int y) {
	return (edges->GetEdge(x, y)->IsEnabled());
}

int Graph::GetNodeDegree(int x) {
	Collection * adyacents = GetAdyacents(x);
	int size = adyacents->Size();
	adyacents->Destroy();
	return size;
}

void Graph::ShowEnableds() {
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

void Graph::EnableAll() {
	int i, j;
	// Habilita todos los nodos.
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
void Graph::DisableAll()
{
	int i, j;
	// Habilita todos los nodes.
	for (i=0; i<nodesCount; i++) {
		DisableNode(i);
	}
	// Habilita todas las edges.
	for (i=0; i<nodesCount; i++) {
		for (j=i+1; j<nodesCount; j++) {
			if (ExistEdge(i, j))
				DisableEdge(i, j);
		}
	}
}

void Graph::EnableAllTerminals()
{
	int i;
	for (i = 0; i < nodesCount; ++i) {
		if (IsTerminal(i)) {
			EnableNode(i);
		}
	}
}

void Graph::DisableAllTerminals()
{
	int i;
	for (i = 0; i < nodesCount; ++i) {
		if (IsTerminal(i)) {
			DisableNode(i);
		}
	}
}

Collection * Graph::GetEnabledNodes() {
	Collection * result = new Collection();
	for (int i=0; i<nodesCount; i++) {
		if (IsNodeEnabled(i))
		{
			result->Add((Object*)new Integer(i));
		}
	}
	return result;
}

Collection * Graph::GetEnabledEdges() {
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

//Obtiene el grafo resultado de aplicar la opración \ entre un grafo y un conjunto de nodos
//PRE: los elementos de la colección son de tipo "Integer"
void Graph::Rest(Collection * nodes)
{
	for(int i=0 ; i < nodes->Size(); i++)
	{
		int node =((Integer*)nodes->GetItem(i))->GetValue();
		DisableNode(node);
		for(int i=0;i < nodesCount;i++)
		{
			if(ExistEdge(i,node))
			{
				DisableEdge(i,node);
			}
		}
	}
}

void Graph::Union(KeyTree * T)
{
	Collection * edges = T->GetEdges();
	for(int i =0;i < edges->Size(); i++)
	{
		EdgeType * edge =(EdgeType*)edges->GetItem(i);
		EnableEdge(edge->GetV1(), edge->GetV2());
	}
	edges->Destroy();
	Collection * nodes = T->GetNodes();
	for(int i =0;i < nodes->Size(); i++)
	{
		Integer * node =(Integer*)nodes->GetItem(i);
		EnableNode(node->GetValue());
	}
	nodes->Destroy();
}

void Graph::Union(Path * path)
{
	int lastNode = path->GetNode(0);
	EnableNode(lastNode);
	for(int i= 1; i < path->Length();i++)
	{
		int currentNode = path->GetNode(i);
		EnableNode(currentNode);
		EnableEdge(currentNode,lastNode);
		lastNode = currentNode;
	}
}

Collection * Graph::GetKeyNodes()
{
	return GetKeyNodes(false);
}

Collection * Graph::GetKeyNodes(bool enabled)
{
	Collection * c = new Collection();
	for(int i=0;i < nodesCount;i++)
	{
		if(! enabled || IsNodeEnabled(i)){
			if(GetNodeDegree(i) != 2 && ! IsTerminal(i))
			{
				c->Add((Object*)new Integer(i));
			}
		}
	}
	return c;
}

//Elimina los costos del camino en el grafo, pero no lo desactiva
void Graph::SetCostZero(Path* path)
{
	if(path->Length() > 0)
	{
		int lastNode = path->GetNode(0);
		for(int i=1; i < path->Length();i++)
		{
			int nextNode = path->GetNode(i);
			if(ExistEdge(lastNode,nextNode))
			{
				SetEdgeCost(lastNode, nextNode, 0);
			}
			lastNode = nextNode;
		}
	}
}

int Graph::GetConnReq(int i, int j)
{
	if(i < j)
		{
			return this->connectionReqs[i][j];
		}
		else
		{
			return this->connectionReqs[j][i];
		}
}

void Graph::SetConnReq(int i, int j,int req)
{
	if(i < j)
		{
			this->connectionReqs[i][j] = req;
		}
		else
		{
			this->connectionReqs[j][i] = req;
		}
}

bool Graph::IsFactible()
{
	DirectedGraph * temp = new DirectedGraph(nodesCount * 2);
	for(int i=0; i < nodesCount;i++)
	{
		temp->AddEdge(i*2, i*2+1, 1);
		for(int j=i; j < nodesCount;j++)
		{
			if(ExistEdge(i,j)){
				if(IsEdgeEnabled(i,j))
				{
					temp->AddEdge(i*2+1, j*2, 1);
					temp->AddEdge(j*2+1, i*2, 1);
				}
			}
		}
	}
	Collection * terminals = GetTerminals();
	int terminal1,terminal2;
	for(int i=0; i < terminals->Size(); i++)
	{
		terminal1 = ((Integer*)terminals->GetItem(i))->GetValue();
		for(int j=i+1; j < terminals->Size(); j++)
		{
			terminal2 = ((Integer*)terminals->GetItem(j))->GetValue();
			int connectivityReq = connectionReqs[terminal1][terminal2];
			int connectivity = Algorithms::FFAlgorithm(temp,terminal1*2+1,terminal2*2);
			if(connectivity < connectivityReq){
				delete temp;
				terminals->Destroy();
				return false;
			}
		}
	}
	delete temp;
	terminals->Destroy();
	return true;
}

double Graph::GetCost()
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

//Convierte un grafo no dirigido a otro dirigido
DirectedGraph * Graph::ToDirectedGraph()
{
	DirectedGraph * temp = new DirectedGraph(nodesCount);
	for(int i=0; i < nodesCount;i++)
	{
		for(int j=i; j < nodesCount;j++)
		{
			if(ExistEdge(i,j)){
				temp->AddEdge(i, j, GetEdgeCost(i,j));
				temp->AddEdge(j, i, GetEdgeCost(i,j));
			}
		}
	}
	return temp;
}

bool Graph::IsKeyNode(int node){

  if (GetNodeDegree(node) > 2 && ! IsTerminal(node))
        return true;
  else 
        return false;
}

void Graph::SetX(int node, int x)
{
	this->nodes[node]->SetPosX(x);
}

void Graph::SetY(int node, int y)
{
	this->nodes[node]->SetPosY(y);
}

Graph * Graph::LoadGraph(string s)
{
	FILE  *f;
	char linea[1001];
	f = fopen(s.c_str(), "r");
	//carga el xml desde el archivo a una variable de tipo string llamada innerText.
	string innerText;
	innerText.assign("");
	do
	{
		fgets(linea, 1000, f);
		innerText.append(linea);
	}while(!feof(f));
	fclose(f);
	int lastNode = 0;
	int n,m,nodesCount =0;
	//Calcula la cantidad de nodos
	do{
		n = innerText.find("<Node>",lastNode);
		if(n != -1)
		{
			lastNode = n+14;
			nodesCount++;
		}
	}while(n != -1);
	//construyo el grafo
	Graph * temp = new Graph(nodesCount);
	lastNode = 0;
	//por cada nodo parseo el contenido
	for(int i=0; i < nodesCount ;i++)
	{
		n = innerText.find("<Node>",lastNode);
		m = innerText.find("</Node>",lastNode);
		lastNode = m+7;
		string nodeInnerText = innerText.substr(n+6,m-n-6);
		//Busca el tag IsTerminal
		n = nodeInnerText.find("<IsTerminal>",0);
		m = nodeInnerText.find("</IsTerminal>",0);
		string aux = nodeInnerText.substr(n+12,m-n-12);
		if((aux == "True") || (aux == "true")){
			temp->MarkTerminal(i);
		}
		//Busca el tag Enabled
		n = nodeInnerText.find("<Enabled>",0);
		m = nodeInnerText.find("</Enabled>",0);
		aux = nodeInnerText.substr(n+9,m-n-9);
		if(aux == "False" || aux == "false"){
			temp->DisableNode(i);
		}
		//Busca el tag R
		n = nodeInnerText.find("<R>",0);
		m = nodeInnerText.find("</R>",0);
		aux = nodeInnerText.substr(n+3,m-n-3);
		temp->SetNodeProbability(i,atof(aux.c_str()));
		//Busca el tag X
		n = nodeInnerText.find("<X>",0);
		m = nodeInnerText.find("</X>",0);
		aux = nodeInnerText.substr(n+3,m-n-3);
		temp->nodes[i]->SetPosX(atoi(aux.c_str()));
		//Busca el tag Y
		n = nodeInnerText.find("<Y>",0);
		m = nodeInnerText.find("</Y>",0);
		aux = nodeInnerText.substr(n+3,m-n-3);
		temp->nodes[i]->SetPosY(atoi(aux.c_str()));
	}
	int lastEdge = lastNode;
	do{
		n = innerText.find("<Edge>",lastEdge);
		m = innerText.find("</Edge>",lastEdge);
		if(n != -1)
		{
			lastEdge = m+7;
			string edgeInnerText = innerText.substr(n+6,m-n-6);
			n = edgeInnerText.find("<Node1Id>",0);
			m = edgeInnerText.find("</Node1Id>",0);
			int node1 = atoi(((string)edgeInnerText.substr(n+9,m-n-9)).c_str());
			n = edgeInnerText.find("<Node2Id>",0);
			m = edgeInnerText.find("</Node2Id>",0);
			int node2 = atoi(((string)edgeInnerText.substr(n+9,m-n-9)).c_str());
			temp->AddEdge(node1, node2);
			n = edgeInnerText.find("<Enabled>",0);
			m = edgeInnerText.find("</Enabled>",0);
			if(((string)edgeInnerText.substr(n+9,m-n-9)) == "False" || ((string)edgeInnerText.substr(n+9,m-n-9)) == "false")
			{
				temp->DisableEdge(node1,node2);
			}
			n = edgeInnerText.find("<Cost>",0);
			m = edgeInnerText.find("</Cost>",0);
			temp->SetEdgeCost(node1,node2,atof(((string)edgeInnerText.substr(n+6,m-n-6)).c_str()));
			n = edgeInnerText.find("<R>",0);
			m = edgeInnerText.find("</R>",0);
			temp->SetEdgeProbability(node1,node2,atof(((string)edgeInnerText.substr(n+3,m-n-3)).c_str()));
		}
	}while(n != -1);
	int lastConnectivity = lastEdge;
	temp->connectionReqs = new (int(*[temp->nodesCount]));
	for(int i=0; i<nodesCount; i++)
	{
		temp->connectionReqs[i] = new int[temp->nodesCount];
	}
	do{
		n = innerText.find("<Connectivity>",lastConnectivity);
		m = innerText.find("</Connectivity>",lastConnectivity);
		if(n != -1)
		{
			lastConnectivity = m+14;
			string connectivityInnerText = innerText.substr(n+14,m-n-14);
			n = connectivityInnerText.find("<Node1Id>",0);
			m = connectivityInnerText.find("</Node1Id>",0);
			int node1 = atoi(((string)connectivityInnerText.substr(n+9,m-n-9)).c_str());
			n = connectivityInnerText.find("<Node2Id>",0);
			m = connectivityInnerText.find("</Node2Id>",0);
			int node2 = atoi(((string)connectivityInnerText.substr(n+9,m-n-9)).c_str());
			n = connectivityInnerText.find("<Value>",0);
			m = connectivityInnerText.find("</Value>",0);
			int value = atoi(((string)connectivityInnerText.substr(n+7,m-n-7)).c_str());
			temp->connectionReqs[node1][node2]= value;
		}
	}while(n != -1);
	return temp;
}

void Graph::SaveGraph(string s,Graph * g)
{
	FILE  * f = fopen(s.c_str(), "w");
	fprintf(f,"<?xml version='1.0' ?> ");
	fprintf(f,"<Graph  xmlns='http://tempuri.org/Graph.xsd'>");
	fprintf(f,"<Nodes>");
	for(int i=0; i< g->nodesCount; i++)
	{
		fprintf(f,"<Node>");
		fprintf(f,"<NodeId>");
		fprintf(f,"%i",i);
		fprintf(f,"</NodeId>");
		fprintf(f,"<IsTerminal>");
		fprintf(f,(g->IsTerminal(i)?"True":"False"));
		fprintf(f,"</IsTerminal>");
		fprintf(f,"<Enabled>");
		fprintf(f,(g->IsNodeEnabled(i)?"True":"False"));
		fprintf(f,"</Enabled>");
		fprintf(f,"<R>");
		fprintf(f,"%f",g->GetNodeProbability(i));
		fprintf(f,"</R>");
		fprintf(f,"<X>");
		fprintf(f,"%i",g->nodes[i]->GetPosX());
		fprintf(f,"</X>");
		fprintf(f,"<Y>");
		fprintf(f,"%i",g->nodes[i]->GetPosY());
		fprintf(f,"</Y>");
		fprintf(f,"</Node>");
	}
	fprintf(f,"</Nodes>");
	fprintf(f,"<Edges>");
	for(int j=0; j< g->nodesCount; j++)
	{
		for(int k=j; k< g->nodesCount; k++)
		{
			if(g->ExistEdge(j,k))
			{
				fprintf(f,"<Edge>");
				fprintf(f,"<Node1Id>");
				fprintf(f,"%i",j);
				fprintf(f,"</Node1Id>");
				fprintf(f,"<Node2Id>");
				fprintf(f,"%i",k);
				fprintf(f,"</Node2Id>");
				fprintf(f,"<Enabled>");
				fprintf(f,(g->IsEdgeEnabled(j,k)?"True":"False"));
				fprintf(f,"</Enabled>");
				fprintf(f,"<Cost>");
				fprintf(f,"%f",g->GetEdgeCost(j,k));
				fprintf(f,"</Cost>");
				fprintf(f,"<R>");
				fprintf(f,"%f",g->GetEdgeProbability(j,k));
				fprintf(f,"</R>");
				fprintf(f,"</Edge>");
			}
		}
	}
	fprintf(f,"</Edges>");
	fprintf(f,"<Connectivities>");
	for(int j=0; j< g->nodesCount; j++)
	{
		if(g->IsTerminal(j))
		{
			for(int k=j; k< g->nodesCount; k++)
			{
				if(g->IsTerminal(k) && j!=k)
				{
					fprintf(f,"<Connectivity>");
					fprintf(f,"<Node1Id>");
					fprintf(f,"%i",j);
					fprintf(f,"</Node1Id>");
					fprintf(f,"<Node2Id>");
					fprintf(f,"%i",k);
					fprintf(f,"</Node2Id>");
					fprintf(f,"<Value>");
					fprintf(f,"%i",g->connectionReqs[j][k]);
					fprintf(f,"</Value>");
					fprintf(f,"</Connectivity>");
				}
			}
		}
	}
	fprintf(f,"</Connectivities>");
	fprintf(f,"</Graph>");
	fclose(f);
}

//Realiza las contracciones necesarias para RVR
int Graph::Contract(int x, int y){
	int node, temp;
	Collection * adyacentes;
	
	DisableEdge(x,y);
	//Si los dos son terminales se fusionan en uno solo
	if (IsTerminal(x) && IsTerminal(y))
		terminalsCount--;
	else
		if (IsTerminal(y)){
			temp = x;
			x = y;
			y = temp;
		}
	// En este punto, el nodo "y" es el no terminal (si alguno de los dos lo es)
	adyacentes = GetAdyacents(y);
	for (int i = 0; i< adyacentes->Size(); i++){
		node = ((Integer*)adyacentes->GetItem(i))->GetValue();
		if (!ExistEdge(x,node)||(ExistEdge(x,node) && !IsEdgeEnabled(x,node))){
			if (!ExistEdge(x,node))
				AddEdge(x,node); 
			SetEdgeProbability(x,node,GetEdgeProbability(y,node));
		} 
		else{
			double r1 = GetEdgeProbability(x,node);
			double r2 = GetEdgeProbability(y,node);
			SetEdgeProbability(x,node,r1 + r2 - r1 * r2);
		}
		EnableEdge(x,node);
		DisableEdge(y,node);
	}
	DisableNode(y);
	adyacentes->Destroy();
	return(x);
}

//Realiza las contracciones necesarias para RVR
void Graph::Contract(){
	int i, j, x, y;
	bool hayCambios = true;
	Collection *enabled;
	
	while (hayCambios){
		hayCambios = false;
		enabled = GetEnabledNodes();
		for (i = 0; i < enabled->Size() && !hayCambios; i++){
			for (j = i+1; j < enabled->Size() && !hayCambios; j++){
				x = ((Integer*)enabled->GetItem(i))->GetValue();
				y = ((Integer*)enabled->GetItem(j))->GetValue();  
				if (ExistEdge(x,y))
					if (IsEdgeEnabled(x,y))
						if ((GetEdgeProbability(x,y) == 1.0) && (GetNodeProbability(x) == 1.0) && (GetNodeProbability(y) == 1.0)){
							Contract(x,y);
							hayCambios = true;
						}
			}				
		}
		enabled->Destroy();			
	}
}

//Da un corte extendido
ExtendedCut Graph::GetKExtendedCut(){
	int node, n;
	
	n = GetTerminal();
	Collection* adyacentes = GetAdyacents(n);
	int grado = GetNodeDegree(n); 
	ExtendedCut result(grado * 2);
	
	for (int i=0; i < grado; i++){
		node = ((Integer*)adyacentes->GetItem(i))->GetValue();
		if (GetEdgeProbability(n,node) < 1.0)
			result.AddItem(Component(ARISTA, 0, EdgeType(n, node), 0.0));
		if (GetNodeProbability(node) < 1.0)
			result.AddItem(Component(NODO, node, EdgeType(), 0.0));
	}
	// Asigna las probabilidades para el sorteo de la componente a funcionar en el
	// corte extendido.
	double qd = AllFailedProb(result);	
	double qdComp = 1.0 - qd;
	double acum = 1.0;
	for (int i=0; i < result.GetSize(); i++){
		double qv;
		if (result[i].GetType() == ARISTA)
			qv = 1.0 - GetEdgeProbability(result[i].GetEdge().GetV1(), result[i].GetEdge().GetV2());
		else
			qv = 1.0 - GetNodeProbability(result[i].GetNode());
		result[i].SetProb((acum * (1.0 - qv)) / qdComp);
		acum = acum * qv;
	}
	adyacentes->Destroy();
	return (result);
}

//Retorna la probabilidad de que fallen todos
double Graph::AllFailedProb(ExtendedCut &d){
	
	double probFalla = 1.0;
	
	for (int i=0; i < d.GetSize(); i++){
		if (d[i].GetType() == ARISTA){
			probFalla = probFalla * (1.0 - GetEdgeProbability(d[i].GetEdge().GetV1(), d[i].GetEdge().GetV2()));
		} 
		else{
			probFalla = probFalla * (1.0 - GetNodeProbability(d[i].GetNode()));
		}
	}
	return (probFalla);
}

int Graph::GetTCount(){
	return(terminalsCount);	
}


