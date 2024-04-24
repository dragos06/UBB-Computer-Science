#pragma once
#include "Service.h"
#include <string>
#include <vector>

class Console {
private:
	Service service;
public:
	Console(Service service);
	
	void startConsole();
	void printUser();
	void printMenuAdmin();
	void printMenuUser();

	void addTutorialConsole();
	void addWatchlistConsole(Tutorial tutorial);

	void deleteTutorialConsole();
	
	void updateTutorialConsole();
	
	void getTutorialsConsole();
	
	std::vector<Tutorial> tutorialsGivenPresenterConsole();

private:
	int validateNumber(const std::string& user_option);
	void generateStartup10Tutorials();
	void iterateTutorials();
	void deleteTutorialWatchList();
	void getWatchListConsole();
};