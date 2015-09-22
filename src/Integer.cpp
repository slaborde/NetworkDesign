#include <iostream>
using namespace std;
#include "Integer.h"

Integer::Integer(int n)
{
	value = n;
}
Integer::~Integer()
{
}

int Integer::GetValue()
{
	return value;
}

bool Integer::Equal(Object * o)
{
	try
	{
		return this->value == ((Integer*)o)->value;
	}
	catch(...)
	{
		return false;
	}
}

void Integer::Show()
{
	cout << value;
}
