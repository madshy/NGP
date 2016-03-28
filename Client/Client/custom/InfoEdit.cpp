/***************************************************
*
*    @file:InfoEdit.cpp
*    @author:madshy
*    @mail:madshy@163.com
*    @date:2016/03/28
*    @comment:Implement InfoEdit.
*
***************************************************/


#include "../include/InfoEdit.h"

InfoEdit::InfoEdit(QWidget *parent)
	:QLineEdit(parent)
{
}

InfoEdit::~InfoEdit()
{
}

void InfoEdit::focusInEvent(QFocusEvent *event)
{
	emit focusGot();
	QLineEdit::focusInEvent(event);
}

void InfoEdit::focusOutEvent(QFocusEvent *event)
{
	emit focusLost();
	QLineEdit::focusOutEvent(event);
}