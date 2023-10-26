CREATE TABLE unique_table2(id1 int, id2 int, col1 int, col2 int);
INSERT INTO unique_table2 VALUES (1,1,1,1);

CREATE UNIQUE INDEX index_id on unique_table2(id2);
UPDATE unique_table2 SET id1=1,id2=4 where id2=2;