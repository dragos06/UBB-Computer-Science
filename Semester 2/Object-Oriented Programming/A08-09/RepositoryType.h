#pragma once

#include <QDialog>
#include "ui_RepositoryType.h"

class RepositoryType : public QDialog
{
	Q_OBJECT

public:
	RepositoryType(QWidget *parent = nullptr);
	~RepositoryType();

private:
	Ui::RepositoryTypeClass ui;
signals:
	void formatChosen(const QString& format);
};
