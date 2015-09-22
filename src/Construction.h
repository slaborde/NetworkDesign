#ifndef CONSTRUCTION_H_
#define CONSTRUCTION_H_

#include "Graph.h"

class MatrixP {
	public:
		MatrixP();
		MatrixP(Graph * g);
		virtual ~MatrixP();
		MatrixP * Copy();
		Collection * GetCell(int i, int j);
		void SetCell(int i, int j, Collection * c);
		void Show();
	private:
		Collection *** p;
		int size;
};

//Esta clase representa una interfaz para objetos de tipo Busqueda Local
class Construction {
	public:
		virtual Graph * Construct(Graph * g, MatrixP *& p, int k, int & ok)=0;
};

#endif /*CONSTRUCTION_H_*/
