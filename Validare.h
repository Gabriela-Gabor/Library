#pragma once
#include"Carte.h"

#include<iostream>
#include<string>
#include<vector>

using std::vector;
using std::string;
using std::ostream;

class ValidareException
{
private:
	string errors;
public:
	ValidareException(string msg) :errors{ msg } {};
	//friend ostream& operator<<(ostream& out, const ValidareException& ex);

	string getMessage()
	{
		return errors;
	}
};

class Validator
{
public:
	/*
		Valideaza cartile
		Verifica daca titlul,autorul sau genul nu sunt vide , daca anul e cuprins intre 0 si 2020(anul curent) si daca id este pozitiv
		In caz contrar arunca ValidareExcepition(errors) unde rrors sunt mesajele corespunzaroare (Titlul/Autorul/Genul nu e valid sau An invlalid)
	*/
	void validare_carte(const Carte& c) const;
};

