/***************************************************
*
*    @file:AddBuddyWidget.h
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/05/10
*    @comment:At present, two ways to add buddy.
*way.1:by id directly
*way.2:by nation(find the buddys having same nation)
*way.3:by game(find the buddys having same game), not implement now cause game module.
*
*Note:cannot use the class Account, i don't know why.
*
***************************************************/

#pragma once

#ifndef ADDBUDDYWIDGET_H
#define ADDBUDDYWIDGET_H

#include <qwidget.h>
#include <qstring.h>

//#include "../include/Account.h"

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

class AddBuddyWidget : public QWidget
{
	Q_OBJECT

private:
	QListWidget *_choiceList;
	QStackedWidget *_choiceStack;
	QTreeWidget *_buddyTree;
	CloseButton *_closeBtn;
	QTcpSocket *_tcpSocket;
	QLineEdit *_accEdit;
	QPoint *_point;

	//Account _acc;
	QString _accId;
	QString _accNation;


public:
	AddBuddyWidget(const QString &, const QString &, QTreeWidget *buddyTree, QWidget *parent = Q_NULLPTR);

protected:
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);

	private slots:
	void addBuddy();
	void addBuddy(QListWidgetItem *);
	void readReply();

private:
	void addBuddy(const QString &);

};

#endif