#include "DepartmentWidget.h"
#include <sstream>
#include <qmessagebox.h>
using namespace std;


DepartmentWidget::DepartmentWidget(Service& service, Department department, QWidget *parent)
	: QWidget(parent), service{service}, department{department}
{
	ui.setupUi(this);
	service.registerObserver(this);
	ui.descriptionLineEdit->setText(QString::fromStdString(department.getDescription()));
	service.notify();
	QObject::connect(ui.addPushButton, &QPushButton::clicked, this, &DepartmentWidget::addButtonHandler);
	QObject::connect(ui.unassignedPushButton, &QPushButton::clicked, this, &DepartmentWidget::unassignedButtonHandler);
	QObject::connect(ui.addUnPushButton, &QPushButton::clicked, this, &DepartmentWidget::addUnButtonHandler);
}

DepartmentWidget::~DepartmentWidget()
{
}

void DepartmentWidget::update()
{
	ui.ownDepartmentListWidget->clear();
	for (auto v : this->service.getVolunteersDepartment(department.getName())) {
		string interests;
		for (auto i : v.getInterests()) {
			interests += i + ", ";
		}
		ui.ownDepartmentListWidget->addItem(QString::fromStdString(v.getName() + " - " + v.getEmail()+ " - " + interests + " - " + v.getDepartment()));
	}

	ui.unassignedListWidget->clear();
	for (auto v : this->service.getVolunteersDepartment("none")) {
		string interests;
		for (auto i : v.getInterests()) {
			interests += i + ";";
		}
		ui.unassignedListWidget->addItem(QString::fromStdString(v.getName() + "," + v.getEmail() + "," + v.getDepartment() + "," + interests));
	}
}

void DepartmentWidget::addButtonHandler()
{
	string name = ui.nameLineEdit->text().toStdString();
	if (name.empty()){
		QMessageBox::warning(this, "Warning", "Name field is empty!");
		return;
	}
	string email = ui.emailLineEdit->text().toStdString();
	if (email.empty()) {
		QMessageBox::warning(this, "Warning", "Email field is empty!");
		return;
	}
	string interests = ui.interestsLineEdit->text().toStdString();
	stringstream stream{ interests };
	string interest;
	vector<std::string> interests_list;
	while (getline(stream, interest, ',')) {
		interests_list.push_back(interest);
	}
	service.addVolunteer(name, email, interests_list, "none");
	service.notify();
}

void DepartmentWidget::save()
{
	service.saveService();
}

void DepartmentWidget::unassignedButtonHandler()
{
	int nr_words = 0;
	string word;
	stringstream stream{ department.getDescription() };
	while (getline(stream, word, ' ')) {
		nr_words++;
	}
	std::vector<Volunteer> volunteers = service.getVolunteersDepartment("none");
	if (volunteers.size() < 3) {
		QMessageBox::warning(this, "Warning", "There are not enough unassigned students!");
		return;
	}
	std::vector<int> top;
	for (auto v : volunteers) {
		double score = 0;
		for (auto i : v.getInterests()) {
			auto res = department.getDescription().find(i);
			if (res != std::string::npos)
				score++;
		}
		score = (double)score / nr_words;
		top.push_back(score);
	}
	for (int i = 0; i < volunteers.size() - 1; i++)
		for (int j = i + 1; j < volunteers.size(); j++) {
			if (top[i] < top[j]) {
				swap(volunteers[i], volunteers[j]);
			}
		}
	std::vector<Volunteer> top3;
	top3.push_back(volunteers[0]);
	top3.push_back(volunteers[1]);
	top3.push_back(volunteers[2]);
	
	ui.unassignedListWidget->clear();
	for (auto v : top3) {
		string interests;
		for (auto i : v.getInterests()) {
			interests += i + ", ";
		}
		ui.unassignedListWidget->addItem(QString::fromStdString(v.getName() + " - " + v.getEmail() + " - " + interests + " - " + v.getDepartment()));
	}
	//service.notify();
}

void DepartmentWidget::addUnButtonHandler()
{
	QListWidgetItem* item = ui.unassignedListWidget->currentItem();
	string volunteer_str = item->text().toStdString();
	stringstream stream{ volunteer_str };
	string name, email, department, interests;
	getline(stream, name, ',');
	getline(stream, email, ',');
	getline(stream, department, ',');
	getline(stream, interests, ',');
	stringstream stream_interests{ interests };
	string interest;
	std::vector<std::string> interests_list;
	while (getline(stream_interests, interest, ';'))
		interests_list.push_back(interest);
	for (auto& v : service.getVolunteers()) {
		if (v.getName() == name && v.getEmail() == email)
			v.setDepartment(this->department.getName());
	}
	this->save();
	this->service.notify();
}
