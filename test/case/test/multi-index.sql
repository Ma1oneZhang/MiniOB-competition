CREATE TABLE null_table(id int not null, num int null, price float not null, birthday date null);
CREATE TABLE null_table2(id int not null, num int null, price float not null, birthday date null);
CREATE INDEX index_num on null_table(num);
insert into null_table VALUES (5, 6, 44.30, '2001-01-10');
insert into null_table VALUES (5, 8, 25.59, '2016-12-04');

SELECT * FROM null_table where num = null; 