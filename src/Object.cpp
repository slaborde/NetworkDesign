#include "Object.h"
#include <string>

bool Object::Equal(Object* o)
{
	return &(*this) == &(*o);
}
void Object::Show()
{
}

Object::~Object()
{
}
