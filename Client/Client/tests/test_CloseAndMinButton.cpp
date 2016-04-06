/***************************************************
*
*    @file:test_CloseAndMinButton.cpp
*    @author:madshy
*    @mail:madshy@163.com
*    @date:2016/03/25
*    @comment:A test case for close and minmize button.
*
***************************************************/

#include "../include/CloseButton.h"
#include "../include/MinimizeButton.h"

#include "test_CloseAndMinButton.h"

#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qfile.h>
#include <qstring.h>

TestCloseAndMinButton::TestCloseAndMinButton(QWidget *parent)
	:QWidget(parent)
{
	closeBtn = new CloseButton();
	minBtn = new MinimizeButton();
	
	QHBoxLayout *layout = new QHBoxLayout;
	layout->setDirection(QBoxLayout::RightToLeft);

	layout->addWidget(closeBtn);
	layout->addWidget(minBtn);

	setLayout(layout);
	setWindowFlags(Qt::FramelessWindowHint);

	QFile file(":/styles/style.css");
	file.open(QFile::ReadOnly);
	QString styleSheet = tr(file.readAll());
	setStyleSheet(styleSheet);
	
	connect(minBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));
	connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));
}

TestCloseAndMinButton::~TestCloseAndMinButton()
{
}