#include "InfoWidget.h"

InfoWidget::InfoWidget(Service& service, QWidget *parent)
	: QWidget(parent), service{service}
{
	ui.setupUi(this);
	service.registerObserver(this);
	service.notify();
}

InfoWidget::~InfoWidget()
{}

void InfoWidget::update()
{
	ui.departmentsListWidget->clear();
	for (auto d : service.getDepartments()) {
		int number = service.getVolunteersDepartment(d.getName()).size();
		ui.departmentsListWidget->addItem(QString::fromStdString(d.getName() + " " + std::to_string(number)));
	}
}
