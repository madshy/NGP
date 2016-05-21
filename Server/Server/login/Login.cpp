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
	*blockSize + flag('b') + quint16(num1) + quint16(num2)+ num QStrings(buddy) + num2 Game(QString, QString).
	*num is the number of buddys.
	*/
	case 'b':
	{
		/*read request*/
		QString user_id;
		in >> user_id;

		if (_db.isOpen())
		{
			/*look into database.*/
			QString sql("select * from Buddy where user_id = '");
			sql += user_id + "'";

			quint16 numBuddy = 0;
			quint16 numGame = 0;
			out << quint16(0) << quint8('b') << quint16(0) << quint16(0);
			query.exec(sql);
			while (query.next())
			{
				++numBuddy;
				QString buddy = query.value("buddy_id").toString();
				out << buddy;
			}

			sql = "select name, d_load_path from Game where game_id in ("
				"select game_id from User_game where user_id = '";
			sql += user_id + "')";

			QString gameName;
			QString downloadPath;
			query.exec(sql);
			while (query.next())
			{
				++numGame;
				gameName = query.value("name").toString();
				downloadPath = query.value("d_load_path").toString();
				out << gameName << downloadPath;
			}

			out.device()->seek(0);
			out << quint16(block.size() - sizeof(quint16));

			out.device()->seek(3);//what's the number?
			out << quint16(numBuddy);

			out << quint16(numGame);

			_tcpSock->write(block);
		}
		return;

	}

	/*
	*game center request.
	*request format:
	*blockSize + flag('g')
	*
	*reply format:
	*blockSize + num + (name + iconPath + nation + descPath + manPath + downloadPath).....
	*/
	case 'g':
	{
		/*look into database.*/
		QString sql("select * from Game");

		if (_db.isOpen())
		{
			quint16 num = 0;
			out << quint16(0) << quint16(0);
			QString name;
			QString nation;
			QString icon;
			QString desc;
			QString man;
			QString downloadPath;
			query.exec(sql);
			while (query.next())
			{
				++num;
				
				name = query.value("name").toString();
				nation = query.value("nation").toString();
				icon = query.value("icon").toString();
				desc = query.value("desc_path").toString();
				man = query.value("man_path").toString();
				downloadPath = query.value("d_load_path").toString();

				out << name << icon << nation << desc << man << downloadPath;
			}

			out.device()->seek(0);
			out << quint16(block.size() - sizeof(quint16));

			out.device()->seek(2);//what's the number?
			out << quint16(num);

			_tcpSock->write(block);
		}
		return;
	}

	/*
	*Add buddy request
	*Format:
	*blockSize + flag('a') + id1 + id2
	*id1 add id2 to his buddy.
	*
	*Reply format:
	*blockSize + flag1('a') + flag2 + buddy(optional)
	*flag2:'o' success while 'n' fail.
	*if flag2 is 'n',no buddy
	*if flag2 is 'o',buddy must be there.
	*/
	case 'a':
	{
		QString id1, id2;
		in >> id1 >> id2;

		if (_db.isOpen())
		{
			QString findBuddySql("select user_id from User where user_id = '");
			findBuddySql += id2 + "'";

			query.exec(findBuddySql);

			/*not find the buddy, it's not a existing user.*/
			if (!query.next())
			{
				out << quint16(0) << quint8('a') << quint8('n');
				out.device()->seek(0);
				out << quint16(block.size() - sizeof(quint16));
				_tcpSock->write(block);
			}
			/*find the buddy and execute add operation*/
			else
			{
				query.exec("insert into Buddy(user_id, buddy_id) values('" + id1 + "','" + id2 + "')");
				query.exec("insert into Buddy(user_id, buddy_id) values('" + id2 + "','" + id1 + "')");
				
				out << quint16(0) << quint8('a') << quint8('o') << id2;
				out.device()->seek(0);
				out << quint16(block.size() - sizeof(quint16));
				_tcpSock->write(block);
			}
		}
		return;
	}

	/*
	*Buddy Candidate request(nation)
	*format:
	*blockSize + flag('n') + id + nation
	*
	*Reply format:
	*blockSize + flag('n') + num(n) + buddy1 + buddy2 + ... + buddyn
	*/
	case 'n':
	{
		if (_db.isOpen())
		{
			quint16 num = 0;
			QString id;
			QString nation;
			in >> id >> nation;

			out << quint16(0) << quint8('n') << num;

			query.exec("select user_id from User "
				"where nation = '" + nation + "'"
				+ " and user_id != '" + id + "'"
				+ " and user_id not in "
				+ "(select buddy_id from buddy "
				"where user_id = '" + id + "')");
			while (query.next())
			{
				++num;
				out << query.value("user_id").toString();
			}

			out.device()->seek(0);
			out << quint16(block.size() - sizeof(quint16));

			out.device()->seek(3);//what's the number?
			out << quint16(num);

			_tcpSock->write(block);
		}
		return;
	}

	/*
	*Buddy Candidate request(game)
	*format:
	*blockSize + flag('G') + game1 + game2 + ... + gamen
	*
	*Reply format:
	*blockSize + flag('G') + gameNum(n) + gameName1 + buddyNum(m) + buddy1 + ... + buddym
	*+ ... + gameNamen + buddyNum(m) + buddy1 + ... + buddym.
	*/
	case 'G':
	{
		//not implement yet.
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