create table group_by(id int null, a int null, b int);
insert into group_by values(null, 1, 1), (null, 2, 2), (3, 3, 3);
insert into group_by values(1, 1, 1), (2, 2, 2), (3, 3, 3);
insert into group_by values(null, null, 1), (null, null, 2), (3, 3, 3);
select id, avg(a) from group_by group by id;


create table group_by_1(id int null, a int null, b int);
insert into group_by_1 values(null, null, 1);
insert into group_by_1 values(null, 1, 1);
insert into group_by_1 values(1, null, 1);
insert into group_by_1 values(1, 1, 1);
select id, a, avg(b) from group_by group by id;