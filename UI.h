#pragma once
#include"Service.h"
#include"Teste.h"

class UI
{
	Service& serv;

	/*
		Citeste comanda. Incearca sa citeasca un numar iar daca utilizatorul introduce altceva
		va semnala prin mesajul "Comanda invalida"
	*/
	int citeste_comada();

	/*
	Citeste datele de la tastatura si incearca salvarea cartii
	Afiseaza mesajul - "Cartea exista deja" daca cartea nu poate fi salvata
					 - "Carte adaugata" daca cartea s-a salvat
	*/
	void adaugaUI();

	/*
		Citeste de la id-ul cartii pe care dorim sa o stergem
		Afiseaza mesajul - "Cartea nu este gasita " daca cartea nu poate fi stearsa
						 - "Carte stearsa" daca cartea s-a sters
	*/
	void stergeUI();

	/*
	Citeste datele de la tastatura si incearca modificarea cartii
	Afiseaza mesajul - "Cartea nu este gasita" daca cartea nu poate fi modificata
					 - "Carte modificata" daca cartea s-a modificat
	*/
	void updateUI();

	/*
		Citeste de la tastatura id-ul cartii pe care dorim sa o cautam
		Afiseaza mesajul - "Cartea nu este gasita " daca cartea nu exista
						 - "Cartea cautata: " si afiseaza cartea cautata de noi
	*/
	void cautaUI();

	/*
		Citeste un an
		Afiseaza lista de carti filtrata dupa anul citit
	*/
	void filtreaza_anUI();

	/*
		Citeste un titlu
		Afiseaza lista de carti filtrata dupa titlu
	*/
	void filtreaza_titluUI();

	/*
		Afiseaza lista de carti sortata dupa titlu
	*/
	void sorteaza_titluUI();

	/*
		Afiseaza lista de carti sortata dupa autor
	*/
	void sorteaza_autorUI();

	/*
		Afiseaza lista de carti sortata dupa an + gen
	*/
	void sorteaza_anGenUI();

	/*
		Afiseaza lista cartilor salvate
	*/
	void tipareste(const vector<Carte>& carti);

	/*
		Afiseaza procentele genurilor
	*/
	void statisticaUI();

	/*
		Citeste de la tastaura un titlu si se adauga in cos cartile din stoc cu titlul respectiv
	*/
	void adaugaCosUI();

	/*
		Sterge cosul
	*/
	void stergeCosUI() noexcept;

	/*
		Se citeste un nr si se genereaza un cos cu nr respectiv de carti daca sunt atatea in stoc, daca nu arunca exceptie
	*/
	void genereazaCosUI();

	/*
		Afiseaza cartile din cos
	*/
	void tiparesteCosUI();

public:
	UI(Service& serv) noexcept :serv{ serv }
	{

	}
	void startUI();

};
