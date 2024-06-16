#include "Practical.h"
#include <QtWidgets/QApplication>
#include "DepartmentRepository.h"
#include "VolunteerRepository.h"
#include "DepartmentWidget.h"
#include "Service.h"
#include "InfoWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DepartmentRepository dep_rep{ "departments.txt" };
    VolunteerRepository vol_rep{ "volunteers.txt" };
    Service serv{ dep_rep, vol_rep };
    InfoWidget info{ serv };
    info.show();
    for (auto d : dep_rep.getDepartmentsRepository()) {
        DepartmentWidget* w = new DepartmentWidget{ serv, d };
        w->setWindowTitle(QString::fromStdString(d.getName()));
        w->show();
    }
    return a.exec();
}
