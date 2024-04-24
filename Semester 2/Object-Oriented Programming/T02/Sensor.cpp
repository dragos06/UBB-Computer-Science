#include "Sensor.h"
using namespace std;

std::string Sensor::toString()
{
    string sensor = "Sensor: " + this->producer + " Recordings ";
    for (auto r : this->recordings)
        sensor += to_string(r) + " ";
    return sensor;
}

std::string Sensor::getProducer()
{
    return this->producer;
}

bool TemperatureSensor::sendAlert()
{
    int count = 0;
    for (auto r : this->recordings) {
        if (r > 35)
            count++;
    }
    if (count >= 2)
        return true;
    return false;
}

double TemperatureSensor::getPrice()
{
    int base_price = 9;
    if (this->diameter < 3)
        base_price += 8;
    return base_price;
}

std::string TemperatureSensor::toString()
{
    string temperature = "Temperature " + Sensor::toString() + " Diameter " + to_string(this->diameter) + " Price " + to_string(this->getPrice()) + " " + (this->sendAlert() ? "Alert" : "No alert");
    return temperature;
}

bool HumiditySensor::sendAlert()
{
    int count = 0;
    for (auto r : this->recordings) {
        if (r < 30)
            count++;
    }
    if (count >= 2)
        return true;
    return false;
}

double HumiditySensor::getPrice()
{
    double base_price = 4;
    return base_price;
}

std::string HumiditySensor::toString()
{
    string humidity = "Humidity " + Sensor::toString() + " Price " + to_string(this->getPrice()) + " " + (this->sendAlert() ? "Alert" : "No alert");
    return humidity;
}

bool SmokeSensor::sendAlert()
{
    int count = 0;
    for (auto r : this->recordings) {
        if (r > 1600)
            count++;
    }
    if (count >= 1)
        return true;
    return false;
}

double SmokeSensor::getPrice()
{
    double base_price = 25;
    return base_price;
}

std::string SmokeSensor::toString()
{
    string smoke = "Smoke " + Sensor::toString() + " Price " + to_string(this->getPrice()) + " " + (this->sendAlert() ? "Alert" : "No alert");
    return smoke;
}
