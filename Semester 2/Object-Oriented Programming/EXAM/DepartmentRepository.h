#pragma once
#include "Department.h"
#include <vector>

class DepartmentRepository {
private:
	std::string filename;
	std::vector<Department> departments;
	void load();
	
public:
	DepartmentRepository(std::string filename);
	std::vector<Department> getDepartmentsRepository();
	void save();
};