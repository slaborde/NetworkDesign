#include <iostream>
using namespace std;
#include "Component.h"


Component::Component(){
	

}

Component::Component(ComponentType t, int n, EdgeType a, double p){
	tipo = t;
	nodo = n;
	arista = a;
	prob = p;
}

ComponentType Component::GetType() {
	return (tipo);
}

int Component::GetNode() {
	return (nodo);
}

EdgeType Component::GetEdge() {
	return (arista);
}

bool Component::operator==(Component c) {
	if (tipo == c.tipo)
		if (tipo == ARISTA)
			return ((arista.GetV1()==c.arista.GetV1())&&(arista.GetV2()==c.arista.GetV2()));
		else
			return (nodo == c.nodo);
	else
		return (false);
}

void Component::SetProb(double p) {
	prob = p;
}

double Component::GetProb() {
	return (prob);
}

void Component::Show() {
	if (tipo == ARISTA)
		cout << "Componente es la arista " << arista.GetV1() << " , " << arista.GetV2() << endl; 
	else
		cout << "Componente es el nodo " << nodo << endl; 
}

