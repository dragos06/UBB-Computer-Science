#include "Repository.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Repository* createRepository()
{
	Repository* repo = malloc(sizeof(Repository));
	repo->arr = createDynamicArray(10, destroyMedicine, equalMedicine);
	return repo;
}


void destroyRepository(Repository* r)
{
	destroyDynamicArray(r->arr);
	free(r);
}

void addElemToRepository(Repository* r, Medicine* medicine)
{
	Medicine** medicines = getElementsDynamicArray(r->arr);
	int position = -1;
	for (int i = 0; i < getSizeDynamicArray(r->arr); i++)
		if (equalMedicine(medicines[i], medicine))
			position = i;
	if (position != -1) {
		setQuantity(medicines[position], medicines[position]->quantity + medicine->quantity);
		destroyMedicine(medicine);
	}
	else
		addElemToDyanmicArray(r->arr, medicine);
}

int deleteElemFromRepository(Repository* r, Medicine* medicine)
{
	int result = deleteElemFromDynamicArray(r->arr, medicine);
	return result;
}

int updateElemFromRepository(Repository* r, char* o_name, int o_concentration, int n_quantity, int n_price)
{
	Medicine** medicines = getElementsDynamicArray(r->arr);
	int position = -1;
	for (int i = 0; i < getSizeDynamicArray(r->arr); i++)
		if (strcmp(medicines[i]->name, o_name) == 0 && medicines[i]->concentration == o_concentration)
			position = i;
	if (position != -1) {
		setQuantity(medicines[position], n_quantity);
		setPrice(medicines[position], n_price);
		return 1;
	}
	return 0;
}

int getSizeRepository(Repository* r)
{
	return getSizeDynamicArray(r->arr);
}

Medicine* getMedicineRepository(Repository* r, char* name, int concentration)
{
	Medicine** medicines = getElementsDynamicArray(r->arr);
	for (int i = 0; i < getSizeDynamicArray(r->arr); i++) {
		if (strcmp(medicines[i]->name, name) == 0 && medicines[i]->concentration == concentration) {
			return medicines[i];
		}
	}
	return NULL;
}

Medicine** getMedicinesRepository(Repository* r)
{
	return getElementsDynamicArray(r->arr);
}

void testRepository()
{
	Repository* repo = createRepository();
	assert(getSizeRepository(repo) == 0);
	Medicine* medicine = createMedicine("Paracetamol", 10, 100, 5);
	addElemToRepository(repo, medicine);
	assert(getSizeRepository(repo) == 1);
	Medicine* medicine2 = createMedicine("Paracetamol", 10, 100, 5);
	addElemToRepository(repo, medicine2);
	assert(getSizeRepository(repo) == 1);
	Medicine* medicine3 = createMedicine("Paracetamol", 20, 100, 5);
	addElemToRepository(repo, medicine3);
	assert(getSizeRepository(repo) == 2);
	Medicine* medicine4 = createMedicine("Nurofen", 10, 100, 5);
	addElemToRepository(repo, medicine4);
	assert(getSizeRepository(repo) == 3);
	Medicine* medicine5 = createMedicine("Nurofen", 10, 100, 5);
	addElemToRepository(repo, medicine5);
	assert(getSizeRepository(repo) == 3);
	Medicine* medicine6 = createMedicine("Nurofen", 20, 100, 5);
	addElemToRepository(repo, medicine6);
	assert(getSizeRepository(repo) == 4);
	destroyRepository(repo);
}
