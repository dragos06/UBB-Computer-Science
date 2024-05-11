#include "ExtendedTest.h"
#include "ShortTest.h"

#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"

#include <iostream>
#include <assert.h>
using namespace std;


int main() {
	//testAll();
	//testAllExtended();

	FixedCapBiMap m(10);
	FixedCapBiMapIterator it = m.iterator(); 
	TElem result, result2;
	m.add(1, 2);
	m.add(1, 5);
	m.add(2, 4);
	m.add(3, 5);
	m.add(4, 2);
	m.add(5, 5);
	m.add(6, 8);
	m.add(6, 2);
	
	it.first();
	it.next();
	it.next();
	it.next();
	result2 = it.remove();
	assert(result2.first == 3 && result2.second == 5);
	//assert(m.mostFrequentValue() == 3);
	


	cout << "That's all!" << endl;
	system("pause");
	return 0;
}


