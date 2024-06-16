#ifndef WATCHLISTTABLEMODEL_H
#define WATCHLISTTABLEMODEL_H

#include <QAbstractTableModel>
#include "Service.h"

class WatchlistTableModel : public QAbstractTableModel {
    Q_OBJECT

private:
    Service& service;

public:
    WatchlistTableModel(Service& s, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
};

#endif // WATCHLISTTABLEMODEL_H
