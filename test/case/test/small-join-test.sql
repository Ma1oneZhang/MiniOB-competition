
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
select * from join_table_large_1 inner join join_table_large_2 on join_table_large_1.id=join_table_large_2.id;
select * from join_table_large_1 inner join join_table_large_2 on join_table_large_1.id=join_table_large_2.id inner join join_table_large_3 on join_table_large_1.id=join_table_large_3.id inner join join_table_large_4 on join_table_large_3.id=join_table_large_4.id inner join join_table_large_5 on 1=1 inner join join_table_large_6 on join_table_large_5.id=join_table_large_6.id where join_table_large_3.num3 <10 and join_table_large_5.num5>90;


INSERT INTO big_order_by_3 VALUES (4, 6, 60.49, '1N8G', '2004-06-25');
INSERT INTO big_order_by_3 VALUES (1, 18, 28.53, '08B3AAC', '2014-11-23');
INSERT INTO big_order_by_3 VALUES (11, 17, 33.96, 'V', '2005-08-26');
INSERT INTO big_order_by_3 VALUES (2, 46, 1.68, 'DDP01Z', '1996-08-21');
INSERT INTO big_order_by_3 VALUES (23, 38, 40.69, 'E6K9P', '2033-01-19');

INSERT INTO big_order_by_2 VALUES (4, 6, 60.49, '1N8G', '2004-06-25');
INSERT INTO big_order_by_2 VALUES (1, 18, 28.53, '08B3AAC', '2014-11-23');
INSERT INTO big_order_by_2 VALUES (11, 17, 33.96, 'V', '2005-08-26');
INSERT INTO big_order_by_2 VALUES (2, 46, 1.68, 'DDP01Z', '1996-08-21');
INSERT INTO big_order_by_2 VALUES (23, 38, 40.69, 'E6K9P', '2033-01-19');

INSERT INTO big_order_by_1 VALUES (4, 6, 60.49, '1N8G', '2004-06-25');
INSERT INTO big_order_by_1 VALUES (1, 18, 28.53, '08B3AAC', '2014-11-23');
INSERT INTO big_order_by_1 VALUES (11, 17, 33.96, 'V', '2005-08-26');
INSERT INTO big_order_by_1 VALUES (2, 46, 1.68, 'DDP01Z', '1996-08-21');
INSERT INTO big_order_by_1 VALUES (23, 38, 40.69, 'E6K9P', '2033-01-19');

INSERT INTO big_order_by_0 VALUES (4, 6, 60.49, '1N8G', '2004-06-25');
INSERT INTO big_order_by_0 VALUES (1, 18, 28.53, '08B3AAC', '2014-11-23');
INSERT INTO big_order_by_0 VALUES (11, 17, 33.96, 'V', '2005-08-26');
INSERT INTO big_order_by_0 VALUES (2, 46, 1.68, 'DDP01Z', '1996-08-21');
INSERT INTO big_order_by_0 VALUES (23, 38, 40.69, 'E6K9P', '2033-01-19');

select * from big_order_by_0, big_order_by_1, big_order_by_2, big_order_by_3 order by big_order_by_2.birthday, big_order_by_1.price, big_order_by_1.num, big_order_by_2.addr, big_order_by_3.id, big_order_by_0.addr, big_order_by_0.birthday, big_order_by_3.addr;
select * from big_order_by_0, big_order_by_1 order by big_order_by_0.id asc, big_order_by_1.id desc;