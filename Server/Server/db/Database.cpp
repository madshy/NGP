/***************************************************
*
*    @file:Database.cpp
*    @author:madshy
*    @mail:madshy@163.com
*    @data:2016/03/20
*    @comment:Implement of class Database.
*
***************************************************/

#include "../include/Database.h"

Database::Database()
	:Database("QMYSQL", "127.0.0.1", 3306, "root", "123456", "ngp")
{
}

Database::Database(const QString &driver, const QString &host, int port,
	const QString &user = QString("root"), const QString &password = QString("123456"),
	const QString &dbName = QString("ngp"))
	: Database("QMYSQL", "127.0.0.1", 3306, user, password, dbName)
{
}

Database::Database(const QString &driver, const QString &host, int port,
	const QString &user, const QString &password,
	const QString &dbName)
	: driver(driver), host(host), port(port), user(user), password(password), dbName(dbName)
{
	init();
}

Database::~Database()
{
	disconnect();
}

QSqlError Database::connect()
{
	QSqlError err;
	if (!db.open())
	{
		err = db.lastError();
	}
	return err;
}

bool Database::disconnect()
{
	if (db.isOpen())
		db.close();
}

bool Database::insert(const QString &sql)
{
	return query.exec(sql);
}

QSqlQuery Database::select(const QString &sql)
{
	query.exec(sql);
	return query;
}

void Database::init()
{
	/*get database*/
	db = QSqlDatabase::addDatabase(driver);

	/*set info*/
	db.setHostName(host);
	db.setPort(port);
	db.setUserName(user);
	db.setPassword(password);
	db.setDatabaseName(dbName);
}