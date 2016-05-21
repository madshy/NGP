/*********************************************
*
*@file:game.sql
*@author:madshy
*@mail:madshy94@163.com
*@data:2016/03/18
*@comment:create a table for game information.
	game_id is the identification of game,auto increment from 1.
	name is what we call the game.
	nation is to which game belongs.
	icon is the path of game's icon.
	desc_path is a path of file decribing the game.
	man_path is path of manual of the game.
	d_load_path is path downloading the game.

	**game_id unsigned smallint auto_increment primary key,
*
*********************************************/

use ngp;

create table Game(
game_id int primary key auto_increment,
name varchar(32) not null,
nation varchar(28),
icon varchar(64) not null, 
desc_path varchar(64) not null,
man_path varchar(64) not null,
d_load_path varchar(64) not null
);