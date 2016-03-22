#include "testlogin.h"

#include <qDebug>
#include <QDataStream>
#include <QString>
#include <QByteArray>
#include <QHostAddress>

TestLogin::TestLogin(bool flag, QObject *parent)
    :QTcpSocket(parent), _logOrReg(flag)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readInfo()));
    connect(this, SIGNAL(connected()), this, SLOT(test()));
}

TestLogin::~TestLogin()
{
}

void TestLogin::login()
{
    qDebug() << "Login now........";

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion (QDataStream::Qt_5_6);

    out << quint16(0) << quint8('l') << QString("shy") << QString("123456");
    out.device () -> seek(0);
    qDebug() << "blockSize:" << block.size();
    out << quint16(block.size() - sizeof(quint16));
    this -> write(block);

    qDebug() << "Login information is sent compeletely.";
}

void TestLogin::reg()
{
    qDebug() << "Register now.......";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion (QDataStream::Qt_5_6);

    out << quint16(0) << quint8('r') << QString("shy") << QString("123456") << QString("miao")
        << QString("youjian") << QString("touxiang");
    out.device () -> seek(0);
    out << quint16(block.size() - sizeof(quint16));
    qDebug() << block.size();
    write(block);
    flush ();
}

bool TestLogin::testReady ()
{
    if (!bind(QHostAddress("127.0.0.1"), 1995))
    {
        qDebug() << "Failed to bind.";
        return false;
    }

    connectToHost(QHostAddress("127.0.0.1"), 1994);
    return true;

}

void TestLogin::readInfo ()
{
    QDataStream in(this);
    in.setVersion (QDataStream::Qt_5_6);

    quint16 blockSize;
    if (bytesAvailable () <= sizeof(quint16))
    {
        qDebug() << "Error size of block.";
        return ;
    }

    in >> blockSize;
    if (bytesAvailable () < blockSize)
    {
        qDebug() << "No info in block.";
        return;
    }

    quint8 flag;
    in >> flag;

    QString result = !_logOrReg ? "Login " : "Register ";
    result += flag == 'o' ? "Ok!" : "Failed.";
    qDebug() << result;

}

void TestLogin::test()
{
    qDebug() << "Connecte success and to perform login or register......";
    _logOrReg ? reg() : login();
}
