#include"Carte.h"
#include"Repository.h"
#include"FileRepository.h"
#include "UI.h""
#include <QtWidgets/QApplication>
#include"QtGui.h"

int main(int argc, char *argv[])
{

	//ruleaza_teste();
	//Repo rep;
	FileRepo rep{ "carti.txt" };
	Validator valid;
	Cosul cos;
	Service srv{ rep,valid ,cos };
	//UI ui{ srv };
	//ui.startUI();

	QApplication a(argc, argv);
	Gui g{ srv };
	g.show();
	

	return a.exec();
}
