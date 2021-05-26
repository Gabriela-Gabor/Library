#include"Repository.h"
#include<assert.h>
#include<algorithm>
#include<random>

using std::make_pair;
using std::pair;
using std::back_inserter;

void Repo::store(const Carte& carte)
{
	float r = float(rand() % 10) / 10;
	if (r < nr)
		throw RepoException("Rata Exceptie\n");

	map<int, Carte>::iterator it;
	it = carti.find(carte.get_id());
	if (it != carti.end())
	{
		throw RepoException("Cartea exista deja\n");
	}
	carti.insert(make_pair(carte.get_id(), carte));

	/*for (const Carte& c : carti)
		if (c.get_id() == carte.get_id())
		{
			throw RepoException("Cartea exista deja\n");
		}
	carti.push_back(carte);*/



}

void Repo::sterge(int id)
{
	float r = rand() % 10 / 10;
	if (r < nr)
		throw RepoException("Rata Exceptie\n");

	auto it = carti.find(id);
	if (it != carti.end())
	{
		carti.erase(it);
	}
	else throw RepoException("Cartea nu a fost gasita\n");


}

void Repo::update(const Carte& carte)
{
	float r = rand() % 10 / 10;
	if (r < nr)
		throw RepoException("Rata Exceptie\n");

	auto it = carti.find(carte.get_id());
	if (it != carti.end())
	{
		carti.at(carte.get_id()).set_gen(carte.get_gen());
		carti.at(carte.get_id()).set_an(carte.get_an());
		carti.at(carte.get_id()).set_autor(carte.get_autor());
		carti.at(carte.get_id()).set_titlu(carte.get_titlu());
	}
	else
		throw RepoException("Cartea nu a fost gasita\n");;

	/*auto it = find_if(carti.begin(), carti.end(), [&](const Carte& c) noexcept { return (c.get_id() == carte.get_id() ); });
	if (it != carti.end())
	{
		carti.at(it - carti.begin()).set_gen(carte.get_gen());
		carti.at(it - carti.begin()).set_an(carte.get_an());
		carti.at(it - carti.begin()).set_autor(carte.get_autor());
		carti.at(it - carti.begin()).set_titlu(carte.get_titlu());
	}
	else
		throw RepoException("Cartea nu a fost gasita\n");*/


}

Carte& Repo::find(int id)
{

	auto it = carti.find(id);
	if (it != carti.end())
	{
		return carti.at(id);
	}
	throw RepoException("Cartea nu a fost gasita\n");

	/*auto it = find_if(carti.begin(), carti.end(), [&](const Carte& c)noexcept { return (c.get_id() == id); });
	if (it != carti.end())
	{
		return carti.at(it - carti.begin());
	}
	else
		throw RepoException("Cartea nu a fost gasita\n");*/
}




vector<Carte> Repo::getAll()
{

	vector<Carte> c;
	std::transform(carti.begin(), carti.end(), back_inserter(c), [](const pair<int, Carte>& carte) {return carte.second; });
	return c;
}



