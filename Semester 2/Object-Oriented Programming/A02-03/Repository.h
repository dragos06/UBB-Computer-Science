#pragma once
#include "DynamicArray.h"

typedef struct {
	DynamicArray* arr;
}Repository;

//Creates a repository
//Returns a pointer to the repository
Repository* createRepository();

//Destroys a repository
//Input: r - pointer to the repository
void destroyRepository(Repository* r);

//Adds a medicine to the repository
//Input: r - pointer to the repository
//		 medicine - pointer to a Medicine
void addElemToRepository(Repository* r, Medicine* medicine);

//Deletes a medicine from the repository
//Input: r - pointer to the repository
//		 medicine - pointer to a Medicine
//Output: 1 if the medicine was deleted, 0 otherwise
int deleteElemFromRepository(Repository* r, Medicine* medicine);

//Updates a medicine from the repository
//Input: r - pointer to the repository
//		 o_name - pointer to a string
//		 o_concentration - integer
//		 n_quantity - integer
//		 n_price - integer
//Output: 1 if the medicine was updated, 0 otherwise
int updateElemFromRepository(Repository* r, char* o_name, int o_concentration, int n_quantity, int n_price);

//Returns the size of the repository
//Input: r - pointer to the repository
//Output: integer
int getSizeRepository(Repository* r);

//Returns the medicine from the repository
//Input: r - pointer to the repository
//		 name - pointer to a string
//		 concentration - integer
//Output: a pointer to a Medicine
Medicine* getMedicineRepository(Repository* r, char* name, int concentration);

//Returns the medicines from the repository
//Input: r - pointer to the repository
//Output: a pointer to a pointer to a Medicine
Medicine** getMedicinesRepository(Repository* r);

//Tests the repository
void testRepository();