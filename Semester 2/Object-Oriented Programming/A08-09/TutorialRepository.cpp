#include "TutorialRepository.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "RepositoryExceptions.h"

using namespace std;


void TutorialRepository::addTutorialRepository(const Tutorial& tutorial)
{
	auto it = find(this->tutorials.begin(), this->tutorials.end(), tutorial);
	if (it != this->tutorials.end())
		//throw std::invalid_argument("Tutorial already exists");
		throw DuplicateTutorialException();
	this->tutorials.push_back(tutorial);
}

void TutorialRepository::deleteTutorialRepository(const Tutorial& tutorial)
{
	auto it = find(this->tutorials.begin(), this->tutorials.end(), tutorial);
	if (it != this->tutorials.end())
		this->tutorials.erase(it);
	else
		//throw std::invalid_argument("Tutorial does not exist");
		throw InexistentTutorialException();
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
	//throw std::invalid_argument("Tutorial does not exist");
	throw InexistentTutorialException();
}

int TutorialRepository::getSizeTutorialRepository()
{
	return this->tutorials.size();
}


void FileTutorialRepository::addTutorialRepository(const Tutorial& tutorial)
{
	TutorialRepository::addTutorialRepository(tutorial);
	this->writeToFile();
}

void FileTutorialRepository::deleteTutorialRepository(const Tutorial& tutorial)
{
	TutorialRepository::deleteTutorialRepository(tutorial);
	this->writeToFile();
}

std::vector<Tutorial> FileTutorialRepository::getTutorialsTutorialRepository()
{
	return TutorialRepository::getTutorialsTutorialRepository();
}

Tutorial& FileTutorialRepository::getTutorialRepository(const std::string& title, const std::string& presenter)
{
	return TutorialRepository::getTutorialRepository(title, presenter);
}

int FileTutorialRepository::getSizeTutorialRepository()
{
	return TutorialRepository::getSizeTutorialRepository();
}

void FileTutorialRepository::writeToFile()
{
	ofstream file(this->filename);
	if (!file.is_open())
		throw std::invalid_argument("The file could not be opened!");
	for (auto tutorial : this->tutorials)
		file << tutorial.getTitle() << "," << tutorial.getPresenter() << "," << tutorial.getDuration() << "," << tutorial.getLikes() << "," << tutorial.getLink() << "\n";
	file.close();
}

void FileTutorialRepository::loadFromFile()
{
	ifstream file(this->filename);
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
