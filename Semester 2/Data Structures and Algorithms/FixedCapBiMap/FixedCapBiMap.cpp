#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"

FixedCapBiMap::FixedCapBiMap(int capacity) {
	//TODO - Implementation
	//BC=WC=TC = Theta(1)
	if (capacity <= 0) {
		throw exception();
	}
	this->capacity = capacity;
	this->mapSize = 0;
	this->elements = new TElem[this->capacity];
}

FixedCapBiMap::~FixedCapBiMap() {
	//TODO - Implementation
	//BC=WC=TC = Theta(1)
	delete[] this->elements;
}

bool FixedCapBiMap::add(TKey c, TValue v){
	//TODO - Implementation
	//BC = Theta(1), when element is present on the first two positions
	//WC = Theta(n), when element is not present or at the end
	//TC = O(n), because BC != WC
	if (this->mapSize == this->capacity) {
		throw exception();
	}
	int count = 0;
	int index = 0;
	while (count < 2 && index < this->mapSize) {
		if (this->elements[index].first == c) {
			count++;
		}
		index++;
	}
	if (count == 2) {
		return false;
	}
	this->elements[this->mapSize].first = c;
	this->elements[this->mapSize].second = v;
	this->mapSize++;
	return true;
}

ValuePair FixedCapBiMap::search(TKey c) const{
	//TODO - Implementation
	//BC = Theta(1), when element is found on first 2 positions
	//WC = Theta(n), when element is not found or on last positions
	//TC = O(n), because BC!=WC
	ValuePair result;
	result.first = NULL_TVALUE;
	result.second = NULL_TVALUE;
	int nrfound = 0;
	int index = 0;
	while (nrfound < 2 && index < this->mapSize) {
		if (this->elements[index].first == c) {
			if (nrfound == 0) {
				result.first = this->elements[index].second;
				nrfound++;
			}
			else {
				result.second = this->elements[index].second;
				nrfound++;
			}
		}
		index++;
	}
	return result;
}

bool FixedCapBiMap::remove(TKey c, TValue v){
	//TODO - Implementation
	//BC = Theta(1), if element is on first position
	//WC = Theta(n), if element is not present or is on last position
	//TC = O(n), because BC != WC
	int index = 0;
	while (index < this->mapSize) {
		if (this->elements[index].first == c && this->elements[index].second == v) {
			this->elements[index] = this->elements[this->mapSize - 1];
			this->mapSize--;
			return true;
		}
		index++;
	}
	return false;
}


int FixedCapBiMap::size() const {
	//TODO - Implementation
	//BC=WC=TC = Theta(1)
	return this->mapSize;
}

bool FixedCapBiMap::isEmpty() const{
	//TODO - Implementation
	//BC=WC=TC = Theta(1)
	return this->mapSize == 0;
}

bool FixedCapBiMap::isFull() const {
	//TODO - Implementation
	//BC=WC=TC = Theta(1)
	return this->mapSize == this->capacity;
}

int FixedCapBiMap::mostFrequentValue() const{
	//for the most frequent values, return the number of its occurency
	//BC=WC=TC = Theta(n^2)
	int max = 0;
	for (int i = 0; i < this->mapSize; i++) {
		int count = 0;
		for (int j = 0; j < this->mapSize; j++) {
			if (this->elements[i].second == this->elements[j].second) {
				count++;
			}
		}
		if (count > max) {
			max = count;
		}
	}
	return max;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() {
	//BC=WC=TC = Theta(1)
	return FixedCapBiMapIterator(*this);
}





