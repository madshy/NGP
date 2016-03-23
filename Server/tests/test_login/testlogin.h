#ifndef TESTLOGIN_H
#define TESTLOGIN_H

#include <QObject>
#include <QTcpSocket>

class TestLogin : public QTcpSocket
{
    Q_OBJECT

private:
    bool _logOrReg;

public:
    TestLogin(bool flag = true, QObject *parent = Q_NULLPTR);
    ~TestLogin();

public:
    void login();
    void reg();
    bool testReady();

public slots:
    void readInfo();
    void test();
};

#endif // TESTLOGIN_H
