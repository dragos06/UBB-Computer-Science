#include "RepositoryType.h"
#include <qboxlayout.h>
#include <qpushbutton.h>

RepositoryType::RepositoryType(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QVBoxLayout* layout = new QVBoxLayout{ this };
	QPushButton* csvButton = new QPushButton{ "CSV", this };
	QPushButton* htmlButton = new QPushButton{ "HTML", this };
	layout->addWidget(csvButton);
	layout->addWidget(htmlButton);
	connect(csvButton, &QPushButton::clicked, [this]() {emit formatChosen("csv"); accept(); });
	connect(htmlButton, &QPushButton::clicked, [this]() {emit formatChosen("html"); accept(); });
}

RepositoryType::~RepositoryType()
{}
