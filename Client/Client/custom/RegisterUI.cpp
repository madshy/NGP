/***************************************************
*
*    @file:RegisterUI.cpp
*    @author:madshy
*    @mail:madshy@163.com
*    @date:2016/03/30
*    @comment:Implement Reigster UI.
*Addition:size of button is 30*30
*
***************************************************/

#include "../include/RegisterUI.h"

/*Qt Widget header*/
#include <qlabel.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qlistwidget.h>

/*Custom Widget header*/
#include "../include/CloseButton.h"
#include "../include/MinimizeButton.h"
#include "../include/InfoEdit.h"
#include "../include/LoginUI.h"

/*Qt Layout header*/
#include <qboxlayout.h>
#include <qgridlayout.h>
#include <qstackedlayout.h>

/*Other header*/
#include <qtcpsocket.h>
#include <qstring.h>
#include <qdatastream.h>
#include <qbytearray.h>
#include <qhostaddress.h>
#include <qpalette.h>
#include <qframe.h>
#include <qfile.h>
#include <qimage.h>
#include <qpainter.h>
#include <qvalidator.h>
#include <qregexp.h>

RegisterUI::RegisterUI(QWidget *parent)
	:QWidget(parent),
	_idOk(false), _pswOk(false), _pswConfirmOk(false), _mailOk(false),
	_iconPath(":/icons/users/1.png"), _id(), _psw(), _tcpSocket(nullptr)
{
	initUI();

	/*connect the signals and slots*/
	connect(_closeBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(_minBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));
	connect(_registerBtn, SIGNAL(clicked()), this, SLOT(reg()));
	connect(_nextPageBtn, SIGNAL(clicked()), this, SLOT(nextPage()));
	connect(_prePageBtn, SIGNAL(clicked()), this, SLOT(prePage()));
	connect(_iconBtn, SIGNAL(clicked()), this, SLOT(chooseIcon()));
	connect(_idEdit, SIGNAL(focusLost()), this, SLOT(checkId()));
	connect(_pswEdit, SIGNAL(focusLost()), this, SLOT(checkPsw()));
	connect(_pswConfirmEdit, SIGNAL(focusLost()), this, SLOT(checkPswConfirm()));
	connect(_mailEdit, SIGNAL(focusLost()), this, SLOT(checkMail()));


	/*set style*/
	QFile file(":/styles/registerStyle.css");
	file.open(QFile::ReadOnly);
	QString styleSheet = QObject::tr(file.readAll());
	setStyleSheet(styleSheet);
}

RegisterUI::~RegisterUI()
{
}

void RegisterUI::initNet()
{
	/*init the connection.*/
	_tcpSocket = new QTcpSocket();
	if (!_tcpSocket->bind(QHostAddress("127.0.0.1"), 1995))
	{
		qDebug() << "Failed to bind.";
		return;
	}

	_tcpSocket->connectToHost(QHostAddress("127.0.0.1"), 1994);
}

void RegisterUI::initUI()
{
	/*Fixed the size*/
	setMaximumSize(500, 250);
	setMinimumSize(500, 250);
	setWindowFlags(Qt::FramelessWindowHint);

	/*show background image in widget.*/
	_frame = new QFrame(this);
	_frame->setObjectName("frame");
	_frame->setFixedSize(500, 250);

	/*Icon, Minimize button and close button*/
	_logoLabel = new QLabel;
	_minBtn = new MinimizeButton;
	_closeBtn = new CloseButton;

	_logoLabel->setObjectName("logoLabel");

	QHBoxLayout *topLayout = new QHBoxLayout;
	topLayout->setDirection(QBoxLayout::RightToLeft);
	topLayout->addWidget(_closeBtn);
	topLayout->addWidget(_minBtn);
	topLayout->addStretch();
	topLayout->addWidget(_logoLabel);

	topLayout->setMargin(0);
	topLayout->setSpacing(0);

	/*init page*/
	_stackLayout = new QStackedLayout;
	QWidget *page1 = new QWidget(this);
	QWidget *page2 = new QWidget(this);

	/*page1*/
	_idLabel = new QLabel(QString::fromLocal8Bit("账号"));
	_idEdit = new InfoEdit;
	_idCheckLabel = new QLabel(QString::fromLocal8Bit("5-11个字母或数字"));
	_idCheckLabel->setHidden(true);
	//QRegExpValidator *idValidator = new QRegExpValidator(QRegExp("[1-9a-zA-Z][0-9a-zA-Z]{4,10}"), this);
	//_idEdit->setValidator(idValidator);

	_pswLabel = new QLabel(QString::fromLocal8Bit("密码"));
	_pswEdit = new InfoEdit;
	_pswEdit->setEchoMode(QLineEdit::NoEcho);
	_pswCheckLabel = new QLabel(QString::fromLocal8Bit("长度:5-11"));
	_pswCheckLabel->setHidden(true);

	_pswConfirmLabel = new QLabel(QString::fromLocal8Bit("密码确认"));
	_pswConfirmEdit = new InfoEdit;
	_pswConfirmEdit->setEchoMode(QLineEdit::NoEcho);
	_pswConfirmCheckLabel = new QLabel(QString::fromLocal8Bit("密码不一致"));
	_pswConfirmCheckLabel->setHidden(true);


	_nationLabel = new QLabel(QString::fromLocal8Bit("民族"));

	_nationComboBox = new QComboBox;
	_nationComboBox->addItem(QString::fromLocal8Bit("苗"));
	_nationComboBox->addItem(QString::fromLocal8Bit("土家"));
	_nationComboBox->addItem(QString::fromLocal8Bit("汉"));
	_nationComboBox->setCurrentIndex(0);

	_nextPageBtn = new QPushButton;
	_nextPageBtn->setText(QString::fromLocal8Bit("下一页"));
	_nextPageBtn->setEnabled(false);
	//_nextPageBtn->setFixedSize(50, 50);

	QGridLayout *page_1_layout = new QGridLayout;

	page_1_layout->setColumnStretch(0, 1);
	page_1_layout->setColumnStretch(1, 1);
	page_1_layout->setColumnStretch(2, 1);

	page_1_layout->setRowStretch(6, 1);

	page_1_layout->setVerticalSpacing(15);

	/*id*/
	QHBoxLayout *idLayout = new QHBoxLayout;
	idLayout->addSpacing(30);
	idLayout->addWidget(_idLabel, 0, Qt::AlignRight);
	idLayout->addSpacing(5);
	idLayout->addWidget(_idEdit, 1, Qt::AlignLeft);
	page_1_layout->addLayout(idLayout, 0, 1);
	//page_1_layout->addWidget(_idLabel, 0, 0, Qt::AlignRight);
	//page_1_layout->addWidget(_idEdit, 0, 1, Qt::AlignLeft);
	page_1_layout->addWidget(_idCheckLabel, 0, 2, Qt::AlignLeft);


	/*psw*/
	QHBoxLayout *pswLayout = new QHBoxLayout;
	pswLayout->addSpacing(30);
	pswLayout->addWidget(_pswLabel, 0, Qt::AlignRight);
	pswLayout->addSpacing(5);
	pswLayout->addWidget(_pswEdit, 1, Qt::AlignLeft);
	page_1_layout->addLayout(pswLayout, 1, 1);
	//page_1_layout->addWidget(_pswLabel, 1, 0, Qt::AlignRight);
	//page_1_layout->addWidget(_pswEdit, 1, 1, Qt::AlignLeft);
	page_1_layout->addWidget(_pswCheckLabel, 1, 2, Qt::AlignLeft);


	/*psw confirm*/
	QHBoxLayout *pswConfirmLayout = new QHBoxLayout;
	pswConfirmLayout->addWidget(_pswConfirmLabel, 0, Qt::AlignRight);
	pswConfirmLayout->addSpacing(5);
	pswConfirmLayout->addWidget(_pswConfirmEdit, 1, Qt::AlignLeft);
	page_1_layout->addLayout(pswConfirmLayout, 2, 1);
	//page_1_layout->addWidget(_pswConfirmLabel, 2, 0, Qt::AlignRight);
	//page_1_layout->addWidget(_pswConfirmEdit, 2, 1, Qt::AlignLeft);
	page_1_layout->addWidget(_pswConfirmCheckLabel, 2, 2, Qt::AlignLeft);


	/*nation*/
	QHBoxLayout *nationLayout = new QHBoxLayout;
	nationLayout->addSpacing(30);
	nationLayout->addWidget(_nationLabel, 0, Qt::AlignRight);
	nationLayout->addSpacing(5);
	nationLayout->addWidget(_nationComboBox, 1, Qt::AlignLeft);
	page_1_layout->addLayout(nationLayout, 3, 1);
	//page_1_layout->addWidget(_nationComboBox, 3, 1, Qt::AlignLeft);


	/*next btn*/
	page_1_layout->addWidget(_nextPageBtn, 4, 1, Qt::AlignCenter);
	
	page_1_layout->setMargin(0);
	page1->setObjectName("page1");

	page1->setLayout(page_1_layout);

	_stackLayout->addWidget(page1);

	/*page2*/
	_mailLabel = new QLabel(QString::fromLocal8Bit("邮箱"));
	_mailEdit = new InfoEdit;
	_mailCheckLabel = new QLabel(QString::fromLocal8Bit("邮件格式错误"));
	_mailCheckLabel->setHidden(true);

	_iconLabel = new QLabel(QString::fromLocal8Bit("头像"));
	_iconBtn = new QPushButton;
	_iconBtn->setFlat(true);
	_iconBtn->setFixedSize(60, 60);

	QPalette palette;
	palette.setBrush(_iconBtn->backgroundRole(), QBrush(QImage(_iconPath)));
	_iconBtn->setPalette(palette);
	_iconBtn->setAutoFillBackground(true);

	_prePageBtn = new QPushButton;
	_registerBtn = new QPushButton;
	_prePageBtn->setText(QString::fromLocal8Bit("上一页"));
	_registerBtn->setText(QString::fromLocal8Bit("注册"));
	_registerBtn->setEnabled(false);

	//_prePageBtn->setFixedSize(50, 25);
	//_registerBtn->setFixedSize(50, 25);

	QGridLayout *page_2_layout = new QGridLayout;

	page_2_layout->setColumnStretch(0, 1);
	page_2_layout->setColumnStretch(1, 1);
	page_2_layout->setColumnStretch(2, 1);

	page_2_layout->setRowStretch(3, 1);

	page_2_layout->setVerticalSpacing(15);

	/*mail*/
	QHBoxLayout *mailLayout = new QHBoxLayout;
	mailLayout->addWidget(_mailLabel, 0, Qt::AlignRight);
	mailLayout->addSpacing(5);
	mailLayout->addWidget(_mailEdit, 1, Qt::AlignLeft);
	page_2_layout->addLayout(mailLayout, 0, 1);
	//page_2_layout->addWidget(_mailLabel, 0, 0, Qt::AlignRight);
	//page_2_layout->addWidget(_mailEdit, 0, 1, Qt::AlignLeft);
	page_2_layout->addWidget(_mailCheckLabel, 0, 2, Qt::AlignLeft);

	/*icon*/
	QHBoxLayout *iconLayout = new QHBoxLayout;
	iconLayout->addWidget(_iconLabel, 0, Qt::AlignRight | Qt::AlignTop);
	iconLayout->addSpacing(5);
	iconLayout->addWidget(_iconBtn, 1, Qt::AlignLeft);
	page_2_layout->addLayout(iconLayout, 1, 1);
	//page_2_layout->addWidget(_iconLabel, 1, 0, Qt::AlignRight | Qt::AlignTop);
	//page_2_layout->addWidget(_iconBtn, 1, 1, Qt::AlignLeft | Qt::AlignTop);
	
	_errLabel = new QLabel;
	_errLabel->setHidden(true);
	page_2_layout->addWidget(_errLabel, 2, 1);

	/*prePageBtn*/
	QHBoxLayout *btnLayout = new QHBoxLayout;
	btnLayout->addSpacing(35);
	btnLayout->addWidget(_prePageBtn);
	btnLayout->addSpacing(20);
	btnLayout->addWidget(_registerBtn);
	page_2_layout->addLayout(btnLayout, 3, 1, Qt::AlignLeft);

	page2->setLayout(page_2_layout);
	_stackLayout->addWidget(page2);
	_stackLayout->setMargin(0);

	/*main layout*/
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(_stackLayout);
	mainLayout->setMargin(0);

	_idEdit->setFrame(false);
	_pswEdit->setFrame(false);
	_pswConfirmEdit->setFrame(false);
	_mailEdit->setFrame(false);

	setLayout(mainLayout);

	_nextPageBtn->setObjectName("nextPageBtn");
	_iconBtn->setObjectName("iconBtn");
	_prePageBtn->setObjectName("prePageBtn");
	_registerBtn->setObjectName("registerBtn");
}

void RegisterUI::reg()
{
	/*connect to the net.*/
	if (nullptr == _tcpSocket)
	{
		initNet();
	}

	_id = _idEdit->text();
	_psw = _pswEdit->text();
	QString nation = _nationComboBox->currentText();
	QString mail = _mailEdit->text();
	QString icon = _iconPath;

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);

	out << quint16(0) << quint8('r') << _id << _psw << nation << mail << icon;
	out.device()->seek(0);
	out << quint16(block.size() - sizeof(quint16));
	_tcpSocket->write(block);

	connect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(replyForRegister()));
}

void RegisterUI::replyForRegister()
{
	disconnect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(replyForRegister()));

	QDataStream in(_tcpSocket);
	in.setVersion(QDataStream::Qt_5_6);

	quint16 blockSize;
	if (_tcpSocket->bytesAvailable() <= sizeof(quint16))
	{
		qDebug() << "Error size of block.";
		_errLabel->setText(QString::fromLocal8Bit("网络故障"));
		_errLabel->setHidden(false);
		return;
	}

	in >> blockSize;
	if (_tcpSocket->bytesAvailable() < blockSize)
	{
		qDebug() << "No info in block.";
		_errLabel->setText(QString::fromLocal8Bit("网络故障"));
		_errLabel->setHidden(false);
		return;
	}

	quint8 flag;
	in >> flag;

	if (flag == 'o')/*register ok.*/
	{
		_tcpSocket->close();
		//delete _tcpSocket;
		//_tcpSocket = nullptr;
		close();
		(new LoginUI(_id, _psw))->show();
	}
	else/*Failed*/
	{
		_errLabel->setText(QString::fromLocal8Bit("注册失败"));
		_errLabel->setHidden(false);
		return;
	}
}

void RegisterUI::nextPage()
{
	_stackLayout->setCurrentIndex(1);
}

void RegisterUI::prePage()
{
	_stackLayout->setCurrentIndex(0);
}

void RegisterUI::chooseIcon()
{
	QListWidget *iconListWidget = new QListWidget(this);
	iconListWidget->setGridSize(QSize(60, 60));
	iconListWidget->setIconSize(QSize(60, 60));
	iconListWidget->setResizeMode(QListView::Adjust);
	iconListWidget->setViewMode(QListView::IconMode);
	iconListWidget->setMovement(QListView::Static);
	iconListWidget->setContentsMargins(0, 0, 0, 0);
	iconListWidget->setFixedSize(210, 180);
	iconListWidget->setWindowFlags(Qt::FramelessWindowHint);

	for (int index = 1; index <= 10; ++index)
	{
		QString strPath = QString(":/icons/users/%1.png").arg(index);
		iconListWidget->addItem(new QListWidgetItem(QIcon(strPath), QString("%1").arg(index)));
	}
	iconListWidget->show();

	connect(iconListWidget, SIGNAL(currentTextChanged(const QString &)),
		this, SLOT(setIcon(const QString &)));
}

void RegisterUI::setIcon(const QString &currentText)
{
	QListWidget *sender = dynamic_cast<QListWidget*>(this->sender());
	sender->setHidden(true);

	_iconPath = ":/icons/users/" + currentText + ".png";

	QPalette palette;
	palette.setBrush(_iconBtn->backgroundRole(), QBrush(QImage(_iconPath)));
	_iconBtn->setPalette(palette);
	_iconBtn->setAutoFillBackground(true);
}

/*No need to hide for hiding in check func-s.*/
//void RegisterUI::hideIdErrLabel()
//{
//	
//}
//
//void RegisterUI::hidePswErrLabel()
//{
//}
//
//void RegisterUI::hidePswConfirmErrLabel()
//{
//
//}
//
//void RegisterUI::hideMailErrLabel()
//{
//
//}

void RegisterUI::checkId()
{
	QRegExp regExp("[a-zA-Z1-9][a-zA-Z0-9]{4,10}");
	if (-1 == regExp.indexIn(_idEdit->text()))
	{
		QString text =
			"" != _idEdit->text() && '0' == _idEdit->text().at(0) ?
			QString::fromLocal8Bit("不能以0开头") :
			QString::fromLocal8Bit("5-11个字母或数字");

		_idCheckLabel->setText(text);

		_idCheckLabel->setHidden(false);
		_idOk = false;
	}
	else
	{
		_idOk = true;
		_idCheckLabel->setHidden(true);
	}
	
	_nextPageBtn->setEnabled(_idOk && _pswOk && _pswConfirmOk);
}

void RegisterUI::checkPsw()
{
	QRegExp regExp(".{5,11}");
	
	if (-1 == regExp.indexIn(_pswEdit->text()))
	{
		_pswOk = false;
		_pswCheckLabel->setHidden(false);
	}
	else
	{
		_pswOk = true;
		_pswCheckLabel->setHidden(true);
	}

	_nextPageBtn->setEnabled(_idOk && _pswOk && _pswConfirmOk);

}

void RegisterUI::checkPswConfirm()
{
	if (_pswEdit->text() != _pswConfirmEdit->text())
	{
		_pswConfirmOk = false;
		_pswConfirmCheckLabel->setHidden(false);
	}
	else
	{
		_pswConfirmOk = true;
		_pswConfirmCheckLabel->setHidden(true);
	}

	QRegExp regExp(".{5,11}");

	if (-1 == regExp.indexIn(_pswEdit->text()))
	{
		_pswOk = false;
		_pswCheckLabel->setHidden(false);
	}
	else
	{
		_pswOk = true;
		_pswCheckLabel->setHidden(true);
	}

	_nextPageBtn->setEnabled(_idOk && _pswOk && _pswConfirmOk);

}

void RegisterUI::checkMail()
{
	QRegExp regExp("^\\\w+([-+.]\\\w+)*@\\\w+([-.]\\\w+)*\\\.\\\w+([-.]\\\w+)*$");

	if (-1 == regExp.indexIn(_mailEdit->text()))
	{
		_mailOk = false;
		_mailCheckLabel->setHidden(false);
	}
	else
	{
		_mailOk = true;
		_mailCheckLabel->setHidden(true);
	}

	_registerBtn->setEnabled(_idOk && _pswOk && _pswConfirmOk);
}