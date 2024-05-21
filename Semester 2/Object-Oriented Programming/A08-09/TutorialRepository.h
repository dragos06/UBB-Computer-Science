#pragma once
//#include "DynamicVector.h"
#include <vector>
#include "Tutorial.h"
#include <map>

class TutorialRepositoryBase {
public:
	std::vector<Tutorial> tutorials;
public:
	TutorialRepositoryBase() {};
	virtual void addTutorialRepository(const Tutorial& tutorial) = 0;
	virtual void deleteTutorialRepository(const Tutorial& tutorial) = 0;
	virtual std::vector<Tutorial> getTutorialsTutorialRepository() = 0;
	virtual Tutorial& getTutorialRepository(const std::string& title, const std::string& presenter) = 0;
	virtual int getSizeTutorialRepository() = 0;
	virtual void writeToFile() {};
	virtual void loadFromFile() {};

};

class TutorialRepository : public TutorialRepositoryBase
{
public:
	//<summary>Default destructor</summary>

	//<summary>Adds a tutorial to the repository</summary>
	//<param name="tutorial">The tutorial to be added</param>
	void addTutorialRepository(const Tutorial& tutorial) override;

	//<summary>Deletes a tutorial from the repository</summary>
	//<param name="tutorial">The tutorial to be deleted</param>
	void deleteTutorialRepository(const Tutorial& tutorial) override;

	//<summary>Getter for the tutorials in the repository</summary>
	//<returns>The tutorials in the repository</returns>
	std::vector<Tutorial> getTutorialsTutorialRepository() override;
	
	//<summary>Getter for a tutorial from the repository</summary>
	//<param name="title">The title of the tutorial</param>
	//<param name="presenter">The presenter of the tutorial</param>
	//<returns>The tutorial from the repository</returns>
	Tutorial& getTutorialRepository(const std::string& title, const std::string& presenter) override;
	
	//<summary>Getter for the size of the repository</summary>
	//<returns>The size of the repository</returns>
	int getSizeTutorialRepository() override;

};

class FileTutorialRepository : public TutorialRepository {
public:
	std::string filename;
public:
	FileTutorialRepository(std::string filename) : filename{ filename } {};

	void addTutorialRepository(const Tutorial& tutorial) override;
	void deleteTutorialRepository(const Tutorial& tutorial) override;
	std::vector<Tutorial> getTutorialsTutorialRepository() override;
	Tutorial& getTutorialRepository(const std::string& title, const std::string& presenter) override;
	int getSizeTutorialRepository() override;

	void writeToFile() override;
	void loadFromFile() override;
};