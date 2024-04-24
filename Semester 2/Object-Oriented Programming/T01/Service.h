#pragma once
#include "Repository.h"

class Service {
private:
	Repository repository;
public:
	Service();
	Service(Repository repository);

	//Adds a protein to the repository
	//param organism: organism of the protein
	//param name: name of the protein
	//param sequence: sequence of the protein
	//return: True if protein can be added, false otherwise
	bool addProteinService(string organism, string name, string sequence);

	vector<Protein> getAllService();

	//Shows all proteins with a given name, sorted by organism
	//param name: name of the protein to filter by
	//return: The list of proteins with the given name sorted by organism
	vector<Protein> proteinGivenName(string name);

	void startUpList();
};