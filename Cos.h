#pragma once
#include"Carte.h"
#include"Observer.h"
#include<vector>

using std::vector;
class CosException
{
	string mesaj;

public:

	CosException(string m) :mesaj{ m }
	{

	}
	string getMessage()
	{
		return mesaj;
	}
};

class Cosul
{
private:
	vector<Carte> cos;
public:
	/*
	Creeaza un cos cu carti
	Arunca exceptie daca vrea sa adauge o carte care exista deja in cos
*/
	void adauga_cos(const vector<Carte>& carti);
	/*
		Sterge cosul de carti
	*/
	void sterge_cos() noexcept;

	/*
		Returneaza lista cartilor din cos
	*/

	vector<Carte> Cos();

	

};