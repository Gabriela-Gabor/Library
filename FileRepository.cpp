#include"FileRepository.h"


void FileRepo::load_from_file()
{
	ifstream fin(filename);
	if (!fin.is_open())
	{
		throw RepoException("Unable to open the file:" + filename);
	}
	string titlu, autor, gen;
	int id = 0, an = 0;
	while (fin >> id >> titlu >> autor >> gen >> an)
	{
		Carte c{ id,titlu,autor,gen,an };
		Repo::store(c);
	}
	fin.close();
}

void FileRepo::write_to_file()
{
	ofstream fout(filename);

	for (auto& c : getAll())
	{
		fout << c.get_id() << ' ' << c.get_titlu() << ' ' << c.get_autor() << ' ' << c.get_gen() << ' ' << c.get_an() << "\n";
	}

	fout.close();
}

void FileRepo::store(const Carte& c)
{
	Repo::store(c);
	write_to_file();
}
void FileRepo::sterge(int id)
{
	Repo::sterge(id);
	write_to_file();
}

void FileRepo::update(const Carte& carte)
{
	Repo::update(carte);
	write_to_file();
}
