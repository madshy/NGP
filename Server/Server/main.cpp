
#include <QtCore/QCoreApplication>
#include <QtCore/qdebug.h>
#include <QtSql\qsqlquery.h>

#include "include/Database.h"
#include "include/LoginServer.h"
#include "include/TransferServer.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QHostAddress addr("192.168.150.1");
	quint16 port(1994);

	LoginServer loginServer(0, addr, port);
	loginServer.start();

	TransferServer server;

	return a.exec();
}