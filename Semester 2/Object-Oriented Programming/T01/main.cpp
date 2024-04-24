#include "Console.h"
#include "Testing.h"

int main() {
	Testing test;
	test.runTests();

	Repository repository;
	Service service{ repository };
	Console console{ service };
	console.startConsole();
}
