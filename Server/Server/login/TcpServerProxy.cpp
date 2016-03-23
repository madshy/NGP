/***************************************************
*
*    @file:TcpServerProxy.cpp
*    @author:madshy
*    @mail:madshy@163.com
*    @data:2016/03/22
*    @comment:See in TcpServerProxy.
*Actually, "QObject: Cannot create children for a parent that is in a different thread"
*	is a hard question to me.
*
***************************************************/

#include "../include/TcpServerProxy.h"

TcpServerProxy::TcpServerProxy(QObject *parent)
	:QTcpServer(parent)
{
}

TcpServerProxy::~TcpServerProxy()
{
}

void TcpServerProxy::proxyListen(const QString &addr, quint16 port)
{
	listen(QHostAddress(addr), port);
}
