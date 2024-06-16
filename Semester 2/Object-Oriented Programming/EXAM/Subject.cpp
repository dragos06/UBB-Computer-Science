#include "Subject.h"

void Subject::registerObserver(Observer* observer)
{
	this->observers.push_back(observer);
}

void Subject::notify()
{
	for (auto o : this->observers)
		o->update();
}
