#include "WatchlistRepository.h"
#include <stdexcept>

WatchlistRepository::~WatchlistRepository()
{
}

void WatchlistRepository::addWatchlistRepository(Tutorial tutorial)
{
	Tutorial* watch_list = this->watch_list.getElements();
	for (int i = 0; i < this->watch_list.getSize(); i++)
		if (watch_list[i] == tutorial)
			throw std::invalid_argument("Tutorial already added to watchlist!");
	this->watch_list.add_element(tutorial);
}

void WatchlistRepository::deleteWatchlistRepository(Tutorial tutorial)
{
	int found = 0;
	Tutorial* tutorials = this->watch_list.getElements();
	for (int i = 0; i < this->watch_list.getSize(); i++)
		if (tutorials[i] == tutorial)
			found = 1;
	if (!found)
		throw std::invalid_argument("Tutorial does not exists!");
	this->watch_list.delete_element(tutorial);
}

Tutorial* WatchlistRepository::getTutorialsWatchlistRepository()
{
	return this->watch_list.getElements();
}

Tutorial& WatchlistRepository::getTutorialWatchlistRepository(const std::string& title, const std::string& presenter)
{
	Tutorial* tutorials = this->watch_list.getElements();
	for (int i = 0; i < this->watch_list.getSize(); i++)
		if (tutorials[i].getTitle() == title && tutorials[i].getPresenter() == presenter)
			return tutorials[i];
}

int WatchlistRepository::getSizeWatchlistRepository()
{
	return this->watch_list.getSize();
}
