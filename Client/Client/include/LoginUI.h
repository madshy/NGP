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
class CloseButton;
class MinimizeButton;
class QPushButton;
class QLineEdit;

/*Login window class*/
class LoginUI : public QWidget
{
	Q_OBJECT

private:
	QLabel *_iconLabel;			/*show icon*/
	QLabel *_errLabel;			/*show if cannot login.*/

	MinimizeButton *_minBtn;	/*minimize the UI*/
	CloseButton *_closeBtn;		/*close the UI*/
	QPushButton *_registerBtn;	/*login after inputing login info*/
	QPushButton *_retrievePsw;	/*retrieve the password if forgot it.*/
	QPushButton *_loginBtn;		/*begin to login after filled in info.*/

	QLineEdit *_idEdit;			/*for inputting user id.*/
	QLineEdit *_pswEdit;		/*for inputting user password.*/

	/*ctors and dtors*/
public:
	LoginUI(QWidget *parent = Q_NULLPTR);
	~LoginUI();

	protected slots:
	/*called when _loginBtn clicked.*/
	void login();
	/*called when _registerBtn clicked.*/
	void reg();
};


#endif