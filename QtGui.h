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
#include<QtWidgets/qtablewidget.h>

#include<vector>
#include<string>
#include"CosCRUDGUI.h"
#include"CosReadOnlyGui.h"
#include"Label.h"
#include"MyListModel.h"


class Gui:public QWidget,public Observer
{
public:
	Gui(Service& service):srv{service}
	{
		srv.addObserver(this);
		initGui();
		lst->setUniformItemSizes(true);
		updateData(srv.getAll());
		color();
		initConnect();
		addbtn(srv.getAll());
	}

private:
	Service& srv;
	QHBoxLayout* lyMain = new QHBoxLayout();

	const QString lineEditColor = "background-color: #e1b6fc;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold;";
	const QString buttonColor = "background-color: #a993e6;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold; ";
	const QString buttonColor2 = "background-color:#9584c4;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold;";

	QLineEdit* txtId = new QLineEdit;
	QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtAutor = new QLineEdit;
	QLineEdit* txtGen = new QLineEdit;
	QLineEdit* txtAn = new QLineEdit;

	QLineEdit* txtTitluCos = new QLineEdit;
	QLineEdit* txtAutorCos = new QLineEdit;
	QLineEdit* txtGenCos = new QLineEdit;
	QLineEdit* txtAnCos = new QLineEdit;
	QLineEdit* txtFisierCos = new QLineEdit;
	QLineEdit* txtNrCos = new QLineEdit;

	QPushButton* btnAdd = new QPushButton{ "&Adauga" };
	QPushButton* btnDelete = new QPushButton{ "&Sterge" };
	QPushButton* btnUpdate = new QPushButton{ "&Modifica" };
	QPushButton* btnFind = new QPushButton{ "&Cauta" };
	QPushButton* btnExit = new QPushButton{ "&Exit" };
	QPushButton* btnOk1 = new QPushButton("&Ok");
	QPushButton* btnOk2 = new QPushButton("&Ok");
	QPushButton* btnOk3 = new QPushButton("&Ok");

	QPushButton* btnAddCos = new QPushButton("&Adauga in cos");
	QPushButton* btnDeleteCos = new QPushButton("&Sterge cos");
	QPushButton* btnRandCos = new QPushButton("&Genereaza cos");
	QPushButton* btnUndoCos = new QPushButton("&Undo Stergere Cos");
	QPushButton* btnOkCos = new QPushButton("&Ok");

	QPushButton* btnCrud = new QPushButton{ "&CosCRUDGUI" };
	QPushButton* btnRead = new QPushButton{ "&CosReadOnlyGUI" };
	QPushButton* btnUndo = new QPushButton{ "&Undo" };
	
	QComboBox* LyFilter = new QComboBox();
	QComboBox* LySort = new QComboBox();
	QComboBox* LyStatistica = new QComboBox();
	QComboBox* LyExport = new QComboBox();

	QListView* lst = new QListView;
	MyListModel* model;
	//QListWidget* listaCos = new QListWidget;
	

	QWidget* tab1= new QWidget;
	QWidget* tab2 = new QWidget;
	QWidget* tab3 = new QWidget;

	QLineEdit* txtNr1 = new QLineEdit;
	QLineEdit* txtNr2 = new QLineEdit;
	QLineEdit* txtNr3 = new QLineEdit;

	QVBoxLayout* lySt = new QVBoxLayout;
	QVBoxLayout* lyDr = new QVBoxLayout;
	QFormLayout* lyNr = new QFormLayout;

	QVBoxLayout* ly = new QVBoxLayout;
	

	QWidget* Repobtns = new QWidget;
	QVBoxLayout* Repoly = new QVBoxLayout;
	vector<QPushButton*> btns;

	
	
	void initGui()
	{
		setLayout(lyMain);
		
		auto stgly = new QVBoxLayout;
		auto formLy = new QFormLayout;

		formLy->addRow("ID", txtId);
		formLy->addRow("TITLU", txtTitlu);
		formLy->addRow("AUTOR", txtAutor);
		formLy->addRow("GEN", txtGen);
		formLy->addRow("AN", txtAn);

		stgly->addLayout(formLy);

		auto LyBtn = new QHBoxLayout();
		LyBtn->addWidget(btnAdd);
		LyBtn->addWidget(btnDelete);
		LyBtn->addWidget(btnUpdate);
		LyBtn->addWidget(btnFind);

		stgly->addLayout(LyBtn);
		stgly->addWidget(btnUndo);

		QHBoxLayout* lyBtnCos = new QHBoxLayout();
		lyBtnCos->addWidget(btnAddCos);
		lyBtnCos->addWidget(btnDeleteCos);
		lyBtnCos->addWidget(btnRandCos);

		stgly->addLayout(lyBtnCos);
		stgly->addWidget(btnUndoCos);


		QHBoxLayout* lyCos = new QHBoxLayout();
		lyCos->addWidget(btnCrud);
		lyCos->addWidget(btnRead);

		stgly->addLayout(lyCos);

		//auto LyUndo = new QGridLayout();
		//LyUndo->addWidget(btnCos);
		//LyUndo->addWidget(btnUndo);
		//LyUndo->addWidget(btnExit);
	
		//stgly->addLayout(LyUndo);

		lyMain->addLayout(stgly);

		auto drly = new QVBoxLayout;
		drly->addWidget(lst);

		auto hly = new QHBoxLayout;

	
		LySort->insertItem(0,"Sorteaza autor");
		LySort->insertItem(1,"Sorteaza titlu");
		LySort->insertItem(2,"Sorteaza an+gen");

		LyFilter->insertItem(0,"Filtreaza an");
		LyFilter->insertItem(1,"Filtreaza titlu");
		


		LyStatistica->insertItem(0, "Statistica gen");
		LyStatistica->insertItem(1, "Statistica an");


		hly->addWidget(LyFilter);
		hly->addWidget(LySort);
		hly->addWidget(LyStatistica);

		drly->addLayout(hly);
		lyMain->addLayout(drly);

		QFormLayout* stat = new QFormLayout;
		stat->addRow("De la:", txtNr1);
		stat->addRow("Pana la:", txtNr2);
		stat->addWidget(btnOk2);
		tab2->setLayout(stat);

		QFormLayout* generare = new QFormLayout;
		generare->addRow("Nr:", txtNr3);
		generare->addWidget(btnOk3);
		tab3->setLayout(generare);

		Repobtns->setLayout(Repoly);
		lyMain->addWidget(Repobtns);
	}

	void clean()
	{
		txtId->setText("");
		txtTitlu->setText("");
		txtAutor->setText("");
		txtGen->setText("");
		txtAn->setText("");
	}

	void update() override

	{
		updateData(srv.getAll());
	}

	void color()
	{

			this->setStyleSheet("background-color: #d6cbf5;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold;");

			btnAdd->setStyleSheet(buttonColor);
			btnDelete->setStyleSheet(buttonColor);
			btnFind->setStyleSheet(buttonColor);
			btnUpdate->setStyleSheet(buttonColor);
	
			//btnCos->setStyleSheet(buttonColor2);
			btnUndo->setStyleSheet(buttonColor);
			btnExit->setStyleSheet(buttonColor);

			btnOk1->setStyleSheet(buttonColor);
			btnOk2->setStyleSheet(buttonColor);
			btnOk3->setStyleSheet(buttonColor);
					
			txtId->setStyleSheet(lineEditColor);
			txtTitlu->setStyleSheet(lineEditColor);
			txtAutor->setStyleSheet(lineEditColor);
			txtGen->setStyleSheet(lineEditColor);
			txtAn->setStyleSheet(lineEditColor);

			tab1->setStyleSheet("background-color: #d6cbf5;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold;");
			tab2->setStyleSheet("background-color: #d6cbf5;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold;");
			tab3->setStyleSheet("background-color: #d6cbf5;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold;");

			txtNr1->setStyleSheet(lineEditColor);
			txtNr2->setStyleSheet(lineEditColor);
			txtNr3->setStyleSheet(lineEditColor);


			//Cos

			btnAddCos->setStyleSheet(buttonColor2);
			btnDeleteCos->setStyleSheet(buttonColor2);
			btnRandCos->setStyleSheet(buttonColor2);
			btnUndoCos->setStyleSheet(buttonColor2);
			btnOkCos->setStyleSheet(buttonColor2);
			btnCrud->setStyleSheet(buttonColor2);
			btnRead->setStyleSheet(buttonColor2);

			txtAnCos->setStyleSheet(lineEditColor);
			txtTitluCos->setStyleSheet(lineEditColor);
			txtAutorCos->setStyleSheet(lineEditColor);
			txtGenCos->setStyleSheet(lineEditColor);
			txtFisierCos->setStyleSheet(lineEditColor);
			txtNrCos->setStyleSheet(lineEditColor);

			LyExport->setStyleSheet(buttonColor);

		

	}
	
	//void loadData()
	//{
	//	lst->clear();
	//	vector<Carte> carti = srv.getAll();
	//	for (const auto& c : carti)
	//	{
	//		QListWidgetItem* item = new QListWidgetItem(QString::number(c.get_id()), lst);			//lst->addItem(QString::number(c.get_id()));
	//		item->setData(Qt::UserRole, QString::fromStdString(c.get_titlu()));
	//		//item->setBackground(QBrush{Qt::red, Qt::SolidPattern});
	//	}
	//}

	void addbtn(vector<Carte>carti)
	{
		while (btns.size() > 0)
		{
			auto btn = btns.back();
			delete btn;
			btns.pop_back();
		}
			
		
		for (const auto& c : carti)
		{
			auto btn = new QPushButton{ QString::number(c.get_id()) };
			btns.push_back(btn);
			btn->setStyleSheet(buttonColor);
		}
		for (const auto& btn: btns)
		{
			Repoly->addWidget(btn);
			QObject::connect(btn, &QPushButton::clicked, [this,btn]()
				{
					try
					{
						srv.sterge(std::stoi(btn->text().toStdString()));
					}
					catch (RepoException & ex)
					{
						QMessageBox::warning(this, "Error", QString::fromStdString(ex.getMessage()));
						return;
					}
					delete btn;
					updateData(srv.getAll());
				});
		}
	}

	void updateData(vector<Carte> carti)
	{
		model = new MyListModel(srv.getAll());
		lst->setModel(model);
	}

	void initConnect()
	{
		
		QObject::connect(btnExit, &QPushButton::clicked, [&]() {
			QMessageBox::information(nullptr, "Biblioteca", "Exit!");
			close();
			});

		QObject::connect(btnAdd, &QPushButton::clicked, [&]() {

			std::string titlu = txtTitlu->text().toStdString();
			std::string  autor = txtAutor->text().toStdString();
			std::string gen = txtGen->text().toStdString();
			int id, an;
			try
			{
				id = std::stoi(txtId->text().toStdString());
			}
			catch (const std::invalid_argument)
			{
				QMessageBox::warning(this, "Error", "Id invalid!");
				clean();
				return;
			}
			try
			{
				an = std::stoi(txtAn->text().toStdString());
			}
			catch (const std::invalid_argument)
			{
				QMessageBox::warning(this, "Error", "An invalid!");
				clean();
				return;
			}

			try {
				srv.add(id, titlu, autor, gen, an);
				updateData(srv.getAll());
				addbtn(srv.getAll());
			}

			catch (RepoException & ex)
			{
				QMessageBox::warning(this, "Error", QString::fromStdString(ex.getMessage()));
				clean();
				return;
			}

			catch (ValidareException & ex)
			{
				QMessageBox::warning(this, "Error", QString::fromStdString(ex.getMessage()));
				clean();
				return;
			}

			clean();



			});

		QObject::connect(btnDelete, &QPushButton::clicked, [&]() {

			int id;
			try
			{
				id = std::stoi(txtId->text().toStdString());
			}
			catch (const std::invalid_argument)
			{
				QMessageBox::warning(this, "Error", "Id invalid!");
				clean();
				return;
			}

			try
			{
				srv.sterge(id);
				updateData(srv.getAll());
				addbtn(srv.getAll());
			}
			catch (RepoException & ex)
			{
				QMessageBox::warning(this, "Error", QString::fromStdString(ex.getMessage()));
				clean();
				return;
			}

			clean();

			});
		QObject::connect(btnUpdate, &QPushButton::clicked, [&]() {

			std::string titlu = txtTitlu->text().toStdString();
			std::string  autor = txtAutor->text().toStdString();
			std::string gen = txtGen->text().toStdString();
			int id, an;
			try
			{
				id = std::stoi(txtId->text().toStdString());
			}
			catch (const std::invalid_argument)
			{
				QMessageBox::warning(this, "Error", "Id invalid!");
				clean();
				return;
			}
			try
			{
				an = std::stoi(txtAn->text().toStdString());
			}
			catch (const std::invalid_argument)
			{
				QMessageBox::warning(this, "Error", "An invalid!");
				clean();
				return;
			}

			try {
				srv.update(id, titlu, autor, gen, an);
				updateData(srv.getAll());
				addbtn(srv.getAll());
			}

			catch (RepoException & ex)
			{
				QMessageBox::warning(this, "Error", QString::fromStdString(ex.getMessage()));
				clean();
				return;
			}

			catch (ValidareException & ex)
			{
				QMessageBox::warning(this, "Error", "Invalid ");
				clean();
				return;
			}

			clean();

			});

		QObject::connect(btnFind, &QPushButton::clicked, [&]() {

			int id;
			try
			{
				id = std::stoi(txtId->text().toStdString());
			}
			catch (const std::invalid_argument)
			{
				QMessageBox::warning(this, "Error", "Id invalid!");
				clean();
				return;
			}
			try
			{
				Carte c = srv.find(id);
				QMessageBox::information(nullptr, "Info", QString::fromStdString(c.get_titlu()));
			}
			catch (RepoException & ex)
			{
				QMessageBox::warning(this, "Error", QString::fromStdString(ex.getMessage()));
				clean();
				return;
			}

			clean();

			});



		QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
			try
			{
				srv.undo();
				updateData(srv.getAll());
				addbtn(srv.getAll());
			}
			catch (CarteException & ex)
			{
				QMessageBox::warning(this, "Error", QString::fromStdString(ex.getMessage()));
				return;
			}
			});

		/*QObject::connect(btnCos, &QPushButton::clicked, [&]() {

			auto cos = new CosQt(srv);
			cos->show();

			});*/



		QObject::connect(LyFilter, QOverload<int>::of(&QComboBox::activated), [=](int index)
			{
				if (index == 0)
				{
					updateData(srv.getAll());
					try
					{
						int an = std::stoi(txtAn->text().toStdString());
						updateData(srv.filtrare_an(an));
					}
					catch (const std::invalid_argument)
					{

						QMessageBox::warning(this, "Error", "An invalid");
						clean();
						return;
					}

					clean();
				}
				else if (index == 1)
				{
					updateData(srv.getAll());;
					std::string titlu = txtTitlu->text().toStdString();
					updateData(srv.filtrare_titlu(titlu));
					clean();
				}


			});


		QObject::connect(LySort, QOverload<int>::of(&QComboBox::activated), [=](int index)
			{
				if (index == 0)
				{
					updateData(srv.sorteaza_autor());
					addbtn(srv.sorteaza_autor());
				}
				else if (index == 1)
				{
					updateData(srv.sorteaza_titlu());
					addbtn(srv.sorteaza_titlu());
				}
					
				else if (index == 2)
				{
					updateData(srv.sorteaza_an_gen());
					addbtn(srv.sorteaza_an_gen());
				}
					

			});
		QObject::connect(LyStatistica, QOverload<int>::of(&QComboBox::activated), [=](int index)
			{
				if (index == 0)
				{
					auto label = new Label{ srv };
					label->show();

					
				}
				else if (index == 1)
				{

					tab2->show();
				}

			});
		QObject::connect(btnOk2, &QPushButton::clicked, [&]()
			{
				int nr1, nr2;
				try
				{
					nr1 = std::stoi(txtNr1->text().toStdString());
					nr2 = std::stoi(txtNr2->text().toStdString());
				}
				catch (const std::invalid_argument)
				{
					QMessageBox::warning(this, "Error", "Nr invalid!");
					txtNr1->setText("");
					txtNr2->setText("");
					return;
				}

				int nr = srv.statistica_an(nr1, nr2);
				QMessageBox::information(nullptr, "Numar carti", QString::number(nr));
				txtNr1->setText("");
				txtNr2->setText("");
				tab2->close();


			});
		QObject::connect(btnOk1, &QPushButton::clicked, [&]()
			{
				tab1->close();

			});
	
		
	


		/*QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {

			if (lst->selectedItems().isEmpty())
			{
				clean();
				return;
			}

			else {


				QListWidgetItem* selectItem = lst->selectedItems().at(0);
				auto ID = selectItem->text();
				auto Titlu = selectItem->data(Qt::UserRole).toString();
				txtId->setText(ID);
				txtTitlu->setText(Titlu);
				auto c = srv.find(std::stoi(ID.toStdString()));
				txtAutor->setText(QString::fromStdString(c.get_autor()));
				txtGen->setText(QString::fromStdString(c.get_gen()));
				txtAn->setText(QString::number(c.get_an()));
				
			}
			});*/

		QObject::connect(lst->selectionModel(), &QItemSelectionModel::selectionChanged, [&]()
			{
				if (lst->selectionModel()->selectedIndexes().isEmpty())
				{
					clean();
					return;
				}

				auto selIndex = lst->selectionModel()->selectedIndexes().at(0);
				auto id = selIndex.data(Qt::DisplayRole).toString();
				txtId->setText(id);
				Carte c = srv.find(std::stoi(id.toStdString()));
				txtAutor->setText(QString::fromStdString(c.get_autor()));
				txtTitlu->setText(QString::fromStdString(c.get_titlu()));
				txtGen->setText(QString::fromStdString(c.get_gen()));
				txtAn->setText(QString::number(c.get_an()));

			});

		//COS
		QObject::connect(btnAddCos, &QPushButton::clicked, [&]()
			{
				srv.adaugaCos(txtTitlu->text().toStdString());
				
			});

		QObject::connect(btnDeleteCos, &QPushButton::clicked, [&]()
			{
				srv.stergeCos();
				
			});


		QObject::connect(btnUndoCos, &QPushButton::clicked, [&]()
			{
				try
				{
					srv.undo();
				
				}
				catch (CarteException & ex)
				{
					QMessageBox::warning(this, "Error", QString::fromStdString(ex.getMessage()));
					return;
				}
			});

		QObject::connect(btnRandCos, &QPushButton::clicked, [&]() {

			tab3->show();
			});

		QObject::connect(btnOk3, &QPushButton::clicked, [&]()
			{
				int nr;
				try
				{
					nr = std::stoi(txtNr3->text().toStdString());
				}
				catch (const std::invalid_argument)
				{
					QMessageBox::warning(this, "Error", "Nr invalid!");
					return;
				}
				try
				{
					srv.genereazaCos(nr);
					tab3->close();
					

				}
				catch (CosException & ex)
				{
					QMessageBox::warning(this, "Error", QString::fromStdString(ex.getMessage()));
					return;
				}
			});

		QObject::connect(btnCrud, &QPushButton::clicked, [&]() {
				
			auto cos = new CosCRUD(srv);
			cos->show();
			

			});

		QObject::connect(btnRead, &QPushButton::clicked, [&]() {

			auto cos = new CosRead(srv);
			cos->show();


			});

		

		/*QObject::connect(listaCos, &QListWidget::itemSelectionChanged, [&]()
			{
				if (listaCos->selectedItems().isEmpty())
				{
					txtTitluCos->setText("");
					txtAutorCos->setText("");
					txtGenCos->setText("");
					txtAnCos->setText("");
					return;
				}

				else
				{
					QListWidgetItem* select = listaCos->selectedItems().at(0);
					auto titlu = select->text();
					auto id = select->data(Qt::UserRole).toString();
					auto c = srv.find(std::stoi(id.toStdString()));

					txtTitluCos->setText(titlu);
					txtAutorCos->setText(QString::fromStdString(c.get_autor()));
					txtGenCos->setText(QString::fromStdString(c.get_gen()));
					txtAnCos->setText(QString::number(c.get_an()));
				}
			});*/
	
	}


};

