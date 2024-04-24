#include "WatchlistRepository.h"
#include <stdexcept>
using namespace std;

WatchlistRepository::~WatchlistRepository()
{
}

void WatchlistRepository::addWatchlistRepository(const Tutorial& tutorial)
{
	auto it = find(this->watch_list.begin(), this->watch_list.end(), tutorial);
	if (it != this->watch_list.end())
		throw std::invalid_argument("Tutorial already exists");
	this->watch_list.push_back(tutorial);
}

void WatchlistRepository::deleteWatchlistRepository(const Tutorial& tutorial)
{
	auto it = find(this->watch_list.begin(), this->watch_list.end(), tutorial);
	if (it != this->watch_list.end())
		this->watch_list.erase(it);
	else
		throw std::invalid_argument("Tutorial does not exist");
}

vector<Tutorial> WatchlistRepository::getTutorialsWatchlistRepository()
{
	return this->watch_list;
}

Tutorial& WatchlistRepository::getTutorialWatchlistRepository(const std::string& title, const std::string& presenter)
{
	for (auto it = this->watch_list.begin(); it!= this->watch_list.end(); it++)
		if ((*it).getTitle() == title && (*it).getPresenter() == presenter)
			return (*it);
	throw std::invalid_argument("Tutorial does not exist");
}

int WatchlistRepository::getSizeWatchlistRepository()
{
	return this->watch_list.size();
}
