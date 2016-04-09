/***************************************************
*
*    @file:test_GameDetailWidget.h
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/08
*    @comment:A class named TestBtn for testing GameDetailWidget
*
***************************************************/

#pragma once

#ifndef TEST_GAMEDETAILWIDGET_H
#define TEST_GAMEDETAILWIDGET_H

#include <qpushbutton.h>
#include <qwidget.h>

/*forward declarations.*/
class GameDetailWidget;

class TestWidget : public QWidget
{
	Q_OBJECT

public:
	TestWidget(QWidget *parent = 0);

private:
	GameDetailWidget *dtl;
	QPushButton *btn;

	public slots:
	void detail();
};

#endif