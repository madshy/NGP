/***************************************************
*
*    @file:GameDetailWidget.cpp
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/06
*    @comment:Implement GameDetailWidget
*450*350
*
***************************************************/

/*Widget header*/
#include <qlabel.h>
#include <qtextedit.h>

/*custom header*/
#include "../include/GameDetailWidget.h"

/*other header*/
#include <qstring.h>
#include <qtextdocument.h>
#include <qpalette.h>

GameDetailWidget::GameDetailWidget(const QString &name, const QString &nation,
	const QString &iconPath, QTextDocument* describeDoc, QTextDocument *manualDoc, QWidget *parent)
	: QWidget(parent)
{

}

GameDetailWidget::~GameDetailWidget()
{

}