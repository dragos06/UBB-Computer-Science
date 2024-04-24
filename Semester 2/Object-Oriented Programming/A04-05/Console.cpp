#include "Console.h"
#include <iostream>

Console::Console(Service service)
{
	this->service = service;
}

void Console::getTutorialsConsole()
{
	Tutorial* tutorials = this->service.getTutorialsService();
	for (int i = 0; i < this->service.getSizeTutorialsService(); i++)
		tutorials[i].printTutorial();
}

Tutorial* Console::tutorialsGivenPresenterConsole(int& number_elements)
{
	std::string given_string;
	std::cout << "\nPlease choose a presenter: ";
	std::getline(std::cin, given_string);
	Tutorial* tutorials = this->service.tutorialsGivenPresenter(given_string, number_elements);
	return tutorials;
}

bool Console::validateString(const std::string& user_option)
{
	for (int i = 0; i < user_option.length(); i++)
		if (isdigit(user_option[i]) == 0 && user_option[i] != ' ')
			return false;
	return true;
}

int Console::validateNumber(const std::string& user_option)
{
	return std::stoi(user_option);
}

void Console::generateStartup10Tutorials()
{
	this->service.addTutorialService("C++ Tutorial for Beginners - Learn C++ in 1 Hour", "Programming with Mosh", 1, 89000, "https://www.youtube.com/watch?v=ZzaPdXTrSb8");
	this->service.addTutorialService("C++ Tutorial for Beginners - Full Course", "freeCodeCamp.org", 4, 278000, "https://www.youtube.com/watch?v=vLnPwxZdW4Y");
	this->service.addTutorialService("C++ Programming Course - Beginner to Advanced", "freeCodeCamp.org", 31, 142000, "https://www.youtube.com/watch?v=8jLOx1hD3_o");
	this->service.addTutorialService("C++ Full Course for free", "Bro Code", 6, 105000, "https://www.youtube.com/watch?v=-TkoO8Z07hI");
	this->service.addTutorialService("Learn C++ With Me #9 - Arrays", "Tech With Tim", 1, 1500, "https://www.youtube.com/watch?v=1FVBeLD_FdE");
	this->service.addTutorialService("C++ Programming All-in-One Tutorial Series (10 HOURS!)", "Caleb Curry", 10, 57000, "https://www.youtube.com/watch?v=_bYFu9mBnr4");
	this->service.addTutorialService("Pointers in C / C++ [Full Course]", "freeCodeCamp.org", 4, 77000, "https://www.youtube.com/watch?v=zuegQmMdy8M");
	this->service.addTutorialService("you will never ask about pointers again after watching this video", "Low Level Learning", 1, 88000, "https://www.youtube.com/watch?v=2ybLD6_2gKM");
	this->service.addTutorialService("C++ Tutorial From Basic to Advance", "Extern Code", 9, 83000, "https://www.youtube.com/watch?v=mUQZ1qmKlLY");
	this->service.addTutorialService("C++ FULL COURSE For Beginners (Learn C++ in 10 hours)", "CodeBeauty", 10, 98000, "https://www.youtube.com/watch?v=GQp1zzTwrIg");
}

void Console::iterateTutorials()
{
	int number_elements = 0;
	Tutorial* tutorials = this->tutorialsGivenPresenterConsole(number_elements);
	if (number_elements != 0) {
		int k = 0;
		while (true) {
			try {
				std::cout << '\n';
				tutorials[k].printTutorial();
				system(std::string("start " + tutorials[k].getLink()).c_str());
				std::cout << "\n[1] Add to watch list.\n";
				std::cout << "[2] Do not add to watch list.\n";
				std::cout << "[3] Exit.\n";
				std::string user_option;
				std::cout << "\nPlease choose an option: ";
				std::getline(std::cin, user_option);
				int user_option_valid = 0;
				user_option_valid = this->validateNumber(user_option);
				bool to_return = false;
				switch (user_option_valid) {
				case 0: {
					std::cout << "\nPlease provide an integer!\n";
					break;
				}
				case 1: {
					this->addWatchlistConsole(tutorials[k]);
					k = (k + 1) % number_elements;
					break;
				}
				case 2: {
					k = (k + 1) % number_elements;
					break;
				}
				case 3: {
					to_return = true;
				}
				}
				if (to_return)
					break;
			}
			catch (std::invalid_argument& e) {
				std::cout << e.what() << "\n";
			}
		}
	}
	delete[] tutorials;
}

void Console::deleteTutorialWatchList()
{
	std::string title, presenter;

	std::cout << "\nPlease enter the title of the tutorial: ";
	std::getline(std::cin, title);

	std::cout << "\nPlease enter the presenter of the tutorial: ";
	std::getline(std::cin, presenter);

	bool found = false;
	Tutorial* tutorials = this->service.getWatchlistService();
	for (int i = 0; i < this->service.getSizeWatchlistService(); i++)
		if (tutorials[i].getTitle() == title && tutorials[i].getPresenter() == presenter)
			found = true;
	if (found)
	{
		std::cout << "\nLike the tutorial?\n";
		std::cout << "[1] Yes.\n";
		std::cout << "[2] No.\n";
		std::string user_option;
		std::cout << "\nPlease choose an option: ";
		std::getline(std::cin, user_option);
		int user_option_valid = 0;
		user_option_valid = this->validateNumber(user_option);

		switch (user_option_valid) {
		case 0: {
			std::cout << "Please provide an integer!";
			break;
		}
		case 1: {
			tutorials = this->service.getTutorialsService();
			for (int i = 0; i < this->service.getSizeTutorialsService(); i++)
				if (tutorials[i].getTitle() == title && tutorials[i].getPresenter() == presenter)
					tutorials[i].setLikes(tutorials[i].getLikes() + 1);
			break;
		}
		case 2: {
			break;
		}
		}

		this->service.deleteWatchlistService(title, presenter);
	}
	else
		std::cout << "\nTutorial not in the watch list\n";
}

void Console::getWatchListConsole()
{
	Tutorial* watch_list = this->service.getWatchlistService();
	for (int i = 0; i < this->service.getSizeWatchlistService(); i++)
		watch_list[i].printTutorial();
}



void Console::startConsole()
{
	this->generateStartup10Tutorials();
	while (true) {
		try {
			this->printUser();
			std::string user_option;
			std::cout << "\nPlease choose an option: ";
			std::getline(std::cin, user_option);
			int user_option_valid = 0;
			user_option_valid = this->validateNumber(user_option);
			switch (user_option_valid) {
			case 0: {
				std::cout << "\nPlease provide an integer!\n";
				break;
			}
			case 1: {
				while (true) {
					try {
						this->printMenuAdmin();
						std::string user_option_admin;
						std::cout << "\nPlease choose an option: ";
						std::getline(std::cin, user_option_admin);
						int user_option_admin_valid = 0;
						user_option_admin_valid = this->validateNumber(user_option_admin);
						bool to_return = false;
						switch (user_option_admin_valid) {
						case 0: {
							std::cout << "\nPlease provide an integer!\n";
							break;
						}
						case 1: {
							this->addTutorialConsole();
							break;
						}
						case 2: {
							this->deleteTutorialConsole();
							break;
						}
						case 3: {
							this->updateTutorialConsole();
							break;
						}
						case 4: {
							std::cout << '\n';
							this->getTutorialsConsole();
							break;
						}
						case 5: {
							to_return = true;
						}
						}
						if (to_return)
							break;
					}
					catch (std::invalid_argument& e) {
						std::cout << e.what() <<"\n";
					
					}
				}
				break;
			}
			case 2: {
				while (true) {
					try {
						this->printMenuUser();
						std::string user_option_user;
						std::cout << "\nPlease choose an option: ";
						std::getline(std::cin, user_option_user);
						int user_option_user_valid = 0;
						user_option_user_valid = this->validateNumber(user_option_user);
						bool to_return = false;
						switch (user_option_user_valid) {
						case 0: {
							std::cout << "\nPlease provide an integer!\n";
							break;
						}
						case 1: {
							this->iterateTutorials();
							break;
						}
						case 2: {
							this->deleteTutorialWatchList();
							break;
						}
						case 3: {
							this->getWatchListConsole();
							break;
						}
						case 4: {
							to_return = true;
						}
						}
						if (to_return)
							break;
					}
					catch (std::invalid_argument& e) {
						std::cout << e.what() << "\n";
					}
				}
				break;

			}
			case 3: {
				std::cout << "\nExiting...\n";
				return;
			}
			}
		}
		catch (std::invalid_argument)
		{
			std::cout << "\nInvalid input!\n";
		}
	}
}

void Console::printUser()
{
	std::cout << "\n	MASTER C++";
	std::cout << "\n[1] Administrator mode";
	std::cout << "\n[2] User mode";
	std::cout << "\n[3] Exit\n";
}

void Console::printMenuAdmin()
{
	std::cout << "\n[1] Add a new tutorial";
	std::cout << "\n[2] Delete a tutorial";
	std::cout << "\n[3] Update the information of a tutorial";
	std::cout << "\n[4] See all the tutorials in the database";
	std::cout << "\n[5] Go back\n";
}

void Console::printMenuUser()
{
	std::cout << "\n[1] See the tutorials having a given presenter";
	std::cout << "\n[2] Delete a tutorial from the watch list";
	std::cout << "\n[3] See the watch list";
	std::cout << "\n[4] Go back\n";
}

void Console::addTutorialConsole()
{
	std::string pre_duration, pre_likes;
	std::string title, presenter, link;
	int duration = 0, likes = 0;
	
	std::cout << "\nPlease enter the title of the tutorial: ";
	std::getline(std::cin, title);

	std::cout << "\nPlease enter the presenter of the tutorial: ";
	std::getline(std::cin, presenter);

	std::cout << "\nPlease enter the duration of the tutorial: ";
	std::getline(std::cin, pre_duration);
	duration = this->validateNumber(pre_duration);
	if (duration == 0) {
		std::cout << "\nInvalid duration!\n";
		return;
	}

	std::cout << "\nPlease enter the likes of the tutorial: ";
	std::getline(std::cin, pre_likes);
	likes = this->validateNumber(pre_likes);
	if (likes == 0) {
		std::cout << "\nInvalid likes!\n";
		return;
	}
	
	std::cout << "\nPlease enter the link of the tutorial: ";
	std::getline(std::cin, link);

	this->service.addTutorialService(title, presenter, duration, likes, link);
}

void Console::addWatchlistConsole(Tutorial tutorial)
{
	this->service.addWatchlistService(tutorial);
}

void Console::deleteTutorialConsole()
{
	std::string title, presenter;

	std::cout << "\nPlease enter the title of the tutorial: ";
	std::getline(std::cin, title);

	std::cout << "\nPlease enter the presenter of the tutorial: ";
	std::getline(std::cin, presenter);

	this->service.deleteTutorialService(title, presenter);
}

void Console::updateTutorialConsole()
{
	std::string pre_duration, pre_likes;
	std::string title, presenter, link;
	int duration = 0, likes = 0;

	std::cout << "\nPlease enter the old title of the tutorial: ";
	std::getline(std::cin, title);

	std::cout << "\nPlease enter the old presenter of the tutorial: ";
	std::getline(std::cin, presenter);

	std::cout << "\nPlease enter the new duration of the tutorial: ";
	std::getline(std::cin, pre_duration);
	duration = this->validateNumber(pre_duration);
	if (duration == 0) {
		std::cout << "\nInvalid duration!\n";
		return;
	}

	std::cout << "\nPlease enter the new likes of the tutorial: ";
	std::getline(std::cin, pre_likes);
	likes = this->validateNumber(pre_likes);
	if (likes == 0) {
		std::cout << "\nInvalid likes!\n";
		return;
	}

	std::cout << "\nPlease enter the new link of the tutorial: ";
	std::getline(std::cin, link);

	this->service.updateTutorialService(title, presenter, duration, likes, link);
}
