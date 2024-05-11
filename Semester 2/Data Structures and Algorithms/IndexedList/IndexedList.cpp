#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"

IndexedList::IndexedList() {
	//WC=BC=TC=Theta(1)
	this->cap = 10;
	this->nodes = new Node[this->cap];
	this->head = -1;
	this->tail = -1;
	this->firstEmpty = 0;
	this->list_size = 0;

	for (int i = 0; i < this->cap; i++) {
		this->nodes[i].setPrev(i - 1);
		this->nodes[i].setNext(i + 1);
	}
	this->nodes[this->cap - 1].setNext(-1);
}

int IndexedList::size() const {
	//WC=BC=TC=Theta(1)
	return this->list_size;
}


bool IndexedList::isEmpty() const {
	//WC=BC=TC=Theta(1)
	return this->list_size == 0;
}

TElem IndexedList::getElement(int pos) const {
	//WC=Theta(n)
	//BC=Theta(1)
	//TC=O(n)
	if (pos < 0 || pos >= this->list_size)
		throw std::exception();
	int current = this->head;
	if (current == -1)
		return NULL_TELEM;
	int current_position = 0;
	while (current_position != pos) {
		current = this->nodes[current].getNext();
		current_position++;
	}
	return this->nodes[current].getInfo();
}

TElem IndexedList::setElement(int pos, TElem e) {
	//WC=Theta(n)
	//BC=Theta(1)
	//TC=O(n)
	if (pos < 0 || pos >= this->list_size)
		throw std::exception();
	int current = this->head;
	if (current == -1)
		return NULL_TELEM;
	int current_position = 0;
	while (current_position != pos) {
		current = this->nodes[current].getNext();
		current_position++;
	}
	TElem old = this->nodes[current].getInfo();
	this->nodes[current].setInfo(e);
	return old;
}

void IndexedList::addToEnd(TElem e) {
	//WC=Theta(n)
	//BC=Theta(1)
	//TC=O(n)
	int new_elem = this->allocate_dlla();
	if (new_elem == -1) {
		this->resize();
		new_elem = allocate_dlla();
	}
	this->nodes[new_elem].setInfo(e);
	if (this->list_size == 0) {
		this->head = new_elem;
		this->tail = new_elem;
	}
	else {
		this->nodes[tail].setNext(new_elem);
		this->nodes[new_elem].setPrev(this->tail);
		this->tail = new_elem;
	}
	this->list_size++;
}

void IndexedList::addToPosition(int pos, TElem e) {
	//WC=Theta(n)
	//BC=Theta(1)
	//TC=O(n)
	if (pos < 0 || pos > this->list_size)
		throw std::exception();
	int new_elem = this->allocate_dlla();
	if (new_elem == -1) {
		this->resize();
		new_elem = allocate_dlla();
	}
	this->nodes[new_elem].setInfo(e);
	if (pos == 0) {
		if (this->head == -1) {
			this->head = new_elem;
			this->tail = new_elem;
		}
		else {
			this->nodes[new_elem].setNext(this->head);
			this->nodes[this->head].setPrev(new_elem);
			this->head = new_elem;
		}
	}
	else {
		int current_node = this->head;
		int current_position = 0;
		while (current_node != -1 && current_position < pos - 1) {
			current_node = this->nodes[current_node].getNext();
			current_position++;
		}
		if (current_node != -1) {
			int next_node = this->nodes[current_node].getNext();
			this->nodes[new_elem].setNext(next_node);
			this->nodes[new_elem].setPrev(current_node);
			this->nodes[current_node].setNext(new_elem);
			if (next_node == -1)
				this->tail = new_elem;
			else
				this->nodes[next_node].setPrev(new_elem);
		}
	}
	this->list_size++;
}

TElem IndexedList::remove(int pos) {
	//WC=Theta(n)
	//BC=Theta(1)
	//TC=O(n)
	if (pos < 0 || pos >= this->list_size)
		throw std::exception();
	int current_node = this->head;
	int current_position = 0;
	while (current_node != -1 && current_position < pos) {
		current_node = this->nodes[current_node].getNext();
		current_position++;
	}
	if (current_node != -1) {
		int old_value = this->nodes[current_node].getInfo();

		int next_node = this->nodes[current_node].getNext();
		int prev_node = this->nodes[current_node].getPrev();
		
		if (prev_node == -1 && next_node == -1) {
			this->free_dlla(current_node);
			this->head = -1;
			this->tail = -1;
			this->list_size = 0;
		}
		if (prev_node == -1 && next_node != -1) {
			this->head = next_node;
			this->nodes[this->head].setPrev(-1);
			this->free_dlla(current_node);
			this->list_size--;
		}
		if (prev_node != -1 && next_node == -1) {
			this->tail = prev_node;
			this->nodes[this->tail].setNext(-1);
			this->free_dlla(current_node);
			this->list_size--;
		}
		if (prev_node != -1 && next_node != -1) {
			this->nodes[next_node].setPrev(prev_node);
			this->nodes[prev_node].setNext(next_node);
			this->free_dlla(current_node);
			this->list_size--;
		}
		return old_value;
	}
}

int IndexedList::search(TElem e) const{
	//WC=Theta(n)
	//BC=Theta(1)
	//TC=O(n)
	int current = this->head;
	int current_position = 0;
	while (current != -1 && this->nodes[current].getInfo() != e){
		current = this->nodes[current].getNext();
		current_position++;
	}
	if (current == -1)
		return -1;
	return current_position;
}

ListIterator IndexedList::iterator() const {
	//WC=BC=TC=Theta(1)
    return ListIterator(*this);        
}

IndexedList::~IndexedList() {
	//WC=BC=TC=Theta(1)
	delete[] this->nodes;
}

int IndexedList::allocate_dlla()
{
	//WC=BC=TC=Theta(1)
	int new_elem = this->firstEmpty;
	if (new_elem != -1) {
		this->firstEmpty = this->nodes[this->firstEmpty].getNext();
		if (this->firstEmpty != -1) {
			this->nodes[this->firstEmpty].setPrev(-1);
		}
		this->nodes[new_elem].setNext(-1);
		this->nodes[new_elem].setPrev(-1);
	}
	return new_elem;
}

void IndexedList::free_dlla(int pos)
{
	//WC=BC=TC=Theta(1)
	this->nodes[pos].setNext(this->firstEmpty);
	this->nodes[pos].setPrev(-1);
	if (this->firstEmpty != -1) {
		this->nodes[this->firstEmpty].setPrev(pos);
	}
	this->firstEmpty = pos;
}

void IndexedList::resize()
{
	//WC=BC=TC=Theta(n)
	this->cap = this->cap * 2;
	Node* new_nodes = new Node[this->cap];
	for (int i = 0; i < this->list_size; i++)
		new_nodes[i] = this->nodes[i];
	
	delete[] this->nodes;
	this->nodes = new_nodes;

	for (int i = this->list_size; i < this->cap; i++) {
		if (i == this->list_size)
			this->nodes[i].setPrev(-1);
		else
			this->nodes[i].setPrev(i - 1);
		this->nodes[i].setNext(i + 1);
	}

	this->firstEmpty = this->list_size;
	//this->nodes[this->list_size].setPrev(-1);
	this->nodes[this->cap - 1].setNext(-1);

}
