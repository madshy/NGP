/***************************************************
*
*    @file:GameListItem.h
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/08
*    @comment:A custom list item used in GameListWidget;
*
***************************************************/

#pragma once

#ifndef GAMELISTITEM_H
#define GAMELISTITEM_H

#include <qlistwidget.h>
#include <qstring.h>
#include <qmap.h>

class GameListItem : public QListWidgetItem
{
private:
	QString _iconPath;
	QString _name;
	QString _nation;
	QString _desc;
	QString _man;
	QString _downloadPath;

	QMap<QString, QString> _infoMap;

public:
	GameListItem(
		const QString &iconPath, const QString &name, const QString &nation, 
		const QString &desc, const QString &man, const QString &downloadPath, 
		const QIcon &icon, const QString &text, QListWidget *parent = Q_NULLPTR, int type = UserType);
	~GameListItem();

public:
	/*
	To get the info mapped by given key
	return a 0-length QString if key is meaness.
	*/
	const QString getInfo(const QString &key);

	/*get iconPath*/
	const QString getIconPath();

	/*get name*/
	const QString getName();

	/*get nation*/
	const QString getNation();

	/*get desc*/
	const QString getDesc();

	/*get man*/
	const QString getMan();

	/*get downloadPath*/
	const QString getDownloadPath();
};

#endif