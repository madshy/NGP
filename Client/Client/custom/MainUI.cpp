/***************************************************
*
*    @file:MainUI.cpp
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/15
*    @comment:Implement MainUI
*
***************************************************/

/*header*/
#include "../include/MainUI.h"

/*Qt widget header*/
#include <qlabel.h>
#include <qpushbutton.h>
#include <qtreewidget.h>
#include <qtabwidget.h>
#include <qtreeview.h>
#include <qstandarditemmodel.h>

/*custom widget header*/
#include "../include/CloseButton.h"
#include "../include/MinimizeButton.h"
#include "../include/GameListWidget.h"

/*layout header*/
#include <qboxlayout.h>

/*others*/
#include <qtcpsocket.h>
#include <qstring.h>
#include <qpalette.h>
#include "../include/Account.h"

MainUI::MainUI(QTcpSocket *tcpSocket, QWidget *parent)
	:QWidget(parent), _tcpSocket(tcpSocket), _gameList(nullptr)
{

}

MainUI::MainUI(QTcpSocket *tcpSocket, const Account &account, QWidget *parent)
	: QWidget(parent), _tcpSocket(tcpSocket), _gameList(nullptr)
{
	/*logo, close and minimize button*/
	_logoLabel = new QLabel;
	_clsBtn = new CloseButton;
	_minBtn = new MinimizeButton;
	QHBoxLayout *logoLayout = new QHBoxLayout;
	logoLayout->addWidget(_logoLabel);
	logoLayout->addStretch();
	logoLayout->addWidget(_minBtn);
	logoLayout->addWidget(_clsBtn);
	logoLayout->setMargin(0);
	logoLayout->setSpacing(0);

	/*info*/
	_nameLabel = new QLabel(QString::fromLocal8Bit(account.getName().toLocal8Bit()));
	_nationLabel = new QLabel(QString::fromLocal8Bit(account.getNation().toLocal8Bit()));
	QVBoxLayout *nameLayout = new QVBoxLayout;
	nameLayout->addWidget(_nameLabel);
	//nameLayout->addStretch();
	nameLayout->addWidget(_nationLabel);
	nameLayout->setMargin(0);
	nameLayout->setSpacing(0);

	_iconBtn = new QPushButton;
	_iconBtn->setFixedSize(60, 60);
	_iconBtn->setFlat(true);
	_iconBtn->setEnabled(false);

	QPalette palette;
	palette.setBrush(_iconBtn->backgroundRole(), QBrush(QImage(account.getIcon())));
	_iconBtn->setPalette(palette);
	_iconBtn->setAutoFillBackground(true);

	_gameCenterBtn = new QPushButton("center");
	
	QHBoxLayout *infoLayout = new QHBoxLayout;
	infoLayout->addSpacing(5);
	infoLayout->addLayout(nameLayout);
	infoLayout->addWidget(_iconBtn);
	infoLayout->addStretch();
	infoLayout->addWidget(_gameCenterBtn, Qt::AlignVCenter);
	infoLayout->addSpacing(5);

	_buddyGameTabWidget = new QTabWidget;
	QTreeView *buddyTree = new QTreeView;
	QStandardItemModel *buddyStandardModel = new QStandardItemModel;
	QStandardItem *buddyRootNode = buddyStandardModel->invisibleRootItem();
	QStandardItem *buddyRootItem = new QStandardItem(QString::fromLocal8Bit("我的好友"));
	for (QList<QString>::const_iterator citor = account.getBuddys().cbegin();
		citor != account.getBuddys().cend(); ++citor)
	{
		buddyRootItem->appendRow(new QStandardItem(*citor));
	}
	buddyRootNode->appendRow(buddyRootItem);
	buddyTree->setModel(buddyStandardModel);
	buddyTree->setHeaderHidden(true);//hidden the header texted 1 or may be "l"

	QTreeView *gameTree = new QTreeView;
	QStandardItemModel *gameStandardModel = new QStandardItemModel;
	QStandardItem *gameRootNode = gameStandardModel->invisibleRootItem();
	QStandardItem *gameRootItem = new QStandardItem(QString::fromLocal8Bit("我的游戏"));
	for (QList<QString>::const_iterator citor = account.getGames().cbegin();
		citor != account.getGames().cend(); ++citor)
	{
		gameRootItem->appendRow(new QStandardItem(*citor));
	}
	gameRootNode->appendRow(gameRootItem);
	gameTree->setModel(gameStandardModel);
	gameTree->setHeaderHidden(true);

	_buddyGameTabWidget->addTab(buddyTree, QString::fromLocal8Bit("伙伴"));
	_buddyGameTabWidget->addTab(gameTree, QString::fromLocal8Bit("游戏"));

	/*add push button*/
	_addBuddyBtn = new QPushButton(QString::fromLocal8Bit("添加好友"));
	_addGameBtn = new QPushButton(QString::fromLocal8Bit("添加游戏"));
	QHBoxLayout *addLayout = new QHBoxLayout;
	addLayout->addWidget(_addBuddyBtn);
	addLayout->addWidget(_addGameBtn);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(logoLayout);
	mainLayout->addSpacing(10);
	mainLayout->addLayout(infoLayout);
	mainLayout->addSpacing(10);
	mainLayout->addWidget(_buddyGameTabWidget);
	mainLayout->addLayout(addLayout);

	mainLayout->setMargin(0);

	setLayout(mainLayout);
	setWindowFlags(Qt::FramelessWindowHint);
	setFixedSize(QSize(250, 700));

	connect(_minBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));
	connect(_clsBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(_gameCenterBtn, SIGNAL(clicked()), this, SLOT(gameCenterSlot()));
}

void MainUI::addBuddySlot()
{

}

void MainUI::addGameSlot()
{

}

void MainUI::gameCenterSlot()
{

}