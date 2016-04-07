/***************************************************
*
*    @file:GameDetailWidget.cpp
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/06
*    @comment:Implement GameDetailWidget
*450*350
*
***************************************************/

/*Widget header*/
#include <qlabel.h>
#include <qtextedit.h>

/*custom header*/
#include "../include/GameDetailWidget.h"
#include "../include/CloseButton.h"

/*other header*/
#include <qstring.h>
#include <qtextdocument.h>
#include <qpalette.h>
#include <qboxlayout.h>

GameDetailWidget::GameDetailWidget(const QString &name, const QString &nation,
	const QString &iconPath, QTextDocument* describeDoc, QTextDocument *manualDoc, QWidget *parent)
	: QWidget(parent)
{
	/*set icon*/
	/*actually it's a btn look like label.*/
	_iconLabel = new QPushButton; 
	_iconLabel->setFlat(true);
	_iconLabel->setFixedSize(60, 60);
	_iconLabel->setEnabled(false);
	QLabel *l = new QLabel;
	QPalette palette;
	palette.setBrush(_iconLabel->backgroundRole(), QBrush(QImage(iconPath)));
	_iconLabel->setPalette(palette);
	_iconLabel->setAutoFillBackground(true);

	QHBoxLayout *iconLayout = new QHBoxLayout;
	//iconLayout->addStretch();
	iconLayout->addWidget(_iconLabel);
	iconLayout->addStretch();

	/*set name*/
	_nameLabel = new QLabel(QString::fromLocal8Bit("名称:"));
	_name = new QLabel(name);

	QHBoxLayout *nameLayout = new QHBoxLayout;
	nameLayout->addWidget(_nameLabel);
	nameLayout->addWidget(_name, Qt::AlignLeft);

	/*set nation*/
	_nationLabel = new QLabel(QString::fromLocal8Bit("民族:"));
	_nation = new QLabel(nation);

	QHBoxLayout *nationLayout = new QHBoxLayout;
	nationLayout->addWidget(_nationLabel);
	nationLayout->addWidget(_nation, Qt::AlignLeft);

	///*set describe*/
	//_describeLabel = new QLabel(QString::fromLocal8Bit("游戏简介:"));
	//_describeText = new QTextEdit;
	////_describeText->setEnabled(false);
	//_describeText->setAcceptRichText(true);

	//QPalette palette1;
	//palette1.setBrush(QPalette::Base, QBrush(QColor(0, 0, 0, 0)));
	//_describeText->setPalette(palette1);
	//
	//_describeText->setDocument(describeDoc);
	////_describeText->setWindowFlags(Qt::FramelessWindowHint);
	//_describeText->setReadOnly(true);

	///*set manual*/
	//_manualLabe = new QLabel(QString::fromLocal8Bit("游戏规则:"));
	//_manualText = new QTextEdit;
	////_manualText->setEnabled(false);
	////_manualText->setDocument(manualDoc);
	//_manualText->setText(manualDoc->toHtml());
	//_manualText->setWindowModified(false);

	/*set describe and manual*/
	_descManText = new QTextEdit;
	_descManText->setReadOnly(true);
	_descManText->append("<b>" + QString::fromLocal8Bit("游戏简介:") + "</b>");
	_descManText->append(describeDoc->toHtml());
	_descManText->append("");
	_descManText->append("<b>" + QString::fromLocal8Bit("游戏规则:") + "</b>");
	_descManText->append(manualDoc->toHtml());

	/*move the cursor to the start.*/
	_descManText->moveCursor(QTextCursor::Start);

	/*left:info layout*/
	QVBoxLayout *infoLayout = new QVBoxLayout;
	infoLayout->addLayout(iconLayout);
	infoLayout->addLayout(nameLayout);
	infoLayout->addLayout(nationLayout);
	infoLayout->addStretch();

	/*right:text layout*/
	//QVBoxLayout *textLayout = new QVBoxLayout;
	//textLayout->addWidget(_describeLabel);
	//textLayout->addWidget(_describeText);
	//textLayout->addSpacing(15);
	//textLayout->addWidget(_manualLabe);
	//textLayout->addWidget(_manualText);

	/*main layout*/
	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addLayout(infoLayout);
	//mainLayout->addLayout(textLayout);
	mainLayout->addSpacing(15);
	mainLayout->addWidget(_descManText, Qt::AlignLeft);

	/*window layout*/
	QVBoxLayout *windowLayout = new QVBoxLayout;
	_closeBtn = new CloseButton;
	QHBoxLayout *closeLayout = new QHBoxLayout;
	closeLayout->addStretch();
	closeLayout->addWidget(_closeBtn);
	windowLayout->addLayout(closeLayout);
	windowLayout->addLayout(mainLayout);
	windowLayout->setMargin(0);
	windowLayout->setContentsMargins(10, 0, 0, 10);

	setLayout(windowLayout);

	_closeBtn->setStyleSheet("CloseButton{"
		"background-image: url(:/images/close1.png);}"
		"CloseButton:hover{"
		"background-image: url(:/images/close2.png);}"
		"CloseButton:pressed{"
		"background-image: url(:/images/close2.png);}");

	setStyleSheet(
		"QTextEdit{border: 0; background-color: rgba(0, 0, 0, 0);}"
		);

	setWindowFlags(Qt::FramelessWindowHint);
	
	setFixedSize(450, 350);

	connect(_closeBtn, SIGNAL(clicked()), this, SLOT(close()));
}

GameDetailWidget::~GameDetailWidget()
{

}