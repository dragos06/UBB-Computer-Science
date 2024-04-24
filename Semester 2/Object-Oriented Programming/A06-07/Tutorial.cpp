#include "Tutorial.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

Tutorial::Tutorial()
{
	this->title = "";
	this->presenter = "";
	this->duration = 0;
	this->likes = 0;
	this->link = "";
}

Tutorial::Tutorial(std::string title, std::string presenter, int duration, int likes, std::string link)
{
	this->title = title;
	this->presenter = presenter;
	this->duration = duration;
	this->likes = likes;
	this->link = link;
}

Tutorial::Tutorial(const Tutorial& tutorial)
{
	this->title = tutorial.title;
	this->presenter = tutorial.presenter;
	this->duration = tutorial.duration;
	this->likes = tutorial.likes;
	this->link = tutorial.link;
}

std::string Tutorial::getTitle() const
{
	return this->title;
}

std::string Tutorial::getPresenter() const
{
	return this->presenter;
}

int Tutorial::getDuration() const
{
	return this->duration;
}

int Tutorial::getLikes() const
{
	return this->likes;
}

std::string Tutorial::getLink() const
{
	return this->link;
}

bool Tutorial::operator==(const Tutorial& tutorial)
{
	return this->title == tutorial.title && this->presenter == tutorial.presenter;
}

void Tutorial::setTitle(const std::string& title)
{
	this->title = title;
}

void Tutorial::setPresenter(const std::string& presenter)
{
	this->presenter = presenter;
}

void Tutorial::setDuration(int duration)
{
	this->duration = duration;
}

void Tutorial::setLikes(int likes)
{
	this->likes = likes;
}

void Tutorial::setLink(const std::string& link)
{
	this->link = link;
}

//void Tutorial::printTutorial()
//{
//	std::cout << this->title << " | " << this->presenter << " | " << this->duration << " | " << this->likes << " | " << this->link << '\n';
//}

vector<string> tokenize(string str, char delimiter)
{
	vector<string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;

}

std::istream& operator>>(std::istream& is, Tutorial& tutorial)
{
	string line;
	getline(is, line);

	vector<string> tokens = tokenize(line, ',');
	if (tokens.size() != 5)
		return is;
	tutorial.title = tokens[0];
	tutorial.presenter = tokens[1];
	tutorial.duration = stoi(tokens[2]);
	tutorial.likes = stoi(tokens[3]);
	tutorial.link = stoi(tokens[4]);
}

std::ostream& operator<<(std::ostream& os, const Tutorial& tutorial)
{
	os << tutorial.title << "," << tutorial.presenter << "," << tutorial.duration << "," << tutorial.likes << "," << tutorial.link << "\n";
	return os;
}

