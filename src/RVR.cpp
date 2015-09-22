#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#include <time.h>
#include "RVR.h"


RVR::RVR(){
	
}	

RVR::~RVR(){

}

ResultRVR RVR::ConfMethod(int sem, long reps, Graph *gsol){
	return Conf(sem,reps,gsol);	
}

//Calcula la confiabilidad de una red mediante RVR. 
//Parte de una semilla y un numero de iteraciones pasados por parametro. 
//Retorna el tiempo de referencia.
ResultRVR RVR::Conf(int sem, long reps, Graph *gsol){
	double media, var, sum, sumCuads, xi;
	
	// Setea la semilla para el generador de numeros seudo-aleatorios.
	srand(sem);
	
	sum=0.0; 
	sumCuads=0.0;	
	
	//Ejecuta reps replicaciones del calculo con la semilla sem.
	for (long i=1; i<=reps; i++){	
		Graph *G = gsol->Copy();	// Grafo auxiliar.
		G->Contract();				// Se chequea si es necesario realizar contracciones
		xi = 1 - Rvr(G);			// Valor de R en una replicacion
		sum = sum + xi;
		sumCuads = sumCuads + xi*xi;
		delete G;
	}
	media = terminales *(sum / reps);
	var = terminales * terminales * (sumCuads - sum * sum /reps)/reps/(reps-1);
	ResultRVR rAux(media, var);
	res = rAux;
		
	return (res);
}

ResultRVR RVR::GetResult(){
	return (res);
}


double RVR::Rvr(Graph * G){
		
	//Si siempre es conexo
	if (G->GetTCount() == 1)	
		return (0);
	else
		//Si no es conexo
		if (!Fi(G))				
			return (1);
		else{
			ExtendedCut d = G->GetKExtendedCut();
			//las aristas incidentes y los nodos adyacentes al nodo terminal
			//seleccionado tienen probabilidad 1
			if (d.GetSize() == 0)
				return 0;
			double qd = G->AllFailedProb(d);
			int indC = GetRandomItem(d);
			Component c = d[indC];
			Remove(G,d,indC - 1);
			Add(G,c);
			return (qd + (1.0 - qd) * Rvr(G));
		}
}

//Sortea un elemento del corte
int RVR::GetRandomItem(ExtendedCut &d){
	double acum, sorteo;
	
	sorteo = (double) rand()/RAND_MAX; //valor entre 0.0 y 1.0;
	acum = 0.0;
	for (int i=0; i<d.GetSize(); i++) {
		acum = acum + d[i].GetProb();
		if (sorteo < acum){
			return(i);
		}
	}
	return (d.GetSize() - 1);
}

//Quita n elementos del corte extendido del grafo
void RVR::Remove(Graph * G, ExtendedCut &d, int ind){
	
	for (int i=0; i<= ind; i++) {
		if (d[i].GetType() == ARISTA){
			int x, y;
			x = d[i].GetEdge().GetV1();
			y = d[i].GetEdge().GetV2();
			G->DisableEdge(x,y);
		} 
		else
			G->DisableNode(d[i].GetNode());
	}
}

//Agrega con probabilidad uno el componente parametro al grafo
void RVR::Add(Graph * G,Component c){
	int x, y, v;
	
	if (c.GetType() == ARISTA) {
		x = c.GetEdge().GetV1();
		y = c.GetEdge().GetV2();
		G->EnableEdge(x,y);
		G->SetEdgeProbability(x,y,1.0);
	} 
	else{
		v = c.GetNode();
		G->EnableNode(v);
		G->SetNodeProbability(v,1.0);
	}
	G->Contract();
}

//Chequea si la estructura esta operativa. 
//Para estar operativa deben estar operativos todos los nodos terminales y además
//existir al menos un camino entre todo par de nodos terminales.
bool RVR::Fi(Graph *G){
	int cant, tam;
	Collection *aux;
	
	cant = G->GetTerminalsCount();
	//Chequeo que esten todos los terminales activos
	if ((cant <  G->GetTCount()) || (G->GetTCount() == 0))
		return(false);
	aux = new Collection();
	mark = aux;
	tam = G->GetNodesCount();
	for (int i=0; i < tam; i++){
		mark->Add((Object*)new Boolean(false));
	}
	reached = 0;
	//Chequeo si hay al menos un camino entre todo par de nodos terminales
	Dfs(G,G->GetTerminal());
	aux->Destroy();
	return (reached == cant);
}

//Recorrida dfs para fi
void RVR::Dfs(Graph * G, int x){
	int nodo, tam;
	Collection * adyacentes;
	
	
	((Boolean*)mark->GetItem(x))->SetValue(true);
	if (G->IsTerminal(x))
		reached++;
	adyacentes = G->GetAdyacents(x);
	tam = adyacentes->Size();
	for (int i=0; i < tam; i++){
		nodo = ((Integer*)adyacentes->GetItem(i))->GetValue();
		if (!((Boolean*)mark->GetItem(nodo))->GetValue())
			Dfs(G,nodo);
	}
	adyacentes->Destroy();
}


