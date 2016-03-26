/***************************************************
*
*    @file:LoginUI.h
*    @author:madshy
*    @mail:madshy@163.com
*    @data:2016/03/25
*    @comment:Login user interface.
*
***************************************************/

#pragma once

#ifndef LOGINUI_H
#define LOGINUI_H

#include <qwidget.h>

/*forward declaration*/
class QLabel;
class QPushButton;
class QLineEdit;
class QCheckBox;

/*Login window class*/
class LoginUI : public QWidget
{
	Q_OBJECT

private:
	QLabel *iconLabel;		/*show icon*/

	QPushButton *minBtn;	/*minimize the UI*/
	QPushButton *closeBtn;	/*close the UI*/
	QPushButton *loginBtn;	/*login after inputing login info*/

};


#endif

