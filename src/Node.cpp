#include "Node.h"
#include <stdio.h>
#include <iostream>
using namespace std;

Node::Node() {
	enabled = true;
	r = 1;
	terminal = false;
	posx = 0;
	posy = 0;
}

Node::Node(bool penabled, double pprobability, bool pterminal) {
	enabled = penabled;
	r = pprobability;
	terminal = pterminal;
	posx = 0;
	posy = 0;
}

Node::Node(int pposx, int pposy, bool penabled, double pprobability, bool pterminal) {
	enabled = penabled;
	r = pprobability;
	terminal = pterminal;
	posx = pposx;
	posy = pposy;
}

Node::Node(const Node &n) {
	enabled = n.enabled;
	r = n.r;
	terminal = n.terminal;
	posx = n.posx;
	posy = n.posy;
}

Node &Node::operator=(const Node &n) {
	if (&n != this) {
		terminal = n.terminal;		
	}
	return (*this);
}

Node::~Node() {

}

Node * Node::Copy()
{
	return new Node(this->posx, this->posy, this->enabled,this->r,this->terminal);
}

void Node::Enable() {
	enabled = true;
}

void Node::Disable() {
	enabled = false;
}

void Node::SetProbability(double prob) {
	r = prob;
}

void Node::MarkTerminal() {
	terminal = true;
}

void Node::MarkNoTerminal() {
	terminal = false;
}

bool Node::IsEnabled() {
	return (enabled);
}

double Node::GetProbability() {
	return (r);
}

bool Node::IsTerminal() {
	return (terminal);
}

void Node::Show() {
	cout << "confiabilidad:" << r << endl;
}

int Node::GetPosX()
{
	return posx;
}

int Node::GetPosY()
{
	return posy;
}

void Node::SetPosX(int pposx)
{
	posx = pposx;
}

void Node::SetPosY(int pposy)
{
	posy = pposy;
}
