create table update_select(id int);
create table update_select1(id int, col1 int);

insert into update_select values(1), (2), (3);
insert into update_select1 values(1, 1), (2, 1), (3, 1);

update update_select set id = (select id from update_select1 where id = 4) where update_select.id = 1;


-- only one col, one row
-- if query return no result, set the value as null
-- if get multi-row, return error
-- The update-select operation not occur at same table