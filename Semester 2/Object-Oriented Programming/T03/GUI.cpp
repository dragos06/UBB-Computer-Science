#include "GUI.h"
#include <qmessagebox.h>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;
GUI::GUI(Service& service, QWidget *parent)
	: QWidget(parent), service{service}
{
	ui.setupUi(this);
	populateMedicationsList();
	QObject::connect(ui.searchLineEdit, &QLineEdit::textChanged, this, &GUI::searchLineEditHandler);
	QObject::connect(ui.namePushButton, &QPushButton::clicked, this, &GUI::nameButtonHandler);
}

GUI::~GUI()
{}

void GUI::populateMedicationsList()
{
	ui.medicationsListWidget->clear();
	vector<Medication> medications = service.getAllService();
	for (Medication m : medications) {
		ui.medicationsListWidget->addItem(QString::fromStdString(m.getCategory() + " | " + m.getName()));
	}
}

void GUI::searchLineEditHandler()
{
	ui.medicationsListWidget->clear();
	string given_string = ui.searchLineEdit->text().toStdString();
	if (given_string.empty())
		populateMedicationsList();
	else {
		vector<Medication> medications = service.searchCategoryName(given_string);
		for (Medication m : medications) {
			ui.medicationsListWidget->addItem(QString::fromStdString(m.getCategory() + " | " + m.getName()));
		}
	}
}

void GUI::nameButtonHandler()
{
	ui.nameListWidget->clear();
	string name = ui.nameLineEdit->text().toStdString();
	string side_effects = service.showSideEffects(name);
	if (side_effects.empty())
		QMessageBox::warning(this, "ERROR", "No such medicine exists!!!");
	else {
		stringstream stream(side_effects);
		std::string effect;
		while(getline(stream, effect, ','))
			ui.nameListWidget->addItem(QString::fromStdString(effect));
	}
}
