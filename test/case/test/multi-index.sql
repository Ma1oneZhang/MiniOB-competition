CREATE TABLE unique_table2(id1 int, id2 int, col1 int, col2 int);
CREATE UNIQUE INDEX index_id on unique_table2(id1);
INSERT INTO unique_table2 VALUES (1, 2, 3, 4);
INSERT INTO unique_table2 VALUES (2, 2, 3, 4);
INSERT INTO unique_table2 VALUES (3, 2, 3, 4);
INSERT INTO unique_table2 VALUES (4, 2, 3, 4);
INSERT INTO unique_table2 VALUES (5, 2, 3, 4);
INSERT INTO unique_table2 VALUES (6, 2, 3, 4);

UPDATE unique_table2 SET id1=1,id2=2 where id2=4;
UPDATE unique_table2 SET id1=2,id2=2 where id1=4;