#ifndef INTEGER_H_
#define INTEGER_H_
#include "Object.h"

class Integer : Object
{
public:
	Integer(int);
	virtual ~Integer();
	int GetValue();
	bool Equal(Object*);
	void Show();
private:
	int value;	
};

#endif /*INTEGER_H_*/
