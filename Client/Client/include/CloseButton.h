/***************************************************
*
*    @file:CloseButton.h
*    @author:madshy
*    @mail:madshy@163.com
*    @date:2016/03/25
*    @comment:A custom Button for closing window.
*
***************************************************/

#pragma once

#ifndef CLOSEBUTTON_H
#define CLOSEBUTTON_H

#include <qpushbutton.h>

/*Custom button for closing window*/
class CloseButton : public QPushButton
{
	Q_OBJECT

	/*ctors and dtors*/
public:
	CloseButton(QWidget *parent = Q_NULLPTR);
	~CloseButton();

	/*virtual functions inherited from QPushButton*/
protected:
	virtual void mousePressEvent(QMouseEvent *event);
};

#endif