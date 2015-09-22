//Clase para el manejo de cortes extendidos (cortes formados por nodos y aristas)

#ifndef _ExtendedCut
#define _ExtendedCut

#include "ComponentDinArray.h"
#include "Component.h"

class ExtendedCut : public ComponentDinArray{
	public:
		ExtendedCut();
		ExtendedCut(int);
		ExtendedCut(const ExtendedCut &);
		void AddItem(Component);
		void RemoveItem(Component);
		int GetSize();
		void Order();
	private:
		int cant;
};

#endif
