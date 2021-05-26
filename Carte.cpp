#include"Carte.h"
#include<assert.h>

string Carte::get_titlu() const
{
	return titlu;
}
string Carte::get_autor() const
{
	return autor;
}
string Carte::get_gen() const
{
	return gen;
}
int Carte::get_an() const noexcept
{
	return an;
}
int Carte::get_id() const noexcept
{
	return id;
}

void Carte::set_titlu(string titlu)
{
	this->titlu = titlu;
}

void Carte::set_autor(string autor)
{
	this->autor = autor;
}

void Carte::set_gen(string gen)
{
	this->gen = gen;
}

void Carte::set_an(int an) noexcept
{
	this->an = an;
}

bool cmpTitlu(const Carte& c1, const  Carte& c2)
{
	return c1.get_titlu() < c2.get_titlu();
}

bool cmpAutor(const Carte& c1, const  Carte& c2)
{
	return c1.get_autor() < c2.get_autor();
}

string DTO::get_gen() const
{
	return this->gen;
}

int DTO::get_procent() const noexcept
{
	return this->procent;
}


void DTO::set_gen(string gen_nou)
{
	this->gen = gen_nou;
}

void DTO::set_procent(int procent_nou) noexcept
{
	this->procent = procent_nou;
}

