#include "Console.h"

int main() {
	Device device;
	Console console{ device };

	console.start();
	return 0;
}