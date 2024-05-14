#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include "TutorialRepository.h"
#include "WatchlistRepository.h"
#include "Testing.h"
#include <string>
#include <iostream>
#include "Service.h"
#include "GUI.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	FileTutorialRepository* tutorial_repository = new FileTutorialRepository("tutorials.txt");
	WatchlistCSV* watchlist_repository = new WatchlistCSV("watchlist.csv");
	Service service{ tutorial_repository, watchlist_repository };
	GUI gui{ service };
	gui.show();
    return a.exec();
}
