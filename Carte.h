#pragma once
#pragma once
#include<string>
using std::string;

class CarteException
{
	string mesaj;

public:

	CarteException(string m) :mesaj{ m }
	{

	}
	string getMessage()
	{
		return mesaj;
	}
};


class Carte
{
private:

	string titlu;
	string autor;
	string gen;
	int an;
	int id;

public:

	string get_titlu() const;
	string get_autor() const;
	string get_gen() const;
	int get_an() const noexcept;
	int get_id() const noexcept;

	void set_titlu(string titlu);
	void set_autor(string autor);
	void set_gen(string gen);
	void set_an(int an) noexcept;


	Carte(int id, string titlu, string autor, string gen, int an) :id{ id }, titlu{ titlu }, autor{ autor }, gen{ gen }, an{ an }
	{

	}



};
/*
	Compara dupa titlu
	returneaza true daca c1.titlu e mai mic decat c2.titlu
	returneaza false in caz contrar
*/
bool cmpTitlu(const Carte& c1, const Carte& c2);

/*
	Compara dupa autor
	returneaza true daca c1.autor e mai mic decat c2.autor
	returneaza false in caz contrar
*/
bool cmpAutor(const Carte& c1, const  Carte& c2);




class DTO
{
private:
	string gen;
	int procent;
public:
	string get_gen() const;
	int get_procent() const noexcept;

	void set_gen(string gen);
	void set_procent(int procent) noexcept;

	DTO(string g, int p) :gen{ g }, procent{ p }{}
	DTO(string g) :gen{ g }, procent{ 0 }{}



};

