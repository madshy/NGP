#include <QtWidgets/QApplication>

#include "../include/LoginUI.h"
#include "../include/RegisterUI.h"

#include <qlistwidget.h>

#include "../include/GameDetailWidget.h"
#include <qtextstream.h>
#include <qfile.h>
#include <qtextdocument.h>
#include <qlabel.h>

#include "../include/GameListWidget.h"
#include "../include/GameListItem.h"
#include <qlist.h>
#include "../include/MainUI.h"
#include "../include/Account.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//LoginUI loginUI;
	//loginUI.show();

	//RegisterUI *regUI = new RegisterUI;
	//regUI->show();

	//QFile *desc = new QFile("file/desc.html");
	//desc->open(QFile::ReadOnly);
	//QTextStream descText(desc);

	//QFile *man = new QFile("file/man.html");
	//man->open(QFile::ReadOnly);

	//QTextDocument *descDoc = new QTextDocument;
	//descDoc->setHtml(desc->readAll());
	//QTextDocument *manDoc = new QTextDocument;
	//manDoc->setHtml(man->readAll());

	////GameDetailWidget *gdw = new GameDetailWidget;
	////gdw->setDetail("three", "miao", ":/icons/users/1.png", descDoc->toHtml(), manDoc->toHtml());
	////gdw->show();
	//GameListItem *item = new GameListItem(QString(":/icons/users/1.png"), QString("three"), QString("miao"),  
	//	descDoc->toHtml(), manDoc->toHtml(), QIcon(":/icons/users/1.png"), "xksadfasfdadfs");
	//QList<GameListItem*> list;
	//list.append(item);

	//GameListWidget *game = new GameListWidget(&list);
	//game->show();
	QList<QString> buddys;
	buddys.append("shy");
	buddys.append("ma");
	buddys.append("uchiha");

	QList<QString> games;
	games.append("lol");
	games.append("dnf");
	games.append("three");

	Account acc("madshy", "miao", ":/icons/users/2.png", buddys, games);

	MainUI *mainUI = new MainUI(nullptr, acc);
	mainUI->show();

	return a.exec();
}
