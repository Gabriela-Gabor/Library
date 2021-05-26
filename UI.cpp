//#pragma once
//#include"UI.h"
//#include<iostream>
//
//using std::cin;
//using std::cout;
//
//void UI::adaugaUI()
//{
//	string titlu, autor, gen;
//	string primeste_id, primeste_an;;
//	int an = 0, id;
//	cout << "ID: ";
//	cin >> primeste_id;
//	try
//	{
//		id = stoi(primeste_id);
//	}
//	catch (const std::invalid_argument) {
//		cout << "ID invalid! \n";
//		return;
//	}
//
//	cout << "Titlu: ";
//	cin >> titlu;
//	cout << "Autor: ";
//	cin >> autor;
//	cout << "Gen: ";
//	cin >> gen;
//	cout << "An: ";
//	cin >> primeste_an;
//	try
//	{
//		an = stoi(primeste_an);
//	}
//	catch (const std::invalid_argument) {
//		cout << "AN invalid! \n";
//		return;
//	}
//	try
//	{
//		serv.add(id, titlu, autor, gen, an);
//		cout << "Carte adaugata\n";
//	}
//
//	catch (RepoException & ex)
//	{
//		cout << ex.getMessage();
//	}
//
//	catch (const ValidareException & ex)
//	{
//		cout << ex;
//	
//	}
//}
//
//void UI::stergeUI()
//{
//	string primeste_id;
//	int id;
//	cout << "ID: ";
//	cin >> primeste_id;
//	try
//	{
//		id = stoi(primeste_id);
//	}
//	catch (const std::invalid_argument) {
//		cout << "ID invalid! \n";
//		return;
//	}
//	try
//	{
//		serv.sterge(id);
//		cout << "Carte stearsa\n";
//	}
//
//	catch (RepoException & ex)
//	{
//		cout << ex.getMessage();
//	}
//}
//
//void UI::updateUI()
//{
//	string titlu, autor, gen;
//	string primeste_id, primeste_an;
//	int an = 0, id;
//	cout << "ID: ";
//	cin >> primeste_id;
//	try
//	{
//		id = stoi(primeste_id);
//	}
//	catch (const std::invalid_argument) {
//		cout << "ID invalid! \n";
//		return;
//	}
//	cout << "Titlu: ";
//	cin >> titlu;
//	cout << "Autor: ";
//	cin >> autor;
//	cout << "Gen: ";
//	cin >> gen;
//	cout << "An: ";
//	cin >> primeste_an;
//	try
//	{
//		an = stoi(primeste_an);
//	}
//	catch (const std::invalid_argument) {
//		cout << "AN invalid! \n";
//		return;
//	}
//	try
//	{
//		serv.update(id, titlu, autor, gen, an);
//		cout << "Carte modificata\n";
//	}
//
//	catch (RepoException & ex)
//	{
//		cout << ex.getMessage();
//	}
//	catch (const ValidareException & ex)
//	{
//		cout << ex;
//	}
//}
//
//void UI::cautaUI()
//{
//	int id;
//	string primeste_id;
//	cout << "ID: ";
//	cin >> primeste_id;
//	try
//	{
//		id = stoi(primeste_id);
//	}
//	catch (const std::invalid_argument) {
//		cout << "ID invalid! \n";
//		return;
//	}
//	try
//	{
//		Carte carte = serv.find(id);
//		cout << "Cartea cautata: " << carte.get_id() << ' ' << carte.get_titlu() << ' ' << carte.get_autor() << ' ' << carte.get_gen() << ' ' << carte.get_an() << '\n';
//	}
//	catch (RepoException & ex)
//	{
//		cout << ex.getMessage();
//	}
//}
//
//void UI::filtreaza_anUI()
//{
//	string primeste_an;
//	int an;
//	cout << "Cartile aparute dupa anul: ";
//	cin >> primeste_an;
//	try
//	{
//		an = stoi(primeste_an);
//	}
//	catch (const std::invalid_argument) {
//		cout << "ID invalid! \n";
//		return;
//	}
//	tipareste(serv.filtrare_an(an));
//
//}
//
//void UI::filtreaza_titluUI()
//{
//	string titlu;
//	cout << "Cartile care contin in titlu: ";
//	cin >> titlu;
//	tipareste(serv.filtrare_titlu(titlu));
//
//}
//void UI::sorteaza_titluUI()
//{
//	cout << "Cartile sortate dupa titlu: \n";
//	tipareste(serv.sorteaza_titlu());
//
//}
//
//void UI::sorteaza_autorUI()
//{
//	cout << "Cartile sortate dupa autor:\n ";
//	tipareste(serv.sorteaza_autor());
//
//}
//
//void UI::sorteaza_anGenUI()
//{
//	cout << "Cartile sortate dupa an + gen :\n ";
//	tipareste(serv.sorteaza_an_gen());
//
//}
//
//void UI::statisticaUI()
//{
//	vector<DTO> stat = this->serv.statistica();
//	for (auto v : stat)
//		cout << "Genul " << v.get_gen() << "  " << v.get_procent() << "% \n";
//}
//
//void UI::adaugaCosUI()
//{
//	string titlu;
//	cout << "Introduceti titlul: \n";
//	cin >> titlu;
//	serv.adaugaCos(titlu);
//}
//
//void UI::stergeCosUI() noexcept
//{
//	serv.stergeCos();
//}
//
//void UI::genereazaCosUI()
//{
//	cout << "Introduceti numarul: \n";
//	string primeste_nr;
//	int nr;
//	cin >> primeste_nr;
//	try
//	{
//		nr = stoi(primeste_nr);
//	}
//	catch (const std::invalid_argument) {
//		cout << "ID invalid! \n";
//		return;
//	}
//	try
//	{
//		serv.genereazaCos(nr);
//	}
//	catch (CosException & ex)
//	{
//		cout << ex.getMessage() << '\n';
//	}
//}
//
//void UI::tiparesteCosUI()
//{
//	tipareste(serv.Cos());
//
//}
//
//
//void UI::tipareste(const vector<Carte>& carti)
//{
//	cout << "Lista carti: \n";
//	for (const auto& carte : carti)
//		cout << carte.get_id() << ' ' << carte.get_titlu() << ' ' << carte.get_autor() << ' ' << carte.get_gen() << ' ' << carte.get_an() << '\n';
//}
//
//int UI::citeste_comada()
//{
//	string primeste_cmd;
//	int cmd;
//	cin >> primeste_cmd;
//	try
//	{
//		cmd = stoi(primeste_cmd);
//	}
//	catch (const std::invalid_argument) {
//		cout << "Comanda invalida! \n";
//		return -1;
//	}
//
//	return cmd;
//}
//
//
//void UI::startUI()
//{
//
//	while (true)
//	{
//		cout << "LISTA COMENZI:\n1 -> Add\n2 -> Print\n3-> Delete\n4 -> Update\n5 -> Find\n6 -> Filtrare\n7 -> Sort\n8 -> Statistica\n9 -> Undo\n10 -> Adauga in cos\n11 -> Sterge cosul\n12 -> Genereaza random cosul\n13 -> Afiseaza cosul\n14 -> Exporta cos\n15 ->  Nr carti cuprinse intre:\n0 -> Exit\nCommand: ";
//		const int cmd = citeste_comada();
//		if (cmd == 0)
//			break;
//		if (cmd == 1)
//			adaugaUI();
//		if (cmd == 2)
//			tipareste(serv.getAll());
//		if (cmd == 3)
//			stergeUI();
//		if (cmd == 4)
//			updateUI();
//		if (cmd == 5)
//			cautaUI();
//		if (cmd == 6)
//		{
//			cout << "		i. Dupa an\n		ii. Dupa titlu\n";
//			string alege;
//			cin >> alege;
//			if (alege == "i")
//				filtreaza_anUI();
//			if (alege == "ii")
//				filtreaza_titluUI();
//		}
//		if (cmd == 7)
//		{
//			cout << "		i. Dupa titlu\n		ii. Dupa autor\n		iii.Dupa an + gen\n";
//			string alege;
//			cin >> alege;
//			if (alege == "i")
//				sorteaza_titluUI();
//			if (alege == "ii")
//				sorteaza_autorUI();
//			if (alege == "iii")
//				sorteaza_anGenUI();
//		}
//
//		if (cmd == 8)
//		{
//			statisticaUI();
//		}
//		if (cmd == 9)
//		{
//			try {
//				serv.undo();
//			}
//			catch (CarteException & ex)
//			{
//				cout << ex.getMessage() << '\n';
//			}
//
//			cout << "COS\n";
//			tipareste(serv.Cos());
//			cout << "CARTI\n";
//			tipareste(serv.getAll());
//		}
//
//		if (cmd == 10)
//		{
//			adaugaCosUI();
//			cout << "Nr carti cos: " << serv.Cos().size() << '\n';
//		}
//		if (cmd == 11)
//		{
//			stergeCosUI();
//			cout << "Nr carti cos: " << serv.Cos().size() << '\n';
//		}
//		if (cmd == 12)
//		{
//			genereazaCosUI();
//			cout << "Nr carti cos: " << serv.Cos().size() << '\n';
//		}
//		if (cmd == 13)
//		{
//			tiparesteCosUI();
//		}
//		if (cmd == 14)
//		{
//			cout << "i. fisier CVS			ii. fisier HTML\n";
//			string alege;
//			cin >> alege;
//			string nume_fisier;
//			cout << "Nume fisier:  ";
//			cin >> nume_fisier;
//			if (alege == "i")
//			{
//				try {
//					serv.exporta_CVS(nume_fisier);
//				}
//				catch (CarteException & ex)
//				{
//					cout << ex.getMessage() << '\n';
//				}
//			}
//			if (alege == "ii")
//			{
//				try {
//					serv.exporta_HTML(nume_fisier);
//				}
//				catch (CarteException & ex)
//				{
//					cout << ex.getMessage() << '\n';
//				}
//			}
//
//
//
//		}
//		if (cmd == 15)
//		{
//			int an1, an2;
//			cout << " anul: \n";
//			cin >> an1;
//			cout << " si  anul : \n";
//			cin >> an2;
//			cout << serv.statistica_an(an1, an2) << '\n';
//		}
//
//
//
//	}
//}
