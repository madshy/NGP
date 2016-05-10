/***************************************************
*
*    @file:GameListWidget.h
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/06
*    @comment:A list of games.
*450*350
*450*350
*
***************************************************/

#pragma once

#ifndef GAMELISTWIDGET_H
#define GAMELISTWIDGET_H

#include <qwidget.h>
#include <qlist.h>
#include <qbytearray.h>

/*forward declarations.*/
class CloseButton;
class GameDetailWidget;
class QListWidget;
class QListWidgetItem;
class GameListItem;
class QFrame;
class QString;
class QTcpSocket;
class QFile;
class QPixmap;

class GameListWidget : public QWidget
{
	Q_OBJECT 

private:
	CloseButton *_closeBtn;   
	QListWidget *_list;
	GameDetailWidget *_detail;
	QFrame *_frame;
	QTcpSocket *_tcpSocket;

	/*transfer arg*/
	qint64 _totalBytes;
	qint64 _bytesReceived;
	qint64 _fileNameSize;

	QString _fileName;
	QFile *_file;
	QByteArray _inBlock;

	QPixmap *backgroundPixmap;

public:
	GameListWidget(QList<GameListItem *> *, QWidget *parent = Q_NULLPTR);
	~GameListWidget();

	protected slots:
	/*send download request*/
	void downloadRequest(QListWidgetItem *);
	/*receive download file*/
	void download();
	//show detail when an item is clicked.
	void detail(QListWidgetItem *);
	/*
	*Hide the detail widget when an minimize button is clicked.
	*Actually, when signal min is emit.
	*/
	void hideDetail();

	/*custom close actions*/
	void customCloseSlot();

signals:
	void customCloseSignal();
	void showDetailSignal();
	void hideDetailSignal();

protected:
	void paintEvent(QPaintEvent *);
};

#endif