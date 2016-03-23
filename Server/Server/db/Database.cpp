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

unsigned int Database::flag = 1;

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
	connName = QString("db_id_%1").arg(flag);
	init();
	++flag;
}

Database::~Database()
{
	/*or nullprt != query*/
	if (query)
	{
		delete query;
		query = nullptr;
	}

	disconnect();
}

QString Database::getConnName()
{
	return connName;
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
	query = new QSqlQuery();
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
	/*
	Actually, so bad design.
	*/
	return query -> exec(sql);
}

QSqlQuery Database::select(const QString &sql)
{
	/*note! may be leak memory.*/
	query -> exec(sql);
	return *query;
}

void Database::init()
{
	/*get database*/
	db = QSqlDatabase::addDatabase(driver, connName);

	/*set info*/
	db.setHostName(host);
	db.setPort(port);
	db.setUserName(user);
	db.setPassword(password);
	db.setDatabaseName(dbName);
}