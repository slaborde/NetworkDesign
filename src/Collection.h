#if !defined(Collection_h)
#define Collection_h

#include <stdlib.h>
#include "Object.h"

class Collection{
	private:
		int param;
		int cantElem;
		Object ** array;
	public:
		Collection();
		Collection(int);
		Collection(const Collection *);
		//Elimina la collecci�n pero no los elemento de la colecci�n
		virtual ~Collection();
		//Elimina la colecci�n y todo el contenido que hay en ella, pero no el objeto collecci�n
		void Destroy();
		int Size();
		//Obtiene el elemento que se encuentra en la posici�n indicada
		Object * GetItem(int);
		void Add(Object*);
		//Invierte el orden de los items de la colecci�n
		void Reverse();
		bool Contains(Object*);
		void Remove(int);
		void Remove(Object*);
		Collection* Remove(Collection*);
		Collection* Union(Collection*);
		Collection* Intersection(Collection*);
		bool IsDisjoint(Collection*);
		void Show();
		
		int IndexOf(Object * o);
		Collection * Concat(Collection *);
};
#endif
