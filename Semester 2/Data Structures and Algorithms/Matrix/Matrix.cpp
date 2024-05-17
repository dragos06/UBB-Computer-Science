#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	//WC=BC=TC=Theta(m)
	if (nrLines < 1 or nrCols < 1)
		throw exception();
	this->nrL = nrLines;
	this->nrC = nrCols;
	this->m = 10;
	this->T = new Node*[m];
	for (int i = 0; i < m; i++)
		this->T[i] = nullptr;
	this->size = 0;
}

Matrix::~Matrix()
{
	//WC=Theta(m+size)
	//BC=Theta(m)
	//TC=O(m+size)
	for (int i = 0; i < this->m; i++) {
		Node* current = this->T[i];
		Node* prev = nullptr;
		while (current != nullptr) {
			prev = current;
			current = current->getNext();
			delete prev;
		}
	}
	delete[] this->T;
}


int Matrix::nrLines() const {
	//WC=BC=TC=Theta(1)
	return this->nrL;
}


int Matrix::nrColumns() const {
	//WC=BC=TC=Theta(1)
	return this->nrC;
}


TElem Matrix::element(int i, int j) const {
	//WC=Theta(n)
	//BC=Theta(1)
	//TC=O(n)
	//TC=Theta(1) average
	if (i < 0 or j < 0 or i >= this->nrL or j >= this->nrC)
		throw exception();
	int hash_value = this->hashFunction(i, j);
	Node* current = this->T[hash_value];
	while (current != nullptr) {
		if (current->getI() == i && current->getJ() == j)
			return current->getInfo();
		current = current->getNext();
	}
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	//WC=Theta((n^2)*m)
	//BC=Theta(1)
	//TC=O((n^2)*m)
	//TC=Theta(1) amortized and on average
	if (i < 0 or j < 0 or i >= this->nrL or j >= this->nrC)
		throw exception();
	int hash_value = this->hashFunction(i, j);
	Node* current = this->T[hash_value];
	Node* prev = nullptr;

	while (current != nullptr && (current->getI() < i || (current->getI() == i && current->getJ() < j))) {
		prev = current;
		current = current->getNext();
	}

	if (current != nullptr) {
		if (current->getI() == i && current->getJ() == j) {
			if (current == this->T[hash_value] && e == NULL_TELEM) {
				TElem old = current->getInfo();
				this->T[hash_value] = this->T[hash_value]->getNext();
				delete current;
				this->size--;
				return old;
			}
			if (current == this->T[hash_value] && e != NULL_TELEM) {
				TElem old = current->getInfo();
				current->setInfo(e);
				return old;
			}
			if (current != this->T[hash_value] && e == NULL_TELEM) {
				TElem old = current->getInfo();
				prev->setNext(current->getNext());
				delete current;
				this->size--;
				return old;
			}
			if (current != this->T[hash_value] && e != NULL_TELEM) {
				TElem old = current->getInfo();
				current->setInfo(e);
				return old;
			}
		}
		else {
			if (current == this->T[hash_value] && e == NULL_TELEM) {
				return NULL_TELEM;
			}
			if (current == this->T[hash_value] && e != NULL_TELEM) {
				Node* new_node = new Node{ i, j, e, current };
				this->T[hash_value] = new_node;
				this->size++;
				if ((double)this->size / this->m > 0.7)
					this->resize();
				return NULL_TELEM;
			}
			if (current != this->T[hash_value] && e == NULL_TELEM) {
				return NULL_TELEM;
			}
			if (current != this->T[hash_value] && e != NULL_TELEM) {
				Node* new_node = new Node{ i, j, e, current };
				prev->setNext(new_node);
				this->size++;
				if ((double)this->size / this->m > 0.7)
					this->resize();
				return NULL_TELEM;
			}
		}
	}
	else {
		if (prev == nullptr && e == NULL_TELEM) {
			return NULL_TELEM;
		}
		if (prev == nullptr && e != NULL_TELEM) {
			Node* new_node = new Node{ i, j, e, nullptr };
			this->T[hash_value] = new_node;
			this->size++;
			if ((double)this->size / this->m > 0.7)
				this->resize();
			return NULL_TELEM;
		}
		if (prev != nullptr && e == NULL_TELEM) {
			return NULL_TELEM;
		}
		if (prev != nullptr && e != NULL_TELEM) {
			Node* new_node = new Node{ i, j, e, nullptr };
			prev->setNext(new_node);
			this->size++;
			if ((double)this->size / this->m > 0.7)
				this->resize();
			return NULL_TELEM;
		}
	}

}

void Matrix::setElemsOnCol(int col, TElem elem)
{
	//WC=Theta((n^2)*m)
	//BC=Theta(nrL)
	//TC=O((n^2)*m)
	if (col < 0 or col >= this->nrC)
		throw exception();
	for (int i = 0; i < this->nrL; i++) {
		this->modify(i, col, elem);
	}
}

int Matrix::getSize()
{
	//WC=BC=TC=Theta(1)
	return this->size;
}

int Matrix::hashFunction(int i, int j) const
{
	//WC=BC=TC=Theta(1)
	return (i+j)%(this->m);
}

void Matrix::resize()
{
	//WC=Theta((n^2)*m)
	//BC=Theta(m)
	//TC=O((n^2)*m)
	int old_m = m;
	this->m = this->m * 2;

	Node** new_T = new Node * [m];
	for (int i = 0; i < this->m; i++)
		new_T[i] = nullptr;

	for (int i = 0; i < old_m; i++) {
		Node* current = this->T[i];
		Node* prev = nullptr;
		while (current != nullptr) {
			int new_hash_value = this->hashFunction(current->getI(), current->getJ());
			Node* new_current = new_T[new_hash_value];
			Node* new_prev = nullptr;
			while (new_current != nullptr && (new_current->getI() < current->getI() || (new_current->getI() == current->getI() && new_current->getJ() < current->getJ()))) {
				new_prev = new_current;
				new_current = new_current->getNext();
			}
			if (new_current != nullptr && new_current == new_T[new_hash_value]) {
				Node* new_node = new Node{ current->getI(), current->getJ(), current->getInfo(), new_current };
				new_T[new_hash_value] = new_node;
			}
			else if (new_current != nullptr && new_current != new_T[new_hash_value]) {
				Node* new_node = new Node{ current->getI(), current->getJ(), current->getInfo(), new_current };
				new_prev->setNext(new_node);
			}
			else if (new_current == nullptr && new_prev == nullptr) {
				Node* new_node = new Node{ current->getI(), current->getJ(), current->getInfo(), nullptr };
				new_T[new_hash_value] = new_node;
			}
			else if (new_current == nullptr && new_prev != nullptr) {
				Node* new_node = new Node{ current->getI(), current->getJ(), current->getInfo(), nullptr };
				new_prev->setNext(new_node);
			}
			prev = current;
			current = current->getNext();
			delete prev;
		}
	}
	delete[] this->T;
	this->T = new_T;

}

Node::Node(int i, int j, TElem info, Node* next)
{
	//WC=BC=TC=Theta(1)
	this->i = i;
	this->j = j;
	this->info = info;
	this->next = next;
}

int Node::getI()
{
	//WC=BC=TC=Theta(1)
	return this->i;
}

int Node::getJ()
{
	//WC=BC=TC=Theta(1)
	return this->j;
}

TElem Node::getInfo()
{
	//WC=BC=TC=Theta(1)
	return this->info;
}

Node* Node::getNext()
{
	//WC=BC=TC=Theta(1)
	return this->next;
}

void Node::setI(int i)
{
	//WC=BC=TC=Theta(1)
	this->i = i;
}

void Node::setJ(int j)
{
	//WC=BC=TC=Theta(1)
	this->j = j;
}

void Node::setInfo(TElem info)
{
	//WC=BC=TC=Theta(1)
	this->info = info;
}

void Node::setNext(Node* next)
{
	//WC=BC=TC=Theta(1)
	this->next = next;
}
