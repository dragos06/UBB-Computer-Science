#include "Service.h"
#include <iostream>
#include <algorithm>
using namespace std;

Service::Service(DepartmentRepository& department_repository, VolunteerRepository& volunteer_repository): department_repository{department_repository}, volunteer_repository{volunteer_repository}
{
}

std::vector<Volunteer> Service::getVolunteersDepartment(std::string department)
{
	vector<Volunteer> volunteers = this->volunteer_repository.getVolunteersRepository();
	vector<Volunteer> copy;
	copy_if(volunteers.begin(), volunteers.end(), back_inserter(copy), [department](Volunteer v) {
		return v.getDepartment() == department;
		});
	sort(copy.begin(), copy.end(), [](Volunteer v1, Volunteer v2) {
		return v1.getName() < v2.getName();
		});
	return copy;
}

void Service::addVolunteer(std::string name, std::string email, std::vector<std::string> interests, std::string department)
{
	this->volunteer_repository.addVolunteerRepository(Volunteer{ name, email, interests, department });
}

void Service::saveService()
{
	this->volunteer_repository.save();
	this->department_repository.save();
}

std::vector<Volunteer>& Service::getVolunteers()
{
	return this->volunteer_repository.getVolunteersRepository();
}

std::vector<Department> Service::getDepartments()
{
	return this->department_repository.getDepartmentsRepository();
}


