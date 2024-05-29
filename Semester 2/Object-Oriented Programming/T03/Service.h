#pragma once
#include "Repository.h"

class Service {
private:
	Repository& repository;
public:
	Service(Repository& repository);
	std::vector<Medication> getAllService();
	std::vector<Medication> searchCategoryName(std::string given_string);
	std::string showSideEffects(std::string name);
};
