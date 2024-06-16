#include "WatchlistTableModel.h"
#include <QFont>
#include <QBrush>

WatchlistTableModel::WatchlistTableModel(Service& s, QObject* parent) : QAbstractTableModel{ parent }, service{ s } {}

int WatchlistTableModel::rowCount(const QModelIndex& parent) const {
    return service.getWatchlistService().size();
}

int WatchlistTableModel::columnCount(const QModelIndex& parent) const {
    return 5; // Title, Presenter, Duration, Likes, Link
}

QVariant WatchlistTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int column = index.column();
    const auto& watchlist = service.getWatchlistService();
    if (row >= watchlist.size())
        return QVariant();

    const Tutorial& tutorial = watchlist[row];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (column) {
        case 0:
            return QString::fromStdString(tutorial.getTitle());
        case 1:
            return QString::fromStdString(tutorial.getPresenter());
        case 2:
            return QString::number(tutorial.getDuration());
        case 3:
            return QString::number(tutorial.getLikes());
        case 4:
            return QString::fromStdString(tutorial.getLink());
        default:
            break;
        }
    }

    if (role == Qt::FontRole) {
        QFont font("Times", 10);
        return font;
    }

    /*if (role == Qt::BackgroundRole && row % 2 == 0) {
        return QBrush{ QColor{220, 220, 220} };
    }*/

    return QVariant{};
}

QVariant WatchlistTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString{ "Title" };
            case 1:
                return QString{ "Presenter" };
            case 2:
                return QString{ "Duration" };
            case 3:
                return QString{ "Likes" };
            case 4:
                return QString{ "Link" };
            default:
                break;
            }
        }
    }

    return QVariant{};
}

Qt::ItemFlags WatchlistTableModel::flags(const QModelIndex& index) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
