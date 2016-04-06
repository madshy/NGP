#include <QtWidgets/QApplication>

#include "../include/LoginUI.h"
#include "../include/RegisterUI.h"

#include <qlistwidget.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//LoginUI loginUI;
	//loginUI.show();

	RegisterUI *regUI = new RegisterUI;
	regUI->show();

	return a.exec();
}
