/***************************************************
*
*    @file:GameListItem.cpp
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/08
*    @comment:Implement GameListItem
*
***************************************************/

#include "../include/GameListItem.h"

GameListItem::GameListItem(
	const QString &iconPath, const QString &name, const QString &nation,
	const QString &desc, const QString &man, const QString &downloadPath, 
	QListWidget *parent, int type)
	:QListWidgetItem(QIcon(iconPath), name, parent, type), 
	_iconPath(iconPath), _name(name), _nation(nation), _desc(desc), _man(man),
	_downloadPath(downloadPath) , _infoMap()
{
	_infoMap.insert("iconPath", _iconPath);
	_infoMap.insert("name", _name);
	_infoMap.insert("nation", _nation);
	_infoMap.insert("desc", _desc);
	_infoMap.insert("man", _man);
	_infoMap.insert("downloadPath", _downloadPath);
}

GameListItem::~GameListItem()
{
}

const QString GameListItem::getInfo(const QString &key)
{
	return _infoMap.value(key);
}

const QString GameListItem::getIconPath()
{
	return _iconPath;
}

const QString GameListItem::getName()
{
	return _name;
}

const QString GameListItem::getNation()
{
	return _nation;
}

const QString GameListItem::getDesc()
{
	return _desc;
}

const QString GameListItem::getMan()
{
	return _man;
}

const QString GameListItem::getDownloadPath()
{
	return _downloadPath;
}