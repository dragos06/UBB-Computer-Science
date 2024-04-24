#include "Repository.h"

bool Repository::addProtein(Protein protein)
{
	for (int i = 0; i < this->proteins.size(); i++)
		if (this->proteins[i].getOrganism() == protein.getOrganism() && this->proteins[i].getName() == protein.getName())
			return false;
	this->proteins.push_back(protein);
	return true;
}

vector<Protein> Repository::getProteins()
{
	return this->proteins;
}
