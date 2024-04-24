#pragma once
#include "Sensor.h"
#include <vector>


class Device {
private:
	std::vector<Sensor*> sensors;
public:
	void addSensor(Sensor* sensor);
	std::vector<Sensor*> getAllSensors();
	std::vector<Sensor*> getAlertingSensors();
	void writeToFile(std::string filename, double maximum = 999);
	void startUp();
	double maxPrice();
};