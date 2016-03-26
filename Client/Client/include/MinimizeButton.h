/***************************************************
*
*    @file:MinimizeButton.h
*    @author:madshy
*    @mail:madshy@163.com
*    @date:2016/03/25
*    @comment:A custom button for minimizing the window.
*
***************************************************/

#pragma once

#ifndef MINIMIZEBUTTON_H
#define MINIMIZEBUTTON_H

#include <qpushbutton.h>

/*Custom button for minimizing the window*/
class MinimizeButton : public QPushButton
{
	Q_OBJECT

	/*ctors and dtors*/
public:
	MinimizeButton(QWidget *parent = Q_NULLPTR);
	~MinimizeButton();

	/*virtual functions inherited from QPushButton*/
protected:
	virtual void mousePressEvent(QMouseEvent *event);
};

#endif