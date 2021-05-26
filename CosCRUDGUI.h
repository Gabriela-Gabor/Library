#pragma once
#include<QtWidgets/qwidget.h>
#include<QtWidgets/qboxlayout.h>
#include<QtWidgets/qformlayout.h>
#include<QtWidgets/qlistwidget.h>
#include<QtWidgets/qlabel.h>
#include<QtWidgets/qlineedit.h>
#include<QtWidgets/qpushbutton.h>
#include<QtWidgets/qmessagebox.h>


class CosCRUD :public QWidget, public Observer
{
public:
	CosCRUD(Service& serv) :srv{ serv }
	{
		srv.addObserver(this);
		initCos();
		loadCos();
		color();
		initConnect();
	}
private:

	Service& srv;
	
	QHBoxLayout* lyMain = new QHBoxLayout();
	QVBoxLayout* lySt = new QVBoxLayout;
	QVBoxLayout* lyDr = new QVBoxLayout;
	

	QPushButton* btnDelete = new QPushButton("&Sterge");
	QPushButton* btnRand = new QPushButton("&Genereaza");

	QListWidget* listaCos = new QListWidget;

	QLineEdit* txtFisier = new QLineEdit;
	QLineEdit* txtNr = new QLineEdit;

	QComboBox* LyExport = new QComboBox();

	void update() override
	{
		loadCos();
	}

	void initCos()
	{
		setLayout(lyMain);
		this->setStyleSheet("background-color: #d6cbf5;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold;");

		lySt->addWidget(listaCos);

		lyMain->addLayout(lySt);

		QFormLayout* form = new QFormLayout;
		form->addRow("Fisier: ", txtFisier);
		form->addRow("Numar: ", txtNr);

		lyDr->addLayout(form);

		LyExport->insertItem(0, "Exporta html");
		LyExport->insertItem(1, "Exporta CVS");

		lyDr->addWidget(LyExport);


		QHBoxLayout* lyBtn = new QHBoxLayout();
		lyBtn->addWidget(btnDelete);
		lyBtn->addWidget(btnRand);

		lyDr->addLayout(lyBtn);

		lyMain->addLayout(lyDr);



	}
	void loadCos()
	{
		listaCos->clear();
		vector<Carte> carti = srv.Cos();
		for (const auto& c : carti)
		{
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(c.get_titlu()), listaCos);
		//	item->setData(Qt::UserRole, QString::number(c.get_id()));

		}
	}

	void color()
	{
		const QString ButtonColor = "background-color:#6c5d94;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold;";
		const QString LineEditColor = "background-color: #e1b6fc;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold;";

		this->setStyleSheet("background-color: #d6cbf5;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold;");


		btnDelete->setStyleSheet(ButtonColor);
		btnRand->setStyleSheet(ButtonColor);

		txtFisier->setStyleSheet(LineEditColor);
		txtNr->setStyleSheet(LineEditColor);

		LyExport->setStyleSheet(ButtonColor);

	}

	void initConnect()
	{
		
		QObject::connect(btnDelete, &QPushButton::clicked, [&]()
			{
				srv.stergeCos();
				loadCos();
				
			});

		QObject::connect(btnRand, &QPushButton::clicked, [&]()
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
				    loadCos();
					txtNr->setText("");
		

				}
				catch (CosException & ex)
				{
					QMessageBox::warning(this, "Error", QString::fromStdString(ex.getMessage()));
					txtNr->setText("");
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
	}

};