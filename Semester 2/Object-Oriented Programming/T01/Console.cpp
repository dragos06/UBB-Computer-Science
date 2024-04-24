#include "Console.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Console::Console(Service service)
{
	this->service = service;
}

void Console::startConsole()
{
	this->service.startUpList();
	while (true) {
		this->print_menu();
		string user_option;
		int user_option_valid;
		cout << "Please choose an option: ";
		getline(cin, user_option);
		user_option_valid = stoi(user_option);
		switch (user_option_valid) {
		case 1:
			this->addProteinConsole();
			break;
		case 2:
			this->showAllConsole();
			break;
		case 3:
			this->showGivenName();
			break;
		case 4:
			cout << "\nExiting...\n";
			return;
		default:
			cout << "\nInvalid option\n";
			break;
		}
	}
}

void Console::addProteinConsole()
{
	string organism;
	string name;
	string sequence;
	
	cout << "Please enter the organism of the protein: ";
	getline(cin, organism);

	cout << "Please enter the name of the protein: ";
	getline(cin, name);

	cout << "Please enter the sequence of the protein: ";
	getline(cin, sequence);

	int result = this->service.addProteinService(organism, name, sequence);
	if (result)
		cout << "\nProtein added succesfully\n";
	else
		cout << "\nProtein already exists\n";
}

void Console::showAllConsole()
{
	vector<Protein> proteins = this->service.getAllService();
	for (int i = 0; i < proteins.size(); i++)
		cout << "\n" << proteins[i].getOrganism() << " | " << proteins[i].getName() << " | " << proteins[i].getSequence();
	cout << "\n";
}

void Console::showGivenName()
{
	string name;
	cout << "\nPlease enter the name of the protein: ";
	getline(cin, name);
	vector<Protein> proteins = this->service.proteinGivenName(name);
	for (int i = 0; i < proteins.size(); i++)
		cout << "\n" << proteins[i].getOrganism() << " | " << proteins[i].getName() << " | " << proteins[i].getSequence();
	cout << "\nNumber of organisms having this protein is: " << proteins.size() << "\n";
}

void Console::print_menu()
{
	cout << "\n		PROTEIN MANAGER";
	cout << "\n[1] Add a new protein";
	cout << "\n[2] Show all proteins";
	cout << "\n[3] Show all proteins with a given name and the numer of organisms having such proteins";
	cout << "\n[4] Exit\n";
}
