#include"Teste.h"
#include<assert.h>
#include<fstream>
#include<iostream>
#include<string.h>

#include<sstream>
using namespace std;
using std::stringstream;
using std::ofstream;


void ruleaza_teste()
{
	test_fileRepo();
	test_creeaza();
	test_storeRepo();
	testAdd();
	test_stergeRepo();
	testSterge();
	test_updateRepo();
	testUpdate();
	testUndo();
	test_findRepo();
	testFind();
	test_cmp();
	testFiltreaza();
	testSort();
	test_valideazaCarte();
	testStatistica();
	testStatistica_an();
	test_DTO();
	test_cos();
	test_rata();


}

//Domain

void test_DTO()
{
	DTO x{ "gen",10 };
	assert(x.get_gen() == "gen");
	assert(x.get_procent() == 10);
	x.set_gen("NOU");
	x.set_procent(11);
	assert(x.get_gen() == "NOU");
	assert(x.get_procent() == 11);
}

void test_creeaza()
{
	Carte c{ 1,"Ion","Rebreanu","Drama",1900 };
	assert(c.get_an() == 1900);
	assert(c.get_autor() == "Rebreanu");
	assert(c.get_titlu() == "Ion");
	assert(c.get_gen() == "Drama");
	assert(c.get_id() == 1);

	c.set_titlu("Mara");
	assert(c.get_titlu() == "Mara");
	c.set_an(1894);
	assert(c.get_an() == 1894);
	c.set_autor("Slavici");
	assert(c.get_autor() == "Slavici");
	c.set_gen("roman");
	assert(c.get_gen() == "roman");
}

void test_cmp()
{
	Carte c1{ 1,"Ion","Rebreanu","Drama",1900 };
	Carte c2{ 2, "Mara","Slavici","Roman",1894 };
	assert(cmpTitlu(c1, c2) == true);
	assert(cmpAutor(c1, c2) == true);

}

//Repository

void test_storeRepo()
{
	Repo rep;
	Carte c{ 1, "Ion","Rebreanu","Drama",1900 };
	rep.store(c);
	const auto& v = rep.getAll();
	assert(v.size() == 1);

	try
	{
		rep.store(c);
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(ex.getMessage() == "Cartea exista deja\n");
	}




}

void test_stergeRepo()
{

	Repo rep;
	Carte c{ 1, "Ion","Rebreanu","Drama",1900 };
	rep.store(c);
	assert(rep.getAll().size() == 1);
	rep.sterge(1);
	assert(rep.getAll().size() == 0);
	try
	{
		rep.sterge(1);
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(ex.getMessage() == "Cartea nu a fost gasita\n");
	}
}

void test_updateRepo()
{
	Repo rep;
	Carte c{ 1, "Ion","Rebreanu","Drama",1900 };
	rep.store(c);
	Carte c_nou{ 1, "Ion","Rebreanu","Roman",1920 };
	rep.update(c_nou);
	const auto& carti = rep.getAll();
	Carte carte = carti.at(0);
	assert(carte.get_an() == 1920);
	assert(carte.get_gen() == "Roman");

	Carte c_rau{ 2, "Mara","Slavici","Roman",1894 };
	try
	{
		rep.update(c_rau);
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(ex.getMessage() == "Cartea nu a fost gasita\n");
	}



}

void test_findRepo()
{
	Repo rep;
	Carte c{ 1, "Ion","Rebreanu","Drama",1900 };
	rep.store(c);
	Carte carte = rep.find(1);
	assert(carte.get_gen() == "Drama");
	assert(carte.get_an() == 1900);
	try
	{
		Carte cartee = rep.find(3);
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(ex.getMessage() == "Cartea nu a fost gasita\n");
	}

}

void test_fileRepo()
{
	ofstream fout("testCarti.txt", std::ios::trunc);
	fout.close();
	FileRepo repF{ "testeCarti.txt " };
	repF.store(Carte{ 1,"Ion","rebreanu","drama",1900 });
	repF.update(Carte{ 1,"Ion","REbreanu","Draama",1900 });
	assert(repF.find(1).get_autor() == "REbreanu");

	FileRepo repF2{ "testeCarti.txt " };
	auto c = repF2.find(1);
	try
	{
		repF2.find(11);
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(ex.getMessage() == "Cartea nu a fost gasita\n");
	}
	repF2.sterge(1);
	try
	{
		repF2.sterge(1);
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(ex.getMessage() == "Cartea nu a fost gasita\n");
	}
	FileRepo repF3{ "testeCarti.txt " };
	assert(repF3.getAll().size() == 0);

	try
	{
		FileRepo repF4{ "tessa.txt" };
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(ex.getMessage() == "Unable to open the file:tessa.txt");
	}


}

void test_rata()
{
	Repo rep{ 0.4 };
	for (int i = 1; i <= 100; i++)
	{
		try
		{
			rep.store(Carte{ 1, "i", "i", "i", 10 });

		}
		catch (RepoException & ex)
		{
			cout << ex.getMessage() << '\n';
		}


	}



}



//Service

void testAdd()
{
	Repo rep;
	Validator valid;
	Cosul cos;
	Service srv{ rep,valid,cos };
	srv.add(1, "Ion", "Rebreanu", "Drama", 1900);
	assert(srv.getAll().size() == 1);
	try
	{
		srv.add(1, "Ion", "Rebreanu", "Drama", 1900);
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(ex.getMessage() == "Cartea exista deja\n");
	}
	try
	{
		srv.add(2, "", "A", "aa", -5);
		assert(false);
	}
	catch (ValidareException)
	{
		assert(true);
	}
}

void testSterge()
{
	Repo rep;
	Validator valid;
	Cosul cos;
	Service srv{ rep,valid,cos };
	srv.add(1, "Ion", "Rebreanu", "Drama", 1900);
	assert(srv.getAll().size() == 1);
	srv.sterge(1);
	assert(srv.getAll().size() == 0);
	try
	{
		srv.sterge(1);
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(ex.getMessage() == "Cartea nu a fost gasita\n");
	}

}

void testUpdate()
{
	Repo rep;
	Validator valid;
	Cosul cos;
	Service srv{ rep,valid,cos };
	srv.add(1, "Ion", "Rebre", "Drama", 1900);
	srv.update(1, "Iona", "Rebreanu", "Roman", 1920);
	const auto& carti = srv.getAll();
	Carte carte = carti.at(0);
	assert(carte.get_titlu() == "Iona");
	assert(carte.get_autor() == "Rebreanu");
	assert(carte.get_an() == 1920);
	assert(carte.get_gen() == "Roman");

	try
	{
		srv.update(12, "Mara", "Slavici", "Roman", 1894);
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(ex.getMessage() == "Cartea nu a fost gasita\n");
	}
	try
	{
		srv.update(-2, "Mara", "Slavici", "", 1894);
		assert(false);
	}
	catch (ValidareException  ex)
	{
		assert(true);
	}
}

void testUndo()
{
	Repo rep;
	Validator valid;
	Cosul cos;
	Service srv{ rep,valid,cos };
	srv.add(1, "Ion", "Rebre", "Drama", 1900);
	srv.update(1, "Ion", "Rebreanu", "drama", 1900);
	srv.sterge(1);
	assert(srv.getAll().size() == 0);
	srv.undo();
	assert(srv.getAll().size() == 1);
	srv.undo();
	Carte c = srv.getAll().at(0);
	assert(c.get_autor() == "Rebre");
	srv.undo();
	assert(srv.getAll().size() == 0);
	try {
		srv.undo();
		assert(false);
	}
	catch (CarteException & ex)
	{
		assert(ex.getMessage() == "Nu mai exista operatii");
	}

	srv.add(1, "Ion", "Rebre", "Drama", 1900);
	srv.adaugaCos("Ion");
	assert(srv.Cos().size() == 1);
	srv.stergeCos();
	assert(srv.Cos().size() == 0);
	srv.undo();
	assert(srv.Cos().size() == 1);


}

void testFind()
{

	Repo rep;
	Validator valid;
	Cosul cos;
	Service srv{ rep,valid,cos };
	srv.add(1, "Ion", "Rebreanu", "Drama", 1900);;
	Carte carte = srv.find(1);
	assert(carte.get_titlu() == "Ion");
	assert(carte.get_autor() == "Rebreanu");
	assert(carte.get_gen() == "Drama");
	assert(carte.get_an() == 1900);
	try
	{
		Carte c = srv.find(3);
		assert(false);
	}
	catch (RepoException & ex)
	{
		assert(ex.getMessage() == "Cartea nu a fost gasita\n");
	}

}

void testFiltreaza()
{
	Repo rep;
	Validator valid;
	Cosul cos;
	Service srv{ rep,valid,cos };
	srv.add(1, "Ion", "Rebreanu", "Drama", 1900);
	srv.add(2, "Mara", "Slavici", "Roman", 1894);
	srv.add(3, "Micul Print", "Antoine", "Fabula", 1943);
	assert(srv.filtrare_an(1899).size() == 2);
	assert(srv.filtrare_titlu("M").size() == 2);
}

void testSort()
{
	Repo rep;
	Validator valid;
	Cosul cos;
	Service srv{ rep,valid,cos };
	srv.add(1, "Ion", "Rebreanu", "Drama", 1900);
	srv.add(2, "Micul Print", "Antoine", "Fabula", 1943);
	srv.add(3, "Mara", "Slavici", "Roman", 1943);

	auto el = srv.sorteaza_titlu().at(1);
	assert(el.get_titlu() == "Mara");

	el = srv.sorteaza_autor().at(0);
	assert(el.get_autor() == "Antoine");

	el = srv.sorteaza_an_gen().at(1);
	assert(el.get_gen() == "Fabula");


}


void testStatistica()
{
	Repo rep;
	Validator valid;
	Cosul cos;
	Service srv{ rep,valid,cos };
	srv.add(1, "Ion", "Rebreanu", "Drama", 1900);
	srv.add(2, "Micul Print", "Antoine", "Fabula", 1943);
	srv.add(3, "Mara", "Slavici", "Drama", 1943);
	srv.add(4, "Titlu", "Autor", "Drama", 1000);
	vector<DTO> v = srv.statistica();
	for (const DTO& x : v)
	{
		if (x.get_gen() == "Drama")
			assert(x.get_procent() == 75);
		if (x.get_gen() == "Fabula")
			assert(x.get_procent() == 25);
	}


}

void testStatistica_an()
{
	Repo rep;
	Validator valid;
	Cosul cos;
	Service srv{ rep,valid,cos };
	srv.add(1, "Ion", "Rebreanu", "Drama", 1900);
	srv.add(2, "Micul Print", "Antoine", "Fabula", 1943);
	srv.add(3, "Mara", "Slavici", "Drama", 1943);
	srv.add(4, "Titlu", "Autor", "Drama", 1000);
	assert(srv.statistica_an(1940, 1950) == 2);
}

//Cos

void test_cos()
{
	Repo rep;
	Validator valid;
	Cosul cos;
	Service srv{ rep,valid,cos };
	srv.add(1, "Ion", "Rebreanu", "Drama", 1900);
	srv.add(2, "Micul Print", "Antoine", "Fabula", 1943);
	srv.add(3, "Mara", "Slavici", "Drama", 1943);
	srv.add(4, "Titlu", "Autor", "Drama", 1000);
	assert(srv.Cos().size() == 0);
	srv.adaugaCos("Ion");
	srv.adaugaCos("Mara");
	assert(srv.Cos().size() == 2);
	srv.stergeCos();
	assert(srv.Cos().size() == 0);
	try
	{
		srv.genereazaCos(5);
		assert(false);
	}
	catch (CosException & ex)
	{
		assert(ex.getMessage() == "Stoc insuficient\n");
	}

	srv.genereazaCos(3);
	assert(srv.Cos().size() == 3);
	srv.exporta_CVS("testExport.cvs");
	ifstream in("testExport.cvs");
	assert(in.is_open());
	int linii = 0;
	while (!in.eof())
	{
		string linie;
		in >> linie;
		linii++;
	}
	assert(linii = 4);
	srv.exporta_HTML("testExport.html");
	ifstream fin("testExport.html");
	assert(fin.is_open());
	try {
		srv.exporta_CVS("test/Export.cvs");
		assert(false);
	}
	catch (CarteException & ex) {
		assert(ex.getMessage() == "Unable to open the file:test/Export.cvs");

	}
	try {
		srv.exporta_HTML("te/st/Export.html");
		assert(false);
	}
	catch (CarteException & ex) {
		assert(ex.getMessage() == "Unable to open the file:te/st/Export.html");

	}




}


//Validare

//void test_valideazaCarte()
//{
//	Carte c{ -11, "","","a",-1 };
//	Validator val;
//	try
//	{
//		val.validare_carte(c);
//		assert(false);
//	}
//	catch (ValidareException ex)
//	{
//		stringstream ss;
//		ss << ex;
//		const auto errorMsg = ss.str();
//		assert(errorMsg.find("Titlul nu poate fi vid") >= 0);
//		assert(errorMsg.find("Autorul nu poate fi vid") >= 0);
//		assert(errorMsg.find("An invalid") >= 0);
//		assert(errorMsg.find("Id invalid") >= 0);
//
//	}
//
//}

void test_valideazaCarte()
{
	Carte c{ -11,"","","a",-1 };
	Validator val;
	try
	{
		val.validare_carte(c);
		assert(false);
	}
	catch (ValidareException & ex)
	{
		assert(ex.getMessage().find("Id invalid"));
		assert(ex.getMessage().find( "Titlul nu poate fi vid"));
		assert(ex.getMessage().find( "Autorul nu poate fi vid"));
		assert(ex.getMessage().find( "An invalid"));
	}
}



