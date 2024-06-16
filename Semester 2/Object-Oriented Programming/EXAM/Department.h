#pragma once
#include <string>

class Department {
private:
	std::string name;
	std::string description;
public:
	Department(std::string name="", std::string description="");
	std::string getName();
	std::string getDescription();
};