/***************************************************
*
*    @file:MainUI.cpp
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/15
*    @comment:Implement MainUI
*
***************************************************/

/*header*/
#include "../include/MainUI.h"

/*Qt widget header*/
#include <qlabel.h>
#include <qpushbutton.h>
#include <qtreewidget.h>
#include <qtabwidget.h>
#include <qtreeview.h>
#include <qtreewidget.h>
#include <qstandarditemmodel.h>

/*custom widget header*/
#include "../include/CloseButton.h"
#include "../include/MinimizeButton.h"
#include "../include/GameListWidget.h"
#include "../include/GameListItem.h"
#include "../include/AddBuddyWidget.h"
#include "../include/AddGameWidget.h"

/*layout header*/
#include <qboxlayout.h>

/*others*/
#include <qtcpsocket.h>
#include <qstring.h>
#include <qpalette.h>
#include "../include/Account.h"
#include <qbytearray.h>
#include <qdatastream.h>
#include <qlist.h>
#include <qfile.h>
#include <qtextdocument.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qbitmap.h>

#include <qevent.h>
#include <qfiledialog.h>
#include <qprocess.h>

#include "../include/GameDownloadThread.h"
#include "../include/Game.h"

#include <qmessagebox.h>
#include <qhostaddress.h>

//MainUI::MainUI(qintptr socketDescriptor, QWidget *parent)
//	:QWidget(parent), _tcpSocket(), _gameList(nullptr)
//{
//
//}

MainUI::MainUI(qintptr socketDescriptor, Account account, QWidget *parent)
	: QWidget(parent), _tcpSocket(nullptr), _gameList(nullptr), _acc(account), _tcpSocketDownload(nullptr), 
	_totalBytes(0), _bytesReceived(0), _fileNameSize(0),
	_fileName(), _file(nullptr), _inBlock()
{
	point = new QPoint;

	/*init net */
	_tcpSocket = new QTcpSocket;

	/*Actually,  Multiple socket notifiers for same socket and type Read*/
	if (!_tcpSocket->setSocketDescriptor(socketDescriptor))
	{
		qDebug() << "SocketDescriptor invalid.";
	}

	/*logo, close and minimize button*/
	_logoLabel = new QLabel;
	_clsBtn = new CloseButton;
	_minBtn = new MinimizeButton;
	QHBoxLayout *logoLayout = new QHBoxLayout;
	logoLayout->addWidget(_logoLabel);
	logoLayout->addStretch();
	logoLayout->addWidget(_minBtn);
	logoLayout->addWidget(_clsBtn);
	logoLayout->setMargin(0);
	logoLayout->setSpacing(0);

	/*info*/
	_nameLabel = new QLabel(QString::fromLocal8Bit(account.getName().toLocal8Bit()));
	_nationLabel = new QLabel(QString::fromLocal8Bit(account.getNation().toLocal8Bit()));
	QVBoxLayout *nameLayout = new QVBoxLayout;
	nameLayout->addWidget(_nameLabel);
	//nameLayout->addStretch();
	nameLayout->addWidget(_nationLabel);
	nameLayout->setMargin(0);
	nameLayout->setSpacing(0);

	_iconBtn = new QPushButton;
	_iconBtn->setFixedSize(60, 60);
	_iconBtn->setFlat(true);
	_iconBtn->setEnabled(false);

	QPalette palette;
	palette.setBrush(_iconBtn->backgroundRole(), QBrush(QImage(account.getIcon())));
	_iconBtn->setPalette(palette);
	_iconBtn->setAutoFillBackground(true);

	_gameCenterBtn = new QPushButton(QString::fromLocal8Bit("游戏中心"));
	
	QHBoxLayout *infoLayout = new QHBoxLayout;
	infoLayout->addSpacing(5);
	infoLayout->addLayout(nameLayout);
	infoLayout->addWidget(_iconBtn);
	infoLayout->addStretch();
	infoLayout->addWidget(_gameCenterBtn, Qt::AlignVCenter);
	infoLayout->addSpacing(5);

	_buddyGameTabWidget = new QTabWidget;
	_buddyGameTabWidget->setStyleSheet("QTabWidget{border: 0; background-color: rgba(0, 0, 0, 0);}");


	/*QTreeView*/
	//QTreeView *buddyTree = new QTreeView;
	//buddyTree->setStyleSheet("QTreeView{border: 0; background-color: rgba(0, 0, 0, 0);}");
	//QStandardItemModel *buddyStandardModel = new QStandardItemModel;
	//QStandardItem *buddyRootNode = buddyStandardModel->invisibleRootItem();
	//QStandardItem *buddyRootItem = new QStandardItem(QString::fromLocal8Bit("我的好友"));
	//for (QList<QString>::const_iterator citor = account.getBuddys().cbegin();
	//	citor != account.getBuddys().cend(); ++citor)
	//{
	//	buddyRootItem->appendRow(new QStandardItem(*citor));
	//}
	//buddyRootNode->appendRow(buddyRootItem);
	//buddyTree->setModel(buddyStandardModel);
	//buddyTree->setHeaderHidden(true);//hidden the header texted 1 or may be "l"

	/*QTreeWidget*/
	QTreeWidget *buddyTree = new QTreeWidget;
	buddyTree->setObjectName("buddyTree");
	buddyTree->setStyleSheet("QTreeWidget{border: 0; background-color: rgba(0, 0, 0, 0);}");

	buddyTree->setColumnCount(2);
	buddyTree->setColumnHidden(1, true);
	buddyTree->setHeaderHidden(true);

	QTreeWidgetItem *buddyGroup = new QTreeWidgetItem;
	buddyGroup->setText(0, QString::fromLocal8Bit("我的好友"));
	buddyGroup->setText(1, "");

	for (QList<QString>::const_iterator citor = _acc.getBuddys().cbegin();
		citor != _acc.getBuddys().cend(); ++citor)
	{
		QTreeWidgetItem *newBuddy = new QTreeWidgetItem(buddyGroup);
		newBuddy->setText(0, *citor);
		newBuddy->setText(1, "accountID");
	}
	
	buddyTree->addTopLevelItem(buddyGroup);
	connect(buddyTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(startChat(QTreeWidgetItem *, int)));

	QTreeWidget *gameTree = new QTreeWidget;
	gameTree->setObjectName("gameTree");
	gameTree->setStyleSheet("QTreeWidget{border: 0; background-color: rgba(0, 0, 0, 0);}");

	/*not a QTreeWidget but a QTreeView*/
	//QStandardItemModel *gameStandardModel = new QStandardItemModel;
	//QStandardItem *gameRootNode = gameStandardModel->invisibleRootItem();
	//QStandardItem *gameRootItem = new QStandardItem(QString::fromLocal8Bit("我的游戏"));
	//for (QList<QString>::const_iterator citor = account.getGames().cbegin();
	//	citor != account.getGames().cend(); ++citor)
	//{
	//	gameRootItem->appendRow(new QStandardItem(*citor));
	//}
	//gameRootNode->appendRow(gameRootItem);
	//gameTree->setModel(gameStandardModel);
	//gameTree->setHeaderHidden(true);
	//gameTree->setContentsMargins(0, 0, 0, 0);

	/*QTreeWidget*/
	gameTree->setColumnCount(2);
	gameTree->setColumnHidden(1, true);
	gameTree->setHeaderHidden(true);
	QTreeWidgetItem *mygame = new QTreeWidgetItem;
	mygame->setText(0, QString::fromLocal8Bit("我的游戏"));
	mygame->setText(1, "");

	for (QList<Game>::const_iterator citor = _acc.getGames().cbegin();
		citor != _acc.getGames().cend(); ++citor)
	{
		QTreeWidgetItem *newGame = new QTreeWidgetItem(mygame);
		newGame->setText(0, citor->Name);
		newGame->setText(1, citor->DownloadPath);
	}

	gameTree->addTopLevelItem(mygame);
	QTreeWidgetItem *localgame = new QTreeWidgetItem;
	localgame->setText(0, QString::fromLocal8Bit("本地游戏"));
	localgame->setText(1, "");
	gameTree->addTopLevelItem(localgame);

	connect(gameTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(startGame(QTreeWidgetItem *, int)));

	_buddyGameTabWidget->addTab(buddyTree, QString::fromLocal8Bit("伙伴"));
	_buddyGameTabWidget->addTab(gameTree, QString::fromLocal8Bit("游戏"));

	/*add push button*/
	_addBuddyBtn = new QPushButton(QString::fromLocal8Bit("添加好友"));
	_addLocalGameBtn = new QPushButton(QString::fromLocal8Bit("添加本地游戏"));
	_addServerGameBtn = new QPushButton(QString::fromLocal8Bit("添加远程游戏"));
	QHBoxLayout *addLayout = new QHBoxLayout;
	addLayout->addWidget(_addBuddyBtn);
	addLayout->addWidget(_addLocalGameBtn);
	addLayout->addWidget(_addServerGameBtn);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(logoLayout);
	mainLayout->addSpacing(10);
	mainLayout->addLayout(infoLayout);
	mainLayout->addSpacing(10);
	mainLayout->addWidget(_buddyGameTabWidget);
	mainLayout->addLayout(addLayout);

	mainLayout->setMargin(0);

	setLayout(mainLayout);
	setWindowFlags(Qt::FramelessWindowHint);
	//setFixedSize(QSize(250, 700));

	connect(_minBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));
	connect(_clsBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(_gameCenterBtn, SIGNAL(clicked()), this, SLOT(gameCenterRequest()));
	connect(_addBuddyBtn, SIGNAL(clicked()), this, SLOT(addBuddy()));
	connect(_addLocalGameBtn, SIGNAL(clicked()), this, SLOT(addLocalGame()));
	connect(_addServerGameBtn, SIGNAL(clicked()), this, SLOT(addGame()));

	setMouseTracking(true);

	//setStyleSheet("MainUI{background-image: url(:/images/bg_main1.png;)}");
	QPalette paletteMain;
	paletteMain.setBrush(backgroundRole(), QBrush(QImage(":/images/bg_main1.png")));
	setPalette(paletteMain);
	setAutoFillBackground(true);

	setAttribute(Qt::WA_TranslucentBackground);
	backgroundPixmap = new QPixmap;
	backgroundPixmap->load(":/images/bg_main1.png");

	resize(backgroundPixmap->width(), backgroundPixmap->height());
	clearMask();
	setMask(backgroundPixmap->mask());


	update();
	setStyleSheet("color: #708090;");
}

void MainUI::addBuddyRequest()
{

}

void MainUI::addGameRequest()
{

}


void MainUI::gameCenterRequest()
{
	/*
	*request format:
	*blockSize + flag('g')
	*/
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);

	out << quint16(0) << quint8('g');
	out.device()->seek(0);
	out << quint16(block.size() - sizeof(quint16));
	_tcpSocket->write(block);
	connect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(gameCenter()));
}

void MainUI::addBuddy()
{
	AddBuddyWidget *addBuddyWidget = new AddBuddyWidget(_acc.getName(),
		_acc.getNation(), dynamic_cast<QTreeWidget *>(_buddyGameTabWidget->widget(0)));
	addBuddyWidget->show();
}

void MainUI::addLocalGame()
{
	QString gamePath = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择游戏"), "", tr("Files (*.exe)"));
	QString gameName = gamePath.right(gamePath.size() - gamePath.lastIndexOf('/') - 1);
	QString game = gameName.left(gameName.size() - (gameName.size() - gameName.lastIndexOf('.') - 1) - 1);

	qDebug() << "game:" << game;

	QTreeWidget *gameTree = findChild<QTreeWidget *>("gameTree");
	if (!gameTree)
	{
		qDebug() << "Not find the child.";
		return;
	}

	/*not a QTreeWidget but for QTreeView*/
	//QStandardItemModel *model = dynamic_cast<QStandardItemModel *>(gameTree->model());
	//QStandardItem *rootItem = model->invisibleRootItem()->child(0);
	//rootItem->appendRow(new QStandardItem(game));

	/*QTreeWidget*/
	for (int index = 0; index < gameTree->topLevelItemCount(); ++index)
	{
		/*find the target*/
		if (gameTree->topLevelItem(index)->text(0) == QString::fromLocal8Bit("本地游戏"))
		{
			QTreeWidgetItem *gameItem = new QTreeWidgetItem(gameTree->topLevelItem(index));
			gameItem->setText(0, game);
			gameItem->setText(1, gamePath);
			break;
		}

	}

}

void MainUI::addGame()
{
	AddGameWidget *addGameWidget = new AddGameWidget(_acc.getName(),
		_acc.getNation(), dynamic_cast<QTreeWidget *>(_buddyGameTabWidget->widget(1)));
	addGameWidget->show();
}

void MainUI::gameCenter()
{
	disconnect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(gameCenter()));

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

	QString name;
	QString nation;
	QString icon;
	QString desc;
	QString man;
	QString downloadPath;

	QList<GameListItem *> list;



	quint16 size;
	in >> size;
	for (quint16 index = 0; index < size; ++index)
	{
		in >> name >> icon >> nation >> desc >> man >> downloadPath;

		QFile descFile(desc);
		descFile.open(QFile::ReadOnly);
		QTextDocument *descDoc = new QTextDocument;
		descDoc->setHtml(descFile.readAll());

		QFile manFile(man);
		manFile.open(QFile::ReadOnly);
		QTextDocument *manDoc = new QTextDocument;
		manDoc->setHtml(manFile.readAll());

		list.append(new GameListItem(icon, name, nation, descDoc->toHtml(), manDoc->toHtml(), downloadPath));

		descFile.close();
		manFile.close();
	}
	
	if (nullptr != _gameList)
	{
		_gameList->close();
		delete _gameList;
		_gameList = nullptr;
	}
	_gameList = new GameListWidget(&list);

	connect(_clsBtn, SIGNAL(clicked()), this, SLOT(closeGameList()));

	//connect(_gameList, SIGNAL(customCloseSignal()), this, SLOT(onlyMain()));
	//connect(_gameList, SIGNAL(hideDetailSignal()), this, SLOT(noDetail()));
	//connect(_gameList, SIGNAL(showDetailSignal()), this, SLOT(showDetail()));

	//backgroundPixmap->load(":/images/bg_main2.png");
	//resize(backgroundPixmap->width(), backgroundPixmap->height());
	//clearMask();
	//setMask(backgroundPixmap->mask());

	_gameList->setGeometry(geometry().x() + geometry().width(), geometry().y(), _gameList->width(), _gameList->height());
	_gameList->show();

	QHBoxLayout *newLayout = new QHBoxLayout;
	newLayout->addLayout(layout());
	newLayout->addWidget(_gameList);
	newLayout->setMargin(0);

	setLayout(newLayout);

	update();
}

void MainUI::mousePressEvent(QMouseEvent *event)
{
	if (Qt::LeftButton == event->button())
	{
		*point = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
}

void MainUI::mouseMoveEvent(QMouseEvent *event)
{
	/*buttons not button*/
	if (event->buttons() & Qt::LeftButton)
	{
		move(event->globalPos() - *point);
		if (_gameList)
		{
			_gameList->setGeometry(geometry().x() + geometry().width(), geometry().y(), _gameList->width(), _gameList->height());
		}

		event->accept();
	}
}

void MainUI::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(0, 0, backgroundPixmap->width(), backgroundPixmap->height(), *backgroundPixmap);
}

void MainUI::onlyMain()
{
	connect(_clsBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void MainUI::noDetail()
{

}

void MainUI::showDetail()
{

}

void MainUI::closeGameList()
{
	if (_gameList)
	{
		_gameList->close();
		delete _gameList;
		_gameList = nullptr;
	}
}

void MainUI::startGame(QTreeWidgetItem *item, int column)
{
	QString gamePath = item->text(1);
	/*The toplevel, that is group*/
	if ("" == gamePath)
	{
		/*why not item->setExpanded(!item->isExpanded());*/
		item->setExpanded(item->isExpanded());
		return;
	}

	QTreeWidgetItem *parent = item->parent();
	//local game and start play.
	if (QString::fromLocal8Bit("本地游戏") == parent->text(0))
	{
		QProcess *process = new QProcess;
		process->start(gamePath);
		//return;
	}

	//server game and start download.
	if (QString::fromLocal8Bit("我的游戏") == parent->text(0))
	{
		downloadRequest(gamePath);
	}

}

void MainUI::startChat(QTreeWidgetItem *item, int column)
{
	QString gamePath = item->text(1);
	/*The toplevel, that is group*/
	if ("" == gamePath)
	{
		/*why not item->setExpanded(!item->isExpanded());*/
		item->setExpanded(item->isExpanded());
		return;
	}

	/*To chat*/
	
}

void MainUI::downloadRequest(const QString &downloadPath)
{
	if (!_tcpSocketDownload)
	{
		_tcpSocketDownload = new QTcpSocket;
		//_tcpSocketDownload->bind(QHostAddress("192.168.150.1"), 2015);
		_tcpSocketDownload->connectToHost(QHostAddress("192.168.150.1"), 2016);
		connect(_tcpSocketDownload, SIGNAL(readyRead()), this, SLOT(download()));
	}

	QByteArray outBlock;
	QDataStream out(&outBlock, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_6);

	out << downloadPath;
	_tcpSocketDownload->write(outBlock);
}

void MainUI::download()
{
	///*because response readyRead in GameDownloadThread*/
	//disconnect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(download()));

	//(new GameDownloadThread(_tcpSocket, this))->start();

	QDataStream in(_tcpSocketDownload);
	in.setVersion(QDataStream::Qt_5_6);

	if (_bytesReceived <= sizeof(qint64) * 2)
	{
		if ((_tcpSocketDownload->bytesAvailable() >= sizeof(qint64) * 2)
			&& (0 == _fileNameSize))
		{
			in >> _totalBytes >> _fileNameSize;
			_bytesReceived += sizeof(qint64) * 2;
		}

		if ((_tcpSocketDownload->bytesAvailable() >= _fileNameSize)
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
		_bytesReceived += _tcpSocketDownload->bytesAvailable();
		_inBlock = _tcpSocketDownload->readAll();
		_file->write(_inBlock);
		_inBlock.resize(0);
	}



	/****************************why else cause error(can't receive file content.)*********************
	*****************************Why if can receive ok !!!!!!!!!!!!!!!!!!!!!!*************************/
	//else/*Fail to receive file*/
	if (_bytesReceived == _totalBytes)
	{
		if (QMessageBox::Ok == QMessageBox::information(0, QString::fromLocal8Bit("游戏下载"), QString::fromLocal8Bit("下载完成"), QMessageBox::Ok))
		{
			_file->close();
		}
	}
}