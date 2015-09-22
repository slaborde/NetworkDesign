#include <iostream>
using namespace std;
#include "Boolean.h"

Boolean::Boolean(bool n)
{
	value = n;
}

bool Boolean::GetValue()
{
	return value;
}

void Boolean::SetValue(bool b){
	value = b;	
}

bool Boolean::Equal(Object * o)
{
	try
	{
		return this->value == ((Boolean*)o)->value;
	}
	catch(...)
	{
		return false;
	}
}

void Boolean::Show()
{
	cout << value;
}
