CREATE TABLE join_table_1(id int, name char(20));
CREATE TABLE join_table_2(id int, age int);

insert into join_table_1 values (1, 'zzy');
insert into join_table_1 values (1, 'zzy');
insert into join_table_2 values (1, 22); 
insert into join_table_2 values (1, 22); 
Select * from join_table_1 inner join join_table_2 on join_table_1.id=join_table_2.id;