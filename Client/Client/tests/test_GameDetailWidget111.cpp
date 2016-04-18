#include <QtWidgets/QApplication>

#include "../include/LoginUI.h"
#include "../include/RegisterUI.h"

#include <qlistwidget.h>

#include "../include/GameDetailWidget.h"
#include <qtextstream.h>
#include <qfile.h>
#include <qtextdocument.h>
#include <qlabel.h>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//LoginUI loginUI;
	//loginUI.show();

	//RegisterUI *regUI = new RegisterUI;
	//regUI->show();

	QFile *desc = new QFile("file/desc.html");
	desc->open(QFile::ReadOnly);
	QTextStream descText(desc);

	QFile *man = new QFile("file/man.html");
	man->open(QFile::ReadOnly);

	QTextDocument *descDoc = new QTextDocument;
	descDoc->setHtml(desc->readAll());
	QTextDocument *manDoc = new QTextDocument;
	manDoc->setHtml(man->readAll());

	GameDetailWidget *gdw = new GameDetailWidget("three", "miao", ":/icons/users/1.png",
		descDoc, manDoc);
	gdw->show();

	return a.exec();
}
