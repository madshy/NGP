/***************************************************
*
*    @file:Login.h
*    @author:madshy
*    @mail:madshy@163.com
*    @data:2016/03/20
*    @comment:Managing login of client.
*
***************************************************/

#pragma once

#ifndef LOGIN_H
#define LOGIN_H

#include "Database.h"

#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qobject.h>
#include <qmap.h>
#include <qstring.h>
#include <qpointer.h>
#include <qsharedpointer.h>


class Login: public QObject
{
	Q_OBJECT
private:
	/*memberships*/
	Database _db;
	QTcpServer _tcpServer;
	QTcpSocket _socket;

public:
	/*ctors
	No need to add a parameter QObject *parent, 
	cause QObject has a default-ctor and Login has no derived class at present.
	*/

	Login();
	Login(const Database &);
	Login(const QTcpServer &, const QTcpSocket &);
	Login(const Database &, const QTcpServer &, const QTcpSocket &);

	/*dtor*/
	~Login();

public:
	/*setter*/
	void setDatabase(const Database &);
	void setTcpServer(const QTcpServer &);
	void setTcpSocket(const QTcpSocket &);

	/*getter*/
	Database getDatabase();
	QTcpServer getTcpServer();
	QTcpSocket getTcpSocket();

public:
	/*maybe need to synchronize*/
	/*The second param should be rethink.*/
	static QMap<QString, QSharedPointer<Login>> OnlineUserList;

public slots:
	/*Add slot*/


signals:
	/*Add signal*/
};

#endif