#pragma once
#include "Service.h"
#include <string>

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
	//void deleteWatchlistConsole();

	void updateTutorialConsole();
	//void updateWatchlistConsole();

	void getTutorialsConsole();
	
	Tutorial* tutorialsGivenPresenterConsole(int& number_elements);
private:
	bool validateString(const std::string& user_option);
	int validateNumber(const std::string& user_option);
	void generateStartup10Tutorials();
	void iterateTutorials();
	void deleteTutorialWatchList();
	void getWatchListConsole();
};