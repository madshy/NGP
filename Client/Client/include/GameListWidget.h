/***************************************************
*
*    @file:GameListWidget.h
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/06
*    @comment:A list of games.
*450*350
*450*350
*
***************************************************/

#pragma once

#ifndef GAMELISTWIDGET_H
#define GAMELISTWIDGET_H

#include <qwidget.h>
#include <qlist.h>

/*forward declarations.*/
class CloseButton;
class GameDetailWidget;
class QListWidget;
class QListWidgetItem;
class GameListItem;

class GameListWidget : public QWidget
{
	Q_OBJECT 

private:
	CloseButton *_closeBtn;   
	QListWidget *_list;
	GameDetailWidget *_detail;

public:
	GameListWidget(QList<GameListItem *> *, QWidget *parent = Q_NULLPTR);
	~GameListWidget();

	protected slots:
	//show detail when an item is clicked.
	void detail(QListWidgetItem *);
	/*
	*Hide the detail widget when an minimize button is clicked.
	*Actually, when signal min is emit.
	*/
	void hideDetail();
};

#endif