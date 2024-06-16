#include "TutorialsTableModel.h"
#include <QFont>
#include <QBrush>

TutorialsTableModel::TutorialsTableModel(Service& s, QObject* parent) :QAbstractTableModel{ parent }, serv{ s }
{
}

TutorialsTableModel::~TutorialsTableModel()
{
}

int TutorialsTableModel::rowCount(const QModelIndex& parent) const
{
	int tutorialsNumber = this->serv.getSizeTutorialsService();
	return tutorialsNumber + 1;
}

int TutorialsTableModel::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant TutorialsTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();
	std::vector<Tutorial> tutorials = this->serv.getTutorialsService();
	if (row == tutorials.size())
		return QVariant();
	Tutorial t = tutorials[row];
	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		switch (column) {
		case 0:
			return QString::fromStdString(t.getTitle());
		case 1:
			return QString::fromStdString(t.getPresenter());
		case 2:
			return QString::number(t.getDuration());
		case 3:
			return QString::number(t.getLikes());
		case 4:
			return QString::fromStdString(t.getLink());
		default:
			break;
		}
	}
	if (role == Qt::FontRole) {
		QFont font("Times", 15, 10, true);
		font.setItalic(false);
		return font;
	}
	if (role == Qt::BackgroundRole) {
		if (row % 2 == 1) {
			return QBrush{ QColor{0, 250, 154} };
		}
	}

	return QVariant{};
}

QVariant TutorialsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
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
	if (role == Qt::FontRole) {
		QFont font("Times", 15, 10, true);
		font.setItalic(false);
		return font;
	}
	return QVariant{};
}

bool TutorialsTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;
	int tutorialIndex = index.row();
	std::vector<Tutorial> tutorials = this->serv.getTutorialsService();
	if (tutorialIndex == tutorials.size()) {
		this->beginInsertRows(QModelIndex{}, tutorialIndex, tutorialIndex);
		switch (index.column()) {
		case 0:
			this->serv.addTutorialService(value.toString().toStdString(), "", -1, -1, "");
			break;
		case 1:
			this->serv.addTutorialService("", value.toString().toStdString(), -1, -1, "");
			break;
		case 2:
			this->serv.addTutorialService("", "", value.toInt(), -1, "");
			break;
		case 3:
			this->serv.addTutorialService("", "", -1, value.toInt(), "" );
			break;
		case 4:
			this->serv.addTutorialService("", "", -1, -1, value.toString().toStdString() );
			break;
		}
		this->endInsertRows();
		return true;
	}
	Tutorial& currentTutorial = tutorials[tutorialIndex];
	switch(index.column()){
	case 0:
		currentTutorial.setTitle(value.toString().toStdString());
		break;
	case 1:
		currentTutorial.setPresenter(value.toString().toStdString());
		break;
	case 2:
		currentTutorial.setDuration(value.toInt());
	case 3:
		currentTutorial.setLikes(value.toInt());
	case 4:
		currentTutorial.setLink(value.toString().toStdString());
	}
	this->serv.updateTutorialNew(tutorialIndex, currentTutorial);
	emit dataChanged(index, index);
	return true;
}

Qt::ItemFlags TutorialsTableModel::flags(const QModelIndex& index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
