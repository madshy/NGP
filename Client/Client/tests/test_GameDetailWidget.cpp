/***************************************************
*
*    @file:test_GameDetailWidget.cpp
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/08
*    @comment:Implement TestBtn
*
***************************************************/

#include "test_GameDetailWidget.h"
#include "../include/GameDetailWidget.h"

#include <qfile.h>
#include <qtextdocument.h>
#include <qtextstream.h>

TestWidget::TestWidget(QWidget *parent)
	:QWidget(parent)
{
	dtl = new GameDetailWidget;
	btn = new QPushButton("btn", this);
	connect(btn, SIGNAL(clicked()), this, SLOT(detail()));
}

void TestWidget::detail()
{
	QFile *desc = new QFile("file/desc.html");
	desc->open(QFile::ReadOnly);
	QTextStream descText(desc);

	QFile *man = new QFile("file/man.html");
	man->open(QFile::ReadOnly);

	QTextDocument *descDoc = new QTextDocument;
	descDoc->setHtml(desc->readAll());
	QTextDocument *manDoc = new QTextDocument;
	manDoc->setHtml(man->readAll());

	dtl->setDetail("three", "miao", ":/icons/users/1.png", descDoc->toHtml(), manDoc->toHtml());
	dtl->show();
}

