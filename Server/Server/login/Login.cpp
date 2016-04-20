/***************************************************
*
*    @file:Login.cpp
*    @author:madshy
*    @mail:madshy@163.com
*    @data:2016/03/22
*    @comment:See in Login.h
*
***************************************************/

#include "../include/Login.h"
#include "../include/LoginServer.h"

#include <qiodevice.h>
#include <qcryptographichash.h>
#include <qbytearray.h>
#include <qdatastream.h>
#include <qdebug.h>



Login::Login(QObject *parent, quintptr sock, const QString& connName)
	:QThread(parent), _sock(sock), _db(QSqlDatabase::database(connName))
{
	_tcpSock = new QTcpSocket();
	_tcpSock->setSocketDescriptor(_sock);
	connect(_tcpSock, SIGNAL(readyRead()), this, SLOT(login()));
	//connect(_tcpSock, SIGNAL(disconnected()), this, SLOT(logout()));
}

Login::~Login()
{
	delete _tcpSock;
}

void Login::run()
{
}

void Login::login()
{
	QDataStream in(_tcpSock);
	in.setVersion(QDataStream::Qt_5_6);

	/*Error occur.*/
	if (_tcpSock -> bytesAvailable() <= sizeof(quint16))
	{
		return;
	}
	quint16 blockSize;
	in >> blockSize;
	if (_tcpSock->bytesAvailable() < blockSize)
	{
		return;
	}

	/*ok to read and reading flag.*/
	quint8 requestType;
	in >> requestType;

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);

	if (!_db.open())
	{
		qDebug() << _db.lastError().text();
		return;
	}

	QSqlQuery query(_db);
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

		QString md5Psw;
		QByteArray bytes;
		bytes = QCryptographicHash::hash(password.toLatin1(), QCryptographicHash::Md5);
		md5Psw.append(bytes.toHex());

		sql += user_id + "' and password = '" + md5Psw + "'";
		if (_db.isOpen())
		{
			query.exec(sql);
			if (query.next())
			{
				/*
				Login success reply format:
				blockSize + flag + user_id + nation + icon.
				*/
				QString nation = query.value("nation").toString();
				QString icon = query.value("icon").toString();

				out << quint16(0) << quint8('o') << user_id << nation << icon;
				out.device()->seek(0);
				out << quint16(block.size() - sizeof(quint16));

				_tcpSock->write(block);

				//connect(_tcpSock, SIGNAL(disconnected()), this, SLOT(logout()));
				LoginServer::OnlineUserList.insert(user_id, QSharedPointer<QTcpSocket>(_tcpSock));
				LoginServer::OnlineHostList.insert(_sock, user_id);
				return;
			}
		}

		/*
		Login fail reply format:
		blockSize + flag.
		*/
		out << quint16(0) << quint8('n');
		out.device()->seek(0);
		out << quint16(block.size() - sizeof(quint16));
		_tcpSock->write(block);
		return;
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

		QString md5Psw;
		QByteArray bytes;
		bytes = QCryptographicHash::hash(password.toLatin1(), QCryptographicHash::Md5);
		md5Psw.append(bytes.toHex());

		if (!_db.isOpen())
		{
			out << quint16(0) << quint8('n');
			out.device()->seek(0);
			out << quint16(block.size() - sizeof(quint16));
			_tcpSock->write(block);
			return;
		}

		sql += user_id + "','" + md5Psw + "','" + nation + "','" + mail + "','" + icon + "')";

		query.exec(sql);

		quint8 flag = query.numRowsAffected() >= 1 ? 'o' : 'n';
		out << quint16(0) << flag;
		out.device()->seek(0);
		out << quint16(block.size() - sizeof(quint16));
		_tcpSock->write(block);
		return;
	}

	/*
	*request buddys format:
	*blockSize + flag('b') + user_id
	*
	*reply format:
	*blockSize + flag('b') + quint16(num) + num QStrings(buddy).
	*num is the number of buddys.
	*/
	case 'b':
	{
		/*read request*/
		QString user_id;
		in >> user_id;

		/*look into database.*/
		QString sql("select * from Buddy where user_id = '");
		sql += user_id + "'";

		if (_db.isOpen())
		{
			quint16 num = 0;
			out << quint16(0) << quint8('b') << quint16(0);
			query.exec(sql);
			while (query.next())
			{
				++num;
				QString buddy = query.value("buddy_id").toString();
				out << buddy;
			}

			out.device()->seek(0);
			out << quint16(block.size() - sizeof(quint16));

			out.device()->seek(3);//what's the number?
			out << quint16(num);

			_tcpSock->write(block);
		}
		return;

	}

	/*default, not defined at present.*/
	default:
		break;
	}
}

void Login::logout()
{
	QTcpSocket *tcpSocket = qobject_cast<QTcpSocket*>(this->sender());
	quintptr sock = tcpSocket->socketDescriptor();
	//delete tcpSocket;
	QString user_id = LoginServer::OnlineHostList[sock];

	LoginServer::OnlineUserList.remove(user_id);
	LoginServer::OnlineHostList.remove(sock);

	/*Broadcast to all.*/
}