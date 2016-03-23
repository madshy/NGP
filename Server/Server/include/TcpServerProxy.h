/***************************************************
*
*    @file:TcpServerProxy.h
*    @author:madshy
*    @mail:madshy@163.com
*    @data:2016/03/22
*    @comment:A proxy for QTcpServer
*At present,it create a slot to call listen();
*
***************************************************/

#pragma once

#include <qtcpserver.h>
#include <qobject.h>
#include <qhostaddress.h>
#include <qstring.h>

/*A proxy for TcpServer*/
class TcpServerProxy : public QTcpServer
{
	Q_OBJECT

public:
	TcpServerProxy(QObject *parent = Q_NULLPTR);
	~TcpServerProxy();

	public slots:
	/*Proxy for listen to make listen work as a slot.*/
	virtual void  proxyListen(const QString&, quint16);
};