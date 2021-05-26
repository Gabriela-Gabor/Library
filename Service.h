#pragma once
#include"Carte.h"
#include"Validare.h"
#include"Repository.h"
#include"Cos.h"
#include"FileRepository.h"
#include"Undo.h"

#include<functional>
#include<map>
#include<string>

using std::string;
using std::function;
using std::map;
using std::unique_ptr;


class Service :public Observable
{
private:

	IRepo& rep;
	Validator& valid;
	Cosul& cos;
	std::vector<unique_ptr<ActiuneUndo>> undoActions;

	/*
	Functia generala de filtrare
	fct- poate fi o funcitte
	fct- poate fi lambda, am folosit  function<> pentru a permite si functii lambda care au ceva in capture list
	returneaza doar cartile care trec de filtrul (fct(carte ==true)
	*/
	vector<Carte> filtreaza(function<bool(const Carte&)>fct);

	/*
		Functia generala de sortare
		maiMic - functie care compara doua carti,verifica daca are loc relatia mai mic
			   - poate fi orice funcite ( in afara clasei)  care respecta signatura ( are 2 parametii Carte si returneaza bool)
			   - poate fi functie lambda ( care nu capteaza nimic in capture-list)
	*/
	vector<Carte> sorteaza(bool (*maiMic)(const Carte&, const Carte&));

public:
	Service(IRepo& rep, Validator& v, Cosul& cos) noexcept :rep{ rep }, valid{ v }, cos{ cos }
	{

	}

	Service() = default;

	//pentru a nu permite copierea de obiecte
	Service(const Service& ot) = delete;

	/*
		Creeaza o carte cu caracteristicile primite ca parametru si incearca sa o salveze
		Arunca exceptie daca cartea exista deja ( daca mai este o carte cu acelasi id)
	*/
	void add(int id, string titlu, string autor, string gen, int an);

	/*
		Sterge cartea cu id primit
		Arunca exceptie daca cartea nu exista o carte cu acel id
	*/
	void sterge(int id);

	/*
		Creeaza o carte cu caracteristicile primite ca parametru si incearca sa modifice cartea care are acelasi id
		Arunca exceptie daca cartea nu exista
	*/
	void update(int id, string titlu, string autor, string gen, int an);

	/*
		Cauta cartea care are id primit ca parametru
		Arunca exceptie daca cartea nu exista
	*/
	const Carte& find(int id);

	/*
		Returneaza cartile salvate
	*/
	vector<Carte> getAll();

	/*
		Filtreaza dupa an
		Returneaza lista cartilor filtrate (care au aparut dupa anul primit ca parametru)
	*/
	vector<Carte> filtrare_an(int an);

	/*
		Filtreaza dupa titlu
		Returneaza lista cartilor filtrate (care contin in titlu stringul primit ca parametru)
	*/
	vector<Carte> filtrare_titlu(string titlu);

	/*
		Sorteaza dupa titlu ( in ordine alfabetica)
		Returneaza lista cartilor sortate
	*/
	vector<Carte> sorteaza_titlu();

	/*
		Sorteaza dupa autor ( in ordine alfabetica)
		Returneaza lista cartilor sortate
	*/
	vector<Carte> sorteaza_autor();

	/*
		Sorteaza dupa an + gen ( ordoneaza cronologic cartile, iar daca sunt carti care au acelasi an le sorteaza dupa gen)
		Returneaza lista cartilor sortate
	*/
	vector<Carte> sorteaza_an_gen();

	/*
		Face o statistica dupa genuri, adica in ce procent se gaseste un gen de carte intre celelalte
	*/
	vector<DTO> statistica();

	/*
		Returneaza numarul de carti cuprinse intre an1 si an2
	*/
	int statistica_an(int an1, int an2);

	/*
		Pimeste ca parametru un titlu si adauga in cos cartile cu titlul respectiv
	*/
	void adaugaCos(string titlu);

	/*
		Sterge cosul
	*/
	void stergeCos();

	/*
		Genereaza random un cos cu un nr de carti ( nr transmim ca parametru iar cartile sunt din stocul de carti)
	*/
	void genereazaCos(int nr);

	/*
			Returneaza lista de carti din cos
	*/
	vector<Carte> Cos();

	/*
		Exporta continutul cosului intr-un fisier CVS
	*/
	void exporta_CVS(const string& nume_fisier);

	/*
		Exporta continutul cosului intr-un fisier HTML
	*/
	void exporta_HTML(const string& nume_fisier);

	/*
		Undo pentru adauga , sterge , modifica
	*/
	void undo();


};

