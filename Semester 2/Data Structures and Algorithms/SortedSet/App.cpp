#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

#include <crtdbg.h>
#include <assert.h>
using namespace std;

bool relation(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testGetRange() {
	cout << "Test getRanged\n";
	SortedSet s(relation);
	assert(s.getRange() == -1);
	s.add(6);
	assert(s.getRange() == 0);
	s.add(7);
	assert(s.getRange() == 1);
	s.add(3);
	assert(s.getRange() == 4);
	s.add(9);
	assert(s.getRange() == 6);
}

int main() {
	{
		testAll();
		testAllExtended();
		testGetRange();
		cout << "Test end" << endl;
		system("pause");
	}
	_CrtDumpMemoryLeaks();
}