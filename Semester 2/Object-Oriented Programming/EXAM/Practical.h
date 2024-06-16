#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Practical.h"

class Practical : public QMainWindow
{
    Q_OBJECT

public:
    Practical(QWidget *parent = nullptr);
    ~Practical();

private:
    Ui::PracticalClass ui;
};
