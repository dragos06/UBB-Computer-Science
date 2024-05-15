#include "WatchlistRepository.h"
#include "RepositoryExceptions.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <cstdlib>
using namespace std;

void WatchlistRepository::addWatchlistRepository(const Tutorial& tutorial)
{
	auto it = find(this->watch_list.begin(), this->watch_list.end(), tutorial);
	if (it != this->watch_list.end())
		throw DuplicateTutorialException();
	this->watch_list.push_back(tutorial);
}

void WatchlistRepository::deleteWatchlistRepository(const Tutorial& tutorial)
{
	auto it = find(this->watch_list.begin(), this->watch_list.end(), tutorial);
	if (it != this->watch_list.end())
		this->watch_list.erase(it);
	else
		throw InexistentTutorialException();
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
	throw InexistentTutorialException();
}

int WatchlistRepository::getSizeWatchlistRepository()
{
	return this->watch_list.size();
}

void WatchlistCSV::addWatchlistRepository(const Tutorial& tutorial)
{
	WatchlistRepository::addWatchlistRepository(tutorial);
	this->writeToFile();
}

void WatchlistCSV::deleteWatchlistRepository(const Tutorial& tutorial)
{
	WatchlistRepository::deleteWatchlistRepository(tutorial);
	this->writeToFile();
}

std::vector<Tutorial> WatchlistCSV::getTutorialsWatchlistRepository()
{
	return WatchlistRepository::getTutorialsWatchlistRepository();
}

Tutorial& WatchlistCSV::getTutorialWatchlistRepository(const std::string& title, const std::string& presenter)
{
	return WatchlistRepository::getTutorialWatchlistRepository(title, presenter);
}

int WatchlistCSV::getSizeWatchlistRepository()
{
	return WatchlistRepository::getSizeWatchlistRepository();
}

void WatchlistCSV::writeToFile()
{
	ofstream file(this->filename);
	if (!file.is_open())
		throw std::invalid_argument("The file could not be opened!");
	for (auto tutorial : this->watch_list)
		file << tutorial.getTitle() << "," << tutorial.getPresenter() << "," << tutorial.getDuration() << "," << tutorial.getLikes() << "," << tutorial.getLink() << "\n";
	file.close();
}

void WatchlistCSV::openWatchlist()
{
	system(string("notepad \"watchlist.csv\"").c_str());
	return;
}

void WatchlistHTML::addWatchlistRepository(const Tutorial& tutorial)
{
	WatchlistRepository::addWatchlistRepository(tutorial);
	this->writeToFile();
}

void WatchlistHTML::deleteWatchlistRepository(const Tutorial& tutorial)
{
	WatchlistRepository::deleteWatchlistRepository(tutorial);
	this->writeToFile();
}

std::vector<Tutorial> WatchlistHTML::getTutorialsWatchlistRepository()
{
	return WatchlistRepository::getTutorialsWatchlistRepository();
}

Tutorial& WatchlistHTML::getTutorialWatchlistRepository(const std::string& title, const std::string& presenter)
{
	return WatchlistRepository::getTutorialWatchlistRepository(title, presenter);
}

int WatchlistHTML::getSizeWatchlistRepository()
{
	return WatchlistRepository::getSizeWatchlistRepository();
}

void WatchlistHTML::writeToFile()
{
	ofstream file(this->filename);
	if (!file.is_open())
		throw std::invalid_argument("The file could not be opened!");
	file << "<!DOCTYPE html>\n";
	file << "<html>\n";
	file << "<head>\n";
	file << "<title>Watchlist</title>\n";
	file << "</head>\n";
	file << "<body>\n";
	file << "<table border=\"1\">\n";
	file << "<tr>\n";
	file << "<td>Title</td>\n";
	file << "<td>Presenter</td>\n";
	file << "<td>Duration</td>\n";
	file << "<td>Likes</td>\n";
	file << "<td>Link</td>\n";
	file << "</tr>\n";
	for (auto tutorial : this->watch_list)
	{
		file << "<tr>\n";
		file << "<td>" << tutorial.getTitle() << "</td>\n";
		file << "<td>" << tutorial.getPresenter() << "</td>\n";
		file << "<td>" << tutorial.getDuration() << "</td>\n";
		file << "<td>" << tutorial.getLikes() << "</td>\n";
		file << "<td><a href=\"" << tutorial.getLink() << "\">Link</a></td>\n";
		file << "</tr>\n";
	}
	file << "</table>\n";
	file << "</body>\n";
	file << "</html>\n";
	file.close();
}

void WatchlistHTML::openWatchlist()
{
	ShellExecuteA(NULL, NULL, "C:\\Program Files\\Mozilla Firefox\\firefox.exe", "watchlist.html", NULL, SW_SHOWMAXIMIZED);
	//"C:\\Users\\Dragos\\College\\Object-Oriented Programming\\oop-a6-7-dragos06\\oop-a6-7-dragos06\\watchlist.html"
	return;
}
