#pragma once
#include <mutex>

class Node 
{
private:
    int value;
    Node* previous;
    Node* next;
    std::mutex* nodeMutex;
public:
    Node(int value, Node *previous = nullptr, Node *next = nullptr);
    int getValue();
    Node* getPrevious();
    Node* getNext();
    std::mutex* getNodeMutex();
    void setValue(int value);
    void setPrevious(Node *previous);
    void setNext(Node *next);
};

class DLL
{
private:
    Node* head;
    Node* tail;
public:
    DLL(Node* head);
    Node* moveNext(Node* currentNode);
    Node* movePrev(Node* currentNode);
    Node* insertAfter(Node* currentNode, int value);
    Node* insertBefore(Node* currentNode, int value);
    Node* getHead();
    void setHead(Node* head);
    Node* getTail();
    void setTail(Node* tail);
};
