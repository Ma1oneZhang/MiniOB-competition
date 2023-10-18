
create table join_table_large_1(id int, num1 int);
create table join_table_large_2(id int, num2 int);
create table join_table_large_3(id int, num3 int);
create table join_table_large_4(id int, num4 int);
create table join_table_large_5(id int, num5 int);
create table join_table_large_6(id int, num6 int);

insert into join_table_large_1 values(1, 1);
insert into join_table_large_1 values(2, 2);
insert into join_table_large_1 values(3, 3);
insert into join_table_large_1 values(4, 4);
insert into join_table_large_1 values(5, 5);
insert into join_table_large_1 values(6, 6);
insert into join_table_large_1 values(7, 7);
insert into join_table_large_1 values(8, 8);
insert into join_table_large_1 values(9, 9);
insert into join_table_large_1 values(10, 10);


insert into join_table_large_2 values(1, 1);
insert into join_table_large_2 values(2, 2);
insert into join_table_large_2 values(3, 3);
insert into join_table_large_2 values(4, 4);
insert into join_table_large_2 values(5, 5);
insert into join_table_large_2 values(6, 6);
insert into join_table_large_2 values(7, 7);
insert into join_table_large_2 values(8, 8);
insert into join_table_large_2 values(9, 9);
insert into join_table_large_2 values(10, 10);
insert into join_table_large_2 values(11, 11);

insert into join_table_large_3 values(1, 1);
insert into join_table_large_3 values(2, 2);
insert into join_table_large_3 values(3, 3);
insert into join_table_large_3 values(4, 4);
insert into join_table_large_3 values(5, 5);
insert into join_table_large_3 values(6, 6);
insert into join_table_large_3 values(7, 7);
insert into join_table_large_3 values(8, 8);
insert into join_table_large_3 values(9, 9);
insert into join_table_large_3 values(10, 10);

insert into join_table_large_4 values(1, 1);
insert into join_table_large_4 values(2, 2);
insert into join_table_large_4 values(3, 3);
insert into join_table_large_4 values(4, 4);
insert into join_table_large_4 values(5, 5);
insert into join_table_large_4 values(6, 6);
insert into join_table_large_4 values(7, 7);
insert into join_table_large_4 values(8, 8);
insert into join_table_large_4 values(9, 9);
insert into join_table_large_4 values(10, 10);


insert into join_table_large_5 values(1, 1);
insert into join_table_large_5 values(2, 2);
insert into join_table_large_5 values(3, 3);
insert into join_table_large_5 values(4, 4);
insert into join_table_large_5 values(5, 5);
insert into join_table_large_5 values(6, 6);
insert into join_table_large_5 values(7, 7);
insert into join_table_large_5 values(8, 8);
insert into join_table_large_5 values(9, 9);
insert into join_table_large_5 values(10, 10);


insert into join_table_large_6 values(1, 1);
insert into join_table_large_6 values(2, 2);
insert into join_table_large_6 values(3, 3);
insert into join_table_large_6 values(4, 4);
insert into join_table_large_6 values(5, 5);
insert into join_table_large_6 values(6, 6);
insert into join_table_large_6 values(7, 7);
insert into join_table_large_6 values(8, 8);
insert into join_table_large_6 values(9, 9);
insert into join_table_large_6 values(10, 10);
select * from join_table_large_1 inner join join_table_large_2;
-- select * from join_table_large_1 inner join join_table_large_2 on join_table_large_1.id=join_table_large_2.id inner join join_table_large_3 on join_table_large_1.id=join_table_large_3.id inner join join_table_large_4 on join_table_large_3.id=join_table_large_4.id inner join join_table_large_5 on 1=1 inner join join_table_large_6 on join_table_large_5.id=join_table_large_6.id where join_table_large_3.num3 <10 and join_table_large_5.num5>90;
