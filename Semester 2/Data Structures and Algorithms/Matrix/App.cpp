
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"


#include <assert.h>
#include <crtdbg.h>

using namespace std;

void testSetElemsOnCol() {
	cout << "Test setElemsOnCol" << endl;
	Matrix m(4, 4);
	m.modify(2,2, 1);
	m.modify(2, 3, 1);
	m.setElemsOnCol(2, 44);
	for(int i = 0; i < m.nrLines(); i++)
		assert(m.element(i, 2) == 44);
	assert(m.getSize() == 5);
}

int main() {
	{	
	testAll();
	testAllExtended();
	testSetElemsOnCol();
	cout << "Test End" << endl;
	system("pause");
	}

	_CrtDumpMemoryLeaks();
}