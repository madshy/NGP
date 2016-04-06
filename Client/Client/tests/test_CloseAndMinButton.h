/***************************************************
*
*    @file:test_CloseAndMinButton.h
*    @author:madshy
*    @mail:madshy@163.com
*    @date:2016/03/25
*    @comment:A test case for close and minimize button.
*
***************************************************/

#pragma once

#ifndef TEST_CLOSEANDMINBUTTON_H
#define TEST_CLOSEANDMINBUTTON_H

/*forward declaration*/
class CloseButton;
class MinimizeButton;
class QPushButton;

#include <qwidget.h>

class TestCloseAndMinButton : public QWidget
{
	Q_OBJECT

public:
	TestCloseAndMinButton(QWidget *parent = Q_NULLPTR);
	~TestCloseAndMinButton();

private:
	CloseButton *closeBtn;
	MinimizeButton *minBtn;
};

#endif