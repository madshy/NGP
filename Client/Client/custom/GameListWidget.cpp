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

GameListWidget::GameListWidget(QList<GameListItem *> *list, QWidget *parent)
	:QWidget(parent)
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
	connect(_closeBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(_list, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(detail(QListWidgetItem *)));
	connect(_detail, SIGNAL(min()), this, SLOT(hideDetail()));

	/*set style*/
	QFile file(":/styles/registerStyle.css");
	file.open(QFile::ReadOnly);
	QString styleSheet = QObject::tr(file.readAll());
	setStyleSheet(styleSheet);
	_list->setStyleSheet("QListWidget{border: 0; background-color: rgba(0, 0, 0, 0);}");

	setWindowFlags(Qt::FramelessWindowHint);
	setFixedSize(450, 350);
}

GameListWidget::~GameListWidget()
{

}

void GameListWidget::detail(QListWidgetItem *item)
{
	GameListItem *gameItem = dynamic_cast<GameListItem *>(item);
	_detail->setDetail(gameItem->getName(), gameItem->getNation(),
		gameItem->getIconPath(), gameItem->getDesc(), gameItem->getMan());
	
	_detail->setHidden(false);
	setFixedSize(450, 700);
}

void GameListWidget::hideDetail()
{
	_detail->setHidden(true);
	setFixedSize(450, 350);
}