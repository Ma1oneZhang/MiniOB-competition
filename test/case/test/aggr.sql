CREATE TABLE aggregation_func(id int, num int, price float, addr char(4), birthday date);
INSERT INTO aggregation_func VALUES (1, 18, 10.0, 'abc', '2020-01-01');
INSERT INTO aggregation_func VALUES (2, 15, 20.0, 'abc', '2010-01-11');
INSERT INTO aggregation_func VALUES (3, 12, 30.0, 'def', '2021-01-21');
INSERT INTO aggregation_func VALUES (4, 15, 30.0, 'dei', '2021-01-31');
SELECT avg(price) FROM aggregation_func WHERE birthday > '2015-03-25';