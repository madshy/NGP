/***************************************************
*
*    @file:Login.h
*    @author:madshy
*    @mail:madshy@163.com
*    @data:2016/03/20
*    @comment:Managing login of client.
*Need to add a connection manager in other port.
*
***************************************************/

#pragma once

#ifndef LOGINSERVER_H
#define LOGINSERVER_H

#include "Database.h"

#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qobject.h>
#include <qmap.h>
#include <qstring.h>
#include <qpointer.h>
#include <qsharedpointer.h>
#include <qthread.h>
#include <qhostaddress.h>
#include <qsharedpointer.h>

class LoginServer: public QThread
{
	Q_OBJECT
	/*memberships*/
private:
	QHostAddress _addr;
	quint16 _port;
	QTcpServer* _server;

	/*ctors and dtors*/
public:
	LoginServer(const QHostAddress&, quint16);
	~LoginServer();

protected slots:
	/*slots*/
	virtual void login();

	/*inherit from QThread*/
protected:
	virtual void run();

public:
	/*maybe need to synchronize*/
	/*
	QString is the name of account.
	quintptr is the user's socket descriptor
	Actually, this two is the reverse of key and value each other.
	and one host can login once not twice, same to user.
	*/
	static QMap<QString, QSharedPointer<QTcpSocket>> OnlineUserList;
	static QMap<quintptr, QString> OnlineHostList;

	/*Inner class*/
protected:
	/*Login manager.*/
	class Login : public QThread
	{
		Q_OBJECT
	
		/*memberships*/
	private:
		quintptr _sock;
		Database _db;

		/*ctors and dtors*/
	public:
		Login(quintptr, const Database&);

		~Login();

		/*slots*/
		public slots:
		virtual void login();
		virtual void logout();

		/*inherits*/
	protected:
		void run();
	};
};

#endif