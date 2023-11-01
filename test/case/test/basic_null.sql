CREATE TABLE null_table(id int not null, num int null, price float not null, birthday date null);
CREATE TABLE null_table2(id int not null, num int null, price float not null, birthday date null);
CREATE INDEX index_num on null_table(num);
insert into null_table VALUES (7, 8, 26.83, '2017-05-17');
insert into null_table VALUES (8, 8, 26.25, '2022-08-07');

SELECT * FROM null_table where 8 is null;
SELECT * FROM null_table where 8 is not null;