/***************************************************
*
*    @file:AddGameWidget.cpp
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/05/22
*    @comment:Implement AddGameWidget
*
***************************************************/

/*custom widget*/
#include "../include/AddGameWidget.h"
#include "../include/CloseButton.h"

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

AddGameWidget::AddGameWidget(const QString &accId, const QString &accNation, QTreeWidget *buddyTree, QWidget *parent)
	:QWidget(parent), _accId(accId), _accNation(accNation), _gameTree(buddyTree)
{
	_point = new QPoint;

	_closeBtn = new CloseButton;
	QHBoxLayout *btnLayout = new QHBoxLayout;
	btnLayout->addStretch();
	btnLayout->addWidget(_closeBtn);

	_choiceList = new QListWidget;
	_choiceList->addItem(QString::fromLocal8Bit("名字添加"));
	_choiceList->addItem(QString::fromLocal8Bit("民族添加"));
	_choiceList->addItem(QString::fromLocal8Bit("好友添加"));
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
	_gameNameEdit = new QLineEdit;
	_gameNameEdit->setPlaceholderText(QString::fromLocal8Bit("游戏名称"));
	QPushButton *addBtn = new QPushButton(QString::fromLocal8Bit("添加"));
	connect(addBtn, SIGNAL(clicked()), this, SLOT(addGame()));
	QHBoxLayout *accPageLayout = new QHBoxLayout;
	accPageLayout->setAlignment(Qt::AlignHCenter);
	accPageLayout->addWidget(_gameNameEdit);
	accPageLayout->addWidget(addBtn);
	accPage->setLayout(accPageLayout);

	/*nation page*/


	/*game page*/
	//QLabel *gameLabel = new QLabel(QString::fromLocal8Bit("好友游戏添加游戏功能内测ing,敬请期待"), gamePage);

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

	connect(_closeBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(_choiceList, SIGNAL(currentRowChanged(int)), this, SLOT(setCurrentIndexProxy(int)));

	setStyleSheet("QListWidget{border: 0; background-color: rgba(0, 0, 0, 0);}");

}

void AddGameWidget::addGame()
{
	addGame(_gameNameEdit->text());
}

void AddGameWidget::addGame(const QString &Game)
{
	//find group
	for (int indexOut = 0; indexOut < _gameTree->topLevelItemCount(); ++indexOut)
	{
		if (QString::fromLocal8Bit("我的游戏") == _gameTree->topLevelItem(indexOut)->text(0))
		{
			//find exist or not.
			for (int indexIn = 0; indexIn < _gameTree->topLevelItem(indexOut)->childCount(); ++indexIn)
			{
				if (Game == _gameTree->topLevelItem(indexOut)->child(indexIn)->text(0))
				{
					QMessageBox::information(0, QString::fromLocal8Bit("添加结果"),
						QString::fromLocal8Bit("该游戏已经在游戏列表中，无法重复添加"), QMessageBox::Ok);
					return;
				}
			}
			break;
		}
	}


	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);

	out << quint16(0) << quint8('A') << _accId << Game;
	out.device()->seek(0);
	out << quint16(block.size() - sizeof(quint16));

	_tcpSocket->write(block);
}

void AddGameWidget::addGame(QListWidgetItem *item)
{
	addGame(item->text());
}


void AddGameWidget::readReply()
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
	case 'A':
	{
		quint8 flag;
		in >> flag;

		/*fail to add*/
		if ('n' == flag)
		{
			QMessageBox::warning(0, QString::fromLocal8Bit("添加结果"),
				QString::fromLocal8Bit("该游戏不存在"), QMessageBox::Ok);
		}
		/*success*/
		else
		{
			QString gameName, gamePath;
			in >> gameName >> gamePath;

			/*add to the Game list.or refresh*/
			QTreeWidgetItem *group = 
				QString::fromLocal8Bit("我的游戏") == _gameTree->topLevelItem(0)->text(0) ? 
				_gameTree->topLevelItem(0) : _gameTree->topLevelItem(1);
			QTreeWidgetItem *newGame = new QTreeWidgetItem(group);
			newGame->setText(0, gameName);
			newGame->setText(1, gamePath);
			//_buddyTree->update();

			/*QMessageBox::information(0, QString::fromLocal8Bit("添加结果"),
			QString::fromLocal8Bit(("成功添加" + Game + "为好友").toLatin1()), QMessageBox::Ok);*/
			QMessageBox::information(0, QString::fromLocal8Bit("添加结果"),
				QString::fromLocal8Bit("添加成功"), QMessageBox::Ok);
		}
		return;
	}

	case 'N':
	{
		quint16 num;
		in >> num;

		QString game;

		QListWidget *list = dynamic_cast<QListWidget *>(_choiceStack->widget(1));
		list->clear();
		connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(addGame(QListWidgetItem *)));
		list->setStyleSheet("QListWidget{border: 0; background-color: rgba(0, 0, 0, 0);}");
		for (int index = 0; index < num; ++index)
		{
			in >> game;
			list->addItem(new QListWidgetItem(game));
		}

		return;
	}

	//如果只是把这里去掉，而没有修改上面的两次_tcpSocket->write()，则可以进行正常添加
	case 'B':
	{
		quint16 num;
		in >> num;

		QString game;

		QListWidget *list = dynamic_cast<QListWidget *>(_choiceStack->widget(2));
		list->clear();
		connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(addGame(QListWidgetItem *)));
		list->setStyleSheet("QListWidget{border: 0; background-color: rgba(0, 0, 0, 0);}");
		for (int index = 0; index < num; ++index)
		{
			in >> game;
			list->addItem(new QListWidgetItem(game));
		}
		return;
	}

	default:
	{
		return;
	}
	}

}

void AddGameWidget::mousePressEvent(QMouseEvent *event)
{
	if (Qt::LeftButton == event->button())
	{
		*_point = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
}

void AddGameWidget::mouseMoveEvent(QMouseEvent *event)
{
	/*buttons not button*/
	if (event->buttons() & Qt::LeftButton)
	{
		move(event->globalPos() - *_point);
		event->accept();
	}
}

void AddGameWidget::setCurrentIndexProxy(int index)
{

	/*send request*/
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);

	switch (index)
	{
	case 1:
	{
		/*init nation part*/
		out << quint16(0) << quint8('N') << _accId << _accNation;
		out.device()->seek(0);
		out << quint16(block.size() - sizeof(quint16));
		_tcpSocket->write(block);
		break;
	}
	
	case 2:
	{
		out << quint16(0) << quint8('B') << _accId;
		out.device()->seek(0);
		out << quint16(block.size() - sizeof(quint16));
		_tcpSocket->write(block);
		break;
	}
	default:
		break;
	}

	_choiceStack->setCurrentIndex(index);
}