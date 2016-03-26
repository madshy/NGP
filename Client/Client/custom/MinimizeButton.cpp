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