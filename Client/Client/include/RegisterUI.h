/***************************************************
*
*    @file:RegisterUI.h
*    @author:madshy
*    @mail:madshy@163.com
*    @date:2016/03/29
*    @comment:UI class for register.
*
***************************************************/

#pragma once

#ifndef REGISTERUI_H
#define REGISTERUI_H

#include <qwidget.h>
#include <qstring.h>

/*forward declaration.*/
class InfoEdit;
class QLabel;
class QPushButton;
class QComboBox;
class QFrame;
class QTcpSocket;
class QStackedLayout;
class CloseButton;
class MinimizeButton;
class QListWidgetItem;


/*custom UI for register.*/
class RegisterUI : public QWidget
{
	Q_OBJECT

private:
	QFrame *_frame;

	QLabel *_logoLabel;
	QLabel *_idLabel;
	QLabel *_idCheckLabel;
	QLabel *_pswLabel;
	QLabel *_pswCheckLabel;
	QLabel *_pswConfirmLabel;
	QLabel *_pswConfirmCheckLabel;
	QLabel *_mailLabel;
	QLabel *_mailCheckLabel;
	QLabel *_nationLabel;
	QLabel *_iconLabel;
	QLabel *_errLabel;

	InfoEdit *_idEdit;
	InfoEdit *_pswEdit;
	InfoEdit *_pswConfirmEdit;
	InfoEdit *_mailEdit;

	QComboBox *_nationComboBox;

	QPushButton *_iconBtn;
	QPushButton *_registerBtn;
	QPushButton *_nextPageBtn;
	QPushButton *_prePageBtn;

	QStackedLayout *_stackLayout;

	CloseButton *_closeBtn;
	MinimizeButton *_minBtn;

	QTcpSocket *_tcpSocket;

	bool _idOk;
	bool _pswOk;
	bool _pswConfirmOk;
	bool _mailOk;

	QString _iconPath;
	QString _id;
	QString _psw;

	/*ctors and dtors*/
public:
	RegisterUI(QWidget *parent = Q_NULLPTR);
	~RegisterUI();

private:
	/*init the ui components..*/
	void initUI();

	/*Initialize the network*/
	void initNet();

//signals:
//	void flagOkToRead();

	protected slots:
	/*called when register Button is clicked.*/
	void reg();
	/*called when _tcpSocket is ready to be read after reg btn clicked.*/
	void replyForRegister();
	///*called to read info from server.*/
	//void readInfo();
	///*called when flagOkToRead emitted.*/
	//void result();
	/*called when next page btn clicked.*/
	void nextPage();
	/*called when pre page btn clicked.*/
	void prePage();
	/*called when iconBtn clicked.*/
	void chooseIcon();
	/*called when icon double clicked.*/
	void setIcon(const QString &);

	///*hide functions called when hiding err label.*/
	//void hideIdErrLabel();
	//void hidePswErrLabel();
	//void hidePswConfirmErrLabel();
	//void hideMailErrLabel();

	/*check functions called when editing info.*/
	void checkId();
	void checkPsw();
	void checkPswConfirm();
	void checkMail();
};

#endif