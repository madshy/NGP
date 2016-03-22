/***************************************************
*
*    @file:Login.h
*    @author:madshy
*    @mail:madshy@163.com
*    @data:2016/03/22
*    @comment:A new Class Cause meta object features not supported for nested classes.
*
***************************************************/

#pragma once

#ifndef LOGIN_H
#define LOGIN_H

#include "Database.h"

#include <qthread.h>

/*Login manager.*/
class Login : public QThread
{
	Q_OBJECT

		/*memberships*/
private:
	quintptr _sock;
	Database _db;

	/*ctors and dtors*/
public:
	Login(QObject *, quintptr, const Database&);

	~Login();

	/*slots*/
	public slots:
	virtual void logout();

	/*inherits*/
protected:
	void run();
};

#endif