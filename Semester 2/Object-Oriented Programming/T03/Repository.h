#pragma once
#include "Medication.h"
#include <vector>

class Repository {
private:
	std::vector<Medication> medications;
	std::string filename;
public:
	Repository(std::string filename);
	void load();
	std::vector<Medication> getAll();

};