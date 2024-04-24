#include "DynamicArray.h"
#include <stdlib.h>
#include <assert.h>

DynamicArray* createDynamicArray(int maxCap, DestroyFunction destroyFct, EqualityFunction equalityFct)
{
	DynamicArray* arr = malloc(sizeof(DynamicArray));
	if (arr == NULL)
		return NULL;
	arr->capacity = maxCap;
	arr->size = 0;

	arr->elems = malloc(maxCap * sizeof(TElem));
	if (arr->elems == NULL) {
		free(arr);
		return NULL;
	}
	arr->destroyFct = destroyFct;
	arr->equalityFct = equalityFct;
	return arr;
}

void destroyDynamicArray(DynamicArray* arr)
{
	if (arr == NULL)
		return;
	for (int i = 0; i < arr->size; i++)
		arr->destroyFct(arr->elems[i]);
	free(arr->elems);
	free(arr);
}

void resize(DynamicArray* arr) {
	if (arr == NULL)
		return;
	if (arr->elems == NULL)
		return;
	arr->capacity *= 2;
	TElem* aux = realloc(arr->elems, arr->capacity * sizeof(TElem));
	if (aux == NULL)
		return;
	arr->elems = aux;
}

void addElemToDyanmicArray(DynamicArray* arr, TElem t)
{
	if (arr == NULL)
		return;
	if (arr->elems == NULL)
		return;
	if (arr->capacity == arr->size)
		resize(arr);
	arr->elems[arr->size++] = t;
}

int deleteElemFromDynamicArray(DynamicArray* arr, TElem t)
{
	if (arr == NULL)
		return 0;
	if (arr->elems == NULL)
		return 0;
	int pos = -1;
	for (int i = 0; i < arr->size; i++) {
		if (arr->equalityFct(arr->elems[i], t)) {
			pos = i;
		}
	}
	if (pos == -1) {
		return 0;
	}
	arr->destroyFct(arr->elems[pos]);
	for (int i = pos; i < arr->size - 1; i++) {
		arr->elems[i] = arr->elems[i + 1];
	}
	arr->size--;
	return 1;
}

int getCapacity(DynamicArray* arr)
{
	if (arr == NULL)
		return 0;
	return arr->size;
}

DynamicArray* copyDynamicArray(DynamicArray* arr) {
	DynamicArray* copy = createDynamicArray(arr->capacity, destroyMedicine, equalMedicine);
	copy->size = arr->size;
	for (int i = 0; i < arr->size; i++) {
		copy->elems[i] = copyMedicine(arr->elems[i]);
	}
	return copy;
}

TElem get(DynamicArray* arr, int pos)
{
	if (arr == NULL)
		return NULL;
	if (pos < 0 || pos >= arr->size)
		return NULL;
	return arr->elems[pos];
}

void deleteElement(DynamicArray* arr, int pos)
{
	if (arr == NULL)
		return;
	if (pos < 0 || pos >= arr->size)
		return;
	arr->destroyFct(arr->elems[pos]);
	for (int i = pos; i < arr->size - 1; i++)
		arr->elems[i] = arr->elems[i + 1];
	arr->size--;
}

int getSizeDynamicArray(DynamicArray* arr)
{
	if (arr == NULL)
		return 0;
	return arr->size;
}

int getCapacityDynamicArray(DynamicArray* arr)
{
	if (arr == NULL)
		return 0;
	return arr->capacity;
}

TElem* getElementsDynamicArray(DynamicArray* arr)
{
	if (arr == NULL)
		return NULL;
	if (arr->elems == NULL)
		return NULL;
	return arr->elems;
}

void testDynamicArray()
{
	DynamicArray* arr = createDynamicArray(2, destroyMedicine, equalMedicine);
	Medicine* m1 = createMedicine("Nurofen", 200, 10, 15);
	Medicine* m2 = createMedicine("Paracetamol", 100, 20, 10);
	Medicine* m3 = createMedicine("Aspirin", 300, 5, 20);
	addElemToDyanmicArray(arr, m1);
	addElemToDyanmicArray(arr, m2);
	addElemToDyanmicArray(arr, m3);
	assert(getSizeDynamicArray(arr) == 3);
	assert(getCapacityDynamicArray(arr) == 4);
	assert(get(arr, 0) == m1);
	assert(get(arr, 1) == m2);
	assert(get(arr, 2) == m3);
	deleteElement(arr, 1);
	assert(getSizeDynamicArray(arr) == 2);
	assert(get(arr, 0) == m1);
	assert(get(arr, 1) == m3);
	destroyDynamicArray(arr);
}
