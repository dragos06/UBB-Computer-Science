#include "Device.h"
#include <fstream>
#include <algorithm>
using namespace std;

void Device::addSensor(Sensor* sensor)
{
	this->sensors.push_back(sensor);
}

std::vector<Sensor*> Device::getAllSensors()
{
	return this->sensors;
}

std::vector<Sensor*> Device::getAlertingSensors()
{
	vector<Sensor*> filtered;
	for (auto s : this->sensors)
		if (s->sendAlert())
			filtered.push_back(s);
	return filtered;
}



void Device::writeToFile(std::string filename, double maximum)
{
	vector<Sensor*> filtered;
		for (auto s : this->sensors)
			if (s->getPrice() < maximum)
				filtered.push_back(s);

		for (int i = 0; i < filtered.size() - 1; i++)
			for (int j = i + 1; j < filtered.size(); j++)
				if (filtered[i]->getProducer() > filtered[j]->getProducer())
					swap(filtered[i], filtered[j]);

		ofstream f(filename);
		if (f.is_open()) {
			for (auto s : filtered)
				f << s->toString() << endl;
		}
}

void Device::startUp()
{
	TemperatureSensor* temperature1 = new TemperatureSensor("Samsung", vector<double> { 21,43,12,33,42 } , 5);
	this->sensors.push_back(temperature1);

	HumiditySensor* humidity1 = new HumiditySensor("Toshina", vector<double> {43, 23, 50, 33});
	this->sensors.push_back(humidity1);

	SmokeSensor* smoke1 = new SmokeSensor("Allview", vector<double> {542, 100, 342, 555});
	this->sensors.push_back(smoke1);

}

double Device::maxPrice()
{
	double maximum = 0;
	for (auto s : this->sensors)
		if (s->getPrice() > maximum)
			maximum = s->getPrice();
	return maximum;
}
