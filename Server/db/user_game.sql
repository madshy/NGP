/*********************************************
*
*@file:user_game.sql
*@author:madshy
*@mail:madshy94@163.com
*@data:2016/03/18
*@comment:create a table for user's game information.
	field user_id and game_id is not only a primary but a foreign key.
*
*********************************************/

use ngp;

create table user_game(
user_id varchar(11),
game_id unsigned smallint,
primary key (user_id, game_id),
foreign key (user_id) references User(user_id)
	on delete cascade,
foreign key (game_id) references Game(game_id)
	on delete cascade
);