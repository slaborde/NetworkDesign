#if !defined(BinaryHeap_h)
#define BinaryHeap_h

#include "EmptyHeapException.h"
#include "FullHeapException.h"
#include "INumerable.h"

class BinaryHeap
{
public:
	BinaryHeap(int size);
	BinaryHeap(int size, bool isMinHeap);
	virtual ~BinaryHeap(void);
	INumerable * GetFirst();
	void Enqueue(INumerable * obj);
	INumerable * DequeueFirst(void);
	bool IsEmpty();

private:
	int param;
	INumerable ** array;
	int size;
	int count;
	bool isMinHeap;
};
#endif
