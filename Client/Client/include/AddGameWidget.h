/***************************************************
*
*    @file:AddGameWidget.h
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/05/22
*    @comment:At present, two ways to add game.
*way.1:by game name directly
*way.2:by nation(find games belongs to the same nation with user.)
*way.3:by buddy(find games belongs to he/her buddys.), not implement now cause game module.
*
*Note:cannot use the class Account, i don't know why.
*
***************************************************/

#pragma once

#ifndef ADDGAMEWIDGET_H
#define ADDGAMEWIDGET_H

#include <qwidget.h>
#include <qstring.h>

/*forward declarations*/
class QListWidget;
class QStackedWidget;
class QTreeWidget;
class CloseButton;
class QListWidgetItem;
class QTcpSocket;
class QLineEdit;
class QPoint;
//class Account;

class AddGameWidget : public QWidget
{
	Q_OBJECT

private:
	QListWidget *_choiceList;
	QStackedWidget *_choiceStack;
	QTreeWidget *_gameTree;
	CloseButton *_closeBtn;
	QTcpSocket *_tcpSocket;
	QLineEdit *_gameNameEdit;
	QPoint *_point;

	//Account _acc;
	QString _accId;
	QString _accNation;


public:
	AddGameWidget(const QString &, const QString &, QTreeWidget *buddyTree, QWidget *parent = Q_NULLPTR);

protected:
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);

	private slots:
	void addGame();
	void addGame(QListWidgetItem *);
	void readReply();

private:
	void addGame(const QString &);
};

#endif