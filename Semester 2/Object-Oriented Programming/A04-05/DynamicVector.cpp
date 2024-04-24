/*#include "DynamicVector.h"

DynamicVector::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elements = new TElement[capacity];
}

DynamicVector::DynamicVector(const DynamicVector& dynamic_vector)
{
	this->size = dynamic_vector.size;
	this->capacity = dynamic_vector.capacity;
	this->elements = new TElement[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = dynamic_vector.elements[i];
}

DynamicVector::~DynamicVector()
{
	delete[] this->elements;
}

DynamicVector& DynamicVector::operator=(const DynamicVector& dynamic_vector)
{
	if (this == &dynamic_vector)
		return *this;

	this->size = dynamic_vector.size;
	this->capacity = dynamic_vector.capacity;

	delete[] this->elements;
	this->elements = new TElement[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = dynamic_vector.elements[i];
	return *this;
}

TElement& DynamicVector::operator[](int position)
{
	return this->elements[position];
}


void DynamicVector::add_element(TElement element)
{
	if (this->size == this->capacity)
		this->resize();
	this->elements[this->size] = element;
	this->size++;
}

void DynamicVector::delete_element(TElement element)
{
	for (int i = 0; i < this->size; i++)
		if (this->elements[i] == element) {
			this->elements[i] = this->elements[this->size - 1];
			this->size--;
		}
}

int DynamicVector::getSize() const
{
	return this->size;
}

TElement* DynamicVector::getElements() const
{
	return this->elements;
}

void DynamicVector::resize(int factor)
{
	this->capacity *= factor;
	TElement* new_elements = new TElement[this->capacity];
	for (int i = 0; i < this->size; i++)
		new_elements[i] = this->elements[i];
	delete[] this->elements;
	this->elements = new_elements;
}
*/