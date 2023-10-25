CREATE TABLE multi_index3(id int, col1 int, col2 float, col3 char(10), col4 date, col5 int, col6 int);
CREATE unique INDEX i_3_i1 ON multi_index3(id);
insert into multi_index3 VALUES (7, 2, 47.71, '5H88M', '2013-07-21', 5, 26);
insert into multi_index3 VALUES (2, 1, 18.70, 'WX07', '2019-03-24', 8, 4);
insert into multi_index3 VALUES (1, 1, 44.34, 'R2Y', '2013-09-24', 4, 80);
CREATE unique INDEX i_3_14 ON multi_index3(col1,col4);
insert into multi_index3 VALUES (7, 2, 28.95, 'QA0AT278R', '2003-06-20', 1, 31);
insert into multi_index3 VALUES (9, 1, 39.07, 'W', '2015-11-26', 5, 43);
insert into multi_index3 VALUES (3, 1, 27.11, 'GXLY9P', '2006-11-11', 7, 64);
insert into multi_index3 VALUES (7, 2, 16.00, '4QOAEIKHCG', '2010-04-05', 7, 14);


-- failure
insert into multi_index3 VALUES (1, 2, 3, '5H88M', '2013-09-24', 4, 80);
insert into multi_index3 VALUES (1, 1, 3, '5H88M', '2013-09-24', 4, 80);

DELETE FROM multi_index3 WHERE id = 3;
DELETE FROM multi_index3 WHERE id = 6;

DELETE FROM multi_index3 WHERE col3 = '2WQI6X';

DELETE FROM multi_index3 WHERE id = 7 and col1 = 2;