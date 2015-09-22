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
		//Elimina la collección pero no los elemento de la colección
		virtual ~Collection();
		//Elimina la colección y todo el contenido que hay en ella, pero no el objeto collección
		void Destroy();
		int Size();
		//Obtiene el elemento que se encuentra en la posición indicada
		Object * GetItem(int);
		void Add(Object*);
		//Invierte el orden de los items de la colección
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
