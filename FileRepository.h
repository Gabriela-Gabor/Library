#pragma once
#include"Repository.h"
#include<iostream>
#include<fstream>
#include<string>

using std::ifstream;
using std::ofstream;

class FileRepo :public Repo
{
private:


	string filename;
	void load_from_file();
	void write_to_file();

public:

	FileRepo(string nume) :Repo(), filename{ nume }
	{
		load_from_file();
	}
	void store(const Carte& c) override;

	void sterge(int id) override;

	void update(const Carte& carte) override;

};