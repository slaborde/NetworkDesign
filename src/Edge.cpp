#include "Edge.h"

#include <stdio.h>
#include <iostream>
using namespace std;


Edge::Edge() {
	enabled = true;
	r = 1.0;
	costo = 0;
}

Edge::Edge(bool hab, double prob, double cost) {
	enabled = hab;
	r = prob;
	costo = cost;
}

Edge::Edge(const Edge &a) {
	enabled = a.enabled;
	r = a.r;
	costo = a.costo;
}

Edge &Edge::operator=(const Edge &a) {
	if (&a != this) {
		enabled = a.enabled;
		r = a.r;
		costo = a.costo;
	}
	return (*this);
}

Edge::~Edge()
{
}

Edge * Edge::Copy()
{
	Edge * temp = new Edge();
	temp->costo = this->costo;
	temp->enabled = this->enabled;
	temp->r = this->r;
	return temp;
}

void Edge::Enable() {
	enabled = true;
}

void Edge::Disable() {
	enabled = false;
}

void Edge::SetProbability(double prob) {
	r = prob;
}

void Edge::SetCost(double cost)
{
	costo =cost;
}

bool Edge::IsEnabled() {
	return (enabled);
}

double Edge::GetProbability() {
	return (r);
}

double Edge::GetCost() {
	return (costo);
}

void Edge::Show() {
	cout << "Confiabilidad " << r << endl;
}

EdgeType::EdgeType(int pv1, int pv2)
{
	v1=pv1;
	v2=pv2;
}

int EdgeType::GetV1()
{
	return v1;
}

int EdgeType::GetV2()
{
	return v2;
}
bool EdgeType::Equal(Object * o)
{
	try
	{
		return (this->v1 == ((EdgeType*)o)->v1) && (this->v2 == ((EdgeType*)o)->v2);
	}
	catch(...)
	{
		return false;
	}
}

EdgeType::~EdgeType()
{
}
