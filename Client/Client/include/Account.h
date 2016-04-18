/***************************************************
*
*    @file:Account.h
*    @author:madshy
*    @mail:madshy94@163.com
*    @date:2016/04/14
*    @comment:user's information,such as name, nation, nation, 
*buddys, games, and so on.
*
***************************************************/

#pragma once

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <qlist.h>
#include <qstring.h>

class Account
{
private:
	QString _name;
	QString _nation;
	QString _icon;

	QList<QString> _buddyList;
	QList<QString> _gameList;

public:
	Account(const QString&, const QString&, const QString&, const QList<QString>&, const QList<QString>&);

	inline const QString & getName();
	inline const QString & getNation();
	inline const QString & getIcon();

	inline const QList<QString> &getBuddys();
	inline const QList<QString> &getGames();

	inline const QString & getName() const ;
	inline const QString & getNation() const;
	inline const QString & getIcon() const ;

	inline const QList<QString> &getBuddys() const;
	inline const QList<QString> &getGames() const;
};

inline const QString& Account::getName()
{
	return _name;
}

inline const QString& Account::getNation()
{
	return _nation;
}

inline const QString& Account::getIcon()
{
	return _icon;
}

inline const QList<QString>& Account::getBuddys()
{
	return _buddyList;
}

inline const QList<QString>& Account::getGames()
{
	return _gameList;
}

inline const QString& Account::getName() const
{
	return _name;
}

inline const QString& Account::getNation() const
{
	return _nation;
}

inline const QString& Account::getIcon() const
{
	return _icon;
}

inline const QList<QString>& Account::getBuddys() const
{
	return _buddyList;
}

inline const QList<QString>& Account::getGames() const
{
	return _gameList;
}

#endif