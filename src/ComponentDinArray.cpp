#include "ComponentDinArray.h"
#include <stdio.h>

ComponentDinArray::ComponentDinArray() {
	datos = NULL;
	tam = 0;
}

ComponentDinArray::ComponentDinArray(int n) {
	datos = new Component[n];
	tam = n;
}

ComponentDinArray::ComponentDinArray(const ComponentDinArray &a) {
	tam = a.tam;
	datos = new Component[tam];
	for (int i=0; i<tam; i++) {
		datos[i] = a.datos[i];
	}
}

ComponentDinArray &ComponentDinArray::operator=(const ComponentDinArray &a) {
	if (&a != this) {
		if (datos != NULL) {
			delete [] datos;				
		}
		tam = a.tam;
		datos = new Component[tam];
		for (int i=0; i<tam; i++) {
			datos[i] = a.datos[i];
		}		
	}
	return (*this);
}

ComponentDinArray::~ComponentDinArray() {
	if (datos != NULL) {
		delete [] datos;				
	}
}

int ComponentDinArray::GetSize() {
	return (tam);
}

Component &ComponentDinArray::operator[](int i) {
	return (datos[i]);
}
