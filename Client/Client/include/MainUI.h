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
	QPushButton *_addGameBtn;
	QPushButton *_iconBtn;

	QTabWidget *_buddyGameTabWidget;

	QTcpSocket *_tcpSocket;

	GameListWidget *_gameList;

public:
	MainUI(QTcpSocket *, QWidget *parent = Q_NULLPTR);
	MainUI(QTcpSocket *, const Account &, QWidget *parent = Q_NULLPTR);

	protected slots:
	void addBuddySlot();
	void addGameSlot();
	void gameCenterSlot();

protected:
	MainUI(const MainUI&);
	const MainUI& operator = (const MainUI&);
};

#endif