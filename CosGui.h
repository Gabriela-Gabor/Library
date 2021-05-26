#pragma once
#include<QtWidgets/qwidget.h>
#include<QtWidgets/qboxlayout.h>
#include<QtWidgets/qformlayout.h>
#include<QtWidgets/qlistwidget.h>
#include<QtWidgets/qlabel.h>
#include<QtWidgets/qlineedit.h>
#include<QtWidgets/qpushbutton.h>
#include<QtWidgets/qmessagebox.h>
#include<QtWidgets/qgridlayout.h>
#include<QtWidgets/qslider.h>
#include<QtWidgets/qcombobox.h>
#include<QtWidgets/qcheckbox.h>
#include"Service.h"
#include"MyListModel.h"
//#include<QtWidgets/qpalette.h>


#include<vector>
#include<string>

class CosQt :public QWidget
{
public:
	CosQt(Service& serv):srv{serv}
	{
		initCos();
		listaCos->setUniformItemSizes(true);
		updateData(srv.Cos());
		color();
		initConnect();
	}

private:

	Service& srv;

	QHBoxLayout* lyMain = new QHBoxLayout();
	QVBoxLayout* lySt = new QVBoxLayout;
	QVBoxLayout* lyDr = new QVBoxLayout;
	QFormLayout* lyNr = new QFormLayout;

	QPushButton* btnAdd = new QPushButton("&Adauga");
	QPushButton* btnDelete = new QPushButton("&Sterge");
	QPushButton* btnRand = new QPushButton("&Genereaza");
	QPushButton* btnUndo = new QPushButton("&Undo Stergere");
	QPushButton* btnOk = new QPushButton("&Ok");

	
	QListView* listaCos = new QListView;
	MyListModel* model;

	QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtAutor = new QLineEdit;
	QLineEdit* txtGen = new QLineEdit;
	QLineEdit* txtAn = new QLineEdit;
	QLineEdit* txtFisier = new QLineEdit;
	QLineEdit* txtNr= new QLineEdit;

	QComboBox* LyExport = new QComboBox();

	void initCos()
	{
		setLayout(lyMain);

		lySt->addWidget(listaCos);

		lyMain->addLayout(lySt);
	
		QFormLayout* form = new QFormLayout;
		form->addRow("Titlu:", txtTitlu);
		form->addRow("Autor:", txtAutor);
		form->addRow("Gen:", txtGen);
		form->addRow("An:", txtAn);
		form->addRow("Fisier: ", txtFisier);

		lyDr->addLayout(form);

		LyExport->insertItem(0, "Exporta html");
		LyExport->insertItem(1, "Exporta CVS");

		lyDr->addWidget(LyExport);


		QHBoxLayout* lyBtn = new QHBoxLayout();
		lyBtn->addWidget(btnAdd);
		lyBtn->addWidget(btnDelete);
		lyBtn->addWidget(btnRand);

		lyDr->addLayout(lyBtn);
		lyDr->addWidget(btnUndo);

		lyMain->addLayout(lyDr);

		lyNr->addRow("Numar: ", txtNr);

	}
	/*void loadCos()
	{
		listaCos->clear();
		vector<Carte> carti = srv.Cos();
		for (const auto& c : carti)
		{
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(c.get_titlu()), listaCos);
			item->setData(Qt::UserRole, QString::number(c.get_id()));
			
		}
	}*/

	void updateData(vector<Carte> carti)
	{
		model = new MyListModel(srv.Cos());
		listaCos->setModel(model);
	}

	void color()
	{
		const QString ButtonColor= "background-color:#6c5d94;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold;";
		const QString LineEditColor = "background-color: #e1b6fc;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold;";

		this->setStyleSheet("background-color: #d6cbf5;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold;");

		btnAdd->setStyleSheet(ButtonColor);
		btnDelete->setStyleSheet(ButtonColor);
		btnRand->setStyleSheet(ButtonColor);
		btnUndo->setStyleSheet(ButtonColor);
		btnOk->setStyleSheet(ButtonColor);

		txtAn->setStyleSheet(LineEditColor);
		txtTitlu->setStyleSheet(LineEditColor);
		txtAutor->setStyleSheet(LineEditColor);
		txtGen->setStyleSheet(LineEditColor);
		txtFisier->setStyleSheet(LineEditColor);
		txtNr->setStyleSheet(LineEditColor);

		LyExport->setStyleSheet(ButtonColor);

	}
	void initConnect()
	{
		QObject::connect(btnAdd, &QPushButton::clicked, [&]()
			{
				srv.adaugaCos(txtTitlu->text().toStdString());
				updateData(srv.Cos()); 
				txtTitlu->setText("");
			});

		QObject::connect(btnDelete, &QPushButton::clicked, [&]()
			{
				srv.stergeCos();
				updateData(srv.Cos());
			});

		QObject::connect(btnRand, &QPushButton::clicked, [&]()
			{
				lySt->addLayout(lyNr);
				lySt->addWidget(btnOk);
				
			});
		QObject::connect(btnOk, &QPushButton::clicked, [&]()
			{
				int nr;
				try
				{
					nr = std::stoi(txtNr->text().toStdString());
				}
				catch (const std::invalid_argument)
				{
					QMessageBox::warning(this, "Error", "Nr invalid!");
					return;
				}
				try
				{
					srv.genereazaCos(nr);
					updateData(srv.Cos());
					txtNr->setText("");
				
				}
				catch (CosException & ex)
				{
					QMessageBox::warning(this, "Error", QString::fromStdString(ex.getMessage()));
					txtNr->setText("");
					return;
				}
			});

		QObject::connect(btnUndo, &QPushButton::clicked, [&]()
			{
				try
				{
					srv.undo();
					updateData(srv.Cos());
				}
				catch (CarteException & ex)
				{
					QMessageBox::warning(this, "Error", QString::fromStdString(ex.getMessage()));
					return;
				}
			});

		QObject::connect(LyExport, QOverload<int>::of(&QComboBox::activated), [=](int index)
			{
				if (index == 0)
					try
					{
						srv.exporta_HTML(txtFisier->text().toStdString());
					}
					catch (CarteException & ex)
					{
						QMessageBox::warning(this, "Error", QString::fromStdString(ex.getMessage()));
						txtFisier->setText("");
						return;
					}
					
				else if (index == 1)
					try
				{
					srv.exporta_CVS(txtFisier->text().toStdString());
				}
				catch (CarteException & ex)
				{
					QMessageBox::warning(this, "Error", QString::fromStdString(ex.getMessage()));
					txtFisier->setText("");
					return;
				}

				txtFisier->setText("");
					
				

			});

		/*QObject::connect(listaCos, &QListWidget::itemSelectionChanged, [&]()
			{
				if (listaCos->selectedItems().isEmpty())
				{
					txtTitlu->setText("");
					txtAutor->setText("");
					txtGen->setText("");
					txtAn->setText("");
					return;
				}

				else
				{
					QListWidgetItem* select = listaCos->selectedItems().at(0);
					auto titlu = select->text();
					auto id = select->data(Qt::UserRole).toString();
					auto c=srv.find(std::stoi(id.toStdString()));

					txtTitlu->setText(titlu);
					txtAutor->setText(QString::fromStdString(c.get_autor()));
					txtGen->setText(QString::fromStdString(c.get_gen()));
					txtAn->setText(QString::number(c.get_an()));
				}
			});*/
	}

};