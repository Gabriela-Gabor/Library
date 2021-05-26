#include"Validare.h"
#include<assert.h>



//
//ostream& operator<<(ostream& out, const ValidareException& ex)
//{
//	vector<string> msg = ex.errors;
//	for (const auto& m : msg)
//	{
//		out << m << "\n";
//	}
//
//	return out;
//}

void Validator::validare_carte(const Carte& c) const
{
	string errors="";
	if (c.get_id() < 0)
		errors+="Id invalid\n";
	if (c.get_titlu() == "")
		errors+="Titlul nu poate fi vid\n";
	if (c.get_autor() == "")
		errors+="Autorul nu poate fi vid\n";
	if (c.get_gen() == "")
		errors+="Genul nu poate fi vid\n";
	if (c.get_an() < 0 || c.get_an() > 2020)
		errors+="An invalid\n";
	if (errors!="")
	{
		throw ValidareException(errors);
	}
}



