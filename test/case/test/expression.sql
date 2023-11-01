create table exp_table(id int, col1 int, col2 int, col3 float, col4 float);
create table exp_table2(id int, col1 int);
insert into exp_table VALUES (2, 6, 1, 4.29, 2.52);
insert into exp_table VALUES (1, 6, 9, 8.5, 3.25);
insert into exp_table VALUES (3, 3, 3, 3.14, 3.99);
select * from exp_table where 9+col2 < 15;