//#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include "TutorialRepository.h"
#include "WatchlistRepository.h"
#include "Testing.h"
#include <string>
#include <iostream>
#include "Service.h"
#include "GUI.h"
#include <qgridlayout.h>
#include "RepositoryType.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	
	FileTutorialRepository* tutorial_repository = new FileTutorialRepository("tutorials.txt");
	WatchlistBase* watchlist_repository = nullptr;

	RepositoryType repositoryDialog;
	QObject::connect(&repositoryDialog, &RepositoryType::formatChosen, [&](const QString& format) {
		if (format == "csv") {
			watchlist_repository = new WatchlistCSV("watchlist.csv");
		}
		else if (format == "html") {
			watchlist_repository = new WatchlistHTML("watchlist.html");
		}
		});
	repositoryDialog.exec();

	Service service{ tutorial_repository, watchlist_repository };
	GUI gui{ service };
	gui.show();
    
	return a.exec();
}
