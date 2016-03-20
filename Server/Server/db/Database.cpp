/***************************************************
*
*    @file:Database.cpp
*    @author:madshy
*    @mail:madshy@163.com
*    @data:2016/03/20
*    @comment:Implement of class Database.
*Note to order of contruct between db and query.
*That is query must be behind to db.
*
***************************************************/

#include "../include/Database.h"

#include <QtCore\qdebug.h>
#include <QtSql\qsqlquery.h>

Database::Database()
	:Database("QMYSQL", "127.0.0.1", 3306, "root", "123456", "ngp")
{
}

//Database::Database(const QString &driver, const QString &host, int port,
//	const QString &user = QString("root"), const QString &password = QString("123456"),
//	const QString &dbName = QString("ngp"))
//	: Database("QMYSQL", "127.0.0.1", 3306, user, password, dbName)
//{
//}

Database::Database(const QString &driver, const QString &host, int port,
	const QString &user, const QString &password,
	const QString &dbName)
	: driver(driver), host(host), port(port), user(user), password(password), dbName(dbName), query(nullptr)
{
	init();
}

Database::~Database()
{
	/*or nullprt != query*/
	if (query)
	{
		delete query;
	}
	disconnect();
}

bool Database::connect()
{
	QSqlError err;
	/*
	db.isOpen() almost make me die.
	*/
	if (!db.open())
	{
		err = db.lastError();
		qDebug() << err.text();
		return false;
	}
	query = new QSqlQuery(db);
	return true;
}

bool Database::disconnect()
{
	if (db.isOpen())
		db.close();
	return true;
}

bool Database::insert(const QString &sql)
{
	if (!query)
	{
		qDebug() << "Connect before insert, calling connect() may be useful.";
		return false;
	}
	
	/*
	Actually, so bad design.
	*/
	return query -> exec(sql);
}

QSqlQuery* Database::select(const QString &sql)
{
	if (!query)
	{
		qDebug() << "Connect before select, calling connect() may be useful.";
		return  nullptr;
	}

	/*note! may be leak memory.*/
	QSqlQuery *temp = new QSqlQuery();
	temp -> exec(sql);
	return temp;
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