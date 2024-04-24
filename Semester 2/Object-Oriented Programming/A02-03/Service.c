#include "Service.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
	

Service* createService()
{
	Service* service = malloc(sizeof(Service));
	Repository* repository = createRepository();
	service->undoStack = createDynamicArray(10, destroyDynamicArray, NULL);
	service->redoStack = createDynamicArray(10, destroyDynamicArray, NULL);
	service->repository = repository;
	return service;
}

void destroyService(Service* service)
{
	destroyDynamicArray(service->undoStack);
	destroyDynamicArray(service->redoStack);

	destroyRepository(service->repository);
	free(service);
}

int compareAscending(Medicine* a, Medicine* b) {
	return strcmp(a->name, b->name);
}

int compareDescending(Medicine* a, Medicine* b) {
	return strcmp(b->name, a->name);
}

int filterByQuantity(Medicine* medicine, int max_quantity) {
	return medicine->quantity < max_quantity;
}

int filterByConcentration(Medicine* medicine, int max_concentration) {
	return medicine->concentration < max_concentration;
}

void addElementToService(Service* service, char* name, int concentration, int quantity, int price)
{
	addElemToDyanmicArray(service->undoStack, copyDynamicArray(service->repository->arr));
	Medicine* medicine = createMedicine(name, concentration, quantity, price);
	addElemToRepository(service->repository, medicine);
	//addElemToDyanmicArray(service->redoStack, copyDynamicArray(service->repository->arr));
}

int deleteMedicineFromService(Service* service, char* name, int concentration)
{
	Medicine* medicine = getMedicineRepository(service->repository, name, concentration);
	if (medicine == NULL)
		return 0;
	addElemToDyanmicArray(service->undoStack, copyDynamicArray(service->repository->arr));
	int result = deleteElemFromRepository(service->repository, medicine);
	//destroyMedicine(medicine);
	//addElemToDyanmicArray(service->redoStack, copyDynamicArray(service->repository->arr));
	return result;
}

int updateMedicineFromService(Service* service, char* o_name, int o_concentration, int n_quantity, int n_price)
{
	Medicine* medicine = getMedicineRepository(service->repository, o_name, o_concentration);
	if (medicine == NULL)
		return 0;
	addElemToDyanmicArray(service->undoStack, copyDynamicArray(service->repository->arr));
	int result = updateElemFromRepository(service->repository, o_name, o_concentration, n_quantity, n_price);
	//addElemToDyanmicArray(service->redoStack, copyDynamicArray(service->repository->arr));
	return result;
}

Medicine** getMedicinesService(Service* service)
{
	return getMedicinesRepository(service->repository);
}

int getSizeService(Service* service)
{
	return getSizeRepository(service->repository);
}

Medicine** sortByString(Service* service, char given_string[], int* nr_elems, CompareFunction compare)
{
	*nr_elems = 0;
	Medicine* aux;
	Medicine** medicines = getMedicinesRepository(service->repository);
	for (int i = 0; i < getSizeRepository(service->repository) - 1; i++)
		for (int j = i + 1; j < getSizeRepository(service->repository); j++)
			//if (strcmp(medicines[i]->name, medicines[j]->name) > 0)
			if (compare(medicines[i], medicines[j]) > 0)
				aux = medicines[i], medicines[i] = medicines[j], medicines[j] = aux;
	if (strlen(given_string) == 0){
		*nr_elems = getSizeRepository(service->repository);
		Medicine** good_list = malloc(sizeof(Medicine*) * (*nr_elems));
		int k = 0;
		for (int i = 0; i < getSizeRepository(service->repository); i++) {
			good_list[k] = medicines[i];
			k++;
		}
		return good_list;
	}
	else {
		for (int i = 0; i < getSizeRepository(service->repository); i++)
			if (strstr(medicines[i]->name, given_string))
				(*nr_elems)++;
		int k = 0;
		Medicine** good_list = malloc(sizeof(Medicine*) * (*nr_elems));
		for (int i = 0; i < getSizeRepository(service->repository); i++)
			if (strstr(medicines[i]->name, given_string))
			{
				good_list[k] = medicines[i];
				k++;
			}
		return good_list;
	}
	return;
}

Medicine** medicinesShortSupply(Service* service, int max_value, int* nr_elems, FilterFunction filter)
{
	*nr_elems = 0;
	Medicine** medicines = getMedicinesRepository(service->repository);
	for (int i = 0; i < getSizeRepository(service->repository); i++)
		//if (medicines[i]->quantity < max_quantity)
		if (filter(medicines[i], max_value))
			(*nr_elems)++;
	int k = 0;
	Medicine** good_list = malloc(sizeof(Medicine*) * (*nr_elems));
	for (int i = 0; i < getSizeRepository(service->repository); i++)
		//if (medicines[i]->quantity < max_value)
		if (filter(medicines[i], max_value))
		{
			good_list[k] = medicines[i];
			k++;
		}
	return good_list;
}



int undo(Service* service) {
	if (getSizeDynamicArray(service->undoStack) == 0) {
		return 0;
	}
	addElemToDyanmicArray(service->redoStack, copyDynamicArray(service->repository->arr));
	destroyDynamicArray(service->repository->arr);
	service->repository->arr = copyDynamicArray((DynamicArray*)get(service->undoStack, getSizeDynamicArray(service->undoStack) - 1));
	deleteElement(service->undoStack, getSizeDynamicArray(service->undoStack) - 1);
	return 1;
}

int redo(Service* service) {
	if (getSizeDynamicArray(service->redoStack) == 0) {
		return 0;
	}
	addElemToDyanmicArray(service->undoStack, copyDynamicArray(service->repository->arr));
	destroyDynamicArray(service->repository->arr);
	service->repository->arr = copyDynamicArray((DynamicArray*)get(service->redoStack, getSizeDynamicArray(service->redoStack) - 1));
	deleteElement(service->redoStack, getSizeDynamicArray(service->redoStack) - 1);
	return 1;
}



void testService()
{
	Service* service = createService();
	assert(getSizeService(service) == 0);
	addElementToService(service, "paracetamol", 10, 100, 5);
	assert(getSizeService(service) == 1);
	addElementToService(service, "nurofen", 20, 50, 10);
	assert(getSizeService(service) == 2);
	assert(deleteMedicineFromService(service, "paracetamol", 10) == 1);
	assert(deleteMedicineFromService(service, "paracetamol", 10) == 0);
	assert(deleteMedicineFromService(service, "nurofen", 20) == 1);
	assert(deleteMedicineFromService(service, "nurofen", 20) == 0);
	assert(getSizeService(service) == 0);
	addElementToService(service, "paracetamol", 10, 100, 5);
	addElementToService(service, "nurofen", 20, 50, 10);
	assert(updateMedicineFromService(service, "paracetamol", 10, 200, 10) == 1);
	assert(updateMedicineFromService(service, "paracetamol", 1, 200, 10) == 0);
	assert(updateMedicineFromService(service, "nurofen", 20, 100, 5) == 1);
	assert(updateMedicineFromService(service, "nurofen", 2, 100, 5) == 0);
	assert(getSizeService(service) == 2);
	destroyService(service);
}