#include "ExtendedCut.h"

ExtendedCut::ExtendedCut() : ComponentDinArray(){
	cant = 0;
}

ExtendedCut::ExtendedCut(int n) : ComponentDinArray(n){
	cant = 0;
}

ExtendedCut::ExtendedCut(const ExtendedCut &a) : ComponentDinArray(a){
	cant = a.cant;
}

void ExtendedCut::AddItem(Component t){
	(*this)[cant++] = t;
}

void ExtendedCut::RemoveItem(Component t){
	int pos = 0;
	bool encontre = false;
	while ((pos < cant) && !encontre) {
		if (this -> operator[](pos) == t)
			encontre = true;
		else
			pos++;
	}
	if (encontre) {
		this -> operator[](pos) = this -> operator[](cant - 1);
		cant--;
	}
}

int ExtendedCut::GetSize(){
	return (cant);
}

void ExtendedCut::Order(){
	int i, j;
	for (i=0; i<=GetSize()-1; i++) {
		for (j=GetSize()-1; j>=i+1; j--) {
			if (operator[](j-1).GetType() == NODO && operator[](j).GetType() == ARISTA) {
				Component temp = operator[](j-1);
				operator[](j-1) = operator[](j);
				operator[](j) = temp;			
			}			
		}
	}
}
