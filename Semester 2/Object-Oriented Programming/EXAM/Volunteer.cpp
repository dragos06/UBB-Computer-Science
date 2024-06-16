#include "Volunteer.h"

Volunteer::Volunteer(std::string name, std::string email, std::vector<std::string> interests, std::string department): name{name}, email{email}, interests{interests}, department{department}
{
}

std::string Volunteer::getName()
{
	return this->name;
}

std::string Volunteer::getEmail()
{
	return this->email;
}

std::vector<std::string> Volunteer::getInterests()
{
	return this->interests;
}

std::string Volunteer::getDepartment()
{
	return this->department;
}

void Volunteer::setDepartment(std::string department)
{
	this->department = department;
}
