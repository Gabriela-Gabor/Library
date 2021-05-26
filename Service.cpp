#include"Service.h"
#include<assert.h>
#include<string.h>
#include<algorithm>
#include<random>
#include<numeric>
#include<fstream>

using std::sort;
using std::find_if;
using std::default_random_engine;
using std::begin;
using std::end;
using std::shuffle;
using std::accumulate;
using std::ofstream;
using std::ifstream;


void Service::add(int id, string titlu, string autor, string gen, int an)
{
	Carte c{ id,titlu,autor,gen,an };
	valid.validare_carte(c);
	rep.store(c);
	undoActions.push_back(std::make_unique<UndoAdauga>(rep, c));
	notify();

}

void Service::sterge(int id)
{
	Carte c = find(id);
	string titlu = c.get_titlu();
	string autor = c.get_autor();
	string gen = c.get_gen();
	const int an = c.get_an();
	rep.sterge(id);
	undoActions.push_back(std::make_unique<UndoSterge>(rep, Carte{ id,titlu,autor,gen,an }));
	notify();
}

void Service::update(int id, string titlu, string autor, string gen, int an)
{
	Carte carte{ id, titlu,autor,gen,an };
	valid.validare_carte(carte);

	Carte c = find(id);
	string titlu2 = c.get_titlu();
	string autor2 = c.get_autor();
	string gen2 = c.get_gen();
	const int an2 = c.get_an();

	rep.update(carte);
	undoActions.push_back(std::make_unique<UndoModifica>(rep, Carte{ id,titlu2,autor2,gen2,an2 }));
	notify();
}

const Carte& Service::find(int id)
{
	return rep.find(id);
}

vector<Carte> Service::getAll()
{
	return rep.getAll();
}

vector<Carte> Service::filtreaza(function<bool(const Carte&)>fct)
{
	/*vector<Carte> carti = rep.getAll();
	vector<Carte> filtrat(carti.size());
	auto it = std::copy_if(carti.begin(), carti.end(), filtrat.begin(), [&](const Carte& carte) {fct(carte); });
	filtrat.resize(std::distance(filtrat.begin(), it));*/
	vector<Carte> filtrat;
	for (const auto& carte : rep.getAll())
	{
		if (fct(carte))
			filtrat.push_back(carte);
	}

	return filtrat;
}

vector<Carte> Service::filtrare_an(int an)
{
	return filtreaza([an](const Carte& carte)  noexcept
		{
			return carte.get_an() > an;
		});
}

vector<Carte> Service::filtrare_titlu(string titlu)
{
	return filtreaza([titlu](const Carte& carte)
		{
			int found = carte.get_titlu().find(titlu);
			if (found != std::string::npos)
				return true;
			return false;
		});

}


vector<Carte> Service::sorteaza(bool(*maiMic)(const Carte&, const Carte&))
{
	vector<Carte> sortat{ rep.getAll() };		//fac o copie a listei de carti
	sort(sortat.begin(), sortat.end(), maiMic);
	return sortat;
}

vector<Carte> Service::sorteaza_titlu()
{
	return sorteaza(cmpTitlu);
}
vector<Carte> Service::sorteaza_autor()
{
	return sorteaza(cmpAutor);
}

vector<Carte> Service::sorteaza_an_gen()
{
	return sorteaza([](const Carte& c1, const Carte& c2)
		{
			if (c1.get_an() == c2.get_an())
				return c1.get_gen() < c2.get_gen();
			return c1.get_an() < c2.get_an();
		});
}

int Service::statistica_an(int an1, int an2)
{
	vector<Carte> carti = this->getAll();
	int sum = 0;
	return accumulate(carti.begin(), carti.end(), sum, [&](int sum, const Carte& c) noexcept {if (c.get_an() > an1&& c.get_an() < an2) return sum + 1; else return sum; });
}


void Service::adaugaCos(string titlu)
{
	vector<Carte> carti = this->getAll();
	vector<Carte> cos;
	for (const auto& carte : carti)
	{
		if (carte.get_titlu() == titlu)
			cos.push_back(carte);
	}

	this->cos.adauga_cos(cos);
	notify();
	
}

void Service::stergeCos()
{
	vector<Carte> c = cos.Cos();
	this->cos.sterge_cos();
	undoActions.push_back(std::make_unique<UndoCos>(cos, c));
	notify();
	

}

void Service::genereazaCos(int nr)
{
	vector<Carte> carti = this->getAll();
	vector<Carte> listacos = this -> Cos();
	vector<Carte> lista;
	if (nr > carti.size())
		throw CosException("Stoc insuficient\n");
	else
	{
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> const dist(0, carti.size() - 1);
		vector<int> v;
		while (v.size() != nr)
		{
			int const rnd = dist(mt);
			vector<int>::iterator it = std::find(v.begin(), v.end(), rnd);
			if (it == v.end())
			{
				v.push_back(rnd);
				lista.push_back(carti.at(rnd));
			}
		}
	}

	this->cos.adauga_cos(lista);
	notify();
	
}
vector<Carte> Service::Cos()
{
	return cos.Cos();
}

void Service::exporta_CVS(const string& nume_fisier)
{
	ofstream f(nume_fisier, std::ios::trunc);
	if (!f.is_open())
	{
		throw CarteException("Unable to open the file:" + nume_fisier);
	}
	auto lista = cos.Cos();
	for (auto l : lista)
	{
		f << l.get_id() << ' ' << l.get_titlu() << ' ' << l.get_autor() << ' ' << l.get_gen() << ' ' << l.get_an();
		f << '\n';
	}
	f.close();

}

void Service::exporta_HTML(const string& nume_fisier)
{
	ofstream f(nume_fisier, std::ios::trunc);
	if (!f.is_open())
	{
		throw CarteException("Unable to open the file:" + nume_fisier);
	}
	f << "<html><body>" << std::endl;
	f << "<table border=\"1\" style=\"width:100 % \">" << std::endl;
	f << "<tr>" << std::endl;
	f << "<td>" << "id" << std::endl;
	f << "<td>" << "titlu" << std::endl;
	f << "<td>" << "autor" << std::endl;
	f << "<td>" << "gen" << std::endl;
	f << "<td>" << "an" << std::endl;
	f << "</tr>" << std::endl;
	auto lista = cos.Cos();
	for (auto l : lista)
	{
		f << "<tr>" << std::endl;
		f << "<td>" << l.get_id() << "</td>" << std::endl;
		f << "<td>" << l.get_titlu() << "</td>" << std::endl;
		f << "<td>" << l.get_autor() << "</td>" << std::endl;
		f << "<td>" << l.get_gen() << "</td>" << std::endl;
		f << "<td>" << l.get_an() << "</td>" << std::endl;
		f << "</tr>" << std::endl;
	}

	f << "</table>" << std::endl;
	f << "</body></html>" << std::endl;
	f.close();
	
}


vector<DTO> Service::statistica()
{
	auto genuri = rep.getAll();
	const int nr_gen = genuri.size();
	map<string, int> statistica;
	for (auto gen : genuri)
	{
		if (statistica.find(gen.get_gen()) == statistica.end())
		{
			DTO nou{ gen.get_gen() };
			statistica.insert(make_pair(gen.get_gen(), 1));
		}
		else
		{
			statistica[gen.get_gen()] += 1;

		}
	}

	map<string, int>::iterator it = statistica.begin();
	vector<DTO> vdto;
	while (it != statistica.end())
	{
		DTO obiect{ it->first,(100 * it->second) / nr_gen };
		vdto.push_back(obiect);
		it++;
	}

	return vdto;
	notify();
}

void Service::undo()
{
	if (undoActions.empty())
	{
		throw CarteException("Nu mai exista operatii");
	}

	undoActions.back()->doUndo();
	undoActions.pop_back();
	notify();
}