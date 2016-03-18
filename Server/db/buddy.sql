/*********************************************
*
*@file:buddy.sql
*@author:madshy
*@mail:madshy94@163.com
*@data:2016/03/18
*@comment:create a table for user's buddies information.
	user_id,one of primary key and reference to User.user_id.
	buddy_id like the user_id.
	note is what buddy is called by user,may be his/her name,
		even a nickname.
*
*********************************************/

use ngp;

create table Buddy(
user_id varchar(11),
buddy_id varchar(11),
note varchar(10),
primary key (user_id, buddy_id),
foreign key (user_id) references User(user_id)
	on delete cascade,
foreign key (buddy_id) references User(user_id)
	on delete cascade
);