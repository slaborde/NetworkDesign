#ifndef BOOLEAN_H_
#define BOOLEAN_H_

#include "Object.h"

class Boolean : Object
{
public:
	Boolean(bool);
	bool GetValue();
	void SetValue(bool);
	bool Equal(Object*);
	void Show();
private:
	bool value;	
};

#endif /*BOOLEAN_H_*/
