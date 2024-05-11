#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;


Queue::Queue() {
	//WC=BC=TC=Theta(1)
	this->capacity = 10;
	this->mapSize = 0;
	this->elements = new TElem[this->capacity];
	this->front = 0;
	this->rear = 0;
}


void Queue::push(TElem elem) {
	//WC = Theta(n), BC = Theta(1), TC = O(n)
	if (this->mapSize == this->capacity)
		this->resize();
	if (this->rear == this->capacity - 1) {
		this->rear = 0;
		this->elements[rear] = elem;
		this->mapSize++;
	}
	else
		if (this->mapSize == 0) {
			this->elements[0] = elem;
			this->mapSize++;
			this->front = 0;
			this->rear = 0;
		}
		else {
			this->rear++;
			this->elements[rear] = elem;
			this->mapSize++;
		}
}


TElem Queue::top() const {
	//WC=BC=TC=Theta(1)
	if (this->mapSize == 0)
		throw exception();
	return this->elements[front];
}

TElem Queue::pop() {
	//WC=BC=TC=Theta(1)
	if (this->mapSize == 0)
		throw exception();
	//if (this->mapSize == this->capacity)
		//this->resize();
	if (this->front == this->capacity - 1) {
		this->front = 0;
		this->mapSize--;
		return this->elements[this->capacity - 1];
	}
	this->front++;
	this->mapSize--;
	return this->elements[front - 1];
}

bool Queue::isEmpty() const {
	//WC=BC=TC=Theta(1)
	return this->mapSize == 0;
}


Queue::~Queue() {
	//WC=BC=TC=Theta(1)
	delete[] this->elements;
}

void Queue::resize(int factor)
{
	/*if (this->front != 0) {
		int counter = this->front;
		while (counter) {
			TElem aux = this->elements[0];
			for (int i = 1; i<this->mapSize ; i++)
				this->elements[i - 1] = this->elements[i];
			this->elements[this->mapSize - 1] = aux;
			counter--;
		}
		this->front = 0;
		this->rear = this->mapSize-1;
	}
	this->capacity *= factor;
	TElem* new_elements = new TElem[this->capacity];
	for (int i = 0; i < this->mapSize; i++)
		new_elements[i] = this->elements[i];
	delete[] this->elements;
	this->elements = new_elements;*/
	
	//WC=BC=TC=Theta(n)
	int new_capacity = this->capacity * factor;
	TElem* new_elements = new TElem[new_capacity];
	int k = 0;
	for (int i = front; i != rear; i = (i + 1) % capacity) {
		new_elements[k++] = this->elements[i];
	}
	new_elements[k] = this->elements[rear];
	this->front = 0;
	this->rear = k;

	delete[] this->elements;
	this->elements = new_elements;
	this->capacity = new_capacity;
}

TElem Queue::getMiddle() const
{
	//WC=BC=TC=Theta(1)
	if (this->mapSize == 0)
		throw exception();

	//int nr_elems = this->mapSize;
	//for (int i = front; i != rear; i = (i + 1) % capacity) {
	//	nr_elems--;
	//	if (nr_elems == this->mapSize / 2)
	//		return this->elements[i];
	//}


	return this->elements[(this->front + this->mapSize / 2) % this->capacity];
}

