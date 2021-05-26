#pragma once
#include<vector>
#include<map>
#include"Carte.h"
using std::vector;
using std::map;

class RepoException
{
	string mesaj;

public:

	RepoException(string m) :mesaj{ m }
	{

	}
	string getMessage()
	{
		return mesaj;
	}
};

class IRepo
{

public:

	virtual ~IRepo() = default;

	virtual void store(const Carte& carte) = 0;
	virtual void sterge(int id) = 0;
	virtual void update(const Carte& carte) = 0;
	virtual vector<Carte> getAll() = 0;
	virtual Carte& find(int id) = 0;


};

class Repo : public IRepo
{
private:

	map<int, Carte> carti;
	vector<Carte> cos;
	float nr = 0;

public:
	Repo(float rata) :nr{ rata } {};
	Repo() = default;
	virtual ~Repo() = default;

	//nu permite copierea de obiecte
	Repo(const Repo& ot) = delete;

	/*
		Salvare carte in lista de carti
		Arunca exceptie daca mai exista o carte cu acelasi id
	*/
	virtual void store(const Carte& carte) override;

	/*
		Sterge o carte din lista
		Arunca exceptie daca cartea nu este gasita (nu exista o carte cu id primit ca parametru)
	*/
	virtual void sterge(int id) override;

	/*
		Modifica cartea ( ii modifica titlul , autorul, genul si anul cu cel ale cartii primite ca parametru)
		Arunca excepite daca cartea nu este gasita (nu exista o carte cu id ca al cartii primite ca parametru)
	*/
	virtual void update(const Carte& carte) override;

	/*
		Cauta o carte in lista
		Arunca exceptie daca cartea nu este gasita
	*/
	Carte& find(int id) override;

	/*
		Returneaza toate cartile salvate
	*/
	vector<Carte> getAll() override;





};




