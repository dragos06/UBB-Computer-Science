#include "VolunteerRepository.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

void VolunteerRepository::load()
{
	ifstream file{ this->filename };
	string line;
	while (getline(file, line)) {
		stringstream stream{ line };
		string name, email, interests, department;
		getline(stream, name, ',');
		getline(stream, email, ',');
		getline(stream, department,',');
		getline(stream, interests, ',');
		stringstream stream_interests{ interests };
		string interest;
		std::vector<std::string> interests_list;
		while (getline(stream_interests, interest, ';')) {
			interests_list.push_back(interest);
		}
		volunteers.push_back(Volunteer{ name, email, interests_list, department });
	}
	file.close();
}

void VolunteerRepository::save()
{
	ofstream file{ this->filename };
	for (auto v : volunteers) {
		string interests;
		for (auto i : v.getInterests())
			interests += i += ';';
		file << v.getName() << ',' << v.getEmail() << ',' << v.getDepartment() << ',' << interests << "\n";
	}
}

VolunteerRepository::VolunteerRepository(std::string filename): filename{filename}
{
	this->load();
}

void VolunteerRepository::addVolunteerRepository(Volunteer volunteer)
{
	this->volunteers.push_back(volunteer);
	save();
}

std::vector<Volunteer>& VolunteerRepository::getVolunteersRepository()
{
	return this->volunteers;
}
