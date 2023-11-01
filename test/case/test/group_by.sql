create table t_group_by (id int not null, score float not null, name char(1) null);
create table t_group_by_2 (id int not null, age int not null);
insert into t_group_by VALUES (2, 1.40, 'O');
insert into t_group_by VALUES (1, 2.29, '1');
insert into t_group_by VALUES (6, 4.02, 'U');
select id, sum(score) from t_group_by group by id;