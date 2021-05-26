#pragma once
#include<QAbstractTableModel>
#include"Carte.h"
#include<vector>
#include<qdebug.h>
#include<qbrush.h>

using std::vector;

class MyListModel:public QAbstractListModel
{
private:

	vector<Carte> carti;

public:
	MyListModel(const vector<Carte>& carti) :carti{ carti } {};
	
	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return carti.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
	{
		if (role == Qt::DisplayRole)
		{
			
			qDebug() << "get row:" << index.row();
			auto c= carti[index.row()].get_id();
			return QString::number(c);

		}

		if (role == Qt::UserRole)
		{
			auto tp = carti[index.row()].get_id();
			return QString::number(tp);
		}

		if (role == Qt::BackgroundRole)
		{
			if (carti[index.row()].get_id()%2==0)
				return QColor(Qt::blue);
		}

		return QVariant{};
	}


};
