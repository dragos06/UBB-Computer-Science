#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


class SortedMultiMap {
	friend class SMMIterator;
    friend class NodeSMM;
    friend class NodeSLL;
    private:
        NodeSMM* head;
        Relation relation;
        int sll_size;
    public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();

    int getKeyRange() const;
};

class NodeSMM {
    friend class NodeSLL;
private:
    TKey key;
    NodeSLL* value_head;
    NodeSMM* next;
public:
    NodeSMM(TKey key, NodeSLL* value_head, NodeSMM* next) { this->key = key; this->value_head = value_head; this->next = next; }
    TKey getKey() { return this->key; }
    NodeSLL* getValueHead() { return this->value_head; }
    void setValueHead(NodeSLL* value_head) { this->value_head = value_head; }
    NodeSMM* getNext() { return this->next; }
    void setNext(NodeSMM* next) { this->next = next; }
    
};

class NodeSLL {
private:
    TValue info;
    NodeSLL* next;
public:
    NodeSLL(TValue info, NodeSLL* next) { this->info = info; this->next = next; }
    ~NodeSLL() {}
    TValue getInfo() { return this->info; }
    NodeSLL* getNext() { return this->next; }
    void setInfo(TValue info) { this->info = info; }
    void setNext(NodeSLL* node) { this->next = node; }
};