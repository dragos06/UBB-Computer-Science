#pragma once
#include "Volunteer.h"

class VolunteerRepository {
private:
	std::vector<Volunteer> volunteers;
	std::string filename;
	void load();

public:
	VolunteerRepository(std::string filename);
	void addVolunteerRepository(Volunteer volunteer);
	std::vector<Volunteer>& getVolunteersRepository();
	void save();

};

