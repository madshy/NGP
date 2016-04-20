/***************************************************
*
*    @file:GameTransferThread.h
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/20
*    @comment:A thread to transfer the installation package of game.
*
***************************************************/

#pragma once

#ifndef GAMETRANSFERTHREAD_H
#define GAMETRANSFERTHREAD_H

#include <qthread.h>

/*forward declaration*/
class QTcpSocket;
class QString;

class GameTransferThread : public QThread
{
	Q_OBJECT

private:
	QTcpSocket *_tcpSocket;
	qint64 _loadSize;/*4kB, size sent each time.*/

public:
	GameTransferThread(quintptr /*socketDescriptor*/, QObject *parent = 0);
	~GameTransferThread();

	private slots:
	/*read the request from client.*/
	void readRequest();

private:
	/*transfer package by given packagePath*/
	void transfer(const QString &/*packagePath*/);
};

#endif