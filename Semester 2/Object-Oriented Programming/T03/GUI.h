#pragma once

#include <QWidget>
#include "ui_GUI.h"
#include "Service.h"

class GUI : public QWidget
{
	Q_OBJECT

public:
	GUI(Service& service, QWidget *parent = nullptr);
	~GUI();

private:
	Ui::GUIClass ui;
	Service& service;
	void populateMedicationsList();
	void searchLineEditHandler();
	void nameButtonHandler();
};
