#include "GUI.h"
#include <qlayout.h>
#include <qlabel.h>
#include <qformlayout.h>
#include <vector>


GUI::GUI(Service& serv, QWidget* parent): QWidget{ parent }, service{ serv }
{
	this->initGUI();
	this->populateList();
}

void GUI::initGUI()
{
	QHBoxLayout* mainLayout = new QHBoxLayout{ this };

	QVBoxLayout* adminLayout = new QVBoxLayout{};
	QLabel* allTutorialsLabel = new QLabel{ "Tutorials" };
	adminLayout->addWidget(allTutorialsLabel);
	allTutorialsList = new QListWidget{};
	adminLayout->addWidget(allTutorialsList);

	QFormLayout* tutorialDataLayout = new QFormLayout;
	QLabel* tutorialTitle = new QLabel{ "Title: " };
	titleEdit = new QLineEdit;
	tutorialDataLayout->addRow(tutorialTitle, titleEdit);
	QLabel* tutorialPresenter = new QLabel{ "Presenter: " };
	presenterEdit = new QLineEdit;
	tutorialDataLayout->addRow(tutorialPresenter, presenterEdit);
	QLabel* tutorialDuration = new QLabel{ "Duration: " };
	durationEdit = new QLineEdit;
	tutorialDataLayout->addRow(tutorialDuration, durationEdit);
	QLabel* tutorialLikes = new QLabel{ "Likes: " };
	likesEdit = new QLineEdit;
	tutorialDataLayout->addRow(tutorialLikes, likesEdit);
	QLabel* tutorialLink = new QLabel{ "Link: " };
	linkEdit = new QLineEdit;
	tutorialDataLayout->addRow(tutorialLink, linkEdit);
	
	adminLayout->addLayout(tutorialDataLayout);

	QGridLayout* buttonsLayout = new QGridLayout;
	addButton = new QPushButton{ "Add" };
	deleteButton = new QPushButton{ "Delete" };
	updateButton = new QPushButton{ "Update" };
	buttonsLayout->addWidget(addButton, 0, 0);
	buttonsLayout->addWidget(deleteButton, 0, 1);
	buttonsLayout->addWidget(updateButton, 0, 2);

	adminLayout->addLayout(buttonsLayout);

	mainLayout->addLayout(adminLayout);

	mainLayout->addSpacing(100);

	QVBoxLayout* userLayout = new QVBoxLayout{};
	
	QLabel* userLabel = new QLabel{ "Watchlist" };
	userLayout->addWidget(userLabel);

	allWatchlistList = new QListWidget{};
	userLayout->addWidget(allWatchlistList);

	QGridLayout* watchlistButtonsLayout = new QGridLayout;
	deleteWatchlistButton = new QPushButton{ "Delete" };
	openWatchlistButton = new QPushButton{ "Open" };
	watchlistButtonsLayout->addWidget(deleteWatchlistButton, 0, 0);
	watchlistButtonsLayout->addWidget(openWatchlistButton, 0, 1);
	userLayout->addLayout(watchlistButtonsLayout);

	userLayout->addSpacing(100);

	QLabel* filterLabel = new QLabel{ "Filter" };
	userLayout->addWidget(filterLabel);

	QGridLayout* filterLayout = new QGridLayout;
	filterEdit = new QLineEdit;
	filterButton = new QPushButton{ "Filter" };
	filterLayout->addWidget(filterEdit, 0, 0);
	filterLayout->addWidget(filterButton, 0, 1);
	userLayout->addLayout(filterLayout);

	filteredTutorialsList = new QListWidget{};
	userLayout->addWidget(filteredTutorialsList);

	QGridLayout* filterButtonsLayout = new QGridLayout;
	openLinkButton = new QPushButton{ "Open Tutorial" };
	addWatchlistButton = new QPushButton{ "Add" };
	nextWatchlistButton = new QPushButton{ "Next" };
	filterButtonsLayout->addWidget(openLinkButton, 0, 0);
	filterButtonsLayout->addWidget(addWatchlistButton, 0, 1);
	filterButtonsLayout->addWidget(nextWatchlistButton, 0, 2);
	userLayout->addLayout(filterButtonsLayout);

	mainLayout->addLayout(userLayout);

}

void GUI::populateList()
{
	//this->allTutorialsList->clear();
	this->service.loadFromFileService();
	std::vector<Tutorial> tutorials = this->service.getTutorialsService();
	
	for (auto t : tutorials) {
		this->allTutorialsList->addItem(QString::fromStdString(t.getTitle() + " - " + t.getPresenter() + " - " + std::to_string(t.getDuration()) + " - " + std::to_string(t.getLikes()) + " - " + t.getLink()));
	}
}
