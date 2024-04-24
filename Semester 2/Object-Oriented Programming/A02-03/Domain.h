#pragma once

typedef struct {
	char* name;
	int concentration;
	int quantity;
	int price;
}Medicine;

//Creates a medicine
// Parameters: name - pointer to a string
// 		   concentration - integer
// 		   quantity - integer
// 		   price - integer
//Returns a pointer to the medicine
Medicine* createMedicine(char* name, int concentration, int quantity, int price);

//Destroys a medicine
//Input: medicine - pointer to the medicine
void destroyMedicine(Medicine* medicine);

//Compares two medicines
//Input: o_medicine - pointer to a medicine
//		 n_medicine - pointer to a medicine
//Output: 1 if the medicines are equal, 0 otherwise
int equalMedicine(Medicine* o_medicine, Medicine* n_medicine);

//Copies a medicine
//Input: medicine - pointer to a medicine
//Returns a pointer to the copy of the medicine
Medicine* copyMedicine(Medicine* medicine);

//Returns the name of the medicine
//Input: medicine - pointer to a medicine
//Output: pointer to a string
char* getName(Medicine* medicine);

//Returns the concentration of the medicine
//Input: medicine - pointer to a medicine
//Output: integer representing the concentration
int getConcentration(Medicine* medicine);

//Returns the quantity of the medicine
//Input: medicine - pointer to a medicine
//Output: integer representing the quantity
int getQuantity(Medicine* medicine);

//Returns the price of the medicine
//Input: medicine - pointer to a medicine
//Output: integer representing the price
int getPrice(Medicine* medicine);

//Sets the name of the medicine
//Input: medicine - pointer to a medicine
//		 name - pointer to a string
void setName(Medicine* medicine, char name[]);

//Sets the concentration of the medicine
//Input: medicine - pointer to a medicine
//		 concentration - integer
void setConcentration(Medicine* medicine, int concentration);

//Sets the quantity of the medicine
//Input: medicine - pointer to a medicine
//		 quantity - integer
void setQuantity(Medicine* medicine, int quantity);

//Sets the price of the medicine
//Input: medicine - pointer to a medicine
//		 price - integer
void setPrice(Medicine* medicine, int price);

//Prints a medicine
//Input: medicine - pointer to a medicine
void printMedicine(Medicine* medicine);

//Tests the Medicine functions
void testMedicine();