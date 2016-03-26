/***************************************************
*
*    @file:CloseButton.cpp
*    @author:madshy
*    @mail:madshy@163.com
*    @date:2016/03/25
*    @comment:Implement CloseButton.
*
***************************************************/

#include "../include/CloseButton.h"

CloseButton::CloseButton(QWidget *parent)
	:QPushButton(parent)
{
	setMinimumSize(25, 25);
	setMaximumSize(25, 25);

	setToolTip("Close the window");
	setFlat(true);
}

CloseButton::~CloseButton()
{
}

void CloseButton::mousePressEvent(QMouseEvent *event)
{
	QPushButton::mousePressEvent(event);
}