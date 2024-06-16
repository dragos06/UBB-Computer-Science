#pragma once

#include <QWidget>
#include "ui_DepartmentWidget.h"
#include "Observer.h"
#include "Service.h"

class DepartmentWidget : public QWidget, public Observer
{
	Q_OBJECT

public:
	DepartmentWidget(Service& service, Department department, QWidget *parent = nullptr);
	~DepartmentWidget();

private:
	Ui::DepartmentWidgetClass ui;
	Service& service;
	Department department;
	void update() override;
public:
	void addButtonHandler();
	void save();
	void unassignedButtonHandler();
	void addUnButtonHandler();
};
