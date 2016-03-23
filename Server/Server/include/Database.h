/***************************************************
*
*    @file:Database.h
*    @author:madshy
*    @mail:madshy@163.com
*    @data:2016/03/20
*    @comment:Managing databases,mainly for it's name.
*
***************************************************/

#pragma once

#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/qsql.h>
#include <QtSql\qsqldatabase.h>
#include <QtSql\qsqlerror.h>
#include <QtCore/qstring.h>
#include <qsqlquery.h>
#include <qobject.h>

class Database : public QSqlDatabase
{
public:
	/*ctors*/
	Database(const QString &driver = QString("QMYSQL"), 
		const QString &host = QString("127.0.0.1"), int port = 3306,
		const QString &user = QString("root"), const QString &password = QString("123456"),
		const QString &dbName = QString("ngp"));

	/*dtor*/
	~Database();

public:
	/*To get a database connection by it's name.*/
	QString getConnName();
	
private:
	void init();

private:
	QString _driver;
	QString _host;
	int _port;
	QString	_user;
	QString _password;
	QString	_dbName;

	/*To identify a database connection*/
	QString _connName;

private:
	/*A flag to distinguish database.Actually, it's a postfix of db's name.*/
	static unsigned int _flag;
};

#endif