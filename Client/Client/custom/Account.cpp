/***************************************************
*
*    @file:Account.cpp
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/14
*    @comment:Implement Account.
*
***************************************************/

#include "../include/Account.h"

Account::Account(const QString &name, const QString &nation, const QString &icon,
	const QList<QString> &buddys, const QList<QString> &games)
	:_name(name), _nation(nation), _icon(icon), _buddyList(buddys), _gameList(games)
{
}