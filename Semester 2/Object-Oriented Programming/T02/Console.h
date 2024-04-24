#pragma once
#include "Device.h"

class Console {
private:
	Device device;
public:
	Console(Device device) { this->device = device; }
	void start();
private:
	void printMenu();
	void printMenuSensor();
	void addSensor();
	void showAll();
	void showAlert();
	void saveToFile();

};