#pragma once

#include <QWidget>
#include "ui_InfoWidget.h"
#include "Observer.h"
#include "Service.h"

class InfoWidget : public QWidget, public Observer
{
	Q_OBJECT

public:
	InfoWidget(Service& service, QWidget *parent = nullptr);
	~InfoWidget();

private:
	Ui::InfoWidgetClass ui;
	Service& service;
	void update() override;
};
