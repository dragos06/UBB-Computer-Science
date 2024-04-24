#include "Console.h"
#include <iostream>
using namespace std;

void Console::start()
{
	this->device.startUp();
	while (true) {
		try {
			this->printMenu();
			cout << "Please choose an option" << endl;
			int user_option = 0;
			cin >> user_option;

			switch (user_option) {
			case 1:
				this->addSensor();
				break;
			case 2:
				this->showAll();
				break;
			case 3:
				this->showAlert();
				break;
			case 4:
				this->saveToFile();
				break;
			case 5:
				cout << "Exiting..." << endl;
				return;
			default:
				cout << "Invalid input" << endl;
				break;
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}
}

void Console::printMenu()
{
	cout << endl << "	IoT DEVICES" << endl;
	cout << "[1] Add a sensor" << endl;
	cout << "[2] Show all sensors" << endl;
	cout << "[3] Show all sensors that emit alerts" << endl;
	cout << "[4] Save to file" << endl;
	cout << "[5] Exit" << endl;
}

void Console::printMenuSensor()
{
	cout << "[1] Temperature Sensor" << endl;
	cout << "[2] Humidity Sensor" << endl;
	cout << "[3] Smoke Sensor" << endl;
}

void Console::addSensor()
{
	cout << "Please enter producer of the sensor" << endl;
	string producer;
	cin >> producer;

	cout << "Please choose the type of sensor" << endl;
	this->printMenuSensor();
	int user_option = 0;
	cin >> user_option;

	if (user_option == 1) {
		cout << "Please enter the number of recordings" << endl;
		int number_rec = 0;
		cin >> number_rec;
		
		cout << "Please enter the recordings of the sensor as temperatures" << endl;
		vector<double> recordings;
		double recording;
		for (int i = 0; i < number_rec; i++) {
			cin >> recording;
			recordings.push_back(recording);
		}

		cout << "Please enter the diameter of the sensor" << endl;
		double diameter = 0;
		cin >> diameter;

		TemperatureSensor* temperature = new TemperatureSensor(producer, recordings, diameter);
		this->device.addSensor(temperature);
		return;
	}

	else if (user_option == 2) {
		cout << "Please enter the number of recordings" << endl;
		int number_rec = 0;
		cin >> number_rec;

		cout << "Please enter the recordings of the sensor as percentages" << endl;
		vector<double> recordings;
		double recording;
		for (int i = 0; i < number_rec; i++) {
			cin >> recording;
			recordings.push_back(recording);
		}

		HumiditySensor* humidity = new HumiditySensor(producer, recordings);
		this->device.addSensor(humidity);
		return;
	}
	else if (user_option == 3) {
		cout << "Please enter the number of recordings" << endl;
		int number_rec = 0;
		cin >> number_rec;

		cout << "Please enter the recordings of the sensor as particle concentrations" << endl;
		vector<double> recordings;
		double recording;
		for (int i = 0; i < number_rec; i++) {
			cin >> recording;
			recordings.push_back(recording);
		}

		SmokeSensor* smoke = new SmokeSensor(producer, recordings);
		this->device.addSensor(smoke);
		return;
	}
	return;
}

void Console::showAll()
{
	for (auto s : this->device.getAllSensors())
		cout << s->toString() << endl;
}

void Console::showAlert()
{
	for (auto s : this->device.getAlertingSensors())
		cout << s->toString() << endl;
}

void Console::saveToFile()
{
	cout << "Please enter the filename" << endl;
	string filename;
	cin >> filename;

	cout << "Please give a maximum value" << endl;
	double maximum;
	cin >> maximum;

	this->device.writeToFile(filename, maximum);
}
