//Matriz de adyacencia del grafo.

#ifndef ADYACENCIA_H_
#define ADYACENCIA_H_

#include "Edge.h"

class Adyacence{
	public:
		Adyacence(void);
		Adyacence(int);
		//Crea una copia de la matriz de adyacencia
		Adyacence * Copy();
		//Adyacence &operator=(const Adyacence &);
		virtual ~Adyacence();
		//Obtiene la arista en las coordenadas x y de la matriz de adyacencia
		Edge * GetEdge(int, int);
		void SetEdge(int i, int j, Edge * edge);
		void Show();

	private:
		Edge *** edges;//son tres asteriscos porque: dos son porque es una matriz cuadrada, y el tercero porque cada elemento de la matriz es un puntero a una arista.
		int dimension;
};

#endif /*ADYACENCIA_H_*/
