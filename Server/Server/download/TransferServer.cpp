/***************************************************
*
*    @file:TransferServer.cpp
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/21
*    @comment:Implement TransferServer
*
***************************************************/

#include "../include/TransferServer.h"
#include "../include/GameTransferThread.h"

#include <qhostaddress.h>

TransferServer::TransferServer(QObject *parent)
	:QTcpServer(parent)
{
	listen(QHostAddress("127.0.0.1"), 2016);
}

TransferServer::~TransferServer()
{

}

void TransferServer::incomingConnection(qintptr socketDescriptor)
{
	/*memory leak maybe*/
	(new GameTransferThread(socketDescriptor, this))->start();
}