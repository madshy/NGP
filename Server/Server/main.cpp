
#include <QtCore/QCoreApplication>
#include <QtCore/qdebug.h>
#include <QtSql\qsqlquery.h>

#include "include/Database.h"
#include "include/LoginServer.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QHostAddress addr("127.0.0.1");
	quint16 port(1994);

	LoginServer loginServer(0, addr, port);
	loginServer.start();

	return a.exec();
}