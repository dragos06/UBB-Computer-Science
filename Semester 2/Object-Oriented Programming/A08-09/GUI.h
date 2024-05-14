#pragma once
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class GUI : public QWidget
{
	Service& service;

	QListWidget* allTutorialsList;

	QLineEdit* titleEdit;
	QLineEdit* presenterEdit;
	QLineEdit* durationEdit;
	QLineEdit* likesEdit;
	QLineEdit* linkEdit;

	QPushButton* addButton;
	QPushButton* updateButton;
	QPushButton* deleteButton;

	QLineEdit* filterEdit;
	QPushButton* filterButton;

	QListWidget* filteredTutorialsList;
	QPushButton* nextWatchlistButton;
	QPushButton* addWatchlistButton;
	QPushButton* openLinkButton;

	QListWidget* allWatchlistList;
	QPushButton* deleteWatchlistButton;
	QPushButton* openWatchlistButton;


public:
	GUI(Service& serv, QWidget* parent = nullptr);

	void initGUI();
	void populateList();
};