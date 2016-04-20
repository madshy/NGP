/***************************************************
*
*    @file:TransferServer.h
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/21
*    @comment:inherited from QTcpServer for use a new connection in another thread
*by override incomingConnection.
*
***************************************************/

#pragma once

#ifndef TRANSFERSERVER_H
#define TRANSFERSERVER_H

#include <qtcpserver.h>

/*
*port:2016
*/
class TransferServer : public QTcpServer
{
	Q_OBJECT

public:
	TransferServer(QObject *parent = 0);
	~TransferServer();

	/*reimplement functions*/
protected:
	virtual void incomingConnection(qintptr);
};

#endif