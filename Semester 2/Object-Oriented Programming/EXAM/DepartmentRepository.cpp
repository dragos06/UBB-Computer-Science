#include "DepartmentRepository.h"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;


void DepartmentRepository::load()
{
	ifstream file{ this->filename };
	string line;
	while (getline(file, line)) {
		stringstream stream{ line };
		string name, description;
		getline(stream, name, ',');
		getline(stream, description);
		departments.push_back(Department{ name,description });
	}
	file.close();
}

void DepartmentRepository::save()
{
	ofstream file{ this->filename };
	for (auto d : departments) {
		file << d.getName() << "," << d.getDescription() << "\n";
	}
	file.close();
}

DepartmentRepository::DepartmentRepository(std::string filename): filename{filename}
{
	this->load();
}

std::vector<Department> DepartmentRepository::getDepartmentsRepository()
{
	return this->departments;
}
