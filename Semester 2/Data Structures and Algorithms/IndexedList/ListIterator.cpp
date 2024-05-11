#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>

ListIterator::ListIterator(const IndexedList& list) : list(list){
    //WC=BC=TC=Theta(1)
    this->currentElement = list.head;
}

void ListIterator::first(){
    //WC=BC=TC=Theta(1)
    this->currentElement = this->list.head;
}

void ListIterator::next(){
    //WC=BC=TC=Theta(1)
    if (this->currentElement == -1)
        throw std::exception();
    this->currentElement = this->list.nodes[this->currentElement].getNext();
}

bool ListIterator::valid() const{
    //WC=BC=TC=Theta(1)
    return this->currentElement != -1;
}

TElem ListIterator::getCurrent() const{
    //WC=BC=TC=Theta(1)
    if (this->currentElement == -1)
        throw std::exception();
    return this->list.nodes[this->currentElement].getInfo();
}

void ListIterator::previous()
{
    //WC=BC=TC=Theta(1)
    if (this->currentElement == -1)
        throw std::exception();
    this->currentElement = this->list.nodes[this->currentElement].getPrev();   
}
