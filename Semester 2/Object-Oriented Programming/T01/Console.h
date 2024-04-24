#pragma once
#include "Service.h"

class Console {
private:
	Service service;
public:
	Console(Service service);
	void startConsole();
private:
	void addProteinConsole();
	void showAllConsole();
	void showGivenName();
	void print_menu();
};