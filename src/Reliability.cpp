#include "Reliability.h"


//Configura para calcular Rst, probabilidad de existencia de por lo menos
//un camino entre los nodos s y t
void Reliability::SetForRst(int s, int t, Graph * g){
	terminales = g->GetNodeProbability(s) * g->GetNodeProbability(t);
	g->SetNodeProbability(s,1.0);
	g->SetNodeProbability(t,1.0);
}

//Configura para calcular Rk, probabilidad de existencia de por lo menos
//un camino entre todo par de nodos del subconjunto K (nodos terminales)
void Reliability::SetForRk(Graph * g){
	Collection * terms = g->GetTerminals();
	int nodo; 
	
	terminales = 1.0;
	for (int i = 0; i < terms->Size(); i++){
		nodo = ((Integer*)terms->GetItem(i))->GetValue();
		terminales = terminales * g->GetNodeProbability(nodo);	
		g->SetNodeProbability(nodo,1.0);
	}
}

//Configura para calcular Rv, probabilidad de existencia de por lo menos
//un camino entre todo par de nodos del grafo
void Reliability::SetForRv(Graph * g){
	Collection * enabled = g->GetEnabledNodes();
	int nodo; 
	
	terminales = 1.0;
	for (int i = 0; i < enabled->Size(); i++){
		nodo = ((Integer*)enabled->GetItem(i))->GetValue();
		terminales = terminales * g->GetNodeProbability(nodo);	
		g->SetNodeProbability(nodo,1.0);
	}
}

