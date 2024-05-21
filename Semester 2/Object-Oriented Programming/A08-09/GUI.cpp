#include "GUI.h"
#include <qlayout.h>
#include <qlabel.h>
#include <qformlayout.h>
#include <vector>
#include <qstackedlayout.h>
#include <qdialogbuttonbox.h>
#include <qpainter.h>
#include <exception>
#include <qmessagebox.h>
#include <qpainter.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include "TutorialValidator.h"
#include "RepositoryExceptions.h"
#include <QtCharts/QChart>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>


GUI::GUI(Service& serv, QWidget* parent): QWidget{ parent }, service{ serv }
{
	this->initGUI();
	this->populateList();
	this->connectSignalsAndSlots();
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
	generateChartButton = new QPushButton{ "Generate Chart" };
	buttonsLayout->addWidget(addButton, 0, 0);
	buttonsLayout->addWidget(deleteButton, 0, 1);
	buttonsLayout->addWidget(updateButton, 0, 2);
	buttonsLayout->addWidget(generateChartButton, 1, 1);

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

int GUI::getSelectedIndex()
{
	if (this->allTutorialsList->count() == 0)
		return -1;

	QModelIndexList index = this->allTutorialsList->selectionModel()->selectedIndexes();
	if (index.size() == 0) {
		this->titleEdit->clear();
		this->presenterEdit->clear();
		this->durationEdit->clear();
		this->likesEdit->clear();
		this->linkEdit->clear();
		return -1;
	}
	int idx = index.at(0).row();
	return idx;
}

void GUI::listItemChanged()
{
	int idx = this->getSelectedIndex();
	std::vector<Tutorial> tutorials = this->service.getTutorialsService();
	if (idx == -1)
		return;
	if (idx >= tutorials.size())
		return;
	
	Tutorial t = tutorials[idx];
	this->titleEdit->setText(QString::fromStdString(t.getTitle()));
	this->presenterEdit->setText(QString::fromStdString(t.getPresenter()));
	this->durationEdit->setText(QString::fromStdString(std::to_string(t.getDuration())));
	this->likesEdit->setText(QString::fromStdString(std::to_string(t.getLikes())));
	this->linkEdit->setText(QString::fromStdString(t.getLink()));

}


void GUI::populateList()
{
	this->allTutorialsList->clear();
	this->service.loadFromFileService();
	std::vector<Tutorial> tutorials = this->service.getTutorialsService();
	
	for (auto t : tutorials) {
		this->allTutorialsList->addItem(QString::fromStdString(t.getTitle() + " - " + t.getPresenter() + " - " + std::to_string(t.getDuration()) + " - " + std::to_string(t.getLikes()) + " - " + t.getLink()));
	}
	if (this->allTutorialsList->count() > 0)
		this->allTutorialsList->setCurrentRow(0);
}

void GUI::populateFilteredTutorialsList()
{
	this->filteredTutorialsList->clear();
	this->filteredTutorialsList->addItem(QString::fromStdString(filtered[currentFiltered].getTitle() + " - " + filtered[currentFiltered].getPresenter() + " - " + std::to_string(filtered[currentFiltered].getDuration()) + " - " + std::to_string(filtered[currentFiltered].getLikes()) + " - " + filtered[currentFiltered].getLink()));
	if (this->filteredTutorialsList->count() > 0)
		this->filteredTutorialsList->setCurrentRow(0);
}

void GUI::populateWatchlist()
{
	this->allWatchlistList->clear();
	std::vector<Tutorial> watchlist = this->service.getWatchlistService();
	for (auto t : watchlist) {
		this->allWatchlistList->addItem(QString::fromStdString(t.getTitle() + " - " + t.getPresenter() + " - " + std::to_string(t.getDuration()) + " - " + std::to_string(t.getLikes()) + " - " + t.getLink()));
	}
	if (this->allWatchlistList->count() > 0)
		this->allWatchlistList->setCurrentRow(0);
}

void GUI::connectSignalsAndSlots()
{
	QObject::connect(this, &GUI::tutorialsUpdatedSignal, this, &GUI::populateList);
	QObject::connect(this, &GUI::filterWatchlistUpdatedSignal, this, &GUI::populateFilteredTutorialsList);
	QObject::connect(this, &GUI::watchlistUpdatedSignal, this, &GUI::populateWatchlist);

	QObject::connect(this->allTutorialsList, &QListWidget::itemSelectionChanged, this, &GUI::listItemChanged);
	QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addTutorialButtonHandler);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GUI::deleteTutorialButtonHandler);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateTutorialButtonHandler);
	QObject::connect(this->generateChartButton, &QPushButton::clicked, this, &GUI::generateChartButtonHandler);
	QObject::connect(this->filterButton, &QPushButton::clicked, this, &GUI::filterButtonHandler);
	QObject::connect(this->nextWatchlistButton, &QPushButton::clicked, this, &GUI::nextWatchlistButtonHandler);
	QObject::connect(this->openLinkButton, &QPushButton::clicked, this, &GUI::openLinkButtonHandler);
	QObject::connect(this->addWatchlistButton, &QPushButton::clicked, this, &GUI::addWatchlistButtonHandler);

	QObject::connect(this, SIGNAL(addTutorialSignal(const std::string&, const std::string&, int, int, const std::string&)), 
		this, SLOT(addTutorial(const std::string&, const std::string&, int, int, const std::string&)));
	QObject::connect(this, SIGNAL(deleteTutorialSignal(const std::string&, const std::string&, int, int, const std::string&)),
		this, SLOT(deleteTutorial(const std::string&, const std::string&, int, int, const std::string&)));
	QObject::connect(this, SIGNAL(updateTutorialSignal(const std::string&, const std::string&, int, int, const std::string&)),
		this, SLOT(updateTutorial(const std::string&, const std::string&, int, int, const std::string&)));
	QObject::connect(this, SIGNAL(filterWatchlistSignal(const std::string&)), this, SLOT(filterWatchlist(const std::string&)));
	QObject::connect(this, SIGNAL(nextWatchlistSignal()), this, SLOT(nextWatchlist()));
	QObject::connect(this, SIGNAL(openLinkSignal()), this, SLOT(openLink()));
	QObject::connect(this, SIGNAL(addWatchlistSignal()), this, SLOT(addWatchlist()));

	QObject::connect(this->deleteWatchlistButton, &QPushButton::clicked, this, &GUI::deleteWatchlistButtonHandler);
	QObject::connect(this->openWatchlistButton, &QPushButton::clicked, this, &GUI::openWatchlistButtonHandler);
}

void GUI::addTutorialButtonHandler()
{
	QString title = this->titleEdit->text();
	QString presenter = this->presenterEdit->text();
	QString duration = this->durationEdit->text();
	QString likes = this->likesEdit->text();
	QString link = this->linkEdit->text();
	emit addTutorialSignal(title.toStdString(), presenter.toStdString(), duration.toInt(), likes.toInt(), link.toStdString());
}

void GUI::deleteTutorialButtonHandler()
{
	QString title = this->titleEdit->text();
	QString presenter = this->presenterEdit->text();
	QString duration = this->durationEdit->text();
	QString likes = this->likesEdit->text();
	QString link = this->linkEdit->text();
	emit deleteTutorialSignal(title.toStdString(), presenter.toStdString(), duration.toInt(), likes.toInt(), link.toStdString());
}

void GUI::updateTutorialButtonHandler()
{
	QString title = this->titleEdit->text();
	QString presenter = this->presenterEdit->text();
	QString duration = this->durationEdit->text();
	QString likes = this->likesEdit->text();
	QString link = this->linkEdit->text();
	emit updateTutorialSignal(title.toStdString(), presenter.toStdString(), duration.toInt(), likes.toInt(), link.toStdString());
}

void GUI::generateChartButtonHandler()
{
	QBarSeries* series = new QBarSeries();
	QBarSet* set = new QBarSet("Tutorials");
	*set << service.getNumberTutorialsDuration(1, 5)
		<< service.getNumberTutorialsDuration(5, 10)
		<< service.getNumberTutorialsDuration(10, 99);
	set->setColor("green");
	series->append(set);

	QChart* chart = new QChart();
	chart->addSeries(series);
	chart->setTitle("Tutorials by duration");
	chart->setAnimationOptions(QChart::SeriesAnimations);

	QStringList categories;
	categories << "1H->5H" << "5H->10" << "+10H";
	QBarCategoryAxis* axisX = new QBarCategoryAxis();
	axisX->append(categories);
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);

	QValueAxis* axisY = new QValueAxis();
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);

	QChartView* chartView = new QChartView(chart);
	chartView->setChart(chart);

	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->resize(400, 300);
	chartView->setWindowTitle("Tutorials by duration");
	chartView->show();
}


void GUI::filterButtonHandler()
{
	QString presenter = this->filterEdit->text();
	emit filterWatchlistSignal(presenter.toStdString());
}

void GUI::nextWatchlistButtonHandler()
{
	emit nextWatchlistSignal();
}

void GUI::openLinkButtonHandler()
{
	emit openLinkSignal();
}

void GUI::addWatchlistButtonHandler()
{
	emit addWatchlistSignal();
}

void GUI::deleteWatchlistButtonHandler()
{
	try {
		int row = this->allWatchlistList->currentRow();
		if (row >= 0) {
			QVBoxLayout* new_layout = new QVBoxLayout{};
			QLabel* new_label = new QLabel{ "Did you like the video?" };
			QDialog* new_widget = new QDialog{};
			QPushButton* like = new QPushButton{ "Like" };
			QPushButton* dislike = new QPushButton{ "Dislike" };
			new_layout->addWidget(new_label);
			new_layout->addWidget(like);
			new_layout->addWidget(dislike);
			new_widget->setLayout(new_layout);

			new_widget->show();
			QObject::connect(like, &QPushButton::clicked, new_widget, [=]() {
				int row = this->allWatchlistList->currentRow();
				if (row >= 0) {
					Tutorial clickedTutorial = this->service.getWatchlistService()[row];
					this->service.deleteWatchlistService(clickedTutorial.getTitle(), clickedTutorial.getPresenter(), 1);
					emit watchlistUpdatedSignal();
					emit tutorialsUpdatedSignal();
					new_widget->close();
				}
				});
			QObject::connect(dislike, &QPushButton::clicked, new_widget, [=]() {
				int row = this->allWatchlistList->currentRow();
				if (row >= 0) {
					Tutorial clickedTutorial = this->service.getWatchlistService()[row];
					this->service.deleteWatchlistService(clickedTutorial.getTitle(), clickedTutorial.getPresenter(), 0);
					emit watchlistUpdatedSignal();
					emit tutorialsUpdatedSignal();
					new_widget->close();
				}});
		}
	}
	catch (RepositoryException& e) {
		QMessageBox::critical(this, "ERROR", e.what());
		return;
	}
	catch (TutorialException& e) {
		std::string err_str = "";
		for (auto error : e.getErrors()) {
			err_str += error + "\n";
		}
		QMessageBox::critical(this, "ERROR", QString::fromStdString(err_str));
		return;
	}
}

void GUI::openWatchlistButtonHandler()
{
	this->service.openWatchlist();
}

void GUI::deleteTutorial(const std::string& title, const std::string& presenter, int duration, int likes, const std::string& link)
{
	try {
		this->service.deleteTutorialService(title, presenter);
		emit tutorialsUpdatedSignal();
	}
	catch (RepositoryException& e) {
		QMessageBox::critical(this, "ERROR", e.what());
		return;
	}
	catch (TutorialException& e) {
		std::string err_str = "";
		for (auto error : e.getErrors()) {
			err_str += error + "\n";
		}
		QMessageBox::critical(this, "ERROR", QString::fromStdString(err_str));
		return;
	}
}

void GUI::updateTutorial(const std::string& title, const std::string& presenter, int duration, int likes, const std::string& link)
{
	try {
		this->service.updateTutorialService(title, presenter, duration, likes, link);
		emit tutorialsUpdatedSignal();
	}
	catch (RepositoryException& e) {
		QMessageBox::critical(this, "ERROR", e.what());
		return;
	}
	catch (TutorialException& e) {
		std::string err_str = "";
		for (auto error : e.getErrors()) {
			err_str += error + "\n";
		}
		QMessageBox::critical(this, "ERROR", QString::fromStdString(err_str));
		return;
	}
}

void GUI::filterWatchlist(const std::string& presenter)
{
	filtered = this->service.tutorialsGivenPresenter(presenter);
	currentFiltered = 0;
	emit filterWatchlistUpdatedSignal();
}

void GUI::nextWatchlist()
{
	if (this->filtered.size() > 0) {
		this->currentFiltered = (this->currentFiltered + 1) % this->filtered.size();
		emit filterWatchlistUpdatedSignal();
	}
}

void GUI::openLink()
{
	if (this->filtered.size() > 0){
		std::string link = this->filtered[currentFiltered].getLink();
		system(std::string("start " + link).c_str());
	}
}

void GUI::addWatchlist()
{
	try {
		if (this->filtered.size() > 0) {
			this->service.addWatchlistService(this->filtered[currentFiltered]);
			emit watchlistUpdatedSignal();
		}
	}
	catch (RepositoryException& e) {
		QMessageBox::critical(this, "ERROR", e.what());
		return;
	}
	catch (TutorialException& e) {
		std::string err_str = "";
		for (auto error : e.getErrors()) {
			err_str += error + "\n";
		}
		QMessageBox::critical(this, "ERROR", QString::fromStdString(err_str));
		return;
	}
}

void GUI::showHelloWorld()
{
	HelloWorldWidget* helloWorldWidget = new HelloWorldWidget();
	helloWorldWidget->show();
}

void GUI::addTutorial(const std::string& title, const std::string& presenter, int duration, int likes, const std::string& link)
{
	try
	{
		this->service.addTutorialService(title, presenter, duration, likes, link);
		emit tutorialsUpdatedSignal(); 
	}
	catch (RepositoryException& e) { 
		QMessageBox::critical(this, "ERROR", e.what());
		return;
	}
	catch (TutorialException& e) {
		std::string err_str = "";
		for (auto error : e.getErrors()) {
			err_str += error + "\n";
		}
		QMessageBox::critical(this, "ERROR", QString::fromStdString(err_str));
		return;
	}
}