#include <iostream>

#include <crtdbg.h>

#include "ShortTest.h"
#include "ExtendedTest.h"

#include "SortedMultiMap.h"
#include <assert.h>


bool relation0(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testGetKeyRange() {
	SortedMultiMap smm = SortedMultiMap(relation0);
	assert(smm.getKeyRange() == -1);
	smm.add(3, 2);
	smm.add(6, 3);
	smm.add(4, 2);
	smm.add(2, 1);
	smm.add(4, 7);
	smm.add(8, 1);
	smm.add(5, 2);
	assert(smm.getKeyRange() == 6);
}

int main() {
	{
		testAll();
		testAllExtended();
		testGetKeyRange();
		std::cout << "Finished SMM Tests!" << std::endl;
	}
	_CrtDumpMemoryLeaks();
	//system("pause");
}
