/***************************************************
*
*    @file:GameTransferThread.cpp
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/20
*    @comment:Implement GameTransferThread
*
***************************************************/

#include "../include/GameTransferThread.h"

#include <qstring.h>
#include <qtcpsocket.h>
#include <qbytearray.h>
#include <qdatastream.h>
#include <qfile.h>

GameTransferThread::GameTransferThread(quintptr socketDescriptor, QObject *parent)
	:QThread(parent), _loadSize(4 * 1024)
{
	_tcpSocket = new QTcpSocket;
	_tcpSocket->setSocketDescriptor(socketDescriptor);

	connect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(readRequest()));
}

GameTransferThread::~GameTransferThread()
{
	_tcpSocket->close();
	delete _tcpSocket;
}

void GameTransferThread::readRequest()
{
	QDataStream in(_tcpSocket);
	in.setVersion(QDataStream::Qt_5_6);

	QString gamePath;
	in >> gamePath;

	/*done means client receive ok.*/
	if ("done" == gamePath)
	{
		exit(0);
	}

	transfer(gamePath);
}

void GameTransferThread::transfer(const QString &packagePath)
{
	QFile *localFile = new QFile(packagePath);
	
	localFile->open(QFile::ReadOnly);

	/*real total bytes not total bytes to be sent.*/
	qint64 totalBytes = localFile->size();
	qint64 bytesRemain = 0;

	QByteArray outBlock;
	QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
	sendOut.setVersion(QDataStream::Qt_5_6);

	/*
	*send the header
	*header format:
	*totalSize + fileNameSize + fileName
	*/
	QString currentFile = packagePath.right(packagePath.size() - packagePath.lastIndexOf('/') - 1);
	sendOut << qint64(0) << qint64(0) << currentFile;
	totalBytes += outBlock.size();/*total bytes to be sent.*/
	bytesRemain = totalBytes;
	sendOut.device()->seek(0);
	sendOut << totalBytes << qint64((outBlock.size() - sizeof(qint64) * 2));
	bytesRemain -= _tcpSocket->write(outBlock);

	outBlock.resize(0);

	/*send file content*/
	while (bytesRemain > 0)
	{
		outBlock = localFile->read(bytesRemain > _loadSize ? _loadSize : bytesRemain);
		bytesRemain -= _tcpSocket->write(outBlock);
		outBlock.resize(0);
	}

	localFile->close();
}