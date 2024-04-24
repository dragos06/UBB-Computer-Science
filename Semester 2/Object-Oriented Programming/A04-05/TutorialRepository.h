#pragma once
#include "DynamicVector.h"

class TutorialRepository
{
private:
	DynamicVector<class Tutorial> tutorials = DynamicVector<class Tutorial>();
public:
	//<summary>Default destructor</summary>
	~TutorialRepository();

	//<summary>Adds a tutorial to the repository</summary>
	//<param name="tutorial">The tutorial to be added</param>
	void addTutorialRepository(Tutorial tutorial);

	//<summary>Deletes a tutorial from the repository</summary>
	//<param name="tutorial">The tutorial to be deleted</param>
	void deleteTutorialRepository(Tutorial tutorial);

	//<summary>Getter for the tutorials in the repository</summary>
	//<returns>The tutorials in the repository</returns>
	Tutorial* getTutorialsTutorialRepository();
	
	//<summary>Getter for a tutorial from the repository</summary>
	//<param name="title">The title of the tutorial</param>
	//<param name="presenter">The presenter of the tutorial</param>
	//<returns>The tutorial from the repository</returns>
	Tutorial& getTutorialRepository(const std::string& title, const std::string& presenter);
	
	//<summary>Getter for the size of the repository</summary>
	//<returns>The size of the repository</returns>
	int getSizeTutorialRepository();
};