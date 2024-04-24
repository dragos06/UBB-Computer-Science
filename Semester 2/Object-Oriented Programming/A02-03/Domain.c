#include "Domain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Medicine* createMedicine(char* name, int concentration, int quantity, int price)
{
	Medicine* medicine = malloc(sizeof(Medicine));
	if (medicine == NULL)
		return NULL;
	medicine->name = malloc(sizeof(char) * (strlen(name) + 1));
	if (medicine->name == NULL) {
		free(medicine);
		return NULL;
	}
	strcpy(medicine->name, name);
	medicine->concentration = concentration;
	medicine->quantity = quantity;
	medicine->price = price;

	return medicine;
}

void destroyMedicine(Medicine* medicine)
{
	if (medicine == NULL)
		return;
	if (medicine->name != NULL)
		free(medicine->name);
	free(medicine);
}

int equalMedicine(Medicine* o_medicine, Medicine* n_medicine)
{
	if (o_medicine == NULL || n_medicine == NULL)
		return 0;
	if (strcmp(o_medicine->name, n_medicine->name) == 0 && o_medicine->concentration == n_medicine->concentration)
		return 1;
	return 0;
}

Medicine* copyMedicine(Medicine* medicine) {
	if (medicine == NULL)
		return NULL;
	return createMedicine(medicine->name, medicine->concentration, medicine->quantity, medicine->price);
}

char* getName(Medicine* medicine)
{
	return medicine->name;
}

int getConcentration(Medicine* medicine)
{
	return medicine->concentration;
}

int getQuantity(Medicine* medicine)
{
	return medicine->quantity;
}

int getPrice(Medicine* medicine)
{
	return medicine->price;
}

void setName(Medicine* medicine, char name[])
{
	strcpy(medicine->name, name);
}

void setConcentration(Medicine* medicine, int concentration)
{
	medicine->concentration = concentration;
}

void setQuantity(Medicine* medicine, int quantity)
{
	medicine->quantity = quantity;
}

void setPrice(Medicine* medicine, int price)
{
	(*medicine).price = price;
}

void printMedicine(Medicine* medicine)
{
	printf("Name: %s | Concentration: %d | Quantity: %d | Price: %d\n", medicine->name, medicine->concentration, medicine->quantity, medicine->price);
}

void testMedicine()
{
	Medicine* medicine = createMedicine("Paracetamol", 10, 100, 5);
	if (strcmp(getName(medicine), "Paracetamol") != 0)
		printf("Error at getName!\n");
	if (getConcentration(medicine) != 10)
		printf("Error at getConcentration!\n");
	if (getQuantity(medicine) != 100)
		printf("Error at getQuantity!\n");
	if (getPrice(medicine) != 5)
		printf("Error at getPrice!\n");
	setName(medicine, "Nurofen");
	if (strcmp(getName(medicine), "Nurofen") != 0)
		printf("Error at setName!\n");
	setConcentration(medicine, 20);
	if (getConcentration(medicine) != 20)
		printf("Error at setConcentration!\n");
	setQuantity(medicine, 200);
	if (getQuantity(medicine) != 200)
		printf("Error at setQuantity!\n");
	setPrice(medicine, 10);
	if (getPrice(medicine) != 10)
		printf("Error at setPrice!\n");
	Medicine* copy = copyMedicine(medicine);
	if (equalMedicine(medicine, copy) == 0)
		printf("Error at equalMedicine!\n");
	destroyMedicine(medicine);
	destroyMedicine(copy);
}


