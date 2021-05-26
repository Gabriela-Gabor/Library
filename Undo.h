#pragma once
#include"Carte.h"
#include"Repository.h"

class ActiuneUndo
{
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga :public ActiuneUndo
{
	Carte carte_adaugata;
	IRepo& rep;
public:

	UndoAdauga(IRepo& rep, const Carte& c) :rep{ rep }, carte_adaugata{ c }{}

	void doUndo() override
	{
		rep.sterge(carte_adaugata.get_id());
	}
};

class UndoSterge :public ActiuneUndo
{
	Carte carte_stearsa;
	IRepo& rep;
public:

	UndoSterge(IRepo& rep, const Carte& c) noexcept :rep{ rep }, carte_stearsa{ c }{}

	void doUndo() override
	{
		rep.store(carte_stearsa);
	}
};

class UndoModifica :public ActiuneUndo
{
	Carte carte_initiala;
	IRepo& rep;
public:
	UndoModifica(IRepo& rep, const Carte& c) noexcept :rep{ rep }, carte_initiala{ c }{}
	void doUndo() override
	{
		rep.update(carte_initiala);
	}
};

class UndoCos :public ActiuneUndo
{
	vector<Carte> c;
	Cosul& Cos;
public:
	UndoCos(Cosul& Cos, const vector<Carte>& c) :Cos{ Cos }, c{ c }{}
	void doUndo() override
	{

		Cos.adauga_cos(c);

	}
};