#include "UI.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <crtdbg.h>

UI* createUI()
{
	UI* ui = malloc(sizeof(UI));
	Service* service = createService();
	ui->service = service;
	return ui;
}

void destroyUI(UI* ui) {
	destroyService(ui->service);
	free(ui);
}

void printMenuUI() {
	printf("\n\n\n	PHARMACY\n");
	printf("[1] Add a medicine\n");
	printf("[2] Delete a medicine\n");
	printf("[3] Update a medicine\n");
	printf("[4] List all medicines containing a string, sorted ascending\n");
	printf("[5] List all medicines containing a string, sorted descending\n");
	printf("[6] List medicines in short supply by quantity\n");
	printf("[7] List medicines in short supply by concentration\n");
	printf("[8] Undo\n");
	printf("[9] Redo\n");
	printf("[10] Exit\n\n\n");
	
}

int validateString(char string[]) {
	for (int i = 0; i < strlen(string); i++)
		if (isalpha(string[i]) == 0 && string[i] != ' ')
			return 0;
	return 1;
}

int validateNumber(char number_str[]) {
	return atoi(number_str);
}

void addMedicineUI(UI* ui) {
	char name[20], concentration_str[20], quantity_str[20], price_str[20];
	int concentration, quantity, price;

	printf("\nPlease enter the name of the medicine: ");
	fgets(name, 20, stdin);
	name[strlen(name)-1] = '\0';

	int str_error = validateString(name);
	if (str_error == 0) {
		printf("Invalid name!");
		return;
	}

	printf("\nPlease enter the concentration of the medicine: ");
	fgets(concentration_str, 20, stdin);
	
	concentration = validateNumber(concentration_str);

	if (concentration == 0) {
		printf("Invalid concentration, it should an integer bigger than 0!");
		return;
	}

	printf("\nPlease enter the quantity of the medicine: ");
	fgets(quantity_str, 20, stdin);
	
	quantity = validateNumber(quantity_str);

	if (quantity == 0) {
		printf("Invalid quantity, it should an integer bigger than 0!");
		return;
	}

	printf("\nPlease enter the price of the medicine: ");
	fgets(price_str, 20, stdin);

	price = validateNumber(price_str);
	
	if (price == 0) {
		printf("Invalid price, it should an integer bigger than 0!");
		return;
	}
	addElementToService(ui->service, name, concentration, quantity, price);
}

void deleteMedicineUI(UI* ui) {
	char name[20], concentration_str[20];
	int concentration;

	printf("\nPlease enter the name of the medicine: ");
	fgets(name, 20, stdin);
	name[strlen(name) - 1] = '\0';
	int str_error = validateString(name);
	if (str_error == 0) {
		printf("Invalid name!");
		return;
	}

	printf("\nPlease enter the concentration of the medicine: ");
	fgets(concentration_str, 20, stdin);

	concentration = validateNumber(concentration_str);

	if (concentration == 0) {
		printf("Invalid concentration, it should an integer bigger than 0!");
		return;
	}

	int delete_error = deleteMedicineFromService(ui->service, name, concentration);
	if (delete_error == 0) {
		printf("Deletion could not be completed!\n");
		return;
	}
}


void updateMedicineUI(UI* ui) {
	char old_name[20], old_concentration_str[20], new_quantity_str[20], new_price_str[20];
	int old_concentration, new_quantity, new_price;

	printf("\nPlease enter the name of the old medicine: ");
	fgets(old_name, 20, stdin);
	old_name[strlen(old_name) - 1] = '\0';
	int str_error = validateString(old_name);
	if (str_error == 0) {
		printf("Invalid name!");
		return;
	}

	printf("\nPlease enter the concentration of the old medicine: ");
	fgets(old_concentration_str, 20, stdin);

	old_concentration = validateNumber(old_concentration_str);

	if (old_concentration == 0) {
		printf("Invalid concentration, it should an integer bigger than 0!");
		return;
	}

	printf("\nPlease enter the quantity of the new medicine: ");
	fgets(new_quantity_str, 20, stdin);

	new_quantity = validateNumber(new_quantity_str);

	if (new_quantity == 0) {
		printf("Invalid quantity, it should an integer bigger than 0!");
		return;
	}

	printf("\nPlease enter the price of the new medicine: ");
	fgets(new_price_str, 20, stdin);

	new_price = validateNumber(new_price_str);

	if (new_price == 0) {
		printf("Invalid price, it should an integer bigger than 0!");
		return;
	}
	int update_error = updateMedicineFromService(ui->service, old_name, old_concentration, new_quantity, new_price);
	if (update_error == 0) {
		printf("Update could not be completed!\n");
		return;
	}
}

void sortByStringUIAscending(UI* ui) {
	char given_string[20];
	int nr_elems = 0;
	printf("\nPlease enter the string to filter by: ");
	gets(given_string);
	Medicine** good_list = sortByString(ui->service, given_string, &nr_elems, compareAscending);
	for (int i = 0; i < nr_elems; i++)
		printMedicine(good_list[i]);
	free(good_list);
}


void sortByStringUIDescending(UI* ui) {
	char given_string[20];
	int nr_elems = 0;
	printf("\nPlease enter the string to filter by: ");
	gets(given_string);
	Medicine** good_list = sortByString(ui->service, given_string, &nr_elems, compareDescending);
	for (int i = 0; i < nr_elems; i++)
		printMedicine(good_list[i]);
	free(good_list);
}

void medicinesShortSupplyQuantityUI(UI* ui) {
	char quantity_str[20];
	int quantity;
	
	printf("\nPlease enter the quantity to filter by: ");
	fgets(quantity_str, 20, stdin);

	quantity = validateNumber(quantity_str);

	if (quantity == 0) {
		printf("Invalid quantity, it should an integer bigger than 0!");
		return;
	}
	int nr_elems = 0;
	Medicine** good_list = medicinesShortSupply(ui->service, quantity, &nr_elems, filterByQuantity);
	for (int i = 0; i < nr_elems; i++)
		printMedicine(good_list[i]);
	free(good_list);
}

void medicinesShortSupplyConcentrationUI(UI* ui) {
	char concentration_str[20];
	int concentration;

	printf("\nPlease enter the concentration to filter by: ");
	fgets(concentration_str, 20, stdin);

	concentration = validateNumber(concentration_str);

	if (concentration == 0) {
		printf("Invalid concentration, it should an integer bigger than 0!");
		return;
	}
	int nr_elems = 0;
	Medicine** good_list = medicinesShortSupply(ui->service, concentration, &nr_elems, filterByConcentration);
	for (int i = 0; i < nr_elems; i++)
		printMedicine(good_list[i]);
	free(good_list);
}


void generateStartUpMedicines(UI* ui) {
	addElementToService(ui->service, "Paracetamol", 30, 40, 50);
	addElementToService(ui->service, "Ibuprofen", 25, 35, 45);
	addElementToService(ui->service, "Aspirin", 20, 30, 40);
	addElementToService(ui->service, "Ciprofloxacin", 15, 25, 35);
	addElementToService(ui->service, "Amoxicillin", 20, 30, 40);
	addElementToService(ui->service, "Omeprazole", 10, 20, 30);
	addElementToService(ui->service, "Loratadine", 25, 35, 45);
	addElementToService(ui->service, "Simvastatin", 30, 40, 50);
	addElementToService(ui->service, "Metformin", 25, 35, 45);
	addElementToService(ui->service, "Atorvastatin", 30, 40, 50);
}

void startUI(UI* ui)
{
	generateStartUpMedicines(ui);
	while (1) {
		printMenuUI();
		char user_option[4];
		printf("\nPlease choose an option: ");
		fgets(user_option, 4, stdin);
		fseek(stdin, 0, SEEK_END);
		int user_option_valid;
		user_option_valid = atoi(user_option);
		switch (user_option_valid) {
		case 0: {
			printf("Please provide an integer!");
			break;
		}
		case 1: {
			addMedicineUI(ui);
			break;
		}
		case 2: {
			deleteMedicineUI(ui);
			break;
		}
		case 3: {
			updateMedicineUI(ui);
			break;
		}
		case 4: {
			sortByStringUIAscending(ui);
			break;
		}
		case 5:{
			sortByStringUIDescending(ui);
			break;
		}
		case 6: {
			medicinesShortSupplyQuantityUI(ui);
			break;
		}
		case 7: {
			medicinesShortSupplyConcentrationUI(ui);
			break;
		}
		case 8: {
			int undo_result = undo(ui->service);
			if (undo_result == 0) {
				printf("Undo could not be completed!\n");
			}
			break;
		}
		case 9: {
			int redo_result = redo(ui->service);
			if (redo_result == 0) {
				printf("Redo could not be completed!\n");
			}
			break;
		}
		case 10: {
			printf("Exiting...");
			return;
		}
		default: {
			printf("Invalid option!");
		}
		}
	}
}


