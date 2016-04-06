/***************************************************
*
*    @file:InfoEdit.h
*    @author:madshy
*    @mail:madshy@163.com
*    @date:2016/03/28
*    @comment:Inherited from QLineEdit, add two signal to perform changing.
*
***************************************************/

#pragma once

#ifndef INFOEDIT_H
#define INFOEDIT_H

#include <qlineedit.h>

class InfoEdit : public QLineEdit
{
	Q_OBJECT

	/*ctors and dtors*/
public:
	InfoEdit(QWidget *parent = Q_NULLPTR);
	~InfoEdit();

signals:
	/*Get the focus.*/
	void focusGot();
	/*Lose the focus.*/
	void focusLost();

	/*virtual functions inherited from QLineEdit, mainly event functions.*/
protected:
	virtual void focusInEvent(QFocusEvent *event);
	virtual void focusOutEvent(QFocusEvent *event);
};

#endif