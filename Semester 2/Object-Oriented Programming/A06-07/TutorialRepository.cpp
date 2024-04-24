#include "TutorialRepository.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

TutorialRepository::~TutorialRepository()
{
}

void TutorialRepository::addTutorialRepository(const Tutorial& tutorial)
{
	auto it = find(this->tutorials.begin(), this->tutorials.end(), tutorial);
	if (it != this->tutorials.end())
		throw std::invalid_argument("Tutorial already exists");
	this->tutorials.push_back(tutorial);
	this->saveToFile();
}

void TutorialRepository::deleteTutorialRepository(const Tutorial& tutorial)
{
	auto it = find(this->tutorials.begin(), this->tutorials.end(), tutorial);
	if (it != this->tutorials.end())
		this->tutorials.erase(it);
	else
		throw std::invalid_argument("Tutorial does not exist");
	this->saveToFile();
}

vector<Tutorial> TutorialRepository::getTutorialsTutorialRepository()
{
	return this->tutorials;
}

Tutorial& TutorialRepository::getTutorialRepository(const std::string& title, const std::string& presenter)
{
	for (auto it = this->tutorials.begin(); it != this->tutorials.end(); it++)
		if ((*it).getTitle() == title && (*it).getPresenter() == presenter)
			return *it;
	throw std::invalid_argument("Tutorial does not exist");
}

int TutorialRepository::getSizeTutorialRepository()
{
	return this->tutorials.size();
}

void TutorialRepository::saveToFile()
{
	ofstream file("tutorials.txt");
	if (!file.is_open())
		throw std::invalid_argument("The file could not be opened!");
	for (auto tutorial : this->tutorials)
		file << tutorial.getTitle() << "," << tutorial.getPresenter() << "," << tutorial.getDuration() << "," << tutorial.getLikes() << "," << tutorial.getLink() << "\n";
	file.close();
}

void TutorialRepository::loadFromFile()
{
	ifstream file("tutorials.txt");
	if (!file.is_open())
		throw std::invalid_argument("The file could not be opened!");
	this->tutorials.clear();
	string line;
	while (getline(file, line))
	{
		stringstream stream(line);
		string title, presenter, duration, likes, link;
		getline(stream, title, ',');
		getline(stream, presenter, ',');
		getline(stream, duration, ',');
		getline(stream, likes, ',');
		getline(stream, link, ',');
		this->tutorials.push_back(Tutorial(title, presenter, stoi(duration), stoi(likes), link));
	}
	file.close();
}







