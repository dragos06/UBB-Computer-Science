#include "Stack.h"
#include <exception>


using namespace std;


Stack::Stack() {
	//WC=BC=TC=Theta(1)
	this->capacity = 10;
	this->mapSize = 0;
	this->elements = new TElem[this->capacity];
	this->head = -1;
}


void Stack::push(TElem e) {
	//WC = Theta(n), BC = Theta(1), TC = O(n)
	if (this->mapSize == this->capacity)
		this->resize();
	this->head++;
	this->elements[head] = e;
	this->mapSize++;
}

TElem Stack::top() const {
	//WC=BC=TC=Theta(1)
	if (this->mapSize == 0)
		throw exception();
	return this->elements[head];
}

TElem Stack::pop() {
	//WC=BC=TC=Theta(1)
	if (this->mapSize == 0)
		throw exception();
	this->head--;
	this->mapSize--;
	return this->elements[head+1];
}


bool Stack::isEmpty() const {
	//WC=BC=TC=Theta(1)
	return this->mapSize == 0;
}

Stack::~Stack() {
	//WC=BC=TC=Theta(1)
	delete[] this->elements;
}

void Stack::resize(int factor)
{
	//WC=BC=TC=Theta(n)
	this->capacity *= factor;
	TElem* new_elements = new TElem[this->capacity];
	for (int i = 0; i < this->mapSize; i++)
		new_elements[i] = this->elements[i];
	delete[] this->elements;
	this->elements = new_elements;
}
