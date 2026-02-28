#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include "DLL.h"

using namespace std;

bool validateList(Node* head, Node* tail) {
    // 1. Check forward and backward traversals agree
    int forwardCount = 0;
    Node* curr = head;
    Node* last = nullptr;
    while (curr) {
        if (curr->getNext() && curr->getNext()->getPrevious() != curr) {
            cerr << "Link inconsistency detected at " << curr->getValue() << endl;
            return false;
        }
        last = curr;
        curr = curr->getNext();
        forwardCount++;
    }

    int backwardCount = 0;
    curr = tail;
    while (curr) {
        if (curr->getPrevious() && curr->getPrevious()->getNext() != curr) {
            cerr << "Reverse link inconsistency at " << curr->getValue() << endl;
            return false;
        }
        curr = curr->getPrevious();
        backwardCount++;
    }

    if (forwardCount != backwardCount) {
        cerr << "Mismatch in node count forward vs backward!" << endl;
        return false;
    }

    cout << "List validated successfully. Nodes: " << forwardCount << endl;
    return true;
}


// Print list from head to tail
void printForward(Node* head) {
    Node* current = head;
    cout << "Forward: ";
    while (current) {
        cout << current->getValue() << " ";
        current = current->getNext();
    }
    cout << endl;
}

// Print list from tail to head
void printBackward(Node* tail) {
    Node* current = tail;
    cout << "Backward: ";
    while (current) {
        cout << current->getValue() << " ";
        current = current->getPrevious();
    }
    cout << endl;
}

int main() {
    cout << "=== Sequential test ===" << endl;

    Node* head = new Node(1);
    DLL list(head);
    Node* n2 = list.insertAfter(head, 2);
    Node* n3 = list.insertAfter(n2, 3);
    Node* n0 = list.insertBefore(head, 0);

    printForward(n0);
    printBackward(n3);

    cout << "\n=== Concurrent stress test ===" << endl;

    const int writerThreads = 8;
    const int readerThreads = 3;
    const int opsPerWriter = 50;
    vector<Node*> baseNodes = {n0, head, n2, n3};

    vector<thread> threads;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distIndex(0, (int)baseNodes.size() - 1);
    uniform_int_distribution<int> distVal(100, 999);

    for (int i = 0; i < writerThreads; ++i) {
        threads.emplace_back([&, i]() {
            for (int j = 0; j < opsPerWriter; ++j) {
                Node* randomNode = baseNodes[distIndex(gen)];
                int val = distVal(gen);
                if (j % 2 == 0) {
                    list.insertAfter(randomNode, val);
                } else {
                    list.insertBefore(randomNode, val);
                }

                this_thread::sleep_for(chrono::milliseconds(2));
            }
        });
    }

    for (int i = 0; i < readerThreads; ++i) {
        threads.emplace_back([&, i]() {
            for (int j = 0; j < 40; ++j) {
                Node* current = n0;
                while (current && current->getNext()) {
                    current = list.moveNext(current);
                }
                while (current && current->getPrevious()) {
                    current = list.movePrev(current);
                }
                this_thread::sleep_for(chrono::milliseconds(10));
            }
        });
    }

    for (auto& t : threads) t.join();

    cout << "\n=== Final traversal ===" << endl;
    printForward(list.getHead());
    printBackward(list.getTail());

    cout << "\n=== Move test ===" << endl;
    Node* current = list.getHead();
    while (current) {
        cout << "Current value: " << current->getValue() << endl;
        current = list.moveNext(current);
    }

    cout << "\nAll stress tests completed successfully!" << endl;

    validateList(list.getHead(), list.getTail());


    return 0;
}
