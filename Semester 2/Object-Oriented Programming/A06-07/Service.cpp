#include "Service.h"
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

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
	Tutorial& tutorial = this->tutorial_repository.getTutorialRepository(title, presenter);

	vector<Tutorial> watch_list = this->watchlist_repository.getTutorialsWatchlistRepository();
	auto it = find(watch_list.begin(), watch_list.end(), tutorial);
	if (it != watch_list.end())
		this->watchlist_repository.deleteWatchlistRepository(tutorial);
	
	this->tutorial_repository.deleteTutorialRepository(tutorial);
	
}

void Service::deleteWatchlistService(const std::string& title, const std::string& presenter, const int& like)
{
	Tutorial& tutorial_wl = this->watchlist_repository.getTutorialWatchlistRepository(title, presenter);
	Tutorial& tutorial_rp = this->tutorial_repository.getTutorialRepository(title, presenter);
	if (like == 1)
		tutorial_rp.setLikes(tutorial_rp.getLikes() + 1);
	this->watchlist_repository.deleteWatchlistRepository(tutorial_wl);
}

void Service::updateTutorialService(const std::string& title, const std::string& presenter, int duration, int likes, const std::string& link)
{
	Tutorial& tutorial = this->tutorial_repository.getTutorialRepository(title, presenter);
	tutorial.setDuration(duration);
	tutorial.setLikes(likes);
	tutorial.setLink(link);
}

vector<Tutorial> Service::getTutorialsService()
{
	return this->tutorial_repository.getTutorialsTutorialRepository();
}

int Service::getSizeTutorialsService()
{
	return this->tutorial_repository.getSizeTutorialRepository();
}

vector<Tutorial> Service::getWatchlistService()
{
	return this->watchlist_repository.getTutorialsWatchlistRepository();
}

int Service::getSizeWatchlistService()
{
	return this->watchlist_repository.getSizeWatchlistRepository();
}

vector<Tutorial> Service::tutorialsGivenPresenter(const std::string& presenter)
{
	/*vector<Tutorial> tutorials = this->tutorial_repository.getTutorialsTutorialRepository();
	vector<Tutorial> copy_tutorials;
	if (presenter.empty()) {
		for (auto it = tutorials.begin(); it != tutorials.end(); it++)
			copy_tutorials.push_back(*it);
		return copy_tutorials;
	}
	for (auto it = tutorials.begin(); it != tutorials.end(); it++)
		if ((*it).getPresenter() == presenter) {
			copy_tutorials.push_back(*it);
		}
	return copy_tutorials;*/

	vector<Tutorial> tutorials = this->tutorial_repository.getTutorialsTutorialRepository();
	vector<Tutorial> copy_tutorials;

	copy_if(tutorials.begin(), tutorials.end(), back_inserter(copy_tutorials), [presenter](const Tutorial& tutorial) { return (tutorial.getPresenter() == presenter) || presenter.empty(); });
	return copy_tutorials;

}

void Service::loadFromFileService()
{
	this->tutorial_repository.loadFromFile();
}
