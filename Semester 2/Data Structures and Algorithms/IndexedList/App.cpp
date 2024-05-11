#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

#include "IndexedList.h"
#include "ListIterator.h"
#include <assert.h>

using namespace std;

void testPrevious() {
    IndexedList list = IndexedList();
    list.addToEnd(1);
    list.addToPosition(0, 2);
    
    ListIterator it = list.iterator();
    
    it.next();
    assert(it.getCurrent() == 1);
    it.previous();
    assert(it.getCurrent() == 2);
    it.previous();
    assert(!it.valid());
}

int main(){
    testAll();
    testAllExtended();
    testPrevious();
    cout<<"Finished LI Tests!"<<endl;
}