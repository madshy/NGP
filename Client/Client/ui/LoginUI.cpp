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

/*Qt Layout header*/
#include <qboxlayout.h>
#include <qgridlayout.h>

/*Other header*/
#include <qtcpsocket.h>
#include <qstring.h>

LoginUI::LoginUI(QWidget *parent)
	:QWidget(parent)
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
	_idEdit = new QLineEdit;
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
	_pswEdit = new QLineEdit;
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
	QHBoxLayout *loginBtnLayout = new QHBoxLayout;
	loginBtnLayout->addWidget(_loginBtn);
	loginBtnLayout->addSpacing(30);

	/*Login field layout*/
	QGridLayout *loginFieldLayout = new QGridLayout;
	loginFieldLayout->addLayout(idLayout, 0, 0);
	loginFieldLayout->addLayout(pswLayout, 1, 0);
	loginFieldLayout->addWidget(_errLabel, 2, 0);
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

	/*To eliminate the bug flushing on QLineEdit*/
	_pswEdit->setFrame(false);
	_idEdit->setFrame(false);

	/*connect the signals and slots*/
	connect(_closeBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(_minBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));
}

LoginUI::~LoginUI()
{
}

void LoginUI::login()
{
}

void LoginUI::reg()
{
}