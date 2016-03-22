#ifndef TESTSERVER_H
#define TESTSERVER_H

#include <QObject>
#include <QTcpServer>

class QTcpSocket;
class TestServer : public QTcpServer
{
    Q_OBJECT

private:
    QTcpSocket *tcpSock;
public:
    TestServer(QObject *parent = 0);
    ~TestServer();

public slots:
    void process();
    void read();
};

#endif // TESTSERVER_H
