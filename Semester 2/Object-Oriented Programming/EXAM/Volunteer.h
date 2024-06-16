#pragma once
#include <string>
#include <Department.h>
#include <vector>

class Volunteer {
private:
	std::string name;
	std::string email;
	std::vector<std::string> interests;
	std::string department;
public:
	Volunteer(std::string name, std::string email, std::vector<std::string> interests, std::string department);
	std::string getName();
	std::string getEmail();
	std::vector<std::string> getInterests();
	std::string getDepartment();
	void setDepartment(std::string department);
};

