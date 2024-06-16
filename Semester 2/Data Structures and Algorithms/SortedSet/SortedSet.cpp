#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
	//WC=BC=TC=Theta(1)
	this->root = nullptr;
	this->r = r;
	this->s = 0;
}


bool SortedSet::add(TComp elem) {
	//WC=Theta(n)
	//BC=Theta(1)
	//TC=O(n)
	BSTNode* currentNode = root;
	BSTNode* previousNode = nullptr;
	while (currentNode != nullptr) {
		if (currentNode->getInfo() == elem)
			return false;
		else 
			if (r(currentNode->getInfo(),elem)) {
				previousNode = currentNode;
				currentNode = currentNode->getRight();
			}
			else {
				previousNode = currentNode;
				currentNode = currentNode->getLeft();
		}
	}
	BSTNode* newNode = new BSTNode(elem, nullptr, nullptr);
	if (previousNode == nullptr)
		root = newNode;
	else 
		if (r(previousNode->getInfo(),elem))
			previousNode->setRight(newNode);
		else
			previousNode->setLeft(newNode);
	s++;
	return true;
}


bool SortedSet::remove(TComp elem) {
	//WC=Theta(n)
	//BC=Theta(1)
	//TC=O(n)
	BSTNode* currentNode = root;
	BSTNode* parentNode = nullptr;

	while (currentNode != nullptr && currentNode->getInfo() != elem) {
		parentNode = currentNode;
		if (r(currentNode->getInfo(), elem)) {
			currentNode = currentNode->getRight();
		}
		else {
			currentNode = currentNode->getLeft();
		}
	}

	if (currentNode == nullptr) {
		return false;
	}

	// 0 OR 1 CHILD
	if (currentNode->getLeft() == nullptr || currentNode->getRight() == nullptr) {
		BSTNode* newCurrent;

		if (currentNode->getLeft() == nullptr) {
			newCurrent = currentNode->getRight();
		}
		else { 
			newCurrent = currentNode->getLeft();
		}

		if (parentNode == nullptr) {
			root = newCurrent;
		}
		else {
			if (currentNode == parentNode->getLeft()) {
				parentNode->setLeft(newCurrent);
			}
			else {
				parentNode->setRight(newCurrent);
			}
		}

		delete currentNode;
	}
	// 2 CHILDREN
	else {
		BSTNode* successorParent = currentNode;
		BSTNode* successor = currentNode->getRight();
		while (successor->getLeft() != nullptr) {
			successorParent = successor;
			successor = successor->getLeft();
		}

		currentNode->setInfo(successor->getInfo());
		successorParent->setLeft(successor->getRight());

		delete successor;
	}

	s--;
	return true;
}


bool SortedSet::search(TComp elem) const {
	//WC=Theta(n)
	//BC=Theta(1)
	//TC=O(n)
	BSTNode* currentNode = root;
	while (currentNode != nullptr) {
		if (currentNode->getInfo() == elem)
			return true;
		else 
			if (r(currentNode->getInfo(),elem))
				currentNode = currentNode->getRight();
			else
				currentNode = currentNode->getLeft();
	}
	return false;
}


int SortedSet::size() const {
	//WC=BC=TC=Theta(1)
	return s;
}



bool SortedSet::isEmpty() const {
	//WC=BC=TC=Theta(1)
	return s == 0;
}

SortedSetIterator SortedSet::iterator() const {
	//WC=BC=TC=Theta(n)
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	//WC=BC=TC=Theta(n)
	BSTNode** stack = new BSTNode*[s];
	int index = -1;
	BSTNode* currentNode = root;
	BSTNode* previousNode = nullptr;

	while (currentNode != nullptr) {
		index++;
		stack[index] = currentNode;
		currentNode = currentNode->getLeft();
	}

	while (index != -1) {
		currentNode = stack[index];
		index--;
		previousNode = currentNode;
		currentNode = currentNode->getRight();
		while (currentNode != nullptr) {
			index++;
			stack[index] = currentNode;
			currentNode = currentNode->getLeft();
		}
		delete previousNode;
	}
	delete[] stack;
}

int SortedSet::getRange() const
{
	//WC=Theta(n)
	//BC=Theta(1)
	//TC=O(n)
	if (s == 0)
		return -1;
	BSTNode* minimum = root;
	BSTNode* maximum = root;
	while (minimum->getLeft() != nullptr)
		minimum = minimum->getLeft();
	while (maximum->getRight() != nullptr)
		maximum = maximum->getRight();
	return maximum->getInfo() - minimum->getInfo();
}

BSTNode::BSTNode(TElem info, BSTNode* left, BSTNode* right): info{info}, left{left}, right{right}
{
	//WC=BC=TC=Theta(1)
}

TElem BSTNode::getInfo()
{
	//WC=BC=TC=Theta(1)
	return info;
}

BSTNode* BSTNode::getLeft()
{
	//WC=BC=TC=Theta(1)
	return left;
}

BSTNode* BSTNode::getRight()
{
	//WC=BC=TC=Theta(1)
	return right;
}

void BSTNode::setInfo(TElem info)
{
	//WC=BC=TC=Theta(1)
	this->info = info;
}

void BSTNode::setLeft(BSTNode* left)
{
	//WC=BC=TC=Theta(1)
	this->left = left;
}

void BSTNode::setRight(BSTNode* right)
{
	//WC=BC=TC=Theta(1)
	this->right = right;
}
