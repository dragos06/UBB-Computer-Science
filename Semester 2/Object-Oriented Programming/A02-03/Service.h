#pragma once
#include "Repository.h"

typedef int (*CompareFunction)(Medicine*, Medicine*);
typedef int (*FilterFunction)(Medicine*, int);

typedef struct {
	Repository* repository;
	DynamicArray* undoStack;
	DynamicArray* redoStack;
}Service;

//Creates a service
//Returns a pointer to the service
Service* createService();

//Destroys a service
//Input: service - pointer to the service
void destroyService(Service* service);

int compareAscending(Medicine* a, Medicine* b);
int compareDescending(Medicine* a, Medicine* b);
int filterByQuantity(Medicine* medicine, int max_quantity);
int filterByConcentration(Medicine* medicine, int max_concentration);

//Adds a medicine to the service
//Input: service - pointer to the service
//		 name - pointer to a string
//		 concentration - integer
//		 quantity - integer
//		 price - integer
void addElementToService(Service* service, char* name, int concentration, int quantity, int price);

//Deletes a medicine from the service
//Input: service - pointer to the service
//		 name - pointer to a string
//		 concentration - integer
//Output: 1 if the medicine was deleted, 0 otherwise
int deleteMedicineFromService(Service* service, char* name, int concentration);

//Updates a medicine from the service
//Input: service - pointer to the service
//		 o_name - pointer to a string
//		 o_concentration - integer
//		 n_quantity - integer
//		 n_price - integer
//Output: 1 if the medicine was updated, 0 otherwise
int updateMedicineFromService(Service* service, char* o_name, int o_concentration, int n_quantity, int n_price);

//Returns the medicines from the service
//Input: service - pointer to the service
//Output: a pointer to a pointer to a Medicine
Medicine** getMedicinesService(Service* service);

//Returns the size of the service
//Input: service - pointer to the service
//Output: integer
int getSizeService(Service* service);

//Returns the medicines that have the given string in their name
//Input: service - pointer to the service
//		 given_string - pointer to a string
//Output: a pointer to a pointer to a Medicine
Medicine** sortByString(Service* service, char given_string[], int* nr_elems, CompareFunction compare);

//Returns the medicines that have the quantity less than a given number
//Input: service - pointer to the service
//		 max_quantity - integer
//Output: a pointer to a pointer to a Medicine
Medicine** medicinesShortSupply(Service* service, int max_value, int* nr_elems, FilterFunction filter);

//Tests the service
void testService();