/***************************************************
*
*    @file:LoginUI.cpp
*    @author:madshy
*    @mail:madshy@163.com
*    @date:2016/03/26
*    @comment:Implement LoginUI
*
***************************************************/

#include "../include/LoginUI.h"

/*Qt Widget header*/
#include <qwidget.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>

/*Custom Widget header*/
#include "../include/CloseButton.h"
#include "../include/MinimizeButton.h"
#include "../include/InfoEdit.h"

/*Qt Layout header*/
#include <qboxlayout.h>
#include <qgridlayout.h>

/*Other header*/
#include <qtcpsocket.h>
#include <qstring.h>
#include <qdatastream.h>
#include <qbytearray.h>
#include <qhostaddress.h>

LoginUI::LoginUI(QWidget *parent)
	:QWidget(parent), _loginFlag(false)
{
	initNet();
	initUI();

	/*connect the signals and slots*/
	connect(_closeBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(_minBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));
	connect(_registerBtn, SIGNAL(clicked()), this, SLOT(reg()));
	connect(_retrievePsw, SIGNAL(clicked()), this, SLOT(retrieve()));
	connect(_loginBtn, SIGNAL(clicked()), this, SLOT(login()));
	connect(this, SIGNAL(flagOkToRead()), this, SLOT(result()));
	connect(_idEdit, SIGNAL(focusGot()), this, SLOT(hideErrLabel()));
	connect(_pswEdit, SIGNAL(focusGot()), this, SLOT(hideErrLabel()));
}

LoginUI::~LoginUI()
{
}

void LoginUI::initUI()
{
	/*Fixed the size*/
	setMaximumSize(500, 250);
	setMinimumSize(500, 250);

	/*Icon, Minimize button and close button*/
	_iconLabel = new QLabel;
	_minBtn = new MinimizeButton;
	_closeBtn = new CloseButton;

	_iconLabel->setObjectName("iconLabel");

	QHBoxLayout *topLayout = new QHBoxLayout;
	topLayout->setDirection(QBoxLayout::RightToLeft);
	topLayout->addWidget(_closeBtn);
	topLayout->addWidget(_minBtn);
	topLayout->addStretch();
	topLayout->addWidget(_iconLabel);

	topLayout->setMargin(0);
	topLayout->setSpacing(0);

	/*Register button and id input widget*/
	_registerBtn = new QPushButton;
	_idEdit = new InfoEdit;
	_registerBtn->setFixedSize(30, 30);
	_registerBtn->setFlat(true);
	_idEdit->setFixedHeight(30);

	QHBoxLayout *idLayout = new QHBoxLayout;
	idLayout->setDirection(QBoxLayout::LeftToRight);
	idLayout->addWidget(_idEdit);
	idLayout->setSpacing(0);
	idLayout->addWidget(_registerBtn);
	idLayout->addSpacing(30);

	_idEdit->setFont(QFont("Times", 12));
	_idEdit->setPlaceholderText("account");

	/*Retrieve and password input widget*/
	_retrievePsw = new QPushButton;
	_pswEdit = new InfoEdit;
	_retrievePsw->setFixedSize(30, 30);
	_retrievePsw->setFlat(true);
	_pswEdit->setFixedHeight(30);
	_pswEdit->setPlaceholderText("password");

	QHBoxLayout *pswLayout = new QHBoxLayout;
	pswLayout->setDirection(QBoxLayout::LeftToRight);
	pswLayout->addWidget(_pswEdit);
	pswLayout->setSpacing(0);
	pswLayout->addWidget(_retrievePsw);
	pswLayout->addSpacing(30);

	_pswEdit->setFont(QFont("Times", 12));
	_pswEdit->setEchoMode(QLineEdit::NoEcho);

	/*Login button and error label.*/
	_loginBtn = new QPushButton;
	_errLabel = new QLabel(QObject::tr("Failed to login."));
	_loginBtn->setFixedHeight(45);
	_errLabel->setFixedHeight(25);
	_errLabel->setHidden(true);

	QHBoxLayout *errLabelLayout = new QHBoxLayout;
	errLabelLayout->addWidget(_errLabel);
	errLabelLayout->addSpacing(30);

	QHBoxLayout *loginBtnLayout = new QHBoxLayout;
	loginBtnLayout->addWidget(_loginBtn);
	loginBtnLayout->addSpacing(30);

	/*Login field layout*/
	QGridLayout *loginFieldLayout = new QGridLayout;
	loginFieldLayout->addLayout(idLayout, 0, 0);
	loginFieldLayout->addLayout(pswLayout, 1, 0);
	loginFieldLayout->addLayout(errLabelLayout, 2, 0);
	loginFieldLayout->addLayout(loginBtnLayout, 3, 0);
	loginFieldLayout->setMargin(30);

	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->setDirection(QBoxLayout::RightToLeft);
	bottomLayout->addLayout(loginFieldLayout);
	bottomLayout->addStretch();

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->setDirection(QBoxLayout::TopToBottom);
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(bottomLayout);
	mainLayout->addStretch();

	mainLayout->setMargin(0);

	setLayout(mainLayout);
	setWindowFlags(Qt::FramelessWindowHint);

	_loginBtn->setObjectName("loginBtn");
	_errLabel->setObjectName("errLabel");

	/*To eliminate the bug flushing on QLineEdit*/
	_pswEdit->setFrame(false);
	_idEdit->setFrame(false);


}

void LoginUI::initNet()
{
	/*init the connection.*/
	_tcpSocket = new QTcpSocket();
	if (!_tcpSocket->bind(QHostAddress("127.0.0.1"), 1995))
	{
		qDebug() << "Failed to bind.";
		return;
	}

	_tcpSocket->connectToHost(QHostAddress("127.0.0.1"), 1994);
}

void LoginUI::login()
{
	connect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(readInfo()));

	QString id = _idEdit->text();
	QString psw = _pswEdit->text();

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);

	out << quint16(0) << quint8('l') << id << psw;
	out.device()->seek(0);
	out << quint16(block.size() - sizeof(quint16));
	_tcpSocket->write(block);
}

void LoginUI::reg()
{

}

void LoginUI::retrieve()
{

}

void LoginUI::readInfo()
{
	disconnect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(readInfo()));

	_loginFlag = false;

	QDataStream in(_tcpSocket);
	in.setVersion(QDataStream::Qt_5_6);

	quint16 blockSize;
	if (_tcpSocket->bytesAvailable() <= sizeof(quint16))
	{
		qDebug() << "Error size of block.";
		emit flagOkToRead();
		return;
	}

	in >> blockSize;
	if (_tcpSocket->bytesAvailable() < blockSize)
	{
		qDebug() << "No info in block.";
		emit flagOkToRead();
		return;
	}

	quint8 flag;
	in >> flag;

	_loginFlag = flag == 'o';
	emit flagOkToRead();
}

void LoginUI::result()
{
	if (!_loginFlag)/*Failed.*/
	{
		_errLabel->show();
	}
	else/*Ok to login and go to logined ui.*/
	{

	}
}

void LoginUI::hideErrLabel()
{
	_errLabel->setHidden(true);
}