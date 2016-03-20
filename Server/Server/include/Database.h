/***************************************************
*
*    @file:Database.h
*    @author:madshy
*    @mail:madshy@163.com
*    @data:2016/03/20
*    @comment:Managing operations of databases such as connect, disconnect, insert and select.
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

class Database{
public:
	/*ctors*/
	Database();
	//Database(const QString &driver, const QString &host, int port,
	//	const QString &user = QString("root"), const QString &password = QString("123456"),
	//	const QString &dbName = QString("ngp"));
	Database(const QString &driver, const QString &host, int port,
		const QString &user, const QString &password,
		const QString &dbName);
	/*dtor*/
	~Database();

public:
	bool connect();
	bool disconnect();
	bool insert(const QString &sql);
	QSqlQuery select(const QString &sql);
	
private:
	void init();

private:
	QSqlDatabase db;
	QSqlQuery query;

	QString driver;
	QString host;
	int port;
	QString	user;
	QString password;
	QString	dbName;
};

#endif