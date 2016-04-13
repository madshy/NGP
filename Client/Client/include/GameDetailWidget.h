/***************************************************
*
*    @file:GameDetailWidget.h
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/06
*    @comment:A detail information for given game.
*A question:Where does QPalette can make an effect???
*Only in ctor or a slot signaled by a widget event???
*
***************************************************/

#pragma once

#ifndef GAMEDETAILWIDGET_H
#define GAMEDETAILWIDGET_H

/*forward declarations.*/
class QLabel;
class QTextEdit;
class QString;
class MinimizeButton;

#include <qpushbutton.h>
#include <qwidget.h>

/*setDetail only being  called in ctor or slot signaled by a widget signal can make an effect.*/
class GameDetailWidget : public QWidget
{
	Q_OBJECT

private:
	QPushButton *_iconBtn;
	//QLabel *_iconLabel;
	QLabel *_nameLabel;
	QLabel *_name;
	QLabel *_nationLabel;
	QLabel *_nation;

	//QLabel *_describeLabel;
	//QLabel *_manualLabe;

	//QTextEdit *_describeText;
	//QTextEdit *_manualText;

	QTextEdit *_descManText;

	MinimizeButton *_minBtn;

public:
	GameDetailWidget(QWidget *parent = Q_NULLPTR);
	~GameDetailWidget();

public:
	/*Only being  called in ctor or slot signaled by a widget signal can make an effect.*/
	void setDetail(const QString &name, const QString &nation, const QString &iconPath,
		const QString &desc, const QString &man);

signals:
	void min();

	protected slots:
	/*To emit signal min()*/
	void minSlot();
};

#endif