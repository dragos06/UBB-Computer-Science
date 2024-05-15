#include <iostream>
#include "TutorialRepository.h"
#include "Service.h"
#include "Console.h"
#include <crtdbg.h>
#include "Testing.h"
#include <iostream>
using namespace std;

int main() {
	{
		Tests test;
		test.TestAll();

		system("cls");

		FileTutorialRepository* tutorial_repository = new FileTutorialRepository("tutorials.txt");
		//TutorialRepository* tutorial_repository = new TutorialRepository;

		cout << "[1] CSV" << endl;
		cout << "[2] HTML" << endl;
		cout << "Please choose the file type: " << endl;
		string file_type_str;
		int file_type;
		getline(cin, file_type_str);
		file_type = stoi(file_type_str);
		if (file_type == 1) {
			WatchlistCSV* watchlist_repository = new WatchlistCSV("watchlist.csv");
			Service service = Service(tutorial_repository, watchlist_repository);
			Console console = Console(service);
			console.startConsole();
			delete watchlist_repository;
		}
		else if (file_type == 2) {
			WatchlistHTML* watchlist_repository = new WatchlistHTML("watchlist.html");
			Service service = Service(tutorial_repository, watchlist_repository);
			Console console = Console(service);
			console.startConsole();
			delete watchlist_repository;
		}
		delete tutorial_repository;
	}

	_CrtDumpMemoryLeaks();
}