/***************************************************
*
*    @file:GameDownloadThread.h
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/21
*    @comment:a thread to download game.
*
***************************************************/

#pragma once
#ifndef GAMEDOWNLOADTHREAD_H
#define GAMEDOWNLOADTHREAD_H

#include <qthread.h>
#include <qstring.h>
#include <qbytearray.h>

class QTcpSocket;
class QFile;

class GameDownloadThread : public QThread
{
	Q_OBJECT

private:
	qint64 _totalBytes;
	qint64 _bytesReceived;
	qint64 _fileNameSize;

	QString _fileName;
	QFile *_file;
	QByteArray _inBlock;
	QTcpSocket *_tcpSocket;


public:
	GameDownloadThread(QTcpSocket *, QObject *parent = 0);
	~GameDownloadThread();

	public slots:
	void receiveFile();
};


#endif