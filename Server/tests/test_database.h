/***************************************************
*
*    @file:test_database.h
*    @author:madshy
*    @mail:madshy@163.com
*    @data:2016/03/20
*    @comment:A test case for Database
*
***************************************************/

#pragma once

#include "../Server/include/Database.h"

void test()
{

	Database db;
	if (!db.connect())
	{
		return 1;
	}

	if (!db.insert("insert into ngp(id, name)"
		"values (8, 'f')"))
	{
		qDebug() << "Insert failed.";
		return 1;
	}

	QSqlQuery* query = db.select("select * from ngp");
	while (query->next())
	{
		qDebug() << "id:" << query->value(0).toInt();
		qDebug() << "name:" << query->value("name").toString();
	}
}