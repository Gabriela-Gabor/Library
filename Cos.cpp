#include"Cos.h"
#include<algorithm>
#include<random>

void Cosul::adauga_cos(const vector<Carte>& carti)
{
	int exceptie = 0;
	for (const auto& carte : carti)
	{
		int ok = 0;
		for (const auto& c : cos)
		{
			if (c.get_titlu() == carte.get_titlu())
			{
				ok = 1;
				exceptie = 1;
			}
		}
		if(ok==0)
			cos.push_back(carte);
	}
	


}


void Cosul::sterge_cos() noexcept
{
	cos.clear();
	
}

vector<Carte> Cosul::Cos()
{
	return cos;
}


