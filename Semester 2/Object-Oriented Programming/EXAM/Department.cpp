#include "Department.h"

Department::Department(std::string name, std::string description): name{name}, description{description}
{
}

std::string Department::getName()
{
	return this->name;
}

std::string Department::getDescription()
{
	return this->description;
}
