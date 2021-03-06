/***************************************************
*
*    @file:MainUI.h
*    @author:madshy
*    @mail:madshy@163.com
*    @date:2016/04/06
*    @comment:MainUI is a user interface after successing to login.
*250*700
*
***************************************************/

#pragma once

#ifndef MAINUI_H
#define MAINUI_H

#include <qwidget.h>
#include <qbytearray.h>
#include <qstring.h>

#include "Account.h"

/*forward declarations*/
class QLabel;
class QPushButton;
class QTreeWidget;
class QTabWidget;

class CloseButton;
class MinimizeButton;
class GameListWidget;

class QTcpSocket;

class Account;

class QPoint;
class QPixmap;

class QTreeWidgetItem;

class QFile;

class MainUI : public QWidget
{
	Q_OBJECT

private:
	QLabel *_logoLabel;
	QLabel *_nameLabel;
	QLabel *_nationLabel;
	
	CloseButton *_clsBtn;
	MinimizeButton *_minBtn;

	QPushButton *_gameCenterBtn;
	QPushButton *_addBuddyBtn;
	QPushButton *_addLocalGameBtn;
	QPushButton *_addServerGameBtn;
	QPushButton *_iconBtn;

	QTabWidget *_buddyGameTabWidget;

	QTcpSocket *_tcpSocket;

	GameListWidget *_gameList;

	QPoint *point;
	QPixmap *backgroundPixmap;

	Account _acc;

	/*transfer arg*/
	QTcpSocket *_tcpSocketDownload;
	qint64 _totalBytes;
	qint64 _bytesReceived;
	qint64 _fileNameSize;

	QString _fileName;
	QFile *_file;
	QByteArray _inBlock;

public:
	//MainUI(qintptr, QWidget *parent = Q_NULLPTR);
	MainUI(qintptr, Account, QWidget *parent = Q_NULLPTR);

	protected slots:
	/*send request slot when relative btn clicked.*/
	void addBuddyRequest();
	void addGameRequest();
	void gameCenterRequest();
	/*read reply from server.*/
	void addBuddy();
	void addLocalGame();
	void addGame();
	void gameCenter();

	/*paint background.*/
	void onlyMain();
	void noDetail();
	void showDetail();

	/*close the gameListWidget*/
	void closeGameList();

	/*start the game*/
	void startGame(QTreeWidgetItem *, int);
	/*start the chat*/
	void startChat(QTreeWidgetItem *, int);

	/*send download request*/
	void downloadRequest(const QString &);
	/*receive download file*/
	void download();

protected:
	MainUI(const MainUI&);
	const MainUI& operator = (const MainUI&);

protected:
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void paintEvent(QPaintEvent *);
};

#endif