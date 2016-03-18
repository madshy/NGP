/*********************************************
*
*@file:user.sql
*@author:madshy
*@mail:madshy94@163.com
*@data:2016/03/18
*@comment:create a table for user information.
	user_id identify the user.
	password is typed char(32),stored the result of md5.
	nation is nationality of user.
	mail is a information for resetting the psw.
	icon is a path of user's icon
*
*********************************************/

use ngp;

create table User(
user_id varchar(11) primary key,
password char(32) not null,		
nation varchar(28),				
mail varchar(32),
icon varchar(64) not null	
);