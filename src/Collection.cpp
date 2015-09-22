#include "Collection.h"
#include <iostream>
using namespace std;

Collection::Collection(){
         param =10;
         cantElem=0;
         array=NULL;
}

Collection::Collection(int n){
         param =n;
         cantElem=0;
         array=NULL;
}

Collection::Collection(const Collection *c)
{
         param = c->param;
         cantElem = c->cantElem;
         array = new Object*[cantElem]; 
         for (int i=0;i<c->cantElem;i++) {
         	array[i] = c->array[i];	
         }
}


Collection::~Collection(){
	if(array!=NULL){
		delete[]array;
	}
}

void Collection::Destroy()
{
	if(array!=NULL){
		for(int i=0;i <cantElem ;i++)
		{
			if(array[i] != NULL)
			{
				delete array[i];
			}
		}
		delete[](array);
		array = NULL;
		cantElem = 0;
	}
	delete this;
}

int Collection::Size(){
	return cantElem;
}

Object * Collection::GetItem(int n){
	return array[n];
}

void Collection::Add(Object* o){
     if((cantElem % param)==0){
          int i;
          Object ** temp;
          temp=new Object*[cantElem + param];
          for(i=0;i<cantElem;i++){
                temp[i]=array[i];
          }
          delete[](array);
          array=temp;
     }
     array[cantElem]=o;
     cantElem++;
}

void Collection::Reverse()
{
	for(int i= 0 ;i < cantElem / 2; i++)
	{
		Object * aux = array[i];
		array[i] = array[cantElem - i - 1];
		array[cantElem - i - 1] = aux;
	}
}

bool Collection::Contains(Object* o)
{
	int i=0;
	for(i=0;i<cantElem;i++)
	{
		if(array[i]->Equal(o)){
			return true;
		}
	}
	return false;
}

void Collection::Remove(int position){
	cantElem--;
	for(int j=position;j<cantElem;j++){
		array[j]=array[j+1];
	}
}

void Collection::Remove(Object * o){
	int i=0;
	for(i=0;i<cantElem;i++)
	{
		if(array[i]->Equal(o)){
			cantElem--;
			for(int j=i;j<cantElem;j++){
				array[j]=array[j+1];
			}
			break;
		}
	}
}

Collection* Collection::Remove(Collection * c)
{
	Collection * temp= new Collection();
	temp->array = new Object*[cantElem];
	temp->cantElem = cantElem;
	for(int i=0;i<cantElem;i++)
	{
		temp->array[i]=this->array[i];
	}
	for(int i=0;i<c->cantElem;i++)
	{
		temp->Remove(c->array[i]);
	}
	return temp;
}

Collection* Collection::Union(Collection * c)
{
	Collection * temp= new Collection();
	for(int i=0;i<cantElem;i++)
	{
		temp->Add(this->array[i]);
	}
	for(int i=0; i < c->cantElem;i++)
	{
		if(! temp->Contains(c->array[i]))
		{
			temp->Add(c->array[i]);
		}
	}
	return temp;
}

Collection* Collection::Intersection(Collection * c)
{
	Collection * temp= new Collection();
	
	if (c->Size()<cantElem) {
		
		for(int i=0;i<c->Size();i++)
		{
			if (this->Contains(c->array[i])) {
				temp->Add(c->array[i]);	
			}
			
		}
	}
	else {
		
		for(int i=0;i<cantElem;i++)
		{
			if (c->Contains(this->array[i])) {
				temp->Add(this->array[i]);	
			}
		}
	}
	return temp;
}

bool Collection::IsDisjoint(Collection * c)
{
	if (c->Size()<cantElem) {
		
		for(int i=0;i<c->Size();i++)
		{
			if (this->Contains(c->array[i])) {
				return false;
			}
			
		}
	}
	else {
		
		for(int i=0;i<cantElem;i++)
		{
			if (c->Contains(this->array[i])) {
				return false;
			}
		}
	}
	return true;
}

void Collection::Show(){
	cout << "[";
	if(cantElem > 0)
	{
		array[0]->Show();
	}
	for(int i=1; i < cantElem;i++)
	{
		cout << ",";
		array[i]->Show();
	}
	cout << "]";
}

int Collection::IndexOf(Object * o)
{
	for(int i=0;i<cantElem;i++) {
		if(array[i]->Equal(o)){
			return i;
		}
	}
	return -1;	
}

Collection * Collection::Concat(Collection * c)
{
	Collection * temp= new Collection();
	for(int i=0;i<cantElem;i++)
	{
		temp->Add(this->array[i]);
	}
	for(int i=0; i < c->cantElem;i++)
	{
		temp->Add(c->array[i]);
	}
	return temp;
}
