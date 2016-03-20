
#include <QtCore/QCoreApplication>
#include <QtCore/qdebug.h>
#include <QtSql\qsqlquery.h>

#include "include/Database.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	return a.exec();
}
