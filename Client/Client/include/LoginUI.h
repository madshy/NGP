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
class InfoEdit;
class QTcpSocket;
class QString;

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

	InfoEdit *_idEdit;			/*for inputting user id.*/
	InfoEdit *_pswEdit;		/*for inputting user password.*/

	QTcpSocket *_tcpSocket;		/*hold on a connection to server.*/

	bool _loginFlag;				/*true means login ok and false means failed.*/

private:
	/*Initialize the UI components.*/
	void initUI();
	/*Initialize the network*/
	void initNet();

signals:
	void flagOkToRead();

	/*ctors and dtors*/
public:
	LoginUI(QWidget *parent = Q_NULLPTR);
	~LoginUI();

	protected slots:
	/*called when _loginBtn clicked.*/
	void login();
	/*called when _registerBtn clicked.*/
	void reg();
	/*called when _retrieveBtn clicked.*/
	void retrieve();
	/*called when _tcpSocket is ready to be read.*/
	void readInfo();
	/*called when signal flagOkToRead emited.*/
	void result();
	/*called when need to hide error label.*/
	void hideErrLabel();
};


#endif