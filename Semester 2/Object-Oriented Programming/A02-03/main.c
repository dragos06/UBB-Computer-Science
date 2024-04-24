#include <stdio.h>
#include "Service.h"
#include <stdlib.h>
#include "UI.h"
#include <crtdbg.h>


int main() {
	testMedicine();
	testDynamicArray();
	testRepository();
	testService();

	UI* ui = createUI();
	startUI(ui);
	destroyUI(ui);
	_CrtDumpMemoryLeaks();
	return 0;
}