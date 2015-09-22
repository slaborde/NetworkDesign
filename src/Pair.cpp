#include "Pair.h"

Pair::Pair(int k,int l)
{
	i = k;
	j = l;
}

Pair::~Pair(void)
{}

int Pair::GetI()
{
	return i;
}

int Pair::GetJ()
{
	return j;
}

void Pair::SetI(int i)
{
	this->i=i;
}

void Pair::SetJ(int j)
{
	this->j=j;
}

