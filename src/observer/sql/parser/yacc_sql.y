
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        UNIQUE
        MAX
        MIN
        COUNT
        AVG
        SUM
        ROUND
        LENGTH
        DATE_FORMAT
        INNER
        JOIN
        RBRACE
        COMMA
        ORDER
        GROUP
        BY
        HAVING
        ASC
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        TEXT_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        LIKE
        NOT
        AND
        OR
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        IS
        NULL_TOKEN
        IN
        EQ
        LT
        GT
        LE
        GE
        NE
        AS

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                   sql_node;
  ConditionSqlNode *                condition;
  Value *                           value;
  std::vector<Value> *              tuple;
  enum CompOp                       comp;
  RelAttrSqlNode *                  rel_attr;
  OrderBySqlNode *                  order_by_attr;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  JoinSqlNode *                     join_node;
  UpdateValue *                     update_value;
  std::vector<UpdateValue> *        update_value_list;
  std::vector<Expression *> *       expression_list;
  std::vector<Value> *              value_list;
  std::vector<std::vector<Value>> * tuple_list;
  std::vector<ConditionSqlNode> *   condition_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  std::vector<OrderBySqlNode> *     order_by_attr_list;
  std::vector<std::string> *        relation_list;
  std::vector<std::vector<std::string>> *        relation_alias_list;
  std::vector<JoinSqlNode> *        join_list;
  char *                            string;
  int                               number;
  float                             floats;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
%token <string> DATE_STR
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <value>               value
%type <tuple>               tuple
%type <number>              number
%type <comp>                comp_op
%type <rel_attr>            rel_attr
%type <update_value>        update_attr
%type <update_value_list>   update_attr_list
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <tuple_list>          tuple_list
%type <condition_list>      where
%type <condition_list>      condition_list
%type <relation_alias_list> rel_list
%type <expression_list>     attr_list
%type <expression_list>     group_by
%type <condition_list>      having
%type <condition_list>      having_list
%type <condition>           having_attr
%type <relation_list>       index_field_list
%type <order_by_attr>       order_by_node
%type <order_by_attr_list>  order_by_node_list
%type <order_by_attr_list>  order_by
%type <join_node>           join_node
%type <join_list>           join_list
%type <expression>          expression
%type <expression>          alias_expression
%type <expression_list>     expression_list
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            show_index_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | show_index_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;
show_index_stmt:
    SHOW INDEX FROM ID {
      $$ = new ParsedSqlNode(SCF_SHOW_INDEX);
      $$->show_index.relation_name = $4;
      free($4);
    };
desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID index_field_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.is_unique = false;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      if($8 != nullptr){
        create_index.attribute_names.swap(*$8);
        free($8);
      }
      create_index.attribute_names.push_back($7);
      std::reverse(create_index.attribute_names.begin(), create_index.attribute_names.end());
      free($3);
      free($5);
      free($7);
    }
    | CREATE UNIQUE INDEX ID ON ID LBRACE ID index_field_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.is_unique = true;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      if($9 != nullptr){
        create_index.attribute_names.swap(*$9);
        free($9);
      }
      create_index.attribute_names.push_back($8);
      std::reverse(create_index.attribute_names.begin(), create_index.attribute_names.end());
      free($4);
      free($6);
      free($8);
    }
    ;

index_field_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID index_field_list
    {
      if($3 != nullptr){
        $$ = $3;
      } else {
        $$ = new std::vector<std::string>;
      }
      $$->push_back($2);
    }

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE AS select_stmt
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
      create_table.select_node = $9;
    }
    | CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE select_stmt
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
      create_table.select_node = $8;
    }
    | CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
    }
    | CREATE TABLE ID AS select_stmt
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);
      create_table.select_node = $5;
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE NULL_TOKEN
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = true;
      if((AttrType)$2 == AttrType::TEXTS){
        $$->length = 40;
      }
      free($1);
    }
    | ID type LBRACE number RBRACE NOT NULL_TOKEN
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = false;
      if((AttrType)$2 == AttrType::TEXTS){
        $$->length = 40;
      }
      free($1);
    }
    | ID type LBRACE number RBRACE 
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = true;
      if((AttrType)$2 == AttrType::TEXTS){
        $$->length = 40;
      }
      free($1);
    }
    | ID type NULL_TOKEN
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->nullable = true;
      if((AttrType)$2 == AttrType::TEXTS){
        $$->length = 40;
      }
      free($1);
    }
    | ID type NOT NULL_TOKEN
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->nullable = false;
      if((AttrType)$2 == AttrType::TEXTS){
        $$->length = 40;
      }
      free($1);
    }
    | ID type
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->nullable = true;
      if((AttrType)$2 == AttrType::TEXTS){
        $$->length = 40;
      }
      free($1);
    }
    ;
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$=INTS; }
    | STRING_T { $$=CHARS; }
    | FLOAT_T  { $$=FLOATS; }
    | DATE_T   { $$=DATES; }
    | TEXT_T   { $$=TEXTS; }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES tuple tuple_list
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($6 != nullptr) {
        $$->insertion.values.swap(*$6);
      }
      $$->insertion.values.emplace_back(*$5);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $5;
      free($3);
    }
    ;
tuple_list:
    /* empty */
    {
      $$ = nullptr;
    };
    | COMMA tuple tuple_list {
      if ($3 != nullptr){
        $$ = $3;
      } else {
        $$ = new std::vector<std::vector<Value>>;
      }
      $$->emplace_back(*$2);
      delete $2;
    };
tuple:
    LBRACE value value_list RBRACE {
      if ($3 != nullptr){
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      std::reverse($$->begin(), $$->end());
      delete $2;
    }

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
    }
    |DATE_STR {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
    }
    | NULL_TOKEN {
      $$ = new Value();
      $$->set_isnull();
    }
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET update_attr update_attr_list where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      if($5 == nullptr){
        $5 = new std::vector<UpdateValue>;
      }
      $5->push_back(*$4);
      $$->update.relation_name = $2;
      for(auto &value : *$5){
        $$->update.attribute_name.push_back(value.attribute_name);
      }
      $$->update.value.swap(*$5);
      // for(auto &value : *$5){
      //   push_back(value.value);
      // }
      if ($6 != nullptr) {
        $$->update.conditions.swap(*$6);
        delete $6;
      }
      free($2);
      free($4);
      free($5);
    }
    ;

update_attr:
    ID EQ value
    {
      $$ = new UpdateValue;
      $$->attribute_name = $1;
      $$->value = *$3;
      $$->is_stmt = false;
    }
    | ID EQ LBRACE select_stmt RBRACE
    {
      $$ = new UpdateValue;
      $$->attribute_name = $1;
      $$->is_stmt = true;
      $$->stmt = $4;
    }
    ;

update_attr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA update_attr update_attr_list 
    {
      if ($3 == nullptr){
        $$ = new std::vector<UpdateValue>;
      }else {
        $$ = $3;
      }
      $$->push_back(*$2);
    };
select_stmt:        /*  select 语句的语法解析树*/
    SELECT expression_list
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.attributes.swap(*$2);
        delete $2;
      }
    }
    | SELECT expression_list FROM ID rel_list join_list where order_by group_by having
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.attributes.swap(*$2);
        delete $2;
      }
      if ($5 != nullptr) {
        $$->selection.relations.swap($5->front());
        $$->selection.relation_alias.swap($5->back());
        delete $5;
      }
      $$->selection.relations.emplace_back($4);
      $$->selection.relation_alias.emplace_back("");
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());
      std::reverse($$->selection.relation_alias.begin(), $$->selection.relation_alias.end());
      if ($6 != nullptr) {
        $$->selection.joinctions.swap(*$6);
        delete $6;
      }
      if ($7 != nullptr) {
        $$->selection.conditions.swap(*$7);
        delete $7;
      }
      if ($8 != nullptr) {
        $$->selection.orderby.swap(*$8);
        delete $8;
      }
      if ($9 != nullptr){
        $$->selection.groupby.swap(*$9);
      }
      if ($10 != nullptr){
        $$->selection.having.swap(*$10);
      }
      free($4);
    }
    | SELECT expression_list FROM ID AS ID rel_list join_list where order_by group_by having
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.attributes.swap(*$2);
        delete $2;
      }
      if ($7 != nullptr) {
        $$->selection.relations.swap($7->front());
        $$->selection.relation_alias.swap($7->back());
        delete $7;
      }
      $$->selection.relations.emplace_back($4);
      $$->selection.relation_alias.emplace_back($6);
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());
      std::reverse($$->selection.relation_alias.begin(), $$->selection.relation_alias.end());
      if ($8 != nullptr) {
        $$->selection.joinctions.swap(*$8);
        delete $8;
      }
      if ($9 != nullptr) {
        $$->selection.conditions.swap(*$9);
        delete $9;
      }
      if ($10 != nullptr) {
        $$->selection.orderby.swap(*$10);
        delete $10;
      }
      if ($11 != nullptr){
        $$->selection.groupby.swap(*$11);
      }
      if ($12 != nullptr){
        $$->selection.having.swap(*$12);
      }
      free($4);
      free($6);
    }
    | SELECT expression_list FROM ID ID rel_list join_list where order_by group_by having
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.attributes.swap(*$2);
        delete $2;
      }
      if ($6 != nullptr) {
        $$->selection.relations.swap($6->front());
        $$->selection.relation_alias.swap($6->back());
        delete $6;
      }

      $$->selection.relations.emplace_back($4);
      $$->selection.relation_alias.emplace_back($5);
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());
      std::reverse($$->selection.relation_alias.begin(), $$->selection.relation_alias.end());
      if ($7 != nullptr) {
        $$->selection.joinctions.swap(*$7);
        delete $7;
      }
      if ($8 != nullptr) {
        $$->selection.conditions.swap(*$8);
        delete $9;
      }
      if ($9 != nullptr) {
        $$->selection.orderby.swap(*$9);
        delete $9;
      }
      if ($10 != nullptr){
        $$->selection.groupby.swap(*$10);
      }
      if ($11 != nullptr){
        $$->selection.having.swap(*$11);
      }
      free($4);
      free($5);
    }
    ;
calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      std::reverse($2->begin(), $2->end());
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    alias_expression
    {
      $$ = new std::vector<Expression*>;
      $$->emplace_back($1);
    }
    | alias_expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Expression *>;
      }
      $$->emplace_back($1);
    }
    | expression
    {
      $$ = new std::vector<Expression*>;
      $$->emplace_back($1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Expression *>;
      }
      $$->emplace_back($1);
    }
    ;

alias_expression:
     expression ID 
    {
      $$ = $1;
      $$->set_name($2);
    }
    | expression AS ID 
    {
      $$ = $1;
      $$->set_name($3);
    }
    ;

expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    } 
    | rel_attr {
      $$ = new FieldExpr(*$1);
      delete $1; 
    }
    | ROUND LBRACE expression RBRACE
    {
      auto zero_value = Value(0);
      $$ = new RoundFuncExpr($3, new ValueExpr(zero_value));
      $$->set_name(token_name(sql_string, &@$));
    }
    | ROUND LBRACE expression COMMA expression RBRACE
    {
      $$ = new RoundFuncExpr($3, $5);
      $$->set_name(token_name(sql_string, &@$));
    }
    | LENGTH LBRACE expression RBRACE
    {
      $$ = new LengthFuncExpr($3);
      $$->set_name(token_name(sql_string, &@$));$$->set_name(token_name(sql_string, &@$));
    } 
    | DATE_FORMAT LBRACE expression COMMA expression RBRACE 
    {
      $$ = new DateFormatFuncExpr($3, $5);
      $$->set_name(token_name(sql_string, &@$));
    };

rel_attr:
    '*' {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = "";
      $$->attribute_name = "*";;
    }
    | ID DOT '*' {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = "*";
      free($1);
    }
    | ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    | MIN LBRACE rel_attr RBRACE
    {
      $$ = $3;
      $$->aggregation_type = AggregationType::MIN;
    }
    | MAX LBRACE rel_attr RBRACE
    {
      $$ = $3;
      $$->aggregation_type = AggregationType::MAX;
    }
    | COUNT LBRACE rel_attr RBRACE 
    {
      $$ = $3;
      $$->aggregation_type = AggregationType::COUNT;
    }
    | AVG LBRACE rel_attr RBRACE
    {
      $$ = $3;
      $$->aggregation_type = AggregationType::AVG;
    }
    | SUM LBRACE rel_attr RBRACE
    {
      $$ = $3;
      $$->aggregation_type = AggregationType::SUM;
    }
    ;

attr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA expression attr_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Expression *>;
      }
      $$->emplace_back($2);
    }
    ;

rel_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID rel_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::vector<std::string>>();
        $$->emplace_back();
        $$->emplace_back();
      }

      $$->front().emplace_back($2);
      $$->back().emplace_back("");
      free($2);
    }
    | COMMA ID AS ID rel_list {
      if ($5 != nullptr) {
        $$ = $5;
      } else {
        $$ = new std::vector<std::vector<std::string>>();
        $$->emplace_back();
        $$->emplace_back();
      }

      $$->front().emplace_back($2);
      $$->back().emplace_back($4);

      free($2);
      free($4);
    }
    | COMMA ID ID rel_list {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<std::vector<std::string>>();
        $$->emplace_back();
        $$->emplace_back();
      }

      $$->front().emplace_back($2);
      $$->back().emplace_back($3);

      free($2);
      free($3);
    }
    ;


group_by:
    /* empty */
    {
      $$ = nullptr;
    }
    | GROUP BY expression attr_list
    {
      if($4 != nullptr){
        $$ = $4;
      } else {
        $$ = new std::vector<Expression *>;
      }
      $$->emplace_back($3);
    };
    
having:
    /* empty */
    {
      $$ = nullptr;
    }
    | HAVING having_attr having_list
    {
      if($3 != nullptr){
        $$ = $3;
      } else {
        $$ = new std::vector<ConditionSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
having_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA having_attr having_list
    {
      if($3 != nullptr){
        $$ = $3;
      } else {
        $$ = new std::vector<ConditionSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;

having_attr:
    rel_attr comp_op value
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
join_node:
    INNER JOIN ID ON condition_list
    {
      $$ = new JoinSqlNode{$3,*$5};
      delete $3;
      delete $5;
    }
    ;

join_list:
       /* empty */
    {
      $$ = nullptr;
    }
    | join_node
    {
      $$ = new std::vector<JoinSqlNode>{*$1};
      delete $1;   
    }
    | join_list join_node
    {
      $$->emplace_back(*$2);
      delete $2;

    }
    ;

order_by:
      /* empty */
    {
      $$ = nullptr;
    }
    | ORDER BY order_by_node order_by_node_list 
    {
      $$ = new std::vector<OrderBySqlNode>;
      if($4 != nullptr){
        $$->swap(*$4);
        delete $4;
      }
      $$->push_back(*$3);
      std::reverse($$->begin(), $$->end());
      delete $3;
    }
    ;

order_by_node_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA order_by_node order_by_node_list
    {
      if($3 != nullptr){
        $$ = $3;
      } else {
        $$ = new std::vector<OrderBySqlNode>;
      }
      $$->push_back(*$order_by_node);
    }
    ;
order_by_node:
    rel_attr DESC
    {
      $$ = new OrderBySqlNode;
      $$->relation_name = std::move($1->relation_name);
      $$->attribute_name = std::move($1->attribute_name);
      $$->is_desc = true;
      free($1);
    }
    | rel_attr ASC 
    {
      $$ = new OrderBySqlNode;
      $$->relation_name = std::move($1->relation_name);
      $$->attribute_name = std::move($1->attribute_name);
      $$->is_desc = false;
      free($1);
    }| rel_attr 
    {
      $$ = new OrderBySqlNode;
      $$->relation_name = std::move($1->relation_name);
      $$->attribute_name = std::move($1->attribute_name);
      $$->is_desc = false;
      free($1);
    };
where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;  
    }
    ;
condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $$->front().link_type = 0;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition OR condition_list {
      $$ = $3;
      $$->front().link_type = 1;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
condition:
    expression comp_op expression
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 4;
      $$->left_expr = $1;
      $$->right_is_attr = 4;
      $$->right_expr = $3;
      $$->comp = $2;
    }
    | expression LIKE expression
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 4;
      $$->left_expr = $1;
      $$->right_is_attr = 4;
      $$->right_expr = $3;
      $$->comp = CompOp::LIKE_OP;
    }
    | expression NOT LIKE expression
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 4;
      $$->left_expr = $1;
      $$->right_is_attr = 4;
      $$->right_expr = $4;
      $$->comp = CompOp::NOT_LIKE_OP;
    }
    | expression IS NULL_TOKEN
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 4;
      $$->left_expr = $1;
      $$->comp = CompOp::IS_NULL;
      $$->right_is_attr = 4;
      auto null_value = Value();
      null_value.set_isnull();
      $$->right_expr = new ValueExpr(null_value);
    }
    | expression IS NOT NULL_TOKEN
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 4;
      $$->left_expr = $1;
      $$->comp = CompOp::IS_NOT_NULL;
      $$->right_is_attr = 4;
      auto null_value = Value();
      null_value.set_isnull();
      $$->right_expr = new ValueExpr(null_value);
    }
    | LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 2;
      $$->left_sub_query = $2;
      $$->right_is_attr = 2;
      $$->right_sub_query = $6;
      $$->comp = $4;
    }
    | expression comp_op LBRACE select_stmt RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 4;
      $$->left_expr = $1;
      $$->right_is_attr = 2;
      $$->right_sub_query = $4;
      $$->comp = $2;
    }
    | LBRACE select_stmt RBRACE comp_op expression
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 2;
      $$->left_sub_query = $2;
      $$->right_is_attr = 4;
      $$->right_expr = $5;
      $$->comp = $4;
    }
    | expression comp_op tuple
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 4;
      $$->left_expr = $1;
      $$->right_is_attr = 3;
      $$->right_value_list = *$3;
      $$->comp = $2;
    }
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | IN { $$ = IN_OP; }
    | NOT IN { $$ = NOT_IN_OP; }
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
