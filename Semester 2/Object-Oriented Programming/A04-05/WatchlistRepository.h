#pragma once
#include "DynamicVector.h"

class WatchlistRepository {
private:
	DynamicVector<class Tutorial> watch_list = DynamicVector<class Tutorial>();
public:
	
	//<summary>Default destructor</summary>
	~WatchlistRepository();

	//<summary>Adds a tutorial to the watchlist repository</summary>
	//<param name="tutorial">The tutorial to be added</param>
	void addWatchlistRepository(Tutorial tutorial);

	//<summary>Deletes a tutorial from the watchlist repository</summary>
	//<param name="tutorial">The tutorial to be deleted</param>
	void deleteWatchlistRepository(Tutorial tutorial);


	//<summary>Getter for the tutorials in the watchlist repository</summary>
	//<returns>The tutorials in the watchlist repository</returns>
	Tutorial* getTutorialsWatchlistRepository();

	//<summary>Getter for a tutorial from the watchlist repository</summary>
	//<param name="title">The title of the tutorial</param>
	//<param name="presenter">The presenter of the tutorial</param>
	//<returns>The tutorial from the watchlist repository</returns>
	Tutorial& getTutorialWatchlistRepository(const std::string& title, const std::string& presenter);
	
	//<summary>Getter for the size of the watchlist repository</summary>
	//<returns>The size of the watchlist repository</returns>
	int getSizeWatchlistRepository();
};