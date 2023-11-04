#include <iostream>

using namespace std;

int main()
{
  cout << "create table text_table(id int, info text);\n";
  string sql = "insert into text_table values(1, \'";
  for (int i = 0; i < (1 << 16) - 1; i++) {
    sql += 'g';
  }
  sql += "\');\n";
  sql += "insert into text_table values(1, \'";
  for (int i = 0; i < (1 << 11) - 50; i++) {
    sql += 'g';
  }
  sql += "\');\n";
  cout << sql;
}