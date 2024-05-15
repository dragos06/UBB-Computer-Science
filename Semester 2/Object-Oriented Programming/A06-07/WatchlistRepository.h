#pragma once
#include "Tutorial.h"
#include <vector>
#include <string>

class WatchlistBase {
protected:
	std::vector<Tutorial> watch_list;
public:
	WatchlistBase() {}
	//<summary>Adds a tutorial to the watchlist repository</summary>
	//<param name="tutorial">The tutorial to be added</param>
	virtual void addWatchlistRepository(const Tutorial& tutorial) = 0;

	//<summary>Deletes a tutorial from the watchlist repository</summary>
	//<param name="tutorial">The tutorial to be deleted</param>
	virtual void deleteWatchlistRepository(const Tutorial& tutorial) = 0;


	//<summary>Getter for the tutorials in the watchlist repository</summary>
	//<returns>The tutorials in the watchlist repository</returns>
	virtual std::vector<Tutorial> getTutorialsWatchlistRepository() = 0;

	//<summary>Getter for a tutorial from the watchlist repository</summary>
	//<param name="title">The title of the tutorial</param>
	//<param name="presenter">The presenter of the tutorial</param>
	//<returns>The tutorial from the watchlist repository</returns>
	virtual Tutorial& getTutorialWatchlistRepository(const std::string& title, const std::string& presenter) = 0;


	//<summary>Getter for the size of the watchlist repository</summary>
	//<returns>The size of the watchlist repository</returns>
	virtual int getSizeWatchlistRepository() = 0;

	virtual void writeToFile() {};
	virtual void openWatchlist() {};
};

class WatchlistRepository : public WatchlistBase{
public:
	//<summary>Adds a tutorial to the watchlist repository</summary>
	//<param name="tutorial">The tutorial to be added</param>
	void addWatchlistRepository(const Tutorial& tutorial) override;

	//<summary>Deletes a tutorial from the watchlist repository</summary>
	//<param name="tutorial">The tutorial to be deleted</param>
	void deleteWatchlistRepository(const Tutorial& tutorial) override;


	//<summary>Getter for the tutorials in the watchlist repository</summary>
	//<returns>The tutorials in the watchlist repository</returns>
	std::vector<Tutorial> getTutorialsWatchlistRepository() override;

	//<summary>Getter for a tutorial from the watchlist repository</summary>
	//<param name="title">The title of the tutorial</param>
	//<param name="presenter">The presenter of the tutorial</param>
	//<returns>The tutorial from the watchlist repository</returns>
	Tutorial& getTutorialWatchlistRepository(const std::string& title, const std::string& presenter) override;
	

	//<summary>Getter for the size of the watchlist repository</summary>
	//<returns>The size of the watchlist repository</returns>
	int getSizeWatchlistRepository() override;
};

class WatchlistCSV : public WatchlistRepository {
protected:
	std::string filename;
public:
	WatchlistCSV(std::string filename) : filename{ filename } {}
	//<summary>Adds a tutorial to the watchlist repository</summary>
	//<param name="tutorial">The tutorial to be added</param>
	void addWatchlistRepository(const Tutorial& tutorial) override;

	//<summary>Deletes a tutorial from the watchlist repository</summary>
	//<param name="tutorial">The tutorial to be deleted</param>
	void deleteWatchlistRepository(const Tutorial& tutorial) override;


	//<summary>Getter for the tutorials in the watchlist repository</summary>
	//<returns>The tutorials in the watchlist repository</returns>
	std::vector<Tutorial> getTutorialsWatchlistRepository() override;

	//<summary>Getter for a tutorial from the watchlist repository</summary>
	//<param name="title">The title of the tutorial</param>
	//<param name="presenter">The presenter of the tutorial</param>
	//<returns>The tutorial from the watchlist repository</returns>
	Tutorial& getTutorialWatchlistRepository(const std::string& title, const std::string& presenter) override;


	//<summary>Getter for the size of the watchlist repository</summary>
	//<returns>The size of the watchlist repository</returns>
	int getSizeWatchlistRepository() override;

	void writeToFile();
	void openWatchlist() override;
};

class WatchlistHTML : public WatchlistRepository {
protected:
	std::string filename;
public:
	WatchlistHTML(std::string filename) : filename{ filename } {}
	void addWatchlistRepository(const Tutorial& tutorial) override;
	void deleteWatchlistRepository(const Tutorial& tutorial) override;
	std::vector<Tutorial> getTutorialsWatchlistRepository() override;
	Tutorial& getTutorialWatchlistRepository(const std::string& title, const std::string& presenter) override;
	int getSizeWatchlistRepository() override;
	void writeToFile();
	void openWatchlist() override;
};
