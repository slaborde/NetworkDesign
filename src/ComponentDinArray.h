//Clase para el manejo de arrays cuyo tamanio se conoce
//en tiempo de ejecucion.

#ifndef _ComponentDinArray
#define _ComponentDinArray

#include "Component.h"

class ComponentDinArray{
	public:
		ComponentDinArray();
		ComponentDinArray(int);
		ComponentDinArray(const ComponentDinArray &);
		ComponentDinArray &operator=(const ComponentDinArray &);
		~ComponentDinArray();
		int GetSize();
		Component &operator[](int);	

	private:
		Component *datos;
		int tam;
};
#endif
