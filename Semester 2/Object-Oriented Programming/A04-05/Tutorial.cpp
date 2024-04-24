#include "Tutorial.h"
#include <iostream>

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

void Tutorial::printTutorial()
{
	std::cout << this->title << " | " << this->presenter << " | " << this->duration << " | " << this->likes << " | " << this->link << '\n';
}




