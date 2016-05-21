/***************************************************
*
*    @file:GameListWidget.cpp
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/13
*    @comment:Implement GameListWidget
*
***************************************************/

/*qt widget header*/
#include <qlistwidget.h>
#include <qmessagebox.h>

/*layout header*/
#include <qboxlayout.h>

/*custom widget header*/
#include "../include/GameListWidget.h"
#include "../include/CloseButton.h"
#include "../include/GameListItem.h"
#include "../include/GameDetailWidget.h"

/*other widget*/
#include <qfile.h>
#include <qstring.h>
#include <qbytearray.h>
#include <qdatastream.h>
#include <qtcpsocket.h>
#include <qhostaddress.h>
#include <qpainter.h>
#include <qbitmap.h>

#include "../include/GameDownloadThread.h"

GameListWidget::GameListWidget(QList<GameListItem *> *list, QWidget *parent)
	:QWidget(parent), _tcpSocket(nullptr), _totalBytes(0), _bytesReceived(0), _fileNameSize(0),
	_fileName(), _file(nullptr), _inBlock(), backgroundPixmap(nullptr)
{
	/*close Button*/
	_closeBtn = new CloseButton;
	QHBoxLayout *btnLayout = new QHBoxLayout;
	btnLayout->addStretch();
	btnLayout->addWidget(_closeBtn);

	/*list*/
	_list = new QListWidget;
	_list->setViewMode(QListView::IconMode);
	for (QList<GameListItem *>::iterator itor = list->begin(); itor != list->end(); ++itor)
	{
		_list->addItem(*itor);
	}
	_list->setGridSize(QSize(80, 80));
	_list->setIconSize(QSize(60, 60));
	QHBoxLayout *listLayout = new QHBoxLayout;
	listLayout->addSpacing(5);
	listLayout->addWidget(_list);
	listLayout->addSpacing(5);

	/*detail*/
	_detail = new GameDetailWidget;
	_detail->setHidden(true);


	/*layout*/
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(btnLayout);
	mainLayout->addLayout(listLayout);
	mainLayout->addWidget(_detail);
	mainLayout->setMargin(0);

	setLayout(mainLayout);

	/*signals and slots*/
	connect(_closeBtn, SIGNAL(clicked()), this, SLOT(customCloseSlot()));
	connect(_list, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(detail(QListWidgetItem *)));
	connect(_list, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(downloadRequest(QListWidgetItem *)));
	connect(_detail, SIGNAL(min()), this, SLOT(hideDetail()));

	/*set style*/
	QFile file(":/styles/registerStyle.css");
	file.open(QFile::ReadOnly);
	QString styleSheet = QObject::tr(file.readAll());
	setStyleSheet(styleSheet);
	_list->setStyleSheet("QListWidget{border: 0; background-color: rgba(0, 0, 0, 0);}");

	setWindowFlags(Qt::FramelessWindowHint);
	//setFixedSize(450, 350);
	QPalette palette;
	palette.setBrush(backgroundRole(), QBrush(QImage(":/images/bg_list1.png")));
	setPalette(palette);
	setAutoFillBackground(true);

	setAttribute(Qt::WA_TranslucentBackground);

	backgroundPixmap = new QPixmap;
	backgroundPixmap->load(":/images/bg_list1.png");

	resize(backgroundPixmap->width(), backgroundPixmap->height());
	clearMask();
	setMask(backgroundPixmap->mask());

	update();
	//setStyleSheet("GameListWidget{background-image: url(:/images/bg_list1.png;)}");
}

GameListWidget::~GameListWidget()
{

}

void GameListWidget::downloadRequest(QListWidgetItem *item)
{
	if (!_tcpSocket)
	{
		_tcpSocket = new QTcpSocket;
		//_tcpSocket->bind(QHostAddress("192.168.150.1"), 2015);
		_tcpSocket->connectToHost(QHostAddress("192.168.150.1"), 2016);
		connect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(download()));
	}

	GameListItem *gameItem = dynamic_cast<GameListItem *>(item);

	QByteArray outBlock;
	QDataStream out(&outBlock, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);

	out << gameItem->getDownloadPath();
	_tcpSocket->write(outBlock);
}

void GameListWidget::download()
{
	///*because response readyRead in GameDownloadThread*/
	//disconnect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(download()));

	//(new GameDownloadThread(_tcpSocket, this))->start();

	QDataStream in(_tcpSocket);
	in.setVersion(QDataStream::Qt_5_6);

	if (_bytesReceived <= sizeof(qint64) * 2)
	{
		if ((_tcpSocket->bytesAvailable() >= sizeof(qint64) * 2)
			&& (0 == _fileNameSize))
		{
			in >> _totalBytes >> _fileNameSize;
			_bytesReceived += sizeof(qint64) * 2;
		}

		if ((_tcpSocket->bytesAvailable() >= _fileNameSize)
			&& (0 != _fileNameSize))
		{
			in >> _fileName;
			_bytesReceived += _fileNameSize;

			_file = new QFile(_fileName);
			if (!_file->open(QFile::WriteOnly))
			{
				QMessageBox::warning(0, QString::fromLocal8Bit("应用程序"),
					QString::fromLocal8Bit("无法读取文件 %1:\n%2.").arg(_fileName).arg(_file->errorString()));
				return;
			}
		}
		else
		{
			return;
		}
	}


	if (_bytesReceived < _totalBytes)
	{
		_bytesReceived += _tcpSocket->bytesAvailable();
		_inBlock = _tcpSocket->readAll();
		_file->write(_inBlock);
		_inBlock.resize(0);
	}



/****************************why else cause error(can't receive file content.)*********************
*****************************Why if can receive ok !!!!!!!!!!!!!!!!!!!!!!*************************/
	//else/*Fail to receive file*/
	if (_bytesReceived == _totalBytes)
	{
		QMessageBox::information(0, QString::fromLocal8Bit("游戏下载"), QString::fromLocal8Bit("下载完成"), QMessageBox::Ok);
		_file->close();
	}
}


void GameListWidget::detail(QListWidgetItem *item)
{
	GameListItem *gameItem = dynamic_cast<GameListItem *>(item);
	_detail->setDetail(gameItem->getName(), gameItem->getNation(),
		gameItem->getIconPath(), gameItem->getDesc(), gameItem->getMan());
	
	_detail->setHidden(false);
	//setFixedSize(450, 700);
	//QPalette palette;
	//palette.setBrush(backgroundRole(), QBrush(QImage(":/images/bg_list2.png")));
	//setPalette(palette);
	//setAutoFillBackground(true);

	backgroundPixmap->load(":/images/bg_list2.png");

	resize(backgroundPixmap->width(), backgroundPixmap->height());
	clearMask();
	setMask(backgroundPixmap->mask());

	update();
	//setStyleSheet("GameListWidget{background-image: url(:/images/bg_list2.png;)}");

	emit showDetailSignal();
}

void GameListWidget::hideDetail()
{
	_detail->setHidden(true);
	//setFixedSize(450, 350);
	//QPalette palette;
	//palette.setBrush(backgroundRole(), QBrush(QImage(":/images/bg_list1.png")));
	//setPalette(palette);
	//setAutoFillBackground(true);

	//setStyleSheet("GameListWidget{background-image: url(:/images/bg_list1.png;)}");

	backgroundPixmap->load(":/images/bg_list1.png");

	resize(backgroundPixmap->width(), backgroundPixmap->height());
	clearMask();
	setMask(backgroundPixmap->mask());

	update();

	emit hideDetailSignal();
}

void GameListWidget::customCloseSlot()
{
	emit customCloseSignal();
	close();
}

void GameListWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.fillRect(0, 0, backgroundPixmap->width(), backgroundPixmap->height(), *backgroundPixmap);
}