/***************************************************
*
*    @file:Login.h
*    @author:madshy
*    @mail:madshy@163.com
*    @data:2016/03/22
*    @comment:A new Class Cause meta object features not supported for nested classes.
*
***************************************************/

#pragma once

#ifndef LOGIN_H
#define LOGIN_H

#include "Database.h"

#include <qthread.h>
#include <qtcpsocket.h>

/*Login manager.*/
class Login : public QThread
{
	Q_OBJECT

		/*memberships*/
private:
	quintptr _sock;
	QSqlDatabase _db;
	QTcpSocket *_tcpSock;

	/*ctors and dtors*/
public:
	Login(QObject *, quintptr, const QString &);

	~Login();

	/*slots*/
	public slots:
	virtual void logout();
	virtual void login();

	/*inherits*/
protected:
	void run();
};

#endif