#pragma once
#include "Tutorial.h"
 

template <typename TElement> 
class DynamicVector
{
private:
	TElement* elements;
	int size;
	int capacity;

public:

	//<summary>Default constructor</summary>
	//<param name="capacity">The capacity of the dynamic vector</param>
	//<returns>The dynamic vector object</returns>
	DynamicVector(int capacity = 10) {
		this->size = 0;
		this->capacity = capacity;
		this->elements = new TElement[capacity];
	}

	//<summary>Copy constructor</summary>
	//<param name="dynamic_vector">The dynamic vector object to be copied</param>
	//<returns>The copied dynamic vector object</returns>
	DynamicVector(const DynamicVector& dynamic_vector){
		this->size = dynamic_vector.size;
		this->capacity = dynamic_vector.capacity;
		this->elements = new TElement[this->capacity];
		for (int i = 0; i < this->size; i++)
			this->elements[i] = dynamic_vector.elements[i];
	}
	
	//<summary>Destructor</summary>
	~DynamicVector() {
		delete[] this->elements;
	}

	//<summary>Operator overload for the assignment operator</summary>
	//<param name="dynamic_vector">The dynamic vector object to be assigned</param>
	DynamicVector operator=(const DynamicVector& dynamic_vector) {
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

	//<summary>Operator overload for the subscript operator</summary>
	//<param name="position">The position of the element</param>
	//<returns>The element at the given position</returns>
	TElement& operator[](int position) {
		return this->elements[position];
	}

	//<summary>Adds an element to the dynamic vector</summary>
	//<param name="element">The element to be added</param>
	void add_element(TElement element) {
		if (this->size == this->capacity)
			this->resize();
		this->elements[this->size] = element;
		this->size++;
	}
	
	//<summary>Deletes an element from the dynamic vector</summary>
	//<param name="element">The element to be deleted</param>
	void delete_element(TElement element) {
		for (int i = 0; i < this->size; i++)
			if (this->elements[i] == element) {
				this->elements[i] = this->elements[this->size - 1];
				this->size--;
			}
	}

	//<summary>Getter for the size of the dynamic vector</summary>
	//<returns>The size of the dynamic vector</returns>
	int getSize() const {
		return this->size;
	}

	//<summary>Getter for the elements of the dynamic vector</summary>
	//<returns>The elements of the dynamic vector</returns>
	TElement* getElements() const {
		return this->elements;
	}

private:

	//<summary>Resizes the dynamic vector</summary>
	//<param name="factor">The factor by which the dynamic vector is resized</param>
	void resize(int factor = 2) {
		this->capacity *= factor;
		TElement* new_elements = new TElement[this->capacity];
		for (int i = 0; i < this->size; i++)
			new_elements[i] = this->elements[i];
		delete[] this->elements;
		this->elements = new_elements;
	}
};