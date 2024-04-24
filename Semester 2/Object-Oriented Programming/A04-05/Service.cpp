#include "Service.h"
#include <string>

#include <iostream>

Service::Service()
{
}

Service::Service(TutorialRepository tutorial_repository, WatchlistRepository watchlist_repository)
{
	this->tutorial_repository = tutorial_repository;
	this->watchlist_repository = watchlist_repository;
}

void Service::addTutorialService(const std::string& title, const std::string& presenter, int duration, int likes, const std::string& link)
{
	this->tutorial_repository.addTutorialRepository(Tutorial(title, presenter, duration, likes, link));
}

void Service::addWatchlistService(Tutorial tutorial)
{
	this->watchlist_repository.addWatchlistRepository(tutorial);
}

void Service::deleteTutorialService(const std::string& title, const std::string& presenter)
{
	Tutorial tutorial = this->tutorial_repository.getTutorialRepository(title, presenter);
	this->tutorial_repository.deleteTutorialRepository(tutorial);
}

void Service::deleteWatchlistService(const std::string& title, const std::string& presenter)
{
	Tutorial tutorial = this->watchlist_repository.getTutorialWatchlistRepository(title, presenter);
	this->watchlist_repository.deleteWatchlistRepository(tutorial);
}

void Service::updateTutorialService(const std::string& title, const std::string& presenter, int duration, int likes, const std::string& link)
{
	Tutorial& tutorial = this->tutorial_repository.getTutorialRepository(title, presenter);
	tutorial.setDuration(duration);
	tutorial.setLikes(likes);
	tutorial.setLink(link);
}

Tutorial* Service::getTutorialsService()
{
	return this->tutorial_repository.getTutorialsTutorialRepository();
}

int Service::getSizeTutorialsService()
{
	return this->tutorial_repository.getSizeTutorialRepository();
}

Tutorial* Service::getWatchlistService()
{
	return this->watchlist_repository.getTutorialsWatchlistRepository();
}

int Service::getSizeWatchlistService()
{
	return this->watchlist_repository.getSizeWatchlistRepository();
}

Tutorial* Service::tutorialsGivenPresenter(const std::string& presenter, int& number_elements)
{
	Tutorial* tutorials = this->tutorial_repository.getTutorialsTutorialRepository();
	Tutorial* copy_tutorials = new Tutorial[this->tutorial_repository.getSizeTutorialRepository()];
	if (presenter.empty()) {
		for (int i = 0; i < this->tutorial_repository.getSizeTutorialRepository(); i++)
			copy_tutorials[i] = tutorials[i];
		number_elements = this->tutorial_repository.getSizeTutorialRepository();
		return copy_tutorials;
	}

	int k = 0;
	for (int i = 0; i < this->tutorial_repository.getSizeTutorialRepository(); i++)
		if (tutorials[i].getPresenter() == presenter) {
			copy_tutorials[k] = tutorials[i];
			k++;
		}
	number_elements = k;
	return copy_tutorials;
}
