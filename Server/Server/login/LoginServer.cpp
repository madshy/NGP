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
#include "qbytearray.h"
#include "qdatastream.h"

#include <qiodevice.h>

/*static membership*/
QMap<QString, quint32> LoginServer::OnlineUserList;
QMap<quint32, QString> LoginServer::OnlineHostList;

LoginServer::LoginServer(const QHostAddress &addr, quint16 port)
	:_addr(addr), _port(port)
{
	_server = new QTcpServer();
	connect(_server, SIGNAL(newConnection()), this, SLOT(login()));
}

/*
Is there should be delete a pointer of QObject?
*/
LoginServer::~LoginServer()
{
	if (_server)
	{
		delete _server;
	}
	_server = nullptr;
}

void LoginServer::run()
{
	_server -> listen(_addr, _port);
}


void LoginServer::login()
{
	quintptr sock = _server->nextPendingConnection()->socketDescriptor();
	/*new a Login, actually a thread to login*/
	Login(sock, Database()).start();
}


/*****************Inner class*********************/


LoginServer::Login::Login(quintptr sock, const Database& db)
	:_sock(sock), _db(db)
{
}

LoginServer::Login::~Login()
{
}

void LoginServer::Login::run()
{
	QTcpSocket tcpSocket;
	tcpSocket.setSocketDescriptor(_sock);

	QDataStream in(&tcpSocket);
	in.setVersion(QDataStream::Qt_5_6);
	
	/*Error occur.*/
	if (tcpSocket.bytesAvailable() <= sizeof(quint16))
	{
		return;
	}
	quint16 blockSize;
	in >> blockSize;
	if (tcpSocket.bytesAvailable <= blockSize)
	{
		return;
	}

	/*ok to read and reading flag.*/
	quint8 requestType;
	in >> requestType;

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);
	
	/*login*/
	switch (requestType)
	{
		/*
		Login:
		Format:
		Success:blockSize + flag + user_id + password.
		*/

	case 'l':
	{
		QString user_id;
		QString password;
		QString sql("select * from user where user_id = '");

		in >> user_id >> password;
		sql += user_id + "' and password = '" + password + "'";
		if (_db.connect())
		{
			QSqlQuery query = _db.select(sql);
			if (query.next())
			{
				/*
				Login success reply format:
				blockSize + flag + nation + icon.
				*/
				QString nation = query.value("nation").toString();
				QString icon = query.value("icon").toString();

				out << quint16(0) << quint8('o') << nation << icon;
				out.device()->seek(0);
				out << quint16(block.size() - sizeof(quint16));

				tcpSocket.write(block);
				return;
			}	
		}
		else
		{
			/*
			Login fail reply format:
			blockSize + flag.
			*/
			out << quint16(0) << quint8('n');
			out.device()->seek(0);
			out << quint16(block.size() - sizeof(quint16));
			tcpSocket.write(block);
			return;
		}
	}

		/*
		Register
		Format:
		blockSize + flag + user_id + password + nation + mail + icon

		reply format:
		blockSize + flag.
		flag 'o' ok, 'n' not ok.
		*/
	case 'r':
	{
		QString user_id;
		QString password;
		QString nation;
		QString mail;
		QString icon;
		QString sql("insert into user values('");

		in >> user_id >> password >> nation >> mail >> icon;
		
		if (!_db.connect())
		{
			out << quint16(0) << quint8('n');
			out.device()->seek(0);
			out << quint16(block.size() - sizeof(quint16));
			tcpSocket.write(block);
			return;
		}

		sql += user_id + "','" + password + "','" + nation + "','" + mail + "','" + icon + "')";
		quint8 flag = _db.insert(sql) ? 'o' : 'n';
		out << quint16(0) << flag;
		out.device()->seek(0);
		out << quint16(block.size() - sizeof(quint16));
		tcpSocket.write(block);
		return;

	}

		/*default, not defined at present.*/
	default:
		
	}


}