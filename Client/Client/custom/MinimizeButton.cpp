/***************************************************
*
*    @file:MinimizeButton.cpp
*    @author:madshy
*    @mail:madshy@163.com
*    @date:2016/03/25
*    @comment:Implement MinimizeButton
*
***************************************************/

#include "../include/MinimizeButton.h"

MinimizeButton::MinimizeButton(QWidget *parent)
	:QPushButton(parent)
{
	setMinimumSize(25, 25);
	setMaximumSize(25, 25);

	setStyleSheet("MinimizeButton{"
		"background-image: url(:/images/minimize1.png);}"
		"MinimizeButton:hover{"
		"background-image: url(:/images/minimize2.png);}"
		"MinimizeButton:pressed{"
		"background-image: url(:/images/minimize2.png);}"
		);
	setToolTip("Minimize the window");
	setFlat(true);
}

MinimizeButton::~MinimizeButton()
{
}

void MinimizeButton::mousePressEvent(QMouseEvent *event)
{
	QPushButton::mousePressEvent(event);
}