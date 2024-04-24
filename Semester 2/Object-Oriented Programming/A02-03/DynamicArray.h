#pragma once
#include "Domain.h"

typedef void* TElem;
typedef void (*DestroyFunction)(TElem);
typedef int (*EqualityFunction)(TElem, TElem);

typedef struct {
	int capacity, size;
	TElem* elems;
	DestroyFunction destroyFct;
	EqualityFunction equalityFct;
}DynamicArray;

//Creates a dynamic array
//Returns a pointer to the dynamic array
DynamicArray* createDynamicArray(int maxCap, DestroyFunction destroyFct, EqualityFunction equalityFct);

//Destroys a dynamic array
//Input: arr - pointer to the dynamic array
void destroyDynamicArray(DynamicArray* arr);

//Creates a copy of a dynamic array
//Returns a pointer to the copy of the dynamic array
DynamicArray* copyDynamicArray(DynamicArray* arr);

//Adds an element to the dynamic array
//Input: arr - pointer to the dynamic array
//		 t - pointer to a TElem
void addElemToDyanmicArray(DynamicArray* arr, TElem t);

//Deletes an element from the dynamic array
//Input: arr - pointer to the dynamic array
//		 t - pointer to a TElem
//Output: 1 if the element was deleted, 0 otherwise
int deleteElemFromDynamicArray(DynamicArray* arr, TElem t);

//Returns the element from the dynamic array at a given position
//Input: arr - pointer to the dynamic array
//		 pos - integer
//Output: a pointer to a TElem
TElem get(DynamicArray* arr, int pos);

//Deletes the element from the dynamic array at a given position
//Input: arr - pointer to the dynamic array
//		 pos - integer
void deleteElement(DynamicArray* arr, int pos);

//Returns the size of the dynamic array
//Input: arr - pointer to the dynamic array
//Output: integer representing the size of the dynamic array
int getSizeDynamicArray(DynamicArray* arr);

//Returns the capacity of the dynamic array
//Input: arr - pointer to the dynamic array
//Output: integer representing the capacity of the dynamic array
int getCapacityDynamicArray(DynamicArray* arr);

//Returns the elements of the dynamic array
//Input: arr - pointer to the dynamic array
//Output: a pointer to a TElem
TElem* getElementsDynamicArray(DynamicArray* arr);

//Tests the dynamic array
void testDynamicArray();