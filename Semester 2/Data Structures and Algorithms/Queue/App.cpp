#include "Queue.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <iostream>
#include <assert.h>

using namespace std;

void testGetMiddle() {
	Queue q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);
	q.push(6);
	assert(q.getMiddle() == 4);
}

int main() {

	testAll();
	testAllExtended();
	testGetMiddle();
	cout << "Test end" << endl;

}