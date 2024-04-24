#include "Service.h"

Service::Service()
{
}

Service::Service(Repository repository)
{
	this->repository = repository;
}

bool Service::addProteinService(string organism, string name, string sequence)
{
	return this->repository.addProtein(Protein{ organism, name, sequence });
}

vector<Protein> Service::getAllService()
{
	return this->repository.getProteins();
}

vector<Protein> Service::proteinGivenName(string name)
{
	vector<Protein> proteins = this->repository.getProteins();
	vector<Protein> copy_proteins;
	for (int i = 0; i < proteins.size(); i++)
		if (proteins[i].getName() == name)
			copy_proteins.push_back(proteins[i]);
	if (copy_proteins.size() != 0)
		for (int i = 0; i < copy_proteins.size() - 1; i++)
			for (int j = i + 1; j < copy_proteins.size(); j++)
				if (copy_proteins[i].getOrganism() > copy_proteins[j].getOrganism())
					swap(copy_proteins[i], copy_proteins[j]);
	return copy_proteins;
}

void Service::startUpList()
{
	this->repository.addProtein(Protein{ "Human","Myosin-2","MSSDSELAVFGEAA" });
	this->repository.addProtein(Protein{ "Human","Keratin","TCGSGFGGRAFSCISACGPRPGRCC" });
	this->repository.addProtein(Protein{ "Mouse","Keratin","MLWWEEVEDCYEREDVQKK" });
	this->repository.addProtein(Protein{ "E-Coli","tufA","VTLIHPIAMDDGLRFAIRE" });
	this->repository.addProtein(Protein{ "E-Coli","cspE","MSKIKGNVKWFNESKGFGFITPEDG" });
}
