#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	//WC=BC=Theta(n)
	stack = new TElem[multime.s];
	index = -1;
	BSTNode* currentNode = multime.root;
	BSTNode** aux_stack = new BSTNode * [multime.s];
	int aux_index = -1;
	while (currentNode != nullptr) {
		aux_index++;
		aux_stack[aux_index] = currentNode;
		currentNode = currentNode->getLeft();
	}

	while (aux_index != -1) {
		currentNode = aux_stack[aux_index];
		aux_index--;

		index++;
		stack[index] = currentNode->getInfo();

		currentNode = currentNode->getRight();
		while (currentNode != nullptr) {
			aux_index++;
			aux_stack[aux_index] = currentNode;
			currentNode = currentNode->getLeft();
		}
	}
	index = 0;
	delete[] aux_stack;
}



void SortedSetIterator::first() {
	//WC=BC=TC=Theta(1)
	index = 0;
}


void SortedSetIterator::next() {
	//WC=BC=TC=Theta(1)
	if (index >= multime.s)
		throw exception();
	index++;
}


TElem SortedSetIterator::getCurrent()
{
	//WC=BC=TC=Theta(1)
	if (index >= multime.s)
		throw exception();
	return stack[index];
}

bool SortedSetIterator::valid() const {
	//WC=BC=TC=Theta(1)
	return index < multime.s;
}

SortedSetIterator::~SortedSetIterator()
{
	//WC=BC=TC=Theta(1)
	delete stack;
}

