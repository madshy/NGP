/***************************************************
*
*    @file:LoginServer.cpp
*    @author:madshy
*    @mail:madshy@163.com
*    @data:2016/03/21
*    @comment:
*
***************************************************/

#include "../include/LoginServer.h"
#include "../include/Login.h"

#include <iostream>
#include <qstring.h>


/*static membership*/
QMap<QString, QSharedPointer<QTcpSocket>> LoginServer::OnlineUserList;
QMap<quintptr, QString> LoginServer::OnlineHostList;

LoginServer::LoginServer(QObject *parent, const QHostAddress &addr, quint16 port)
	:QThread(parent), _addr(addr), _port(port), _serverProxy(nullptr)
{
	_serverProxy = new TcpServerProxy();
	connect(_serverProxy, SIGNAL(newConnection()), this, SLOT(login()));

	/*if not proxy, is can ok to connect this signal to slot listen of QTcpServer???*/
	connect(this, SIGNAL(listenEmit(const QString &, quint16)), _serverProxy, SLOT(proxyListen(const QString &, quint16)));
}

/*
Is there should be delete a pointer of QObject?
*/
LoginServer::~LoginServer()
{
	if (_serverProxy)
	{
		delete _serverProxy;
	}
	_serverProxy = nullptr;
}

void LoginServer::run()
{
	std::cout << "Listening......" << std::endl;
	/*Add a signal to emmit???and a slot to new a thread,listen in here??*/
	//_server -> listen(_addr, _port);
	emit listenEmit(_addr.toString(), _port);
}


void LoginServer::login()
{
	std::cout << "New connection......";
	quintptr sock = _serverProxy->nextPendingConnection()->socketDescriptor();

	/*new a Login, actually a thread to login*/
	(new Login(this, sock, Database())) -> start();
}

