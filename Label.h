#pragma once
#include<QtWidgets/qwidget.h>
#include<QtWidgets/qboxlayout.h>
#include<QtWidgets/qformlayout.h>
#include<QtWidgets/qlistwidget.h>
#include<QtWidgets/qlabel.h>
#include<QtWidgets/qlineedit.h>
#include<QtWidgets/qpushbutton.h>
#include<QtWidgets/qmessagebox.h>
#include"Service.h"

class Label :public QWidget, public Observer
{
public:
	Label(Service& serv) :srv{ serv }
	{
		srv.addObserver(this);
		init();
		loadData();
		connect();
	}

private:
	Service& srv;

	QListWidget* listaStatistica = new QListWidget;

	QHBoxLayout* lyMain = new QHBoxLayout();

	QLineEdit* GEN = new QLineEdit;
	QLineEdit* PROCENT = new QLineEdit;


	void update()
	{
		loadData();
	}
	void init()
	{
		this->setLayout(lyMain);
		this->setStyleSheet("background-color: #d6cbf5;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold;");

		lyMain->addWidget(listaStatistica);

		QFormLayout* genstat = new QFormLayout;
		genstat->addRow("Gen", GEN);
		genstat->addRow("Procent", PROCENT);
		lyMain->addLayout(genstat);
		
	}

	void loadData()
	{
		listaStatistica->clear();
		vector<DTO> stat = this->srv.statistica();

		for (auto v : stat)
		{
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(v.get_gen()), listaStatistica);
			item->setData(Qt::UserRole, QString::number(v.get_procent()));

		}
	}
	void connect()
	{

	QObject::connect(listaStatistica, &QListWidget::itemSelectionChanged, [&]() {

			if (listaStatistica->selectedItems().isEmpty())
			{
				PROCENT->setText("");
				GEN->setText("");
				return;
			}

			else {


				QListWidgetItem* selectItem = listaStatistica->selectedItems().at(0);
				auto Gen = selectItem->text();
				auto Procent = selectItem->data(Qt::UserRole).toString();
				GEN->setText(Gen);
				PROCENT->setText(Procent);
			}

			});
	}

};