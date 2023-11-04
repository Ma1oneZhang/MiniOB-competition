/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    INDEX = 263,                   /* INDEX  */
    CALC = 264,                    /* CALC  */
    SELECT = 265,                  /* SELECT  */
    DESC = 266,                    /* DESC  */
    SHOW = 267,                    /* SHOW  */
    SYNC = 268,                    /* SYNC  */
    INSERT = 269,                  /* INSERT  */
    DELETE = 270,                  /* DELETE  */
    UPDATE = 271,                  /* UPDATE  */
    LBRACE = 272,                  /* LBRACE  */
    UNIQUE = 273,                  /* UNIQUE  */
    MAX = 274,                     /* MAX  */
    MIN = 275,                     /* MIN  */
    COUNT = 276,                   /* COUNT  */
    AVG = 277,                     /* AVG  */
    SUM = 278,                     /* SUM  */
    ROUND = 279,                   /* ROUND  */
    LENGTH = 280,                  /* LENGTH  */
    DATE_FORMAT = 281,             /* DATE_FORMAT  */
    INNER = 282,                   /* INNER  */
    JOIN = 283,                    /* JOIN  */
    RBRACE = 284,                  /* RBRACE  */
    COMMA = 285,                   /* COMMA  */
    ORDER = 286,                   /* ORDER  */
    GROUP = 287,                   /* GROUP  */
    BY = 288,                      /* BY  */
    HAVING = 289,                  /* HAVING  */
    ASC = 290,                     /* ASC  */
    TRX_BEGIN = 291,               /* TRX_BEGIN  */
    TRX_COMMIT = 292,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 293,            /* TRX_ROLLBACK  */
    INT_T = 294,                   /* INT_T  */
    STRING_T = 295,                /* STRING_T  */
    FLOAT_T = 296,                 /* FLOAT_T  */
    DATE_T = 297,                  /* DATE_T  */
    TEXT_T = 298,                  /* TEXT_T  */
    HELP = 299,                    /* HELP  */
    EXIT = 300,                    /* EXIT  */
    DOT = 301,                     /* DOT  */
    INTO = 302,                    /* INTO  */
    VALUES = 303,                  /* VALUES  */
    FROM = 304,                    /* FROM  */
    WHERE = 305,                   /* WHERE  */
    LIKE = 306,                    /* LIKE  */
    NOT = 307,                     /* NOT  */
    AND = 308,                     /* AND  */
    OR = 309,                      /* OR  */
    SET = 310,                     /* SET  */
    ON = 311,                      /* ON  */
    LOAD = 312,                    /* LOAD  */
    DATA = 313,                    /* DATA  */
    INFILE = 314,                  /* INFILE  */
    EXPLAIN = 315,                 /* EXPLAIN  */
    IS = 316,                      /* IS  */
    NULL_TOKEN = 317,              /* NULL_TOKEN  */
    IN = 318,                      /* IN  */
    EQ = 319,                      /* EQ  */
    LT = 320,                      /* LT  */
    GT = 321,                      /* GT  */
    LE = 322,                      /* LE  */
    GE = 323,                      /* GE  */
    NE = 324,                      /* NE  */
    AS = 325,                      /* AS  */
    NUMBER = 326,                  /* NUMBER  */
    FLOAT = 327,                   /* FLOAT  */
    ID = 328,                      /* ID  */
    SSS = 329,                     /* SSS  */
    DATE_STR = 330,                /* DATE_STR  */
    UMINUS = 331                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 127 "yacc_sql.y"

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

#line 168 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);


#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
