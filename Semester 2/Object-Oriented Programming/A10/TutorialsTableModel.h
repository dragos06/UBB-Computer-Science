#pragma once
#include <QAbstractTableModel>
#include "TutorialRepository.h"
#include "Service.h"

class TutorialsTableModel : public QAbstractTableModel {
	Q_OBJECT
private:
	Service& serv;
public:
	TutorialsTableModel(Service& serv, QObject* parent = NULL);
	~TutorialsTableModel();
	
	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
};