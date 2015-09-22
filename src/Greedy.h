#ifndef GREEDY_H_
#define GREEDY_H_

#define MAX_ATTEMPTS 5

#include "Integer.h"
#include "Pair.h"
#include "Algorithms.h"
#include "Construction.h"


class MatrixM
{
	public:
		MatrixM(Graph * g);
		virtual ~MatrixM();
		int GetCell(int i, int j);
		void SetCell(int i, int j, int);
		static MatrixM * GetMatrixM(Graph * g, MatrixP * p);
		void Show();
	private:
		int ** m;
		int size;
};

class MatrixA
{
	public:
		MatrixA(Graph * g);
		virtual ~MatrixA();
		int GetCell(int i, int j);
		void SetCell(int i, int j, int);
	private:
		int ** a;
		int size;
};

class Greedy: public Construction {
	
	public:
		Greedy();
		virtual ~Greedy();
		Graph * Construct(Graph * g, MatrixP *& p,int k,int & ok);
		static Graph * GreedyConstruction(Graph *, MatrixP *&, int , int &);
		static void DisablePath(Graph * g, Path * p);
		static void DisablePathsPij(Graph * g, MatrixP * p, int i, int j);
		static Collection * PairTerm(MatrixM *, Graph *);
		static bool Intentos(Collection *, MatrixA *);
		static Pair * Sortea(Collection *);
		static Path * SorteaPath(Collection * c);
		static void ActualizarCostos(Graph * , Graph * );
		static void GeneralUpdateMatrix(Graph *, MatrixP *, MatrixM *, Path *, int, int);
};

#endif /*GREEDY_H_*/

