#include <iostream>
#include "TutorialRepository.h"
#include "Service.h"
#include "Console.h"
#include <crtdbg.h>
#include "Testing.h"


int main() {
	{
		//Tests test;
		//test.TestAll();

		system("cls");

		TutorialRepository tutorial_repository = TutorialRepository();
		WatchlistRepository watchlist_repository = WatchlistRepository();
		Service service = Service(tutorial_repository, watchlist_repository);
		Console console = Console(service);
		console.startConsole();
	}

	_CrtDumpMemoryLeaks();
}