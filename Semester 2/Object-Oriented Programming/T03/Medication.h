#pragma once
#include <string>

class Medication {
private:
	std::string category;
	std::string name;
	std::string effects;
public:
	Medication(std::string category, std::string name, std::string effects);
	std::string getCategory();
	std::string getName();
	std::string getEffects();
};