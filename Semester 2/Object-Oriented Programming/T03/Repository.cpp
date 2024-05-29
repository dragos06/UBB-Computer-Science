#include "Repository.h"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

Repository::Repository(std::string filename): filename{filename}
{
	load();
}

void Repository::load()
{
	ifstream file(filename);
	string line;
	while (getline(file, line)) {
		stringstream stream(line);
		std::string category, name, effects;
		getline(stream, category, '|');
		getline(stream, name, '|');
		getline(stream, effects, '|');
		medications.push_back(Medication(category, name, effects));
	}
	file.close();
}

std::vector<Medication> Repository::getAll()
{
	return medications;
}
