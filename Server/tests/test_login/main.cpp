#include "testlogin.h"

#include <QCoreApplication>
#include <QTcpSocket>
#include <QHostAddress>
#include <QString>
#include <QDataStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*Failed to bind if this two exist at the same time*/
    TestLogin testReg(false);
    if (!testReg.testReady ())
    {
        return 1;
    }



    return a.exec();
}
