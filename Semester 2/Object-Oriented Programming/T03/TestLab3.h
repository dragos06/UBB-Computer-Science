#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TestLab3.h"

class TestLab3 : public QMainWindow
{
    Q_OBJECT

public:
    TestLab3(QWidget *parent = nullptr);
    ~TestLab3();

private:
    Ui::TestLab3Class ui;
};
