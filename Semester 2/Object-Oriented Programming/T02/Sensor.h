#pragma once
#include <string>
#include <vector>

class Sensor {
protected:
	std::string producer;
	std::vector<double> recordings;
public:
	Sensor() {};
	Sensor(std::string producer, std::vector<double> recordings) { this->producer = producer; this->recordings = recordings; }
	virtual bool sendAlert() = 0;
	virtual double getPrice() = 0;
	virtual std::string toString();
	std::string getProducer();
};

class TemperatureSensor : public Sensor {
private:
	double diameter;
public:
	TemperatureSensor(std::string producer, std::vector<double> recordings, double diameter) { this->producer = producer; this->recordings = recordings; this->diameter = diameter; }
	bool sendAlert() override;
	double getPrice() override;
	std::string toString();
};

class HumiditySensor : public Sensor {
public:
	HumiditySensor(std::string producer, std::vector<double> recordings) { this->producer = producer; this->recordings = recordings; }
	bool sendAlert() override;
	double getPrice() override;
	std::string toString();
};

class SmokeSensor : public Sensor {
public:
	SmokeSensor(std::string producer, std::vector<double> recordings) { this->producer = producer; this->recordings = recordings; }
	bool sendAlert() override;
	double getPrice() override;
	std::string toString();
};
