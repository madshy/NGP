/***************************************************
*
*    @file:GameDetailWidget.h
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/06
*    @comment:A detail information for given game.
*
***************************************************/

#pragma once

#ifndef GAMEDETAILWIDGET_H
#define GAMEDETAILWIDGET_H

/*forward declarations.*/
class QLabel;
class QTextEdit;
class QTextDocument;
class QString;
class CloseButton;

#include <qpushbutton.h>
#include <qwidget.h>

class GameDetailWidget : public QWidget
{
	Q_OBJECT

private:
	QPushButton *_iconLabel;
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

	CloseButton *_closeBtn;

public:
	GameDetailWidget(const QString &, const QString &, const QString &, 
		QTextDocument *, QTextDocument *, QWidget *parent = Q_NULLPTR);
	~GameDetailWidget();
};




#endif