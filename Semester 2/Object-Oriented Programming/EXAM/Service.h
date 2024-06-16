#pragma once
#include "Subject.h"
#include "DepartmentRepository.h"
#include "VolunteerRepository.h"

class Service : public Subject {
private:
	DepartmentRepository& department_repository;
	VolunteerRepository& volunteer_repository;
public:
	Service(DepartmentRepository& department_repository, VolunteerRepository& volunteer_repository);
	std::vector<Volunteer> getVolunteersDepartment(std::string department);
	void addVolunteer(std::string name, std::string email, std::vector<std::string> interests, std::string department);
	void saveService();
	std::vector<Volunteer>& getVolunteers();
	std::vector<Department> getDepartments();
};