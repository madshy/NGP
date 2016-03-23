#include "testserver.h"

#include <QDataStream>
#include <QTcpSocket>
#include <QString>
#include <QHostAddress>
#include <QDebug>

TestServer::TestServer(QObject *parent)
    :QTcpServer(parent), tcpSock(Q_NULLPTR)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(process()));
}

TestServer::~TestServer (){}

void TestServer::process()
{
    tcpSock = nextPendingConnection ();
    connect(tcpSock, SIGNAL(readyRead()), this, SLOT(read()));
}

void TestServer::read()
{
    QDataStream in(tcpSock);
    in.setVersion (QDataStream::Qt_5_6);


    if (tcpSock -> bytesAvailable () <= sizeof(quint16))
    {
        qDebug() << "Error block size";
        return ;
    }

    qDebug() << "bytesAvailable(before):" << tcpSock -> bytesAvailable ();

    quint16 size;
    in >> size;
    if (tcpSock -> bytesAvailable () < size)
    {
        qDebug() << "Error block size:no info.";
        return ;
    }

    quint8 flag;
    in >> flag;
    QString user_id, password;
    in >> user_id >> password;

    qDebug() << "user_id:" << user_id;
    qDebug() << "password:" << password;

    qDebug() << tcpSock -> bytesAvailable ();

}
