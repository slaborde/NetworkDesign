#ifndef PAIR_H_
#define PAIR_H_

#include "Object.h"

class Pair: Object {
	
	public:
		
		Pair(int,int);
		virtual ~Pair(void);
		int GetI();
		int GetJ();
		void SetI(int);
		void SetJ(int);
		
	private:
		
		int i,j;
};

#endif /*PAIR_H_*/
