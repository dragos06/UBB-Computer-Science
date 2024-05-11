#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(FixedCapBiMap& d) : map(d)
{
	//TODO - Implementation
	//BC=WC=TC = Theta(1)
	this->currentPosition = 0;
}


void FixedCapBiMapIterator::first() {
	//TODO - Implementation
	//BC=WC=TC = Theta(1)
	this->currentPosition = 0;
}


void FixedCapBiMapIterator::next() {
	//TODO - Implementation
	//BC=WC=TC = Theta(1)
	if (this->currentPosition == this->map.mapSize) {
		throw exception();
	}
	this->currentPosition++;
}


TElem FixedCapBiMapIterator::getCurrent(){
	//TODO - Implementation
	//BC=WC=TC = Theta(1)
	if (this->currentPosition == this->map.mapSize) {
		throw exception();
	}
	return this->map.elements[this->currentPosition];
}


bool FixedCapBiMapIterator::valid() const {
	//TODO - Implementation
	//BC=WC=TC = Theta(1)
	return this->currentPosition < this->map.mapSize;
}

TElem FixedCapBiMapIterator::remove()
{
	//BC=WC=TC = Theta(1)
	TElem result;
	if (this->currentPosition >= this->map.mapSize) {
		throw exception();
	}
	result = this->map.elements[this->currentPosition];
	this->map.elements[this->currentPosition] = this->map.elements[this->map.mapSize - 1];
	this->map.mapSize--;
	return result;
}



