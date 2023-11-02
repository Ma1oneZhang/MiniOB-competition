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
    ROUND = 279,
    LENGTH = 280,
    DATE_FORMAT = 281,
    INNER = 282,
    JOIN = 283,
    RBRACE = 284,
    COMMA = 285,
    ORDER = 286,
    GROUP = 287,
    BY = 288,
    HAVING = 289,
    ASC = 290,
    TRX_BEGIN = 291,
    TRX_COMMIT = 292,
    TRX_ROLLBACK = 293,
    INT_T = 294,
    STRING_T = 295,
    FLOAT_T = 296,
    DATE_T = 297,
    HELP = 298,
    EXIT = 299,
    DOT = 300,
    INTO = 301,
    VALUES = 302,
    FROM = 303,
    WHERE = 304,
    LIKE = 305,
    NOT = 306,
    AND = 307,
    OR = 308,
    SET = 309,
    ON = 310,
    LOAD = 311,
    DATA = 312,
    INFILE = 313,
    EXPLAIN = 314,
    IS = 315,
    NULL_TOKEN = 316,
    IN = 317,
    EQ = 318,
    LT = 319,
    GT = 320,
    LE = 321,
    GE = 322,
    NE = 323,
    NUMBER = 324,
    FLOAT = 325,
    ID = 326,
    SSS = 327,
    DATE_STR = 328,
    UMINUS = 329
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 125 "yacc_sql.y"

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

#line 268 "yacc_sql.cpp"

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
#define YYFINAL  78
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   392

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  145
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  295

#define YYUNDEFTOK  2
#define YYMAXUTOK   329


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
       2,     2,    76,    74,     2,    75,     2,    77,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    78
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   219,   219,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   251,   257,   262,   268,   274,   280,
     286,   293,   298,   304,   312,   329,   350,   353,   364,   374,
     393,   396,   409,   418,   427,   436,   445,   454,   465,   468,
     469,   470,   471,   474,   489,   492,   502,   515,   518,   529,
     533,   537,   542,   547,   554,   566,   592,   599,   610,   613,
     623,   631,   666,   676,   681,   692,   695,   698,   701,   704,
     708,   711,   716,   720,   726,   731,   736,   741,   749,   754,
     759,   766,   771,   776,   781,   786,   795,   798,   810,   813,
     828,   831,   843,   846,   859,   862,   875,   888,   898,   901,
     906,   916,   919,   934,   937,   948,   956,   963,   973,   976,
     982,   985,   990,   996,  1004,  1013,  1022,  1031,  1042,  1053,
    1062,  1071,  1080,  1092,  1093,  1094,  1095,  1096,  1097,  1098,
    1099,  1103,  1116,  1124,  1134,  1135
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
  "SUM", "ROUND", "LENGTH", "DATE_FORMAT", "INNER", "JOIN", "RBRACE",
  "COMMA", "ORDER", "GROUP", "BY", "HAVING", "ASC", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "LIKE", "NOT",
  "AND", "OR", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "IS",
  "NULL_TOKEN", "IN", "EQ", "LT", "GT", "LE", "GE", "NE", "NUMBER",
  "FLOAT", "ID", "SSS", "DATE_STR", "'+'", "'-'", "'*'", "'/'", "UMINUS",
  "$accept", "commands", "command_wrapper", "exit_stmt", "help_stmt",
  "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "show_index_stmt",
  "desc_table_stmt", "create_index_stmt", "index_field_list",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "number", "type", "insert_stmt", "tuple_list", "tuple", "value_list",
  "value", "delete_stmt", "update_stmt", "update_attr", "update_attr_list",
  "select_stmt", "calc_stmt", "expression_list", "expression", "rel_attr",
  "attr_list", "rel_list", "group_by", "having", "having_list",
  "having_attr", "join_node", "join_list", "order_by",
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
     325,   326,   327,   328,    43,    45,    42,    47,   329
};
# endif

#define YYPACT_NINF (-210)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-58)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     286,    95,     9,    61,    61,   -55,    97,  -210,    -2,     0,
      -8,  -210,  -210,  -210,  -210,  -210,     8,    53,   286,    55,
     132,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210,  -210,    78,    79,   139,    80,    92,    61,   147,   152,
     154,   160,   161,   164,   171,   172,  -210,  -210,  -210,   149,
    -210,  -210,    61,  -210,  -210,  -210,   108,  -210,   165,  -210,
    -210,   166,   126,   138,   174,   155,   157,  -210,  -210,  -210,
    -210,   210,   176,   158,  -210,   185,   -10,    17,    17,    17,
      17,    17,    61,    61,    61,   170,   175,    61,  -210,    61,
      61,    61,    61,   180,   183,   196,   206,   189,   -20,   191,
     193,   194,   190,   195,  -210,   239,   248,   249,   250,   251,
      91,    99,   182,  -210,  -210,    48,    48,   175,   175,   257,
    -210,   275,   135,  -210,   230,   264,  -210,   259,    76,   280,
     294,   241,  -210,  -210,  -210,  -210,  -210,  -210,  -210,    61,
    -210,    61,   242,   287,   -20,   295,     1,   284,  -210,    74,
      39,   189,   206,   320,  -210,  -210,  -210,  -210,    -4,   193,
     298,   260,   311,   124,   173,   257,   304,  -210,     2,   303,
     275,  -210,   307,    61,    45,   -16,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,   200,   135,   135,   327,  -210,   264,  -210,
     267,   270,   282,  -210,   280,  -210,   323,   283,  -210,  -210,
    -210,   285,  -210,   310,   -20,   328,   295,   253,    68,    61,
    -210,   301,  -210,     1,  -210,    68,  -210,  -210,   334,  -210,
    -210,  -210,   335,  -210,  -210,   296,   336,   323,   313,   333,
     337,   303,  -210,  -210,   308,   213,    68,  -210,   111,   342,
    -210,     7,   323,  -210,   343,   135,    17,   340,   341,  -210,
       1,    68,  -210,   315,  -210,  -210,  -210,  -210,    -1,   344,
      61,    17,  -210,   348,  -210,  -210,  -210,    17,  -210,   232,
     253,   349,  -210,   344,    61,  -210,   -20,    17,  -210,  -210,
     232,  -210,   349,  -210,  -210
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
      20,    21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,    59,    60,    89,
      61,    62,     0,    88,    81,    72,    73,    82,    70,    33,
      31,     0,     0,     0,     0,     0,     0,   142,     1,   145,
       2,     0,     0,     0,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    80,     0,    87,     0,
       0,     0,     0,     0,     0,     0,   118,     0,     0,     0,
       0,     0,     0,     0,    79,     0,     0,     0,     0,     0,
       0,     0,     0,    90,    74,    75,    76,    77,    78,    98,
      32,     0,   120,    64,     0,    68,   143,     0,     0,    40,
       0,     0,    38,    92,    91,    93,    94,    95,    83,     0,
      85,     0,     0,   108,     0,    54,     0,     0,   119,   121,
       0,     0,   118,     0,    49,    50,    51,    52,    47,     0,
       0,     0,     0,     0,     0,    98,     0,   109,   118,    57,
       0,    53,     0,     0,     0,     0,   139,   133,   134,   135,
     136,   137,   138,     0,   120,   120,     0,    66,    68,    65,
       0,     0,     0,    45,    40,    39,    36,     0,    84,    86,
      99,     0,   110,   111,     0,     0,    54,     0,   125,     0,
     140,     0,   127,     0,   132,   124,   122,   123,     0,    69,
     141,    48,     0,    46,    41,     0,     0,    36,     0,     0,
     100,    57,    56,    55,     0,     0,   126,   128,    81,     0,
      67,    44,    36,    34,     0,   120,     0,     0,   102,    58,
       0,   131,   130,     0,    42,    37,    35,   107,   117,   113,
       0,     0,    71,     0,    43,   115,   116,     0,   112,    96,
       0,   104,   129,   113,     0,   101,     0,     0,   103,   114,
      96,   106,   104,    97,   105
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -210,  -210,   360,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,  -209,  -210,  -210,   177,   211,  -210,
    -210,  -210,   167,  -147,   141,  -100,  -210,  -210,   223,   187,
    -154,  -210,     5,    -3,   -84,    96,   212,  -210,  -210,    98,
     101,   214,  -210,  -210,   106,   114,  -148,  -163,  -210,  -205,
    -210,  -210,  -210,  -210
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,   236,    32,    33,   170,   139,   232,
     168,    34,   181,   155,   215,    64,    35,    36,   135,   162,
      37,    38,    65,    86,    67,   285,   153,   258,   272,   288,
     281,   177,   178,   240,   278,   269,   133,   158,   159,   193,
      39,    40,    41,    80
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      66,    66,   182,   115,   116,   117,   118,   119,   136,    68,
     275,     4,   245,   201,   199,    45,    69,    46,    47,   114,
      48,    49,    50,    51,    52,    53,    54,    55,   254,   176,
     213,   226,   227,   216,   276,   221,    48,    49,    50,    51,
      52,    56,   228,   265,    72,   222,   224,   202,    73,    57,
      58,   132,    60,    61,   179,    78,   196,   203,   263,    96,
     197,    98,    56,    74,    99,   100,   101,   102,   264,   249,
      57,    58,    59,    60,    61,   286,    62,    63,    47,    75,
      48,    49,    50,    51,    52,    53,    54,    55,    59,   120,
     121,   122,   267,    63,    66,   219,   125,   126,   127,   128,
      56,    42,   124,    43,    70,    71,   273,   220,    57,    58,
      76,    60,    61,    44,   241,   164,   165,   166,   167,    98,
     148,   149,    56,   248,   101,   102,   194,   195,   150,   157,
      57,    58,    59,    60,    61,    79,    62,    63,    97,    98,
     -57,   214,    99,   100,   101,   102,   173,    83,   174,    81,
      82,    84,   156,   208,    48,    49,    50,    51,    52,    53,
      54,    55,    98,    85,    87,    99,   100,   101,   102,    88,
      98,    89,   268,    99,   100,   101,   102,    90,    91,    98,
     218,    92,    99,   100,   101,   102,   291,   280,    93,    94,
     225,   157,   157,   268,    95,    98,    56,   105,    99,   100,
     101,   102,   209,   280,    57,    58,    59,    60,    61,   106,
      62,    63,   151,   103,   104,   109,   246,   223,   108,    48,
      49,    50,    51,    52,    53,    54,    55,   110,   107,   112,
     260,   111,    48,    49,    50,    51,    52,    53,    54,    55,
     113,   123,   261,   131,    98,   141,    98,    99,   100,   101,
     102,   129,   157,    98,   130,   132,    99,   100,   101,   102,
     134,    56,   284,   137,   138,   140,   142,   279,   143,    57,
      58,    59,    60,    61,    56,    62,    63,   144,   145,   146,
     147,   290,    57,    58,    59,    60,    61,   152,    62,    63,
       1,     2,   154,   160,   161,     3,     4,     5,     6,     7,
       8,     9,    10,    98,   244,   163,    99,   100,   101,   102,
     169,   171,   172,   175,   176,   186,   187,   188,   189,   190,
     191,   192,    11,    12,    13,   180,   200,   205,   207,    14,
      15,   206,   211,   214,   183,   184,   217,     4,   230,   231,
      16,   239,    17,   233,   185,    18,   186,   187,   188,   189,
     190,   191,   192,   235,   237,    98,   238,   242,    99,   100,
     101,   102,   247,   250,   251,   253,   256,   252,   255,   257,
     220,   262,   266,   270,   277,   271,   274,   282,    77,   287,
     204,   234,   259,   243,   198,   229,   293,   210,   292,   289,
     294,   283,   212
};

static const yytype_int16 yycheck[] =
{
       3,     4,   156,    87,    88,    89,    90,    91,   108,     4,
      11,    10,   217,    17,   162,     6,    71,     8,    17,    29,
      19,    20,    21,    22,    23,    24,    25,    26,   237,    27,
     178,   194,   195,   180,    35,    51,    19,    20,    21,    22,
      23,    61,   196,   252,    46,    61,   193,    51,    48,    69,
      70,    49,    72,    73,   154,     0,    17,    61,    51,    62,
     160,    71,    61,    71,    74,    75,    76,    77,    61,   223,
      69,    70,    71,    72,    73,   280,    75,    76,    17,    71,
      19,    20,    21,    22,    23,    24,    25,    26,    71,    92,
      93,    94,   255,    76,    97,    50,    99,   100,   101,   102,
      61,     6,    97,     8,     7,     8,   260,    62,    69,    70,
      57,    72,    73,    18,   214,    39,    40,    41,    42,    71,
      29,    30,    61,   223,    76,    77,    52,    53,    29,   132,
      69,    70,    71,    72,    73,     3,    75,    76,    30,    71,
      29,    30,    74,    75,    76,    77,   149,     8,   151,    71,
      71,    71,    17,    29,    19,    20,    21,    22,    23,    24,
      25,    26,    71,    71,    17,    74,    75,    76,    77,    17,
      71,    17,   256,    74,    75,    76,    77,    17,    17,    71,
     183,    17,    74,    75,    76,    77,   286,   271,    17,    17,
     193,   194,   195,   277,    45,    71,    61,    71,    74,    75,
      76,    77,    29,   287,    69,    70,    71,    72,    73,    71,
      75,    76,    30,    48,    48,    58,   219,    17,    63,    19,
      20,    21,    22,    23,    24,    25,    26,    17,    54,    71,
      17,    55,    19,    20,    21,    22,    23,    24,    25,    26,
      55,    71,   245,    47,    71,    55,    71,    74,    75,    76,
      77,    71,   255,    71,    71,    49,    74,    75,    76,    77,
      71,    61,    30,    72,    71,    71,    71,   270,    29,    69,
      70,    71,    72,    73,    61,    75,    76,    29,    29,    29,
      29,   284,    69,    70,    71,    72,    73,    30,    75,    76,
       4,     5,    17,    63,    30,     9,    10,    11,    12,    13,
      14,    15,    16,    71,    51,    46,    74,    75,    76,    77,
      30,    17,    71,    71,    27,    62,    63,    64,    65,    66,
      67,    68,    36,    37,    38,    30,     6,    29,    17,    43,
      44,    71,    28,    30,    50,    51,    29,    10,    71,    69,
      54,    31,    56,    61,    60,    59,    62,    63,    64,    65,
      66,    67,    68,    30,    71,    71,    71,    29,    74,    75,
      76,    77,    61,    29,    29,    29,    33,    71,    55,    32,
      62,    29,    29,    33,    30,    34,    61,    29,    18,    30,
     169,   204,   241,   216,   161,   198,   290,   175,   287,   283,
     292,   277,   178
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    15,
      16,    36,    37,    38,    43,    44,    54,    56,    59,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    94,    95,   100,   105,   106,   109,   110,   129,
     130,   131,     6,     8,    18,     6,     8,    17,    19,    20,
      21,    22,    23,    24,    25,    26,    61,    69,    70,    71,
      72,    73,    75,    76,   104,   111,   112,   113,   111,    71,
       7,     8,    46,    48,    71,    71,    57,    81,     0,     3,
     132,    71,    71,     8,    71,    71,   112,    17,    17,    17,
      17,    17,    17,    17,    17,    45,   112,    30,    71,    74,
      75,    76,    77,    48,    48,    71,    71,    54,    63,    58,
      17,    55,    71,    55,    29,   113,   113,   113,   113,   113,
     112,   112,   112,    71,   111,   112,   112,   112,   112,    71,
      71,    47,    49,   125,    71,   107,   104,    72,    71,    97,
      71,    55,    71,    29,    29,    29,    29,    29,    29,    30,
      29,    30,    30,   115,    17,   102,    17,   112,   126,   127,
      63,    30,   108,    46,    39,    40,    41,    42,    99,    30,
      96,    17,    71,   112,   112,    71,    27,   120,   121,   104,
      30,   101,   109,    50,    51,    60,    62,    63,    64,    65,
      66,    67,    68,   128,    52,    53,    17,   104,   107,   125,
       6,    17,    51,    61,    97,    29,    71,    17,    29,    29,
     115,    28,   120,   125,    30,   103,   102,    29,   112,    50,
      62,    51,    61,    17,   102,   112,   126,   126,   109,   108,
      71,    69,    98,    61,    96,    30,    93,    71,    71,    31,
     122,   104,    29,   101,    51,   128,   112,    61,   104,   109,
      29,    29,    71,    29,    93,    55,    33,    32,   116,   103,
      17,   112,    29,    51,    61,    93,    29,   126,   113,   124,
      33,    34,   117,   109,    61,    11,    35,    30,   123,   112,
     113,   119,    29,   124,    30,   114,   128,    30,   118,   123,
     112,   104,   119,   114,   118
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    92,    93,    93,    94,    95,
      96,    96,    97,    97,    97,    97,    97,    97,    98,    99,
      99,    99,    99,   100,   101,   101,   102,   103,   103,   104,
     104,   104,   104,   104,   105,   106,   107,   107,   108,   108,
     109,   109,   110,   111,   111,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   113,   113,
     113,   113,   113,   113,   113,   113,   114,   114,   115,   115,
     116,   116,   117,   117,   118,   118,   119,   120,   121,   121,
     121,   122,   122,   123,   123,   124,   124,   124,   125,   125,
     126,   126,   126,   126,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   128,   128,   128,   128,   128,   128,   128,
     128,   129,   130,   131,   132,   132
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
       2,    10,     2,     1,     3,     3,     3,     3,     3,     3,
       2,     1,     1,     4,     6,     4,     6,     2,     1,     1,
       3,     4,     4,     4,     4,     4,     0,     3,     0,     3,
       0,     4,     0,     3,     0,     3,     3,     5,     0,     1,
       2,     0,     4,     0,     3,     2,     2,     1,     0,     2,
       0,     1,     3,     3,     3,     3,     4,     3,     4,     7,
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
#line 220 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1808 "yacc_sql.cpp"
    break;

  case 24:
#line 251 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1817 "yacc_sql.cpp"
    break;

  case 25:
#line 257 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1825 "yacc_sql.cpp"
    break;

  case 26:
#line 262 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1833 "yacc_sql.cpp"
    break;

  case 27:
#line 268 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1841 "yacc_sql.cpp"
    break;

  case 28:
#line 274 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1849 "yacc_sql.cpp"
    break;

  case 29:
#line 280 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1857 "yacc_sql.cpp"
    break;

  case 30:
#line 286 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1867 "yacc_sql.cpp"
    break;

  case 31:
#line 293 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1875 "yacc_sql.cpp"
    break;

  case 32:
#line 298 "yacc_sql.y"
                       {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1885 "yacc_sql.cpp"
    break;

  case 33:
#line 304 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1895 "yacc_sql.cpp"
    break;

  case 34:
#line 313 "yacc_sql.y"
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
#line 1916 "yacc_sql.cpp"
    break;

  case 35:
#line 330 "yacc_sql.y"
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
#line 1937 "yacc_sql.cpp"
    break;

  case 36:
#line 350 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 1945 "yacc_sql.cpp"
    break;

  case 37:
#line 354 "yacc_sql.y"
    {
      if((yyvsp[0].relation_list) != nullptr){
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->push_back((yyvsp[-1].string));
    }
#line 1958 "yacc_sql.cpp"
    break;

  case 38:
#line 365 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1970 "yacc_sql.cpp"
    break;

  case 39:
#line 375 "yacc_sql.y"
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
#line 1990 "yacc_sql.cpp"
    break;

  case 40:
#line 393 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1998 "yacc_sql.cpp"
    break;

  case 41:
#line 397 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2012 "yacc_sql.cpp"
    break;

  case 42:
#line 410 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-5].string));
    }
#line 2025 "yacc_sql.cpp"
    break;

  case 43:
#line 419 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-6].string));
    }
#line 2038 "yacc_sql.cpp"
    break;

  case 44:
#line 428 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-4].string));
    }
#line 2051 "yacc_sql.cpp"
    break;

  case 45:
#line 437 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-2].string));
    }
#line 2064 "yacc_sql.cpp"
    break;

  case 46:
#line 446 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-3].string));
    }
#line 2077 "yacc_sql.cpp"
    break;

  case 47:
#line 455 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-1].string));
    }
#line 2090 "yacc_sql.cpp"
    break;

  case 48:
#line 465 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2096 "yacc_sql.cpp"
    break;

  case 49:
#line 468 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2102 "yacc_sql.cpp"
    break;

  case 50:
#line 469 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2108 "yacc_sql.cpp"
    break;

  case 51:
#line 470 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2114 "yacc_sql.cpp"
    break;

  case 52:
#line 471 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2120 "yacc_sql.cpp"
    break;

  case 53:
#line 475 "yacc_sql.y"
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
#line 2136 "yacc_sql.cpp"
    break;

  case 54:
#line 489 "yacc_sql.y"
    {
      (yyval.tuple_list) = nullptr;
    }
#line 2144 "yacc_sql.cpp"
    break;

  case 55:
#line 492 "yacc_sql.y"
                             {
      if ((yyvsp[0].tuple_list) != nullptr){
        (yyval.tuple_list) = (yyvsp[0].tuple_list);
      } else {
        (yyval.tuple_list) = new std::vector<std::vector<Value>>;
      }
      (yyval.tuple_list)->emplace_back(*(yyvsp[-1].tuple));
      delete (yyvsp[-1].tuple);
    }
#line 2158 "yacc_sql.cpp"
    break;

  case 56:
#line 502 "yacc_sql.y"
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
#line 2173 "yacc_sql.cpp"
    break;

  case 57:
#line 515 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2181 "yacc_sql.cpp"
    break;

  case 58:
#line 518 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2195 "yacc_sql.cpp"
    break;

  case 59:
#line 529 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2204 "yacc_sql.cpp"
    break;

  case 60:
#line 533 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2213 "yacc_sql.cpp"
    break;

  case 61:
#line 537 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2223 "yacc_sql.cpp"
    break;

  case 62:
#line 542 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2233 "yacc_sql.cpp"
    break;

  case 63:
#line 547 "yacc_sql.y"
                 {
      (yyval.value) = new Value();
      (yyval.value)->set_isnull();
    }
#line 2242 "yacc_sql.cpp"
    break;

  case 64:
#line 555 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2256 "yacc_sql.cpp"
    break;

  case 65:
#line 567 "yacc_sql.y"
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
#line 2283 "yacc_sql.cpp"
    break;

  case 66:
#line 593 "yacc_sql.y"
    {
      (yyval.update_value) = new UpdateValue;
      (yyval.update_value)->attribute_name = (yyvsp[-2].string);
      (yyval.update_value)->value = *(yyvsp[0].value);
      (yyval.update_value)->is_stmt = false;
    }
#line 2294 "yacc_sql.cpp"
    break;

  case 67:
#line 600 "yacc_sql.y"
    {
      (yyval.update_value) = new UpdateValue;
      (yyval.update_value)->attribute_name = (yyvsp[-4].string);
      (yyval.update_value)->is_stmt = true;
      (yyval.update_value)->stmt = (yyvsp[-1].sql_node);
    }
#line 2305 "yacc_sql.cpp"
    break;

  case 68:
#line 610 "yacc_sql.y"
    {
      (yyval.update_value_list) = nullptr;
    }
#line 2313 "yacc_sql.cpp"
    break;

  case 69:
#line 614 "yacc_sql.y"
    {
      if ((yyvsp[0].update_value_list) == nullptr){
        (yyval.update_value_list) = new std::vector<UpdateValue>;
      }else {
        (yyval.update_value_list) = (yyvsp[0].update_value_list);
      }
      (yyval.update_value_list)->push_back(*(yyvsp[-1].update_value));
    }
#line 2326 "yacc_sql.cpp"
    break;

  case 70:
#line 624 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2338 "yacc_sql.cpp"
    break;

  case 71:
#line 632 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-8].expression_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-8].expression_list));
        delete (yyvsp[-8].expression_list);
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
      if ((yyvsp[-1].expression_list) != nullptr){
        (yyval.sql_node)->selection.groupby.swap(*(yyvsp[-1].expression_list));
      }
      if ((yyvsp[0].condition_list) != nullptr){
        (yyval.sql_node)->selection.having.swap(*(yyvsp[0].condition_list));
      }
      free((yyvsp[-6].string));
    }
#line 2375 "yacc_sql.cpp"
    break;

  case 72:
#line 667 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2386 "yacc_sql.cpp"
    break;

  case 73:
#line 677 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2395 "yacc_sql.cpp"
    break;

  case 74:
#line 682 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2408 "yacc_sql.cpp"
    break;

  case 75:
#line 692 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2416 "yacc_sql.cpp"
    break;

  case 76:
#line 695 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2424 "yacc_sql.cpp"
    break;

  case 77:
#line 698 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2432 "yacc_sql.cpp"
    break;

  case 78:
#line 701 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2440 "yacc_sql.cpp"
    break;

  case 79:
#line 704 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2449 "yacc_sql.cpp"
    break;

  case 80:
#line 708 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2457 "yacc_sql.cpp"
    break;

  case 81:
#line 711 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2467 "yacc_sql.cpp"
    break;

  case 82:
#line 716 "yacc_sql.y"
               {
      (yyval.expression) = new FieldExpr(*(yyvsp[0].rel_attr));
      delete (yyvsp[0].rel_attr); 
    }
#line 2476 "yacc_sql.cpp"
    break;

  case 83:
#line 721 "yacc_sql.y"
    {
      auto zero_value = Value(0);
      (yyval.expression) = new RoundFuncExpr((yyvsp[-1].expression), new ValueExpr(zero_value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2486 "yacc_sql.cpp"
    break;

  case 84:
#line 727 "yacc_sql.y"
    {
      (yyval.expression) = new RoundFuncExpr((yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2495 "yacc_sql.cpp"
    break;

  case 85:
#line 732 "yacc_sql.y"
    {
      (yyval.expression) = new LengthFuncExpr((yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));(yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2504 "yacc_sql.cpp"
    break;

  case 86:
#line 737 "yacc_sql.y"
    {
      (yyval.expression) = new DateFormatFuncExpr((yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2513 "yacc_sql.cpp"
    break;

  case 87:
#line 742 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2522 "yacc_sql.cpp"
    break;

  case 88:
#line 749 "yacc_sql.y"
        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = "";
      (yyval.rel_attr)->attribute_name = "*";;
    }
#line 2532 "yacc_sql.cpp"
    break;

  case 89:
#line 754 "yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2542 "yacc_sql.cpp"
    break;

  case 90:
#line 759 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2554 "yacc_sql.cpp"
    break;

  case 91:
#line 767 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggregation_type = AggregationType::MIN;
    }
#line 2563 "yacc_sql.cpp"
    break;

  case 92:
#line 772 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggregation_type = AggregationType::MAX;
    }
#line 2572 "yacc_sql.cpp"
    break;

  case 93:
#line 777 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggregation_type = AggregationType::COUNT;
    }
#line 2581 "yacc_sql.cpp"
    break;

  case 94:
#line 782 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggregation_type = AggregationType::AVG;
    }
#line 2590 "yacc_sql.cpp"
    break;

  case 95:
#line 787 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggregation_type = AggregationType::SUM;
    }
#line 2599 "yacc_sql.cpp"
    break;

  case 96:
#line 795 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2607 "yacc_sql.cpp"
    break;

  case 97:
#line 798 "yacc_sql.y"
                                 {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 2620 "yacc_sql.cpp"
    break;

  case 98:
#line 810 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2628 "yacc_sql.cpp"
    break;

  case 99:
#line 813 "yacc_sql.y"
                        {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }

      (yyval.relation_list)->push_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2643 "yacc_sql.cpp"
    break;

  case 100:
#line 828 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2651 "yacc_sql.cpp"
    break;

  case 101:
#line 832 "yacc_sql.y"
    {
      if((yyvsp[0].expression_list) != nullptr){
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 2664 "yacc_sql.cpp"
    break;

  case 102:
#line 843 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2672 "yacc_sql.cpp"
    break;

  case 103:
#line 847 "yacc_sql.y"
    {
      if((yyvsp[0].condition_list) != nullptr){
        (yyval.condition_list) = (yyvsp[0].condition_list);
      } else {
        (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      }
      (yyval.condition_list)->emplace_back(*(yyvsp[-1].condition));
      delete (yyvsp[-1].condition);
    }
#line 2686 "yacc_sql.cpp"
    break;

  case 104:
#line 859 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2694 "yacc_sql.cpp"
    break;

  case 105:
#line 863 "yacc_sql.y"
    {
      if((yyvsp[0].condition_list) != nullptr){
        (yyval.condition_list) = (yyvsp[0].condition_list);
      } else {
        (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      }
      (yyval.condition_list)->emplace_back(*(yyvsp[-1].condition));
      delete (yyvsp[-1].condition);
    }
#line 2708 "yacc_sql.cpp"
    break;

  case 106:
#line 876 "yacc_sql.y"
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
#line 2724 "yacc_sql.cpp"
    break;

  case 107:
#line 889 "yacc_sql.y"
    {
      (yyval.join_node) = new JoinSqlNode{(yyvsp[-2].string),*(yyvsp[0].condition_list)};
      delete (yyvsp[-2].string);
      delete (yyvsp[0].condition_list);
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 108:
#line 898 "yacc_sql.y"
    {
      (yyval.join_list) = nullptr;
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 109:
#line 902 "yacc_sql.y"
    {
      (yyval.join_list) = new std::vector<JoinSqlNode>{*(yyvsp[0].join_node)};
      delete (yyvsp[0].join_node);   
    }
#line 2751 "yacc_sql.cpp"
    break;

  case 110:
#line 907 "yacc_sql.y"
    {
      (yyval.join_list)->emplace_back(*(yyvsp[0].join_node));
      delete (yyvsp[0].join_node);

    }
#line 2761 "yacc_sql.cpp"
    break;

  case 111:
#line 916 "yacc_sql.y"
    {
      (yyval.order_by_attr_list) = nullptr;
    }
#line 2769 "yacc_sql.cpp"
    break;

  case 112:
#line 920 "yacc_sql.y"
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
#line 2784 "yacc_sql.cpp"
    break;

  case 113:
#line 934 "yacc_sql.y"
    {
      (yyval.order_by_attr_list) = nullptr;
    }
#line 2792 "yacc_sql.cpp"
    break;

  case 114:
#line 938 "yacc_sql.y"
    {
      if((yyvsp[0].order_by_attr_list) != nullptr){
        (yyval.order_by_attr_list) = (yyvsp[0].order_by_attr_list);
      } else {
        (yyval.order_by_attr_list) = new std::vector<OrderBySqlNode>;
      }
      (yyval.order_by_attr_list)->push_back(*(yyvsp[-1].order_by_attr));
    }
#line 2805 "yacc_sql.cpp"
    break;

  case 115:
#line 949 "yacc_sql.y"
    {
      (yyval.order_by_attr) = new OrderBySqlNode;
      (yyval.order_by_attr)->relation_name = std::move((yyvsp[-1].rel_attr)->relation_name);
      (yyval.order_by_attr)->attribute_name = std::move((yyvsp[-1].rel_attr)->attribute_name);
      (yyval.order_by_attr)->is_desc = true;
      free((yyvsp[-1].rel_attr));
    }
#line 2817 "yacc_sql.cpp"
    break;

  case 116:
#line 957 "yacc_sql.y"
    {
      (yyval.order_by_attr) = new OrderBySqlNode;
      (yyval.order_by_attr)->relation_name = std::move((yyvsp[-1].rel_attr)->relation_name);
      (yyval.order_by_attr)->attribute_name = std::move((yyvsp[-1].rel_attr)->attribute_name);
      (yyval.order_by_attr)->is_desc = false;
      free((yyvsp[-1].rel_attr));
    }
#line 2829 "yacc_sql.cpp"
    break;

  case 117:
#line 964 "yacc_sql.y"
    {
      (yyval.order_by_attr) = new OrderBySqlNode;
      (yyval.order_by_attr)->relation_name = std::move((yyvsp[0].rel_attr)->relation_name);
      (yyval.order_by_attr)->attribute_name = std::move((yyvsp[0].rel_attr)->attribute_name);
      (yyval.order_by_attr)->is_desc = false;
      free((yyvsp[0].rel_attr));
    }
#line 2841 "yacc_sql.cpp"
    break;

  case 118:
#line 973 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2849 "yacc_sql.cpp"
    break;

  case 119:
#line 976 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2857 "yacc_sql.cpp"
    break;

  case 120:
#line 982 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2865 "yacc_sql.cpp"
    break;

  case 121:
#line 985 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2875 "yacc_sql.cpp"
    break;

  case 122:
#line 990 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->front().link_type = 0;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2886 "yacc_sql.cpp"
    break;

  case 123:
#line 996 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->front().link_type = 1;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2897 "yacc_sql.cpp"
    break;

  case 124:
#line 1005 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 4;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 4;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 2910 "yacc_sql.cpp"
    break;

  case 125:
#line 1014 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 4;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 4;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = CompOp::LIKE_OP;
    }
#line 2923 "yacc_sql.cpp"
    break;

  case 126:
#line 1023 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 4;
      (yyval.condition)->left_expr = (yyvsp[-3].expression);
      (yyval.condition)->right_is_attr = 4;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = CompOp::NOT_LIKE_OP;
    }
#line 2936 "yacc_sql.cpp"
    break;

  case 127:
#line 1032 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 4;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->comp = CompOp::IS_NULL;
      (yyval.condition)->right_is_attr = 4;
      auto null_value = Value();
      null_value.set_isnull();
      (yyval.condition)->right_expr = new ValueExpr(null_value);
    }
#line 2951 "yacc_sql.cpp"
    break;

  case 128:
#line 1043 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 4;
      (yyval.condition)->left_expr = (yyvsp[-3].expression);
      (yyval.condition)->comp = CompOp::IS_NOT_NULL;
      (yyval.condition)->right_is_attr = 4;
      auto null_value = Value();
      null_value.set_isnull();
      (yyval.condition)->right_expr = new ValueExpr(null_value);
    }
#line 2966 "yacc_sql.cpp"
    break;

  case 129:
#line 1054 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 2;
      (yyval.condition)->left_sub_query = (yyvsp[-5].sql_node);
      (yyval.condition)->right_is_attr = 2;
      (yyval.condition)->right_sub_query = (yyvsp[-1].sql_node);
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 2979 "yacc_sql.cpp"
    break;

  case 130:
#line 1063 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 4;
      (yyval.condition)->left_expr = (yyvsp[-4].expression);
      (yyval.condition)->right_is_attr = 2;
      (yyval.condition)->right_sub_query = (yyvsp[-1].sql_node);
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 2992 "yacc_sql.cpp"
    break;

  case 131:
#line 1072 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 2;
      (yyval.condition)->left_sub_query = (yyvsp[-3].sql_node);
      (yyval.condition)->right_is_attr = 4;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3005 "yacc_sql.cpp"
    break;

  case 132:
#line 1081 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 4;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 3;
      (yyval.condition)->right_value_list = *(yyvsp[0].tuple);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3018 "yacc_sql.cpp"
    break;

  case 133:
#line 1092 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3024 "yacc_sql.cpp"
    break;

  case 134:
#line 1093 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3030 "yacc_sql.cpp"
    break;

  case 135:
#line 1094 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3036 "yacc_sql.cpp"
    break;

  case 136:
#line 1095 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3042 "yacc_sql.cpp"
    break;

  case 137:
#line 1096 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3048 "yacc_sql.cpp"
    break;

  case 138:
#line 1097 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3054 "yacc_sql.cpp"
    break;

  case 139:
#line 1098 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3060 "yacc_sql.cpp"
    break;

  case 140:
#line 1099 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP; }
#line 3066 "yacc_sql.cpp"
    break;

  case 141:
#line 1104 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3080 "yacc_sql.cpp"
    break;

  case 142:
#line 1117 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3089 "yacc_sql.cpp"
    break;

  case 143:
#line 1125 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3101 "yacc_sql.cpp"
    break;


#line 3105 "yacc_sql.cpp"

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
#line 1137 "yacc_sql.y"

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
