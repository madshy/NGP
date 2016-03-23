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
#include "TcpServerProxy.h"

#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qobject.h>
#include <qmap.h>
#include <qstring.h>
#include <qpointer.h>
#include <qsharedpointer.h>
#include <qthread.h>
#include <qhostaddress.h>

/*Port of this server is 1994*/
class LoginServer: public QThread
{
	Q_OBJECT
	/*memberships*/
private:
	QHostAddress _addr;
	quint16 _port;
	TcpServerProxy* _serverProxy;

	/*ctors and dtors*/
public:
	LoginServer(QObject *parent, const QHostAddress&, quint16);
	~LoginServer();

signals:
	void listenEmit(const QString&, quint16);

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
};

#endif