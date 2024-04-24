#pragma once
#include "TutorialRepository.h"
#include "WatchlistRepository.h"

class Service {
private:
	TutorialRepository tutorial_repository;
	WatchlistRepository watchlist_repository;
public:
	//<summary>Default constructor</summary>
	Service();

	//<summary>Constructor with parameters</summary>
	//<param name="tutorial_repository">The repository of tutorials</param>
	//<param name="watchlist_repository">The repository of the watchlist</param>
	Service(TutorialRepository tutorial_repository, WatchlistRepository watchlist_repository);
	
	//<summary>Adds a tutorial to the repository</summary>
	//<param name="title">The title of the tutorial</param>
	//<param name="presenter">The presenter of the tutorial</param>
	//<param name="duration">The duration of the tutorial</param>
	//<param name="likes">The likes of the tutorial</param>
	//<param name="link">The link of the tutorial</param>
	void addTutorialService(const std::string& title, const std::string& presenter, int duration, int likes, const std::string& link);
	
	//<summary>Adds a tutorial to the watchlist</summary>
	//<param name="title">The title of the tutorial</param>
	//<param name="presenter">The presenter of the tutorial</param>
	//<param name="duration">The duration of the tutorial</param>
	//<param name="likes">The likes of the tutorial</param>
	//<param name="link">The link of the tutorial</param>
	void addWatchlistService(Tutorial tutorial);
	
	//<summary>Deletes a tutorial from the repository</summary>
	//<param name="title">The title of the tutorial</param>
	//<param name="presenter">The presenter of the tutorial</param>
	void deleteTutorialService(const std::string& title, const std::string& presenter);

	//<summary>Deletes a tutorial from the watchlist</summary>
	//<param name="title">The title of the tutorial</param>
	//<param name="presenter">The presenter of the tutorial</param>
	void deleteWatchlistService(const std::string& title, const std::string& presenter);

	//<summary>Updates a tutorial from the repository</summary>
	//<param name="title">The title of the tutorial</param>
	//<param name="presenter">The presenter of the tutorial</param>
	//<param name="duration">The duration of the tutorial</param>
	//<param name="likes">The likes of the tutorial</param>
	//<param name="link">The link of the tutorial</param>
	void updateTutorialService(const std::string& title, const std::string& presenter, int duration, int likes, const std::string& link);
	
	//<summary>Updates a tutorial from the watchlist</summary>
	//<param name="title">The title of the tutorial</param>
	//void updateWatchlistService(const std::string& title, const std::string& presenter, int duration, int likes, const std::string& link);
	
	//<summary>Getter for the tutorials in the repository</summary>
	//<returns>The tutorials in the repository</returns>
	Tutorial* getTutorialsService();

	//<summary>Getter for the size of the repository</summary>
	//<returns>The size of the repository</returns>
	int getSizeTutorialsService();

	//<summary>Getter for the watchlist</summary>
	//<returns>The watchlist</returns>
	Tutorial* getWatchlistService();

	//<summary>Getter for the size of the watchlist</summary>
	//<returns>The size of the watchlist</returns>
	int getSizeWatchlistService();

	//<summary>Getter for the tutorials given by a presenter</summary>
	//<param name="presenter">The presenter of the tutorials</param>
	//<returns>The tutorials given by the presenter</returns>
	Tutorial* tutorialsGivenPresenter(const std::string& presenter, int& number_elements);

};