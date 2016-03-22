#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QString>
#include <QHostAddress>

#include "testserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestServer *server = new TestServer();
    server -> listen(QHostAddress("127.0.0.1"), 1994);

    return a.exec();
}
