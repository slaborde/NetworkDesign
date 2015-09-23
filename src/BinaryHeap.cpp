#include "BinaryHeap.h"

BinaryHeap::BinaryHeap(int psize)
{
	size = psize;
	count = 0;
	param = 100;
	isMinHeap = true;
	array = new (INumerable*[psize + 1]);
}
BinaryHeap::BinaryHeap(int psize, bool pisMinHeap)
{
	size = psize;
	count = 0;
	isMinHeap = pisMinHeap;
	array = new (INumerable*[psize + 1]);
}

BinaryHeap::~BinaryHeap(void)
{
	delete [] array;
}

//Obtiene el menor elemento del heap, pero no lo desencola
INumerable * BinaryHeap::GetFirst()
{
	if (count == 0)
	{
		throw new EmptyHeapException();
	}
	else
	{
		return array[1];
	}
}

//Encola un elemento en el heap
void BinaryHeap::Enqueue(INumerable * obj)
{
	int i;

	if (count == size)
	{
		INumerable ** temp = new (INumerable*[size * 2 +1]);
		for(int m= 1; m <= size; m++)
		{
			temp[m]=array[m];
		}
		delete[](array);
		array=temp;
		size = size * 2;
	}
	count++;

	for (i = count; i > 1 && (isMinHeap ? array[i / 2]->GetValue() > obj->GetValue() : array[i / 2]->GetValue() < obj->GetValue()); i /= 2)
	{
		array[i] = array[i / 2];
	}
	array[i] = obj;
}

//Obtiene y quita un elemento del heap
INumerable * BinaryHeap::DequeueFirst(void)
{
	int i;

	if (count == 0)
	{
		throw new EmptyHeapException();
	}
	INumerable * comparableObject1 = array[1];
	INumerable * comparableObject2 = array[count];
	count--;
	int j;

	for (i = 1; 2 * i < count + 1; i = j)
	{
		j = 2 * i;
		if (j + 1 < count + 1 && (isMinHeap ? array[j + 1]->GetValue() < array[j]->GetValue():array[j + 1]->GetValue() > array[j]->GetValue()))
		{
			j++;
		}
		double value2 = comparableObject2->GetValue();
		double valuej = array[j]->GetValue();
		if ((isMinHeap ? comparableObject2->GetValue() <= array[j]->GetValue():comparableObject2->GetValue() >= array[j]->GetValue()))
		{
			break;
		}
		array[i] = array[j];
	}
	array[i] = comparableObject2;
	return comparableObject1;
}

bool BinaryHeap::IsEmpty()
{
	return (count == 0);
}
