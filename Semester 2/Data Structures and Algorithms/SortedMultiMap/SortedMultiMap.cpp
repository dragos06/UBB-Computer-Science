#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	// WC = BC = TC = Theta(1)
	this->head = nullptr;
	this->relation = r;
	this->sll_size = 0;
}

void SortedMultiMap::add(TKey c, TValue v) {
	// WC = Theta(n), Key already exists and the value needs to be added at the end
	// BC = Theta(1), Key doesn't exist and it needs to be added on the first position
	// TC = O(n)

	NodeSMM* previous = nullptr;
	NodeSMM* current = this->head;
	while (current != nullptr && this->relation(current->getKey(), c) && current->getKey() != c) {
		previous = current;
		current = current->getNext();
	}
	if (current != nullptr && current->getKey() != c)
		current = nullptr;
	if (current == nullptr) {
		NodeSMM* new_node = new NodeSMM{ c, nullptr, nullptr };
		NodeSLL* new_value_head = new NodeSLL{ v, nullptr };
		new_node->setValueHead(new_value_head);
		if (previous != nullptr) {
			new_node->setNext(previous->getNext());
			previous->setNext(new_node);
		}
		else {
			new_node->setNext(this->head);
			this->head = new_node;
		}
	}
	else {
		NodeSLL* new_value = new NodeSLL{ v, nullptr };
		NodeSLL* current_value = current->getValueHead();
		while (current_value->getNext() != nullptr) {
			current_value = current_value->getNext();
		}
		current_value->setNext(new_value);
	}
	this->sll_size++;
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	// WC = Theta(n + m), n = number of keys, m = number of values
	// BC = Theta(m), first key is found, m = number of values
	// TC = O(n + m)

	vector<TValue> values;
	NodeSMM* current = this->head;
	while (current != nullptr && current->getKey() != c)
		current = current->getNext();
	if (current == nullptr)
		return values;
	NodeSLL* current_value = current->getValueHead();
	while (current_value != nullptr) {
		values.push_back(current_value->getInfo());
		current_value = current_value->getNext();
	}
	return values;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	// WC = Theta(n + m), n = number of keys, m = number of values
	// BC = Theta(1)
	// TC = O(n + m)
	
	NodeSMM* previous = nullptr;
	NodeSMM* current = this->head;
	while (current != nullptr && this->relation(current->getKey(), c) && current->getKey() != c) {
		previous = current;
		current = current->getNext();
	}
	if (current != nullptr && current->getKey() != c)
		current = nullptr;
	
	if (current == nullptr)
		return false;
	else {
		NodeSLL* previous_value = nullptr;
		NodeSLL* current_value = current->getValueHead();
		while (current_value != nullptr && current_value->getInfo() != v) {
			current_value = current_value->getNext();
		}
		if (current_value == nullptr)
			return false;
		else {
			if (previous_value != nullptr) {
				previous_value->setNext(current_value->getNext());
				delete current_value;
			}
			else {
				current->setValueHead(current_value->getNext());
				delete current_value;
			}
		}
		if (current->getValueHead() == nullptr) {
			if (previous != nullptr) {
				previous->setNext(current->getNext());
				delete current;
			}
			else {
				this->head = current->getNext();
				delete current;
			}
		}
	}
	this->sll_size--;
	return true;
}


int SortedMultiMap::size() const {
	// WC = BC = TC = Theta(1)
	return this->sll_size;
}

bool SortedMultiMap::isEmpty() const {
	// WC = BC = TC = Theta(1)
	return this->sll_size == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	// WC = BC = TC = Theta(1)

	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	// WC = BC = TC = Theta(n + m), n = number of keys, m = number of values

	NodeSMM* previous_node = nullptr;
	NodeSMM* current_node = this->head;
	while (current_node != nullptr) {
		NodeSLL* previous_value = nullptr;
		NodeSLL* current_value = current_node->getValueHead();
		while (current_value != nullptr) {
			previous_value = current_value;
			current_value = current_value->getNext();
			delete previous_value;
		}
		previous_node = current_node;
		current_node = current_node->getNext();
		delete previous_node;
	}
}

int SortedMultiMap::getKeyRange() const
{
	// WC = BC = TC = Theta(n)

	if (this->sll_size == 0)
		return -1;
	NodeSMM* current = this->head;
	int start = current->getKey();
	while (current->getNext() != nullptr)
		current = current->getNext();
	int finish = current->getKey();
	return abs(finish - start);
}
