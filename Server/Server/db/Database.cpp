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

unsigned int Database::_flag = 1;

Database::Database(const QString &driver, const QString &host, int port,
	const QString &user, const QString &password,
	const QString &dbName)
	:_driver(driver), _host(host), _port(port), _user(user),
	_password(password), _dbName(dbName), _connName("")
{
	_connName += QString("db_id_%1").arg(_flag);
	init();
	++_flag;
}

Database::~Database()
{
}

QString Database::getConnName()
{
	return _connName;
}

void Database::init()
{
	/*get database*/
	QSqlDatabase db = QSqlDatabase::addDatabase(_driver, _connName);

	/*set info*/
	db.setHostName(_host);
	db.setPort(_port);
	db.setUserName(_user);
	db.setPassword(_password);
	db.setDatabaseName(_dbName);
}