/***************************************************
*
*    @file:GameDownloadThread.cpp
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/21
*    @comment:Implement GameDownloadThread
*
***************************************************/

#include "../include/GameDownloadThread.h"

#include <qtcpsocket.h>
#include <qfile.h>
#include <qdatastream.h>
#include <qmessagebox.h>

GameDownloadThread::GameDownloadThread(QTcpSocket *tcpSocket, QObject *parent)
	:QThread(parent), _tcpSocket(tcpSocket), _totalBytes(0), _bytesReceived(0), _fileNameSize(0),
	_fileName(), _file(nullptr), _inBlock()
{
	QDataStream in(_tcpSocket);
	in.setVersion(QDataStream::Qt_5_6);

	if ((_tcpSocket->bytesAvailable() >= sizeof(qint64) * 2)
		&& (0 == _fileNameSize))
	{
		in >> _totalBytes >> _fileNameSize;
		_bytesReceived += sizeof(qint64) * 2;
	}

	if ((_tcpSocket->bytesAvailable() >= _fileNameSize)
		&& (0 != _fileNameSize))
	{
		in >> _fileName;
		_bytesReceived += _fileNameSize;
		
		_file = new QFile(_fileName);
		if (!_file->open(QFile::WriteOnly))
		{
			QMessageBox::warning(0, QString::fromLocal8Bit("应用程序"),
				QString::fromLocal8Bit("无法读取文件 %1:\n%2.").arg(_fileName).arg(_file->errorString()));
			return;
		}
	}
}

GameDownloadThread::~GameDownloadThread()
{

}

void GameDownloadThread::receiveFile()
{
	if (_bytesReceived < _totalBytes)
	{
		_bytesReceived += _tcpSocket->bytesAvailable();
		_inBlock = _tcpSocket->readAll();
		_file->write(_inBlock);
		_inBlock.resize(0);
	}
	else
	{
		QMessageBox::information(0, QString::fromLocal8Bit("游戏下载"), QString::fromLocal8Bit("下载完成"), QMessageBox::Ok);
		_file->close();
		exit(0);
	}
}