#include "Testing.h"
#include "Tutorial.h"
#include "TutorialRepository.h"
#include "WatchlistRepository.h"
#include "Service.h"
#include <assert.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "RepositoryExceptions.h"
using namespace std;


void Tests::TestTutorial()
{
	Tutorial test_tutorial{ "C++ Tutorial", "John Doe", 10, 10000, "www.link1" };
	assert(test_tutorial.getTitle() == "C++ Tutorial");
	assert(test_tutorial.getPresenter() == "John Doe");
	assert(test_tutorial.getDuration() == 10);
	assert(test_tutorial.getLikes() == 10000);
	assert(test_tutorial.getLink() == "www.link1");

	test_tutorial.setTitle("New Title");
	test_tutorial.setPresenter("New Presenter");
	test_tutorial.setDuration(999);
	test_tutorial.setLikes(999);
	test_tutorial.setLink("www.New Link");

	assert(test_tutorial.getTitle() == "New Title");
	assert(test_tutorial.getPresenter() == "New Presenter");
	assert(test_tutorial.getDuration() == 999);
	assert(test_tutorial.getLikes() == 999);
	assert(test_tutorial.getLink() == "www.New Link");

	test_tutorial.setTitle("Tutorial Test");
	test_tutorial.setPresenter("Test Complete");
	test_tutorial.setDuration(1);
	test_tutorial.setLikes(1);
	test_tutorial.setLink("");

	cout<<test_tutorial;
}

void Tests::TestTutorialRepository()
{
	TutorialRepository* test_tutorial_repository = new TutorialRepository();
	test_tutorial_repository->addTutorialRepository(Tutorial{ "title","presenter",1,2,"www.link" });
	assert(test_tutorial_repository->getSizeTutorialRepository() == 1);
	assert(test_tutorial_repository->getTutorialRepository("title", "presenter").getTitle() == "title");
	assert(test_tutorial_repository->getTutorialsTutorialRepository()[0].getPresenter() == "presenter");

	try {
		test_tutorial_repository->addTutorialRepository(Tutorial{ "title","presenter",1,2,"www.link" });
	}
	catch (RepositoryException){
		assert(true);
	}

	Tutorial tutorial{ "title","presenter",1,2,"link" };
	test_tutorial_repository->deleteTutorialRepository(tutorial);
	assert(test_tutorial_repository->getSizeTutorialRepository() == 0);

	try {
		test_tutorial_repository->deleteTutorialRepository(Tutorial{ "title","presenter",1,2,"www.link" });
	}
	catch (RepositoryException) {
		assert(true);
	}
	try {
		test_tutorial_repository->getTutorialRepository("a", "b");
	}
	catch (RepositoryException) {
		assert(true);
	}

	delete test_tutorial_repository;
}

void Tests::TestWatchListRepository()
{
	WatchlistRepository* test_watchlist_repository = new WatchlistRepository();
	test_watchlist_repository->addWatchlistRepository(Tutorial{ "title", "presenter", 1, 2, "www.link" });
	assert(test_watchlist_repository->getSizeWatchlistRepository() == 1);
	assert(test_watchlist_repository->getTutorialWatchlistRepository("title", "presenter").getTitle() == "title");
	assert(test_watchlist_repository->getTutorialsWatchlistRepository()[0].getPresenter() == "presenter");

	try {
		test_watchlist_repository->addWatchlistRepository(Tutorial{ "title","presenter",1,2,"www.link" });
	}
	catch (RepositoryException) {
		assert(true);
	}

	test_watchlist_repository->deleteWatchlistRepository(Tutorial{ "title", "presenter", 1, 2, "www.link" });
	assert(test_watchlist_repository->getSizeWatchlistRepository() == 0);

	try {
		test_watchlist_repository->deleteWatchlistRepository(Tutorial{ "title", "presenter", 1, 2, "www.link" });
	}
	catch (RepositoryException) {
		assert(true);
	}

	delete test_watchlist_repository;
}

void Tests::TestService()
{
	TutorialRepository* tutorial_repository = new TutorialRepository();
	WatchlistRepository* watchlist_repository = new WatchlistRepository();
	Service test_service{ tutorial_repository, watchlist_repository };
	Service service1;

	test_service.addTutorialService("title", "presenter", 1, 2, "www.link");
	assert(test_service.getSizeTutorialsService() == 1);
	assert(test_service.getTutorialsService()[0].getTitle() == "title");

	test_service.deleteTutorialService("title", "presenter");
	assert(test_service.getSizeTutorialsService() == 0);

	test_service.addTutorialService("title1", "presenter1", 1, 2, "www.link1");
	test_service.addTutorialService("title2", "presenter2", 3, 4, "www.link2");
	test_service.addTutorialService("title3", "presenter2", 5, 6, "www.link3");

	test_service.updateTutorialService("title1", "presenter1", 99, 99, "www.new link");
	assert(test_service.getTutorialsService()[0].getDuration() == 99);
	assert(test_service.getTutorialsService()[0].getLikes() == 99);
	assert(test_service.getTutorialsService()[0].getLink() == "www.new link");

	test_service.addWatchlistService(Tutorial{ "title2", "presenter2", 3, 4, "www.link2" });
	assert(test_service.getSizeWatchlistService() == 1);
	assert(test_service.getWatchlistService()[0].getTitle() == "title2");
	vector<Tutorial> tutorials = test_service.tutorialsGivenPresenter("presenter2");
	assert(tutorials.size() == 2);
	tutorials = test_service.tutorialsGivenPresenter("");
	assert(tutorials.size() == 3);

	test_service.deleteWatchlistService("title2", "presenter2", 0);
	assert(test_service.getSizeWatchlistService() == 0);

	delete tutorial_repository;
	delete watchlist_repository;
}


void Tests::TestAll()
{
	TestTutorial();
	TestTutorialRepository();
	TestWatchListRepository();
	TestService();
}
