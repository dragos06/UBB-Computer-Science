#include "Testing.h"
#include "Service.h"
#include <assert.h>

void Testing::testAddService()
{
	Repository repository;
	Service service{ repository };

	service.addProteinService("Human","Myosin-2","MSSDSELAVFGEAA");
	service.addProteinService("Human","Keratin","TCGSGFGGRAFSCISACGPRPGRCC");
	service.addProteinService("Mouse","Keratin","MLWWEEVEDCYEREDVQKK");
	service.addProteinService("E-Coli","tufA","VTLIHPIAMDDGLRFAIRE");
	service.addProteinService("E-Coli","cspE","MSKIKGNVKWFNESKGFGFITPEDG");

	assert(service.getAllService().size() == 5);
	assert(service.getAllService()[0].getOrganism() == "Human");
	assert(service.getAllService()[1].getName() == "Keratin");
	assert(service.getAllService()[2].getSequence() == "MLWWEEVEDCYEREDVQKK");
}

void Testing::testShowGivenName()
{
	Repository repository;
	Service service{ repository };

	service.addProteinService("Human", "Myosin-2", "MSSDSELAVFGEAA");
	service.addProteinService("Human", "Keratin", "TCGSGFGGRAFSCISACGPRPGRCC");
	service.addProteinService("Mouse", "Keratin", "MLWWEEVEDCYEREDVQKK");
	service.addProteinService("E-Coli", "tufA", "VTLIHPIAMDDGLRFAIRE");
	service.addProteinService("E-Coli", "cspE", "MSKIKGNVKWFNESKGFGFITPEDG");
	service.addProteinService("Animal", "Keratin", "DSADFDSFDSFD");

	assert(service.proteinGivenName("Keratin").size() == 3);
	assert(service.proteinGivenName("Keratin")[0].getOrganism() == "Animal");
	assert(service.proteinGivenName("Keratin")[1].getName() == "Keratin");
	assert(service.proteinGivenName("Keratin")[2].getSequence() == "MLWWEEVEDCYEREDVQKK");
}

void Testing::runTests()
{
	this->testAddService();
	this->testShowGivenName();
}
