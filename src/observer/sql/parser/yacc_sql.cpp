/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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


#line 114 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    CREATE = 259,
    DROP = 260,
    TABLE = 261,
    TABLES = 262,
    INDEX = 263,
    CALC = 264,
    SELECT = 265,
    DESC = 266,
    SHOW = 267,
    SYNC = 268,
    INSERT = 269,
    DELETE = 270,
    UPDATE = 271,
    LBRACE = 272,
    UNIQUE = 273,
    MAX = 274,
    MIN = 275,
    COUNT = 276,
    AVG = 277,
    SUM = 278,
    INNER = 279,
    JOIN = 280,
    RBRACE = 281,
    COMMA = 282,
    ORDER = 283,
    GROUP = 284,
    BY = 285,
    HAVING = 286,
    ASC = 287,
    TRX_BEGIN = 288,
    TRX_COMMIT = 289,
    TRX_ROLLBACK = 290,
    INT_T = 291,
    STRING_T = 292,
    FLOAT_T = 293,
    DATE_T = 294,
    HELP = 295,
    EXIT = 296,
    DOT = 297,
    INTO = 298,
    VALUES = 299,
    FROM = 300,
    WHERE = 301,
    LIKE = 302,
    NOT = 303,
    AND = 304,
    SET = 305,
    ON = 306,
    LOAD = 307,
    DATA = 308,
    INFILE = 309,
    EXPLAIN = 310,
    IS = 311,
    NULL_TOKEN = 312,
    IN = 313,
    EQ = 314,
    LT = 315,
    GT = 316,
    LE = 317,
    GE = 318,
    NE = 319,
    NUMBER = 320,
    FLOAT = 321,
    ID = 322,
    SSS = 323,
    DATE_STR = 324,
    UMINUS = 325
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 121 "yacc_sql.y"

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
  std::vector<JoinSqlNode> *        join_list;
  char *                            string;
  int                               number;
  float                             floats;

#line 264 "yacc_sql.cpp"

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



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  76
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   310

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  145
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  288

#define YYUNDEFTOK  2
#define YYMAXUTOK   325


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    72,    70,     2,    71,     2,    73,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    74
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   217,   217,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   249,   255,   260,   266,   272,   278,
     284,   291,   296,   302,   310,   327,   348,   351,   362,   372,
     391,   394,   407,   416,   425,   434,   443,   452,   463,   466,
     467,   468,   469,   472,   487,   490,   500,   513,   516,   527,
     531,   535,   540,   545,   552,   564,   590,   597,   608,   611,
     621,   656,   666,   671,   682,   685,   688,   691,   694,   698,
     701,   709,   718,   730,   735,   740,   751,   754,   764,   777,
     780,   793,   798,   803,   808,   813,   821,   824,   837,   840,
     853,   856,   869,   882,   892,   895,   900,   910,   913,   928,
     931,   942,   950,   957,   967,   970,   976,   979,   984,   991,
    1003,  1015,  1027,  1039,  1048,  1057,  1064,  1071,  1079,  1087,
    1096,  1107,  1118,  1132,  1133,  1134,  1135,  1136,  1137,  1138,
    1139,  1143,  1156,  1164,  1174,  1175
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "CALC", "SELECT", "DESC", "SHOW", "SYNC", "INSERT",
  "DELETE", "UPDATE", "LBRACE", "UNIQUE", "MAX", "MIN", "COUNT", "AVG",
  "SUM", "INNER", "JOIN", "RBRACE", "COMMA", "ORDER", "GROUP", "BY",
  "HAVING", "ASC", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T",
  "STRING_T", "FLOAT_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES",
  "FROM", "WHERE", "LIKE", "NOT", "AND", "SET", "ON", "LOAD", "DATA",
  "INFILE", "EXPLAIN", "IS", "NULL_TOKEN", "IN", "EQ", "LT", "GT", "LE",
  "GE", "NE", "NUMBER", "FLOAT", "ID", "SSS", "DATE_STR", "'+'", "'-'",
  "'*'", "'/'", "UMINUS", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "show_index_stmt", "desc_table_stmt", "create_index_stmt",
  "index_field_list", "drop_index_stmt", "create_table_stmt",
  "attr_def_list", "attr_def", "number", "type", "insert_stmt",
  "tuple_list", "tuple", "value_list", "value", "delete_stmt",
  "update_stmt", "update_attr", "update_attr_list", "select_stmt",
  "calc_stmt", "expression_list", "expression", "select_attr", "rel_attr",
  "attr_list", "rel_list", "aggr_attr", "group_by", "having",
  "having_list", "having_attr", "join_node", "join_list", "order_by",
  "order_by_node_list", "order_by_node", "where", "condition_list",
  "condition", "comp_op", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
      43,    45,    42,    47,   325
};
# endif

#define YYPACT_NINF (-222)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     156,    97,    30,    65,    28,   -35,     7,  -222,    -3,     9,
       4,  -222,  -222,  -222,  -222,  -222,    12,     3,   156,    81,
      83,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,    17,    18,    94,    37,    39,    65,  -222,  -222,
    -222,  -222,  -222,    65,  -222,  -222,   122,    90,   101,   103,
     108,   118,    79,  -222,    78,   111,   111,  -222,  -222,   100,
      95,    96,   107,   105,   119,  -222,  -222,  -222,  -222,   158,
     131,   116,  -222,   133,   106,  -222,    65,    65,    65,    65,
      65,   -33,   -33,   -33,   -33,   -33,   120,   136,    28,  -222,
    -222,   137,   142,   159,   140,   -24,   141,   151,   152,   171,
     173,  -222,  -222,   -20,   -20,  -222,  -222,   212,   213,   215,
     216,   217,  -222,   218,   111,   111,  -222,   227,     8,  -222,
     187,   220,  -222,   206,   104,   223,   234,   185,  -222,  -222,
    -222,  -222,  -222,  -222,   186,   230,  -222,  -222,   -24,   228,
     246,   -40,   165,  -222,   208,    82,   140,   159,   252,  -222,
    -222,  -222,  -222,   -11,   151,   233,   193,   244,   218,   238,
    -222,   -17,   237,   227,  -222,   239,   209,    69,  -222,  -222,
    -222,  -222,  -222,  -222,  -222,    87,   -24,    10,    71,    44,
       8,   246,  -222,   220,  -222,   199,   203,   214,  -222,   223,
    -222,   243,   205,  -222,   207,  -222,   245,   -24,   249,   228,
     172,  -222,   219,  -222,  -222,  -222,  -222,   -24,   221,  -222,
       1,  -222,  -222,  -222,  -222,   251,  -222,  -222,  -222,   253,
    -222,  -222,   222,   254,   243,   231,   255,   257,   237,  -222,
    -222,    11,  -222,  -222,  -222,   258,  -222,    89,   243,  -222,
     261,     8,   -33,   260,   250,  -222,   246,  -222,  -222,   226,
    -222,  -222,  -222,  -222,    -2,   264,   -33,   179,  -222,   262,
    -222,  -222,  -222,   -33,  -222,   111,   172,   265,  -222,   264,
    -222,   -24,   179,  -222,  -222,  -222,   265,  -222
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     144,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    13,    14,     8,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,    63,    59,
      60,    61,    62,     0,    80,    71,    72,     0,     0,     0,
       0,     0,    84,    83,     0,    86,    86,    33,    31,     0,
       0,     0,     0,     0,     0,   142,     1,   145,     2,     0,
       0,     0,    30,     0,     0,    79,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    81,
      82,     0,     0,   114,     0,     0,     0,     0,     0,     0,
       0,    78,    73,    74,    75,    76,    77,     0,     0,     0,
       0,     0,    85,    89,    86,    86,    32,     0,   116,    64,
       0,    68,   143,     0,     0,    40,     0,     0,    38,    92,
      91,    93,    94,    95,     0,   104,    87,    88,     0,    54,
       0,     0,     0,   115,   117,     0,     0,   114,     0,    49,
      50,    51,    52,    47,     0,     0,     0,     0,    89,     0,
     105,   114,    57,     0,    53,     0,     0,     0,   139,   133,
     134,   135,   136,   137,   138,     0,     0,     0,     0,     0,
     116,     0,    66,    68,    65,     0,     0,     0,    45,    40,
      39,    36,     0,    90,     0,   106,   107,     0,     0,    54,
       0,   140,     0,   127,   120,   122,   123,     0,     0,   125,
       0,   132,   119,   121,   118,     0,    69,   141,    48,     0,
      46,    41,     0,     0,    36,     0,     0,    96,    57,    56,
      55,     0,   128,   124,   126,     0,    67,    44,    36,    34,
       0,   116,     0,     0,    98,    58,     0,   131,   130,     0,
      42,    37,    35,   103,   113,   109,     0,     0,    70,     0,
      43,   111,   112,     0,   108,    86,     0,   100,   129,   109,
      97,     0,     0,    99,   110,   102,   100,   101
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -222,  -222,   275,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,  -222,  -221,  -222,  -222,    98,   130,  -222,
    -222,  -222,    86,  -163,    58,   -93,  -222,  -222,   143,   109,
    -148,  -222,   224,   127,  -222,    -4,   -65,   132,     0,  -222,
    -222,    15,    16,   134,  -222,  -222,    24,    31,  -140,  -187,
    -222,  -147,  -222,  -222,  -222,  -222
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,   233,    32,    33,   165,   135,   229,
     163,    34,   174,   149,   208,    54,    35,    36,   131,   157,
      37,    38,    55,    56,    64,   152,    99,   145,   276,   254,
     268,   283,   277,   170,   171,   237,   274,   265,   129,   153,
     154,   185,    39,    40,    41,    78
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      65,   100,   175,   224,    66,   189,   196,   169,   176,   271,
     209,     4,   132,   250,    68,    69,   177,   194,   178,   179,
     180,   181,   182,   183,   184,   150,   221,   261,   256,   128,
     272,   206,    67,    48,    62,   151,    45,   197,    46,    63,
      70,    49,    50,   225,    51,    52,   198,    57,    58,    59,
      60,    61,    89,    90,    71,   172,    74,   217,    48,   146,
     147,   220,   192,   241,   263,    48,    49,    50,   211,    51,
      52,    72,   245,    49,    50,    62,    51,    52,    62,    73,
      63,    76,    47,    63,    79,    80,    77,   117,   118,   119,
     120,   121,   214,   216,   124,    62,   222,   151,   125,   191,
      63,    48,    81,    42,    82,    43,    83,    91,   269,    49,
      50,    62,    51,    52,   238,    44,    63,   212,    92,   218,
      93,    96,    48,    97,   243,    94,   213,   172,   219,   281,
      49,    50,   111,    51,    52,    95,    53,   259,    98,    48,
     159,   160,   161,   162,    48,   101,   260,    49,    50,    86,
      51,    52,    49,    50,    62,    51,    52,   104,   151,    63,
       1,     2,   102,   103,   105,     3,     4,     5,     6,     7,
       8,     9,    10,   106,    84,   107,    87,    88,    89,    90,
      85,   215,   108,   109,   110,   223,   127,   122,   285,    11,
      12,    13,    87,    88,    89,    90,    14,    15,    57,    58,
      59,    60,    61,   123,   126,   128,    16,   130,    17,   133,
     280,    18,   186,   187,   113,   114,   115,   116,   134,   136,
     176,   188,   137,   178,   179,   180,   181,   182,   183,   184,
     178,   179,   180,   181,   182,   183,   184,   257,   139,   140,
     138,   141,   142,   143,   148,   144,   155,   156,   264,   158,
     164,   166,   167,   168,   169,   173,     4,   190,   195,   200,
     201,   202,   275,   204,   207,   210,   227,   211,   228,   264,
     232,   230,   234,   236,   235,   239,   242,   246,   244,   247,
     249,   267,   251,   270,   258,   252,   253,   262,   278,   248,
     266,   273,   282,    75,   199,   240,   255,   231,   286,   193,
     203,   287,   226,   284,   279,   205,     0,     0,     0,     0,
     112
};

static const yytype_int16 yycheck[] =
{
       4,    66,   150,   190,     4,   152,    17,    24,    48,    11,
     173,    10,   105,   234,     7,     8,    56,   157,    58,    59,
      60,    61,    62,    63,    64,    17,   189,   248,    17,    46,
      32,   171,    67,    57,    67,   128,     6,    48,     8,    72,
      43,    65,    66,   191,    68,    69,    57,    19,    20,    21,
      22,    23,    72,    73,    45,   148,    53,    47,    57,   124,
     125,    17,   155,   210,   251,    57,    65,    66,    58,    68,
      69,    67,   220,    65,    66,    67,    68,    69,    67,    67,
      72,     0,    17,    72,    67,    67,     3,    91,    92,    93,
      94,    95,   185,   186,    98,    67,   189,   190,    98,    17,
      72,    57,     8,     6,    67,     8,    67,    17,   256,    65,
      66,    67,    68,    69,   207,    18,    72,    48,    17,    48,
      17,    42,    57,    45,   217,    17,    57,   220,    57,   276,
      65,    66,    26,    68,    69,    17,    71,    48,    27,    57,
      36,    37,    38,    39,    57,    45,    57,    65,    66,    27,
      68,    69,    65,    66,    67,    68,    69,    50,   251,    72,
       4,     5,    67,    67,    59,     9,    10,    11,    12,    13,
      14,    15,    16,    54,    47,    17,    70,    71,    72,    73,
      53,   185,    51,    67,    51,   189,    44,    67,   281,    33,
      34,    35,    70,    71,    72,    73,    40,    41,    19,    20,
      21,    22,    23,    67,    67,    46,    50,    67,    52,    68,
     275,    55,    47,    48,    87,    88,    89,    90,    67,    67,
      48,    56,    51,    58,    59,    60,    61,    62,    63,    64,
      58,    59,    60,    61,    62,    63,    64,   241,    26,    26,
      67,    26,    26,    26,    17,    27,    59,    27,   252,    43,
      27,    17,    67,    67,    24,    27,    10,    49,     6,    26,
      67,    17,   266,    25,    27,    26,    67,    58,    65,   273,
      27,    57,    67,    28,    67,    26,    57,    26,    57,    26,
      26,    31,    51,    57,    26,    30,    29,    26,    26,    67,
      30,    27,    27,    18,   164,   209,   238,   199,   282,   156,
     168,   286,   193,   279,   273,   171,    -1,    -1,    -1,    -1,
      86
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    15,
      16,    33,    34,    35,    40,    41,    50,    52,    55,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    90,    91,    96,   101,   102,   105,   106,   127,
     128,   129,     6,     8,    18,     6,     8,    17,    57,    65,
      66,    68,    69,    71,   100,   107,   108,    19,    20,    21,
      22,    23,    67,    72,   109,   110,   113,    67,     7,     8,
      43,    45,    67,    67,    53,    77,     0,     3,   130,    67,
      67,     8,    67,    67,   108,   108,    27,    70,    71,    72,
      73,    17,    17,    17,    17,    17,    42,    45,    27,   111,
     111,    45,    67,    67,    50,    59,    54,    17,    51,    67,
      51,    26,   107,   108,   108,   108,   108,   110,   110,   110,
     110,   110,    67,    67,   110,   113,    67,    44,    46,   123,
      67,   103,   100,    68,    67,    93,    67,    51,    67,    26,
      26,    26,    26,    26,    27,   112,   111,   111,    17,    98,
      17,   100,   110,   124,   125,    59,    27,   104,    43,    36,
      37,    38,    39,    95,    27,    92,    17,    67,    67,    24,
     118,   119,   100,    27,    97,   105,    48,    56,    58,    59,
      60,    61,    62,    63,    64,   126,    47,    48,    56,   126,
      49,    17,   100,   103,   123,     6,    17,    48,    57,    93,
      26,    67,    17,   112,    25,   118,   123,    27,    99,    98,
      26,    58,    48,    57,   100,   110,   100,    47,    48,    57,
      17,    98,   100,   110,   124,   105,   104,    67,    65,    94,
      57,    92,    27,    89,    67,    67,    28,   120,   100,    26,
      97,   126,    57,   100,    57,   105,    26,    26,    67,    26,
      89,    51,    30,    29,   114,    99,    17,   110,    26,    48,
      57,    89,    26,   124,   110,   122,    30,    31,   115,   105,
      57,    11,    32,    27,   121,   110,   113,   117,    26,   122,
     111,   126,    27,   116,   121,   100,   117,   116
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    88,    89,    89,    90,    91,
      92,    92,    93,    93,    93,    93,    93,    93,    94,    95,
      95,    95,    95,    96,    97,    97,    98,    99,    99,   100,
     100,   100,   100,   100,   101,   102,   103,   103,   104,   104,
     105,   106,   107,   107,   108,   108,   108,   108,   108,   108,
     108,   109,   109,   110,   110,   110,   111,   111,   111,   112,
     112,   113,   113,   113,   113,   113,   114,   114,   115,   115,
     116,   116,   117,   118,   119,   119,   119,   120,   120,   121,
     121,   122,   122,   122,   123,   123,   124,   124,   124,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   126,   126,   126,   126,   126,   126,   126,
     126,   127,   128,   129,   130,   130
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     4,     2,     9,    10,     0,     3,     5,     7,
       0,     3,     6,     7,     5,     3,     4,     2,     1,     1,
       1,     1,     1,     6,     0,     3,     4,     0,     3,     1,
       1,     1,     1,     1,     4,     6,     3,     5,     0,     3,
      10,     2,     1,     3,     3,     3,     3,     3,     3,     2,
       1,     2,     2,     1,     1,     3,     0,     3,     3,     0,
       3,     4,     4,     4,     4,     4,     0,     4,     0,     3,
       0,     3,     3,     5,     0,     1,     2,     0,     4,     0,
       3,     2,     2,     1,     0,     2,     0,     1,     3,     3,
       3,     3,     3,     3,     4,     3,     4,     3,     4,     7,
       5,     5,     3,     1,     1,     1,     1,     1,     1,     1,
       2,     7,     2,     4,     0,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 218 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1785 "yacc_sql.cpp"
    break;

  case 24:
#line 249 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1794 "yacc_sql.cpp"
    break;

  case 25:
#line 255 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1802 "yacc_sql.cpp"
    break;

  case 26:
#line 260 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1810 "yacc_sql.cpp"
    break;

  case 27:
#line 266 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1818 "yacc_sql.cpp"
    break;

  case 28:
#line 272 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1826 "yacc_sql.cpp"
    break;

  case 29:
#line 278 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1834 "yacc_sql.cpp"
    break;

  case 30:
#line 284 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1844 "yacc_sql.cpp"
    break;

  case 31:
#line 291 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1852 "yacc_sql.cpp"
    break;

  case 32:
#line 296 "yacc_sql.y"
                       {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1862 "yacc_sql.cpp"
    break;

  case 33:
#line 302 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1872 "yacc_sql.cpp"
    break;

  case 34:
#line 311 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.is_unique = false;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      if((yyvsp[-1].relation_list) != nullptr){
        create_index.attribute_names.swap(*(yyvsp[-1].relation_list));
        free((yyvsp[-1].relation_list));
      }
      create_index.attribute_names.push_back((yyvsp[-2].string));
      std::reverse(create_index.attribute_names.begin(), create_index.attribute_names.end());
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 1893 "yacc_sql.cpp"
    break;

  case 35:
#line 328 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.is_unique = true;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      if((yyvsp[-1].relation_list) != nullptr){
        create_index.attribute_names.swap(*(yyvsp[-1].relation_list));
        free((yyvsp[-1].relation_list));
      }
      create_index.attribute_names.push_back((yyvsp[-2].string));
      std::reverse(create_index.attribute_names.begin(), create_index.attribute_names.end());
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 1914 "yacc_sql.cpp"
    break;

  case 36:
#line 348 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 1922 "yacc_sql.cpp"
    break;

  case 37:
#line 352 "yacc_sql.y"
    {
      if((yyvsp[0].relation_list) != nullptr){
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->push_back((yyvsp[-1].string));
    }
#line 1935 "yacc_sql.cpp"
    break;

  case 38:
#line 363 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1947 "yacc_sql.cpp"
    break;

  case 39:
#line 373 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 1967 "yacc_sql.cpp"
    break;

  case 40:
#line 391 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1975 "yacc_sql.cpp"
    break;

  case 41:
#line 395 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 1989 "yacc_sql.cpp"
    break;

  case 42:
#line 408 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-5].string));
    }
#line 2002 "yacc_sql.cpp"
    break;

  case 43:
#line 417 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-6].string));
    }
#line 2015 "yacc_sql.cpp"
    break;

  case 44:
#line 426 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-4].string));
    }
#line 2028 "yacc_sql.cpp"
    break;

  case 45:
#line 435 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-2].string));
    }
#line 2041 "yacc_sql.cpp"
    break;

  case 46:
#line 444 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-3].string));
    }
#line 2054 "yacc_sql.cpp"
    break;

  case 47:
#line 453 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-1].string));
    }
#line 2067 "yacc_sql.cpp"
    break;

  case 48:
#line 463 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2073 "yacc_sql.cpp"
    break;

  case 49:
#line 466 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2079 "yacc_sql.cpp"
    break;

  case 50:
#line 467 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2085 "yacc_sql.cpp"
    break;

  case 51:
#line 468 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2091 "yacc_sql.cpp"
    break;

  case 52:
#line 469 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2097 "yacc_sql.cpp"
    break;

  case 53:
#line 473 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-3].string);
      if ((yyvsp[0].tuple_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[0].tuple_list));
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-1].tuple));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-1].tuple);
      free((yyvsp[-3].string));
    }
#line 2113 "yacc_sql.cpp"
    break;

  case 54:
#line 487 "yacc_sql.y"
    {
      (yyval.tuple_list) = nullptr;
    }
#line 2121 "yacc_sql.cpp"
    break;

  case 55:
#line 490 "yacc_sql.y"
                             {
      if ((yyvsp[0].tuple_list) != nullptr){
        (yyval.tuple_list) = (yyvsp[0].tuple_list);
      } else {
        (yyval.tuple_list) = new std::vector<std::vector<Value>>;
      }
      (yyval.tuple_list)->emplace_back(*(yyvsp[-1].tuple));
      delete (yyvsp[-1].tuple);
    }
#line 2135 "yacc_sql.cpp"
    break;

  case 56:
#line 500 "yacc_sql.y"
                                   {
      if ((yyvsp[-1].value_list) != nullptr){
        (yyval.tuple) = (yyvsp[-1].value_list);
      } else {
        (yyval.tuple) = new std::vector<Value>;
      }
      (yyval.tuple)->emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.tuple)->begin(), (yyval.tuple)->end());
      delete (yyvsp[-2].value);
    }
#line 2150 "yacc_sql.cpp"
    break;

  case 57:
#line 513 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2158 "yacc_sql.cpp"
    break;

  case 58:
#line 516 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2172 "yacc_sql.cpp"
    break;

  case 59:
#line 527 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2181 "yacc_sql.cpp"
    break;

  case 60:
#line 531 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2190 "yacc_sql.cpp"
    break;

  case 61:
#line 535 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2200 "yacc_sql.cpp"
    break;

  case 62:
#line 540 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2210 "yacc_sql.cpp"
    break;

  case 63:
#line 545 "yacc_sql.y"
                 {
      (yyval.value) = new Value();
      (yyval.value)->set_isnull();
    }
#line 2219 "yacc_sql.cpp"
    break;

  case 64:
#line 553 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2233 "yacc_sql.cpp"
    break;

  case 65:
#line 565 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      if((yyvsp[-1].update_value_list) == nullptr){
        (yyvsp[-1].update_value_list) = new std::vector<UpdateValue>;
      }
      (yyvsp[-1].update_value_list)->push_back(*(yyvsp[-2].update_value));
      (yyval.sql_node)->update.relation_name = (yyvsp[-4].string);
      for(auto &value : *(yyvsp[-1].update_value_list)){
        (yyval.sql_node)->update.attribute_name.push_back(value.attribute_name);
      }
      (yyval.sql_node)->update.value.swap(*(yyvsp[-1].update_value_list));
      // for(auto &value : *$5){
      //   push_back(value.value);
      // }
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-4].string));
      free((yyvsp[-2].update_value));
      free((yyvsp[-1].update_value_list));
    }
#line 2260 "yacc_sql.cpp"
    break;

  case 66:
#line 591 "yacc_sql.y"
    {
      (yyval.update_value) = new UpdateValue;
      (yyval.update_value)->attribute_name = (yyvsp[-2].string);
      (yyval.update_value)->value = *(yyvsp[0].value);
      (yyval.update_value)->is_stmt = false;
    }
#line 2271 "yacc_sql.cpp"
    break;

  case 67:
#line 598 "yacc_sql.y"
    {
      (yyval.update_value) = new UpdateValue;
      (yyval.update_value)->attribute_name = (yyvsp[-4].string);
      (yyval.update_value)->is_stmt = true;
      (yyval.update_value)->stmt = (yyvsp[-1].sql_node);
    }
#line 2282 "yacc_sql.cpp"
    break;

  case 68:
#line 608 "yacc_sql.y"
    {
      (yyval.update_value_list) = nullptr;
    }
#line 2290 "yacc_sql.cpp"
    break;

  case 69:
#line 612 "yacc_sql.y"
    {
      if ((yyvsp[0].update_value_list) == nullptr){
        (yyval.update_value_list) = new std::vector<UpdateValue>;
      }else {
        (yyval.update_value_list) = (yyvsp[0].update_value_list);
      }
      (yyval.update_value_list)->push_back(*(yyvsp[-1].update_value));
    }
#line 2303 "yacc_sql.cpp"
    break;

  case 70:
#line 622 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-8].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-8].rel_attr_list));
        delete (yyvsp[-8].rel_attr_list);
      }
      if ((yyvsp[-5].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-5].relation_list));
        delete (yyvsp[-5].relation_list);
      }
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-6].string));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());
      if ((yyvsp[-4].join_list) != nullptr) {
        (yyval.sql_node)->selection.joinctions.swap(*(yyvsp[-4].join_list));
        delete (yyvsp[-4].join_list);
      }
      if ((yyvsp[-3].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-3].condition_list));
        delete (yyvsp[-3].condition_list);
      }
      if ((yyvsp[-2].order_by_attr_list) != nullptr) {
        (yyval.sql_node)->selection.orderby.swap(*(yyvsp[-2].order_by_attr_list));
        delete (yyvsp[-2].order_by_attr_list);
      }
      if ((yyvsp[-1].rel_attr_list) != nullptr){
        (yyval.sql_node)->selection.groupby.swap(*(yyvsp[-1].rel_attr_list));
      }
      if ((yyvsp[0].condition_list) != nullptr){
        (yyval.sql_node)->selection.having.swap(*(yyvsp[0].condition_list));
      }
      free((yyvsp[-6].string));
    }
#line 2340 "yacc_sql.cpp"
    break;

  case 71:
#line 657 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2351 "yacc_sql.cpp"
    break;

  case 72:
#line 667 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2360 "yacc_sql.cpp"
    break;

  case 73:
#line 672 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2373 "yacc_sql.cpp"
    break;

  case 74:
#line 682 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2381 "yacc_sql.cpp"
    break;

  case 75:
#line 685 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2389 "yacc_sql.cpp"
    break;

  case 76:
#line 688 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2397 "yacc_sql.cpp"
    break;

  case 77:
#line 691 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2405 "yacc_sql.cpp"
    break;

  case 78:
#line 694 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2414 "yacc_sql.cpp"
    break;

  case 79:
#line 698 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2422 "yacc_sql.cpp"
    break;

  case 80:
#line 701 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2432 "yacc_sql.cpp"
    break;

  case 81:
#line 709 "yacc_sql.y"
                       {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2446 "yacc_sql.cpp"
    break;

  case 82:
#line 718 "yacc_sql.y"
                          {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2460 "yacc_sql.cpp"
    break;

  case 83:
#line 730 "yacc_sql.y"
        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = "";
      (yyval.rel_attr)->attribute_name = "*";;
    }
#line 2470 "yacc_sql.cpp"
    break;

  case 84:
#line 735 "yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2480 "yacc_sql.cpp"
    break;

  case 85:
#line 740 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2492 "yacc_sql.cpp"
    break;

  case 86:
#line 751 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2500 "yacc_sql.cpp"
    break;

  case 87:
#line 754 "yacc_sql.y"
                               {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2515 "yacc_sql.cpp"
    break;

  case 88:
#line 764 "yacc_sql.y"
                                {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2529 "yacc_sql.cpp"
    break;

  case 89:
#line 777 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2537 "yacc_sql.cpp"
    break;

  case 90:
#line 780 "yacc_sql.y"
                        {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }

      (yyval.relation_list)->push_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2552 "yacc_sql.cpp"
    break;

  case 91:
#line 794 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggregation_type = AggregationType::MIN;
    }
#line 2561 "yacc_sql.cpp"
    break;

  case 92:
#line 799 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggregation_type = AggregationType::MAX;
    }
#line 2570 "yacc_sql.cpp"
    break;

  case 93:
#line 804 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggregation_type = AggregationType::COUNT;
    }
#line 2579 "yacc_sql.cpp"
    break;

  case 94:
#line 809 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggregation_type = AggregationType::AVG;
    }
#line 2588 "yacc_sql.cpp"
    break;

  case 95:
#line 814 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggregation_type = AggregationType::SUM;
    }
#line 2597 "yacc_sql.cpp"
    break;

  case 96:
#line 821 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2605 "yacc_sql.cpp"
    break;

  case 97:
#line 825 "yacc_sql.y"
    {
      if((yyvsp[0].rel_attr_list) != nullptr){
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2619 "yacc_sql.cpp"
    break;

  case 98:
#line 837 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2627 "yacc_sql.cpp"
    break;

  case 99:
#line 841 "yacc_sql.y"
    {
      if((yyvsp[0].condition_list) != nullptr){
        (yyval.condition_list) = (yyvsp[0].condition_list);
      } else {
        (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      }
      (yyval.condition_list)->emplace_back(*(yyvsp[-1].condition));
      delete (yyvsp[-1].condition);
    }
#line 2641 "yacc_sql.cpp"
    break;

  case 100:
#line 853 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2649 "yacc_sql.cpp"
    break;

  case 101:
#line 857 "yacc_sql.y"
    {
      if((yyvsp[0].condition_list) != nullptr){
        (yyval.condition_list) = (yyvsp[0].condition_list);
      } else {
        (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      }
      (yyval.condition_list)->emplace_back(*(yyvsp[-1].condition));
      delete (yyvsp[-1].condition);
    }
#line 2663 "yacc_sql.cpp"
    break;

  case 102:
#line 870 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 2679 "yacc_sql.cpp"
    break;

  case 103:
#line 883 "yacc_sql.y"
    {
      (yyval.join_node) = new JoinSqlNode{(yyvsp[-2].string),*(yyvsp[0].condition_list)};
      delete (yyvsp[-2].string);
      delete (yyvsp[0].condition_list);
    }
#line 2689 "yacc_sql.cpp"
    break;

  case 104:
#line 892 "yacc_sql.y"
    {
      (yyval.join_list) = nullptr;
    }
#line 2697 "yacc_sql.cpp"
    break;

  case 105:
#line 896 "yacc_sql.y"
    {
      (yyval.join_list) = new std::vector<JoinSqlNode>{*(yyvsp[0].join_node)};
      delete (yyvsp[0].join_node);   
    }
#line 2706 "yacc_sql.cpp"
    break;

  case 106:
#line 901 "yacc_sql.y"
    {
      (yyval.join_list)->emplace_back(*(yyvsp[0].join_node));
      delete (yyvsp[0].join_node);

    }
#line 2716 "yacc_sql.cpp"
    break;

  case 107:
#line 910 "yacc_sql.y"
    {
      (yyval.order_by_attr_list) = nullptr;
    }
#line 2724 "yacc_sql.cpp"
    break;

  case 108:
#line 914 "yacc_sql.y"
    {
      (yyval.order_by_attr_list) = new std::vector<OrderBySqlNode>;
      if((yyvsp[0].order_by_attr_list) != nullptr){
        (yyval.order_by_attr_list)->swap(*(yyvsp[0].order_by_attr_list));
        delete (yyvsp[0].order_by_attr_list);
      }
      (yyval.order_by_attr_list)->push_back(*(yyvsp[-1].order_by_attr));
      std::reverse((yyval.order_by_attr_list)->begin(), (yyval.order_by_attr_list)->end());
      delete (yyvsp[-1].order_by_attr);
    }
#line 2739 "yacc_sql.cpp"
    break;

  case 109:
#line 928 "yacc_sql.y"
    {
      (yyval.order_by_attr_list) = nullptr;
    }
#line 2747 "yacc_sql.cpp"
    break;

  case 110:
#line 932 "yacc_sql.y"
    {
      if((yyvsp[0].order_by_attr_list) != nullptr){
        (yyval.order_by_attr_list) = (yyvsp[0].order_by_attr_list);
      } else {
        (yyval.order_by_attr_list) = new std::vector<OrderBySqlNode>;
      }
      (yyval.order_by_attr_list)->push_back(*(yyvsp[-1].order_by_attr));
    }
#line 2760 "yacc_sql.cpp"
    break;

  case 111:
#line 943 "yacc_sql.y"
    {
      (yyval.order_by_attr) = new OrderBySqlNode;
      (yyval.order_by_attr)->relation_name = std::move((yyvsp[-1].rel_attr)->relation_name);
      (yyval.order_by_attr)->attribute_name = std::move((yyvsp[-1].rel_attr)->attribute_name);
      (yyval.order_by_attr)->is_desc = true;
      free((yyvsp[-1].rel_attr));
    }
#line 2772 "yacc_sql.cpp"
    break;

  case 112:
#line 951 "yacc_sql.y"
    {
      (yyval.order_by_attr) = new OrderBySqlNode;
      (yyval.order_by_attr)->relation_name = std::move((yyvsp[-1].rel_attr)->relation_name);
      (yyval.order_by_attr)->attribute_name = std::move((yyvsp[-1].rel_attr)->attribute_name);
      (yyval.order_by_attr)->is_desc = false;
      free((yyvsp[-1].rel_attr));
    }
#line 2784 "yacc_sql.cpp"
    break;

  case 113:
#line 958 "yacc_sql.y"
    {
      (yyval.order_by_attr) = new OrderBySqlNode;
      (yyval.order_by_attr)->relation_name = std::move((yyvsp[0].rel_attr)->relation_name);
      (yyval.order_by_attr)->attribute_name = std::move((yyvsp[0].rel_attr)->attribute_name);
      (yyval.order_by_attr)->is_desc = false;
      free((yyvsp[0].rel_attr));
    }
#line 2796 "yacc_sql.cpp"
    break;

  case 114:
#line 967 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2804 "yacc_sql.cpp"
    break;

  case 115:
#line 970 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2812 "yacc_sql.cpp"
    break;

  case 116:
#line 976 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2820 "yacc_sql.cpp"
    break;

  case 117:
#line 979 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2830 "yacc_sql.cpp"
    break;

  case 118:
#line 984 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2840 "yacc_sql.cpp"
    break;

  case 119:
#line 992 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 2856 "yacc_sql.cpp"
    break;

  case 120:
#line 1004 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 2872 "yacc_sql.cpp"
    break;

  case 121:
#line 1016 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 2888 "yacc_sql.cpp"
    break;

  case 122:
#line 1028 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].rel_attr);
    }
#line 2904 "yacc_sql.cpp"
    break;

  case 123:
#line 1040 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = CompOp::LIKE_OP;
    }
#line 2917 "yacc_sql.cpp"
    break;

  case 124:
#line 1049 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-3].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = CompOp::NOT_LIKE_OP;
    }
#line 2930 "yacc_sql.cpp"
    break;

  case 125:
#line 1058 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->comp = CompOp::IS_NULL;
    }
#line 2941 "yacc_sql.cpp"
    break;

  case 126:
#line 1065 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-3].rel_attr);
      (yyval.condition)->comp = CompOp::IS_NOT_NULL;
    }
#line 2952 "yacc_sql.cpp"
    break;

  case 127:
#line 1072 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->comp = CompOp::IS_NULL;
    }
#line 2964 "yacc_sql.cpp"
    break;

  case 128:
#line 1080 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-3].value);
      (yyval.condition)->comp = CompOp::IS_NOT_NULL;
    }
#line 2976 "yacc_sql.cpp"
    break;

  case 129:
#line 1088 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 2;
      (yyval.condition)->left_sub_query = (yyvsp[-5].sql_node);
      (yyval.condition)->right_is_attr = 2;
      (yyval.condition)->right_sub_query = (yyvsp[-1].sql_node);
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 2989 "yacc_sql.cpp"
    break;

  case 130:
#line 1097 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_is_attr = 2;
      (yyval.condition)->right_sub_query = (yyvsp[-1].sql_node);
      (yyval.condition)->comp = (yyvsp[-3].comp);

      delete (yyvsp[-4].rel_attr);
    }
#line 3004 "yacc_sql.cpp"
    break;

  case 131:
#line 1108 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 2;
      (yyval.condition)->left_sub_query = (yyvsp[-3].sql_node);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].rel_attr);
    }
#line 3019 "yacc_sql.cpp"
    break;

  case 132:
#line 1119 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 3;
      (yyval.condition)->right_value_list = *(yyvsp[0].tuple);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
    }
#line 3034 "yacc_sql.cpp"
    break;

  case 133:
#line 1132 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3040 "yacc_sql.cpp"
    break;

  case 134:
#line 1133 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3046 "yacc_sql.cpp"
    break;

  case 135:
#line 1134 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3052 "yacc_sql.cpp"
    break;

  case 136:
#line 1135 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3058 "yacc_sql.cpp"
    break;

  case 137:
#line 1136 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3064 "yacc_sql.cpp"
    break;

  case 138:
#line 1137 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3070 "yacc_sql.cpp"
    break;

  case 139:
#line 1138 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3076 "yacc_sql.cpp"
    break;

  case 140:
#line 1139 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP; }
#line 3082 "yacc_sql.cpp"
    break;

  case 141:
#line 1144 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3096 "yacc_sql.cpp"
    break;

  case 142:
#line 1157 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3105 "yacc_sql.cpp"
    break;

  case 143:
#line 1165 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3117 "yacc_sql.cpp"
    break;


#line 3121 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1177 "yacc_sql.y"

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
