/***************************************************
*
*    @file:AddBuddyWidget.cpp
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/05/10
*    @comment:Implement AddBuddyWidget
*
***************************************************/

/*custom widget*/
#include "../include/AddBuddyWidget.h"
#include "../include/CloseButton.h"

#include "../include/Account.h"

/*Qt widget*/
#include <qlistwidget.h>
#include <qtreewidget.h>
#include <qstackedwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qmessagebox.h>

/*net work*/
#include <qtcpsocket.h>
#include <qhostaddress.h>

#include <qbytearray.h>
#include <qdatastream.h>

/*other*/
#include <qboxlayout.h>
#include <qevent.h>

AddBuddyWidget::AddBuddyWidget(const QString &accId, const QString &accNation, QTreeWidget *buddyTree, QWidget *parent)
	:QWidget(parent), _accId(accId), _accNation(accNation), _buddyTree(buddyTree)
{
	_point = new QPoint;

	_closeBtn = new CloseButton;
	QHBoxLayout *btnLayout = new QHBoxLayout;
	btnLayout->addStretch();
	btnLayout->addWidget(_closeBtn);

	_choiceList = new QListWidget;
	_choiceList->addItem(QString::fromLocal8Bit("账号添加"));
	_choiceList->addItem(QString::fromLocal8Bit("民族添加"));
	_choiceList->addItem(QString::fromLocal8Bit("兴趣添加"));
	_choiceList->setFixedWidth(60);
	_choiceList->setStyleSheet("QListWidget{border: 0; background-color: rgba(0, 0, 0, 0);}");
	QVBoxLayout *listLayout = new QVBoxLayout;
	listLayout->addStretch();
	listLayout->addWidget(_choiceList);
	listLayout->addStretch();

	_choiceStack = new QStackedWidget;
	QWidget *accPage = new QWidget;
	QWidget *gamePage = new QWidget;
	
	_choiceStack->addWidget(accPage);
	_choiceStack->addWidget(new QListWidget);
	_choiceStack->addWidget(new QListWidget);

	/*acc page*/
	_accEdit = new QLineEdit;
	_accEdit->setPlaceholderText(QString::fromLocal8Bit("好友账号"));
	QPushButton *addBtn = new QPushButton(QString::fromLocal8Bit("添加"));
	connect(addBtn, SIGNAL(clicked()), this, SLOT(addBuddy()));
	QHBoxLayout *accPageLayout = new QHBoxLayout;
	accPageLayout->setAlignment(Qt::AlignHCenter);
	accPageLayout->addWidget(_accEdit);
	accPageLayout->addWidget(addBtn);
	accPage->setLayout(accPageLayout);

	/*nation page*/

	/*game page*/


	QHBoxLayout *widgetLayout = new QHBoxLayout;
	widgetLayout->addLayout(listLayout);
	widgetLayout->addWidget(_choiceStack);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->setMargin(0);
	mainLayout->addLayout(btnLayout);
	mainLayout->addLayout(widgetLayout);

	setLayout(mainLayout);
	setWindowFlags(Qt::FramelessWindowHint);

	_tcpSocket = new QTcpSocket;
	_tcpSocket->connectToHost(QHostAddress("192.168.150.1"), 1994);
	connect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(readReply()));

	/*send request*/
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);

	qDebug() << _accId;
	qDebug() << _accNation;
	out << quint16(0) << quint8('n') << _accId << _accNation;
	out.device()->seek(0);
	out << quint16(block.size() - sizeof(quint16));

	_tcpSocket->write(block);

	connect(_closeBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(_choiceList, SIGNAL(currentRowChanged(int)), _choiceStack, SLOT(setCurrentIndex(int)));

	setStyleSheet("QListWidget{border: 0; background-color: rgba(0, 0, 0, 0);}");

}

void AddBuddyWidget::addBuddy()
{
	addBuddy(_accEdit->text());
}

void AddBuddyWidget::addBuddy(const QString &buddy)
{
	if (buddy == _accId)
	{
		QMessageBox::information(0, QString::fromLocal8Bit("添加结果"),
			QString::fromLocal8Bit("无法添加自己为好友"), QMessageBox::Ok);
		return;
	}

	QTreeWidgetItem *group = _buddyTree->topLevelItem(0);
	for (int index = 0; index < group->childCount(); ++index)
	{
		if (buddy == group->child(index)->text(0))
		{
			QMessageBox::information(0, QString::fromLocal8Bit("添加结果"),
				QString::fromLocal8Bit("该用户已经在好友列表中，无法重复添加"), QMessageBox::Ok);
			return;
		}
	}
	
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);

	out << quint16(0) << quint8('a') << _accId << buddy;
	out.device()->seek(0);
	out << quint16(block.size() - sizeof(quint16));

	_tcpSocket->write(block);
}

void AddBuddyWidget::addBuddy(QListWidgetItem *item)
{
	addBuddy(item->text());
}


void AddBuddyWidget::readReply()
{
	QDataStream in(_tcpSocket);
	in.setVersion(QDataStream::Qt_5_6);

	quint16 blockSize;
	if (_tcpSocket->bytesAvailable() <= sizeof(quint16))
	{
		qDebug() << "Error size of block.";
		return;
	}

	in >> blockSize;
	if (_tcpSocket->bytesAvailable() < blockSize)
	{
		qDebug() << "No info in block.";
		return;
	}
	
	quint8 replyType;
	in >> replyType;
	switch (replyType)
	{
		case 'a':
		{
			quint8 flag;
			in >> flag;
			
			/*fail to add*/
			if ('n' == flag)
			{
				QMessageBox::warning(0, QString::fromLocal8Bit("添加结果"), 
					QString::fromLocal8Bit("输入用户不存在"), QMessageBox::Ok);
			}
			/*success*/
			else
			{
				QString buddy;
				in >> buddy;

				/*add to the buddy list.or refresh*/
				QTreeWidgetItem *group = _buddyTree->topLevelItem(0);
				QTreeWidgetItem *newBuddy = new QTreeWidgetItem(group);
				newBuddy->setText(0, buddy);
				newBuddy->setText(1, "accountID");
				//_buddyTree->update();
				
				/*QMessageBox::information(0, QString::fromLocal8Bit("添加结果"),
					QString::fromLocal8Bit(("成功添加" + buddy + "为好友").toLatin1()), QMessageBox::Ok);*/
				QMessageBox::information(0, QString::fromLocal8Bit("添加结果"),
					QString::fromLocal8Bit("添加成功"), QMessageBox::Ok);
			}
			return;
		}

		case 'n':
		{
			quint16 num;
			in >> num;

			QString buddy;

			QListWidget *list = dynamic_cast<QListWidget *>(_choiceStack->widget(1));
			connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(addBuddy(QListWidgetItem *)));
			list->setStyleSheet("QListWidget{border: 0; background-color: rgba(0, 0, 0, 0);}");
			for (int index = 0; index < num; ++index)
			{
				in >> buddy;
				list->addItem(new QListWidgetItem(buddy));
			}

			return;
		}

		case 'G':
		{
			quint16 num;
			in >> num;

			QString buddy;

			QListWidget *list = dynamic_cast<QListWidget *>(_choiceStack->widget(2));
			connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(addBuddy(QListWidgetItem *)));
			list->setStyleSheet("QListWidget{border: 0; background-color: rgba(0, 0, 0, 0);}");
			for (int index = 0; index < num; ++index)
			{
				in >> buddy;
				list->addItem(new QListWidgetItem(buddy));
			}

			return;
		}

		default:
		{
			return;
		}
	}

}

void AddBuddyWidget::mousePressEvent(QMouseEvent *event)
{
	if (Qt::LeftButton == event->button())
	{
		*_point = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
}

void AddBuddyWidget::mouseMoveEvent(QMouseEvent *event)
{
	/*buttons not button*/
	if (event->buttons() & Qt::LeftButton)
	{
		move(event->globalPos() - *_point);
		event->accept();
	}
}