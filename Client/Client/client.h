#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets/QMainWindow>
#include "ui_client.h"

class Client : public QMainWindow
{
	Q_OBJECT

public:
	Client(QWidget *parent = 0);
	~Client();

private:
	Ui::ClientClass ui;
};

#endif // CLIENT_H
