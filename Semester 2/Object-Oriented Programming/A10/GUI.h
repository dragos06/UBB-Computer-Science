#pragma once
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include "ui_oopa10dragos06.h"
#include <qpainter.h>
#include <QTableView>
#include "WatchlistTableModel.h"
#include <qshortcut.h>

class GUI : public QWidget
{
	Q_OBJECT

private:
	std::vector<Tutorial> filtered;
	int currentFiltered;

	Service& service;
	QTableView* watchlistTableView;
	WatchlistTableModel* watchlistTableModel;

	QListWidget* allTutorialsList;

	QLineEdit* titleEdit;
	QLineEdit* presenterEdit;
	QLineEdit* durationEdit;
	QLineEdit* likesEdit;
	QLineEdit* linkEdit;

	QPushButton* addButton;
	QPushButton* updateButton;
	QPushButton* deleteButton;
	QPushButton* generateChartButton;
	QPushButton* undoButton;
	QPushButton* redoButton;

	QLineEdit* filterEdit;
	QPushButton* filterButton;

	QListWidget* filteredTutorialsList;
	QPushButton* nextWatchlistButton;
	QPushButton* addWatchlistButton;
	QPushButton* openLinkButton;

	//QListWidget* allWatchlistList;
	QPushButton* deleteWatchlistButton;
	QPushButton* openWatchlistButton;

	QPushButton* csvButton;
	QPushButton* htmlButton;

	QShortcut* undoShortcut;
	QShortcut* redoShortcut;

public:
	GUI(Service& serv, QWidget* parent = nullptr);

private:
	void initGUI();
	
	int getSelectedIndex();
	void listItemChanged();
	


	void populateList();
	void populateFilteredTutorialsList();
	void populateWatchlist();
	void connectSignalsAndSlots();

	void addTutorialButtonHandler();
	void deleteTutorialButtonHandler();
	void updateTutorialButtonHandler();
	void generateChartButtonHandler();

	void filterButtonHandler();
	void nextWatchlistButtonHandler();
	void openLinkButtonHandler();
	void addWatchlistButtonHandler();

	void deleteWatchlistButtonHandler();
	void openWatchlistButtonHandler();

	void undoButtonHandler();
	void redoButtonHandler();



signals:
	void tutorialsUpdatedSignal();
	void filterWatchlistUpdatedSignal();
	void watchlistUpdatedSignal();

	void addTutorialSignal(const std::string& title, const std::string& presenter, int duration, int likes, const std::string& link);
	void deleteTutorialSignal(const std::string& title, const std::string& presenter, int duration, int likes, const std::string& link);
	void updateTutorialSignal(const std::string& title, const std::string& presenter, int duration, int likes, const std::string& link);

	void filterWatchlistSignal(const std::string& presenter);
	void nextWatchlistSignal();
	void openLinkSignal();
	void addWatchlistSignal();
public slots:
	void addTutorial(const std::string& title, const std::string& presenter, int duration, int likes, const std::string& link);
	void deleteTutorial(const std::string& title, const std::string& presenter, int duration, int likes, const std::string& link);
	void updateTutorial(const std::string& title, const std::string& presenter, int duration, int likes, const std::string& link);

	void filterWatchlist(const std::string& presenter);
	void nextWatchlist();
	void openLink();
	void addWatchlist();

	void showHelloWorld();

	void tableItemChanged(const QItemSelection& selected, const QItemSelection& deselected);
}; 

class HelloWorldWidget : public QWidget {
public:
	HelloWorldWidget(QWidget* parent = 0) : QWidget{ parent } {};
protected:
	void paintEvent(QPaintEvent* event) override {
		QPainter painter(this);
		painter.drawText(rect(), Qt::AlignCenter, "Hello World");
	}
};