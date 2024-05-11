#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	// WC = BC = TC = Theta(1)

	this->current_node = d.head;
	if (d.head != nullptr) {
		this->current_value = d.head->getValueHead();
	}
}

void SMMIterator::first(){
	// WC = BC = TC = Theta(1)

	this->current_node = this->map.head;
	if (this->map.head != nullptr) {
		this->current_value = this->map.head->getValueHead();
	}
}

void SMMIterator::next(){
	// WC = BC = TC = Theta(1)

	if (!this->valid())
		throw exception();
	if (current_value->getNext() != nullptr)
		current_value = current_value->getNext();
	else {
		current_node = current_node->getNext();
		if (current_node != nullptr)
			current_value = current_node->getValueHead();
	}
}

bool SMMIterator::valid() const{
	// WC = BC = TC = Theta(1)

	return this->current_node != nullptr;
}

TElem SMMIterator::getCurrent() const{
	// WC = BC = TC = Theta(1)
	
	if (!this->valid())
		throw exception();
	return TElem(current_node->getKey(), current_value->getInfo());
}


