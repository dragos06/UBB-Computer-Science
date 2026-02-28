#include "DLL.h"
#include <thread>
using namespace std;

Node::Node(int value, Node *previous, Node *next)
{
    this->value = value;
    this->previous = previous;
    this->next = next;
    this->nodeMutex = new mutex{};
}

int Node::getValue()
{
    return this->value;
}

Node *Node::getPrevious()
{
    return this->previous;
}

Node *Node::getNext()
{
    return this->next;
}

mutex* Node::getNodeMutex()
{
    return this->nodeMutex;
}

void Node::setValue(int value)
{
    this->value = value;
}

void Node::setPrevious(Node *previous)
{
    this->previous = previous;
}

void Node::setNext(Node *next)
{
    this->next = next;
}

DLL::DLL(Node *head)
{
    this->head = head;
    this->tail = head;
}

Node *DLL::moveNext(Node *currentNode)
{
    (currentNode->getNodeMutex())->lock();
    Node* nextNode = currentNode->getNext();
    (currentNode->getNodeMutex())->unlock();
    return nextNode;
}

Node *DLL::movePrev(Node *currentNode)
{
    (currentNode->getNodeMutex())->lock();
    Node* previousNode = currentNode->getPrevious();
    (currentNode->getNodeMutex())->unlock();
    return previousNode;
}

Node *DLL::insertAfter(Node *currentNode, int value)
{
    Node* newNode = new Node{value};
    currentNode->getNodeMutex()->lock();

    Node* nextNode = currentNode->getNext();
    if(nextNode){
        nextNode->getNodeMutex()->lock();
    }

    newNode->setPrevious(currentNode);
    newNode->setNext(nextNode);
    currentNode->setNext(newNode);

    if (nextNode) {
        nextNode->setPrevious(newNode);
        nextNode->getNodeMutex()->unlock();
    } 
    else {
        this->tail = newNode;
    }

    currentNode->getNodeMutex()->unlock();
    return newNode;
}

Node *DLL::insertBefore(Node *currentNode, int value)
{
    while(true) {
        Node* newNode = new Node{value};

        currentNode->getNodeMutex()->lock();
        Node* prevNode = currentNode->getPrevious();
        currentNode->getNodeMutex()->unlock();

        if(prevNode){
            prevNode->getNodeMutex()->lock();
            currentNode->getNodeMutex()->lock();
            if(currentNode->getPrevious() != prevNode) {
                currentNode->getNodeMutex()->unlock();
                prevNode->getNodeMutex()->unlock();
                
                this_thread::yield();
                continue;
            }
            else {
                newNode->setPrevious(prevNode);
                newNode->setNext(currentNode);
                prevNode->setNext(newNode);
                currentNode->setPrevious(newNode);
                currentNode->getNodeMutex()->unlock();
                prevNode->getNodeMutex()->unlock();
                return newNode;
            }
        }
        else{
            currentNode->getNodeMutex()->lock();
            if(currentNode->getPrevious() != nullptr) {
                currentNode->getNodeMutex()->unlock();
                this_thread::yield();
                continue;
            }
            else {
                newNode->setNext(currentNode);
                currentNode->setPrevious(newNode);
                this->head = newNode;
                currentNode->getNodeMutex()->unlock();
                return newNode;
            }
        }
    }
}

Node *DLL::getHead()
{
    return this->head;
}

void DLL::setHead(Node *head)
{
    this->head = head;
}

Node *DLL::getTail()
{
    return this->tail;
}

void DLL::setTail(Node *tail)
{
    this->tail = tail;
}
