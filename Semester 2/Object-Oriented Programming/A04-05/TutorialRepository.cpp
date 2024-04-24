#include "TutorialRepository.h"
#include <stdexcept>

TutorialRepository::~TutorialRepository()
{
}

void TutorialRepository::addTutorialRepository(Tutorial tutorial)
{
	Tutorial* tutorials = this->tutorials.getElements();
	for (int i = 0; i < this->tutorials.getSize(); i++)
		if (tutorials[i] == tutorial)
			throw std::invalid_argument("Tutorial already exists!");
	this->tutorials.add_element(tutorial);
}

void TutorialRepository::deleteTutorialRepository(Tutorial tutorial)
{
	int found = 0;
	Tutorial* tutorials = this->tutorials.getElements();
	for (int i = 0; i < this->tutorials.getSize(); i++)
		if (tutorials[i] == tutorial)
			found = 1;
	if (!found)
		throw std::invalid_argument("Tutorial does not exists!");
	this->tutorials.delete_element(tutorial);
}

Tutorial* TutorialRepository::getTutorialsTutorialRepository()
{
	return this->tutorials.getElements();
}

Tutorial& TutorialRepository::getTutorialRepository(const std::string& title, const std::string& presenter)
{
	Tutorial* tutorials = this->tutorials.getElements();
	for (int i = 0; i < this->tutorials.getSize(); i++)
		if (tutorials[i].getTitle() == title && tutorials[i].getPresenter() == presenter)
			return tutorials[i];
	throw std::invalid_argument("Tutorial does not exists!");
}

int TutorialRepository::getSizeTutorialRepository()
{
	return this->tutorials.getSize();
}



