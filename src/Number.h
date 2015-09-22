#ifndef NUMBER_H_
#define NUMBER_H_

#include "INumerable.h"

class Number : INumerable
{
public:
	Number(double);
	virtual ~Number();
	double GetValue();
private:
	double number;
};

#endif /*NUMBER_H_*/
