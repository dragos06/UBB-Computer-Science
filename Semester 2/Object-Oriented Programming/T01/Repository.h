#pragma once
#include <string>
#include <vector>
#include "Domain.h"
using namespace std;

class Repository {
private:
	vector<Protein> proteins;
public:
	//Adds a protein to the list
	//param: protein -> Protein to be added
	//return: True if protein doesn't exist, false otherwise
	bool addProtein(Protein protein);
	vector<Protein> getProteins();
};