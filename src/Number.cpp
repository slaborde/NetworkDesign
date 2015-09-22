#include "Number.h"

Number::Number(double pnumber)
{
	number = pnumber;
}

Number::~Number()
{
}
double Number::GetValue()
{
	return number;
}
