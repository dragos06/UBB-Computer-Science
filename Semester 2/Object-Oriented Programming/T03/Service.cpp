#include "Service.h"
#include <algorithm>
#include <iostream>
using namespace std;
Service::Service(Repository& repository): repository{repository}
{
}

std::vector<Medication> Service::getAllService()
{
	vector<Medication> medications = repository.getAll();
	sort(medications.begin(), medications.end(), [](Medication m1, Medication m2) {
		return m1.getCategory() < m2.getCategory();
		});
	return medications;
}

std::vector<Medication> Service::searchCategoryName(std::string given_string)
{
	vector<Medication> medications = repository.getAll();
	vector<Medication> copy;
	copy_if(medications.begin(), medications.end(), back_inserter(copy), [given_string](Medication m) {
		return m.getCategory().find(given_string) != std::string::npos || m.getName().find(given_string) != std::string::npos;
		});
	return copy;
}

std::string Service::showSideEffects(std::string name)
{
	vector<Medication> medications = repository.getAll();
	for (Medication m : medications) {
		if (m.getName() == name)
			return m.getEffects();
	}
	return string();
}
