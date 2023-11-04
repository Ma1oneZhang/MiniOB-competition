/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

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


#line 115 "yacc_sql.cpp"

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

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_CALC = 9,                       /* CALC  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_SHOW = 12,                      /* SHOW  */
  YYSYMBOL_SYNC = 13,                      /* SYNC  */
  YYSYMBOL_INSERT = 14,                    /* INSERT  */
  YYSYMBOL_DELETE = 15,                    /* DELETE  */
  YYSYMBOL_UPDATE = 16,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_UNIQUE = 18,                    /* UNIQUE  */
  YYSYMBOL_MAX = 19,                       /* MAX  */
  YYSYMBOL_MIN = 20,                       /* MIN  */
  YYSYMBOL_COUNT = 21,                     /* COUNT  */
  YYSYMBOL_AVG = 22,                       /* AVG  */
  YYSYMBOL_SUM = 23,                       /* SUM  */
  YYSYMBOL_ROUND = 24,                     /* ROUND  */
  YYSYMBOL_LENGTH = 25,                    /* LENGTH  */
  YYSYMBOL_DATE_FORMAT = 26,               /* DATE_FORMAT  */
  YYSYMBOL_INNER = 27,                     /* INNER  */
  YYSYMBOL_JOIN = 28,                      /* JOIN  */
  YYSYMBOL_RBRACE = 29,                    /* RBRACE  */
  YYSYMBOL_COMMA = 30,                     /* COMMA  */
  YYSYMBOL_ORDER = 31,                     /* ORDER  */
  YYSYMBOL_GROUP = 32,                     /* GROUP  */
  YYSYMBOL_BY = 33,                        /* BY  */
  YYSYMBOL_HAVING = 34,                    /* HAVING  */
  YYSYMBOL_ASC = 35,                       /* ASC  */
  YYSYMBOL_TRX_BEGIN = 36,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 37,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 38,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 39,                     /* INT_T  */
  YYSYMBOL_STRING_T = 40,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 41,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 42,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 43,                    /* TEXT_T  */
  YYSYMBOL_HELP = 44,                      /* HELP  */
  YYSYMBOL_EXIT = 45,                      /* EXIT  */
  YYSYMBOL_DOT = 46,                       /* DOT  */
  YYSYMBOL_INTO = 47,                      /* INTO  */
  YYSYMBOL_VALUES = 48,                    /* VALUES  */
  YYSYMBOL_FROM = 49,                      /* FROM  */
  YYSYMBOL_WHERE = 50,                     /* WHERE  */
  YYSYMBOL_LIKE = 51,                      /* LIKE  */
  YYSYMBOL_NOT = 52,                       /* NOT  */
  YYSYMBOL_AND = 53,                       /* AND  */
  YYSYMBOL_OR = 54,                        /* OR  */
  YYSYMBOL_SET = 55,                       /* SET  */
  YYSYMBOL_ON = 56,                        /* ON  */
  YYSYMBOL_LOAD = 57,                      /* LOAD  */
  YYSYMBOL_DATA = 58,                      /* DATA  */
  YYSYMBOL_INFILE = 59,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 60,                   /* EXPLAIN  */
  YYSYMBOL_IS = 61,                        /* IS  */
  YYSYMBOL_NULL_TOKEN = 62,                /* NULL_TOKEN  */
  YYSYMBOL_IN = 63,                        /* IN  */
  YYSYMBOL_EQ = 64,                        /* EQ  */
  YYSYMBOL_LT = 65,                        /* LT  */
  YYSYMBOL_GT = 66,                        /* GT  */
  YYSYMBOL_LE = 67,                        /* LE  */
  YYSYMBOL_GE = 68,                        /* GE  */
  YYSYMBOL_NE = 69,                        /* NE  */
  YYSYMBOL_AS = 70,                        /* AS  */
  YYSYMBOL_NUMBER = 71,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 72,                     /* FLOAT  */
  YYSYMBOL_ID = 73,                        /* ID  */
  YYSYMBOL_SSS = 74,                       /* SSS  */
  YYSYMBOL_DATE_STR = 75,                  /* DATE_STR  */
  YYSYMBOL_76_ = 76,                       /* '+'  */
  YYSYMBOL_77_ = 77,                       /* '-'  */
  YYSYMBOL_78_ = 78,                       /* '*'  */
  YYSYMBOL_79_ = 79,                       /* '/'  */
  YYSYMBOL_UMINUS = 80,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 81,                  /* $accept  */
  YYSYMBOL_commands = 82,                  /* commands  */
  YYSYMBOL_command_wrapper = 83,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 84,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 85,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 86,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 87,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 88,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 89,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 90,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 91,          /* show_tables_stmt  */
  YYSYMBOL_show_index_stmt = 92,           /* show_index_stmt  */
  YYSYMBOL_desc_table_stmt = 93,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 94,         /* create_index_stmt  */
  YYSYMBOL_index_field_list = 95,          /* index_field_list  */
  YYSYMBOL_drop_index_stmt = 96,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 97,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 98,             /* attr_def_list  */
  YYSYMBOL_attr_def = 99,                  /* attr_def  */
  YYSYMBOL_number = 100,                   /* number  */
  YYSYMBOL_type = 101,                     /* type  */
  YYSYMBOL_insert_stmt = 102,              /* insert_stmt  */
  YYSYMBOL_tuple_list = 103,               /* tuple_list  */
  YYSYMBOL_tuple = 104,                    /* tuple  */
  YYSYMBOL_value_list = 105,               /* value_list  */
  YYSYMBOL_value = 106,                    /* value  */
  YYSYMBOL_delete_stmt = 107,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 108,              /* update_stmt  */
  YYSYMBOL_update_attr = 109,              /* update_attr  */
  YYSYMBOL_update_attr_list = 110,         /* update_attr_list  */
  YYSYMBOL_select_stmt = 111,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 112,                /* calc_stmt  */
  YYSYMBOL_expression_list = 113,          /* expression_list  */
  YYSYMBOL_alias_expression = 114,         /* alias_expression  */
  YYSYMBOL_expression = 115,               /* expression  */
  YYSYMBOL_rel_attr = 116,                 /* rel_attr  */
  YYSYMBOL_attr_list = 117,                /* attr_list  */
  YYSYMBOL_rel_list = 118,                 /* rel_list  */
  YYSYMBOL_group_by = 119,                 /* group_by  */
  YYSYMBOL_having = 120,                   /* having  */
  YYSYMBOL_having_list = 121,              /* having_list  */
  YYSYMBOL_having_attr = 122,              /* having_attr  */
  YYSYMBOL_join_node = 123,                /* join_node  */
  YYSYMBOL_join_list = 124,                /* join_list  */
  YYSYMBOL_order_by = 125,                 /* order_by  */
  YYSYMBOL_order_by_node_list = 126,       /* order_by_node_list  */
  YYSYMBOL_order_by_node = 127,            /* order_by_node  */
  YYSYMBOL_where = 128,                    /* where  */
  YYSYMBOL_condition_list = 129,           /* condition_list  */
  YYSYMBOL_condition = 130,                /* condition  */
  YYSYMBOL_comp_op = 131,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 132,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 133,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 134,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 135             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   418

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  157
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  327

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   331


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    78,    76,     2,    77,     2,    79,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    80
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   223,   223,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   255,   261,   266,   272,   278,   284,
     290,   297,   302,   308,   316,   333,   354,   357,   368,   378,
     395,   412,   428,   439,   442,   455,   467,   479,   491,   503,
     515,   529,   532,   533,   534,   535,   536,   539,   554,   557,
     567,   580,   583,   594,   598,   602,   607,   612,   619,   631,
     657,   664,   675,   678,   688,   696,   732,   769,   809,   819,
     824,   833,   838,   850,   855,   863,   866,   869,   872,   875,
     879,   882,   887,   891,   897,   902,   907,   914,   919,   925,
     930,   937,   942,   947,   952,   957,   966,   969,   981,   984,
     997,  1012,  1032,  1035,  1047,  1050,  1063,  1066,  1079,  1092,
    1102,  1105,  1110,  1120,  1123,  1138,  1141,  1152,  1160,  1167,
    1177,  1180,  1186,  1189,  1194,  1200,  1208,  1217,  1226,  1235,
    1246,  1257,  1266,  1275,  1284,  1296,  1297,  1298,  1299,  1300,
    1301,  1302,  1303,  1307,  1320,  1328,  1338,  1339
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "CALC", "SELECT", "DESC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "UNIQUE", "MAX", "MIN",
  "COUNT", "AVG", "SUM", "ROUND", "LENGTH", "DATE_FORMAT", "INNER", "JOIN",
  "RBRACE", "COMMA", "ORDER", "GROUP", "BY", "HAVING", "ASC", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
  "LIKE", "NOT", "AND", "OR", "SET", "ON", "LOAD", "DATA", "INFILE",
  "EXPLAIN", "IS", "NULL_TOKEN", "IN", "EQ", "LT", "GT", "LE", "GE", "NE",
  "AS", "NUMBER", "FLOAT", "ID", "SSS", "DATE_STR", "'+'", "'-'", "'*'",
  "'/'", "UMINUS", "$accept", "commands", "command_wrapper", "exit_stmt",
  "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "show_index_stmt",
  "desc_table_stmt", "create_index_stmt", "index_field_list",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "number", "type", "insert_stmt", "tuple_list", "tuple", "value_list",
  "value", "delete_stmt", "update_stmt", "update_attr", "update_attr_list",
  "select_stmt", "calc_stmt", "expression_list", "alias_expression",
  "expression", "rel_attr", "attr_list", "rel_list", "group_by", "having",
  "having_list", "having_attr", "join_node", "join_list", "order_by",
  "order_by_node_list", "order_by_node", "where", "condition_list",
  "condition", "comp_op", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-224)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-62)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     328,   201,   142,     0,     0,   -43,   183,  -224,   -13,    27,
      21,  -224,  -224,  -224,  -224,  -224,    24,    66,   328,    79,
     117,  -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,
    -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,
    -224,  -224,    63,    78,   123,    85,    98,     0,   145,   177,
     179,   185,   203,   206,   212,   215,  -224,  -224,  -224,   172,
    -224,  -224,     0,  -224,  -224,  -224,   204,   122,  -224,   188,
    -224,  -224,   189,   163,   176,   195,   190,   192,  -224,  -224,
    -224,  -224,    -1,   225,   198,  -224,   226,    38,    17,    17,
      17,    17,    17,     0,     0,     0,    91,  -224,     0,     0,
     207,  -224,     0,     0,     0,     0,   210,   213,   220,   235,
     214,    72,   216,   218,   278,   219,   233,   228,  -224,   273,
     274,   275,   276,   283,    22,    62,   105,  -224,  -224,  -224,
    -224,  -224,   132,   132,  -224,  -224,    11,  -224,   299,   222,
    -224,   265,   304,  -224,   307,   224,   316,  -224,   338,   285,
    -224,  -224,  -224,  -224,  -224,  -224,  -224,     0,  -224,     0,
     286,   294,   326,   330,    72,   339,   153,   284,  -224,   159,
      51,   214,   235,   362,  -224,  -224,  -224,  -224,  -224,     1,
     218,   341,   298,   357,    77,    89,    13,   326,   330,   347,
    -224,    58,   346,   299,  -224,   348,     0,    -2,   -17,  -224,
    -224,  -224,  -224,  -224,  -224,  -224,   236,   222,   222,   278,
    -224,   304,  -224,   305,   308,   318,  -224,   316,    19,   351,
     309,  -224,  -224,   311,   326,  -224,   330,    58,   313,  -224,
     356,    72,   360,   339,   254,   109,     0,  -224,   329,  -224,
     153,  -224,   109,  -224,  -224,   361,  -224,  -224,  -224,   363,
    -224,  -224,   278,  -224,   320,   365,   351,   326,  -224,    58,
     356,   340,   364,   366,   346,  -224,  -224,   332,   253,   109,
    -224,   187,   370,  -224,    80,  -224,   351,  -224,   371,  -224,
     356,   366,   222,    17,   368,   369,  -224,   153,   109,  -224,
     342,  -224,  -224,  -224,   366,   369,  -224,    31,   372,     0,
      17,  -224,   376,  -224,   369,  -224,  -224,  -224,    17,  -224,
     127,   254,   377,  -224,  -224,   372,     0,  -224,    72,    17,
    -224,  -224,   127,  -224,   377,  -224,  -224
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     156,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    13,    14,     8,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    67,    63,    64,    99,
      65,    66,     0,    97,    91,    78,    79,    81,    92,    74,
      33,    31,     0,     0,     0,     0,     0,     0,   154,     1,
     157,     2,     0,     0,     0,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    90,     0,     0,
       0,    83,     0,     0,     0,     0,     0,     0,     0,   130,
       0,     0,     0,     0,     0,     0,     0,     0,    89,     0,
       0,     0,     0,     0,     0,     0,     0,   100,    98,    80,
      82,    84,    85,    86,    87,    88,   108,    32,     0,   132,
      68,     0,    72,   155,     0,     0,    43,    42,     0,     0,
      38,   102,   101,   103,   104,   105,    93,     0,    95,     0,
       0,     0,   108,   120,     0,    58,     0,     0,   131,   133,
       0,     0,   130,     0,    52,    53,    54,    55,    56,    50,
       0,     0,     0,     0,     0,     0,   108,   108,   120,     0,
     121,   130,    61,     0,    57,     0,     0,     0,     0,   151,
     145,   146,   147,   148,   149,   150,     0,   132,   132,     0,
      70,    72,    69,     0,     0,     0,    48,    43,    41,    36,
       0,    94,    96,     0,   108,   109,   120,   130,     0,   122,
     123,     0,     0,    58,     0,   137,     0,   152,     0,   139,
       0,   144,   136,   134,   135,     0,    73,   153,    51,     0,
      49,    44,     0,    40,     0,     0,    36,   108,   111,   130,
     123,     0,     0,   112,    61,    60,    59,     0,     0,   138,
     140,    91,     0,    71,    47,    39,    36,    34,     0,   110,
     123,   112,   132,     0,     0,   114,    62,     0,   143,   142,
       0,    45,    37,    35,   112,   114,   119,   129,   125,     0,
       0,    75,     0,    46,   114,    77,   127,   128,     0,   124,
     106,     0,   116,   141,    76,   125,     0,   113,     0,     0,
     115,   126,   106,   118,   116,   107,   117
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -224,  -224,   388,  -224,  -224,  -224,  -224,  -224,  -224,  -224,
    -224,  -224,  -224,  -224,  -149,  -224,  -224,   191,   229,  -224,
    -224,  -224,   178,  -162,   146,  -110,  -224,  -224,   241,   202,
    -107,  -224,     6,  -224,   -47,   -86,    92,  -154,  -201,  -167,
      93,    96,  -177,  -161,  -151,   101,   110,  -163,  -195,  -224,
    -223,  -224,  -224,  -224,  -224
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,   255,    32,    33,   181,   146,   249,
     179,    34,   194,   165,   232,    64,    35,    36,   142,   172,
      37,    38,    65,    66,    67,    68,   317,   163,   285,   301,
     320,   312,   190,   191,   263,   309,   298,   140,   168,   169,
     206,    39,    40,    41,    81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      87,   143,   119,   120,   121,   122,   123,   147,   188,   212,
      69,   268,   243,   244,   229,    97,   113,    47,   214,    48,
      49,    50,    51,    52,    53,    54,    55,   227,   230,     4,
      70,   233,   225,   226,    73,   238,    48,    49,    50,    51,
      52,   160,   306,   160,   241,   239,   124,   125,   126,   236,
     229,   156,   157,   215,   192,   132,   133,   134,   135,   195,
     210,   237,    56,   216,   260,   259,   307,   118,   209,   114,
     258,    57,    58,    59,    60,    61,    74,    62,    63,    79,
     295,   161,   229,   223,   162,   189,   224,   296,   318,   252,
      59,   158,   167,   304,    75,    63,   280,    76,   102,   103,
     104,   105,   245,   279,   129,   130,   221,   278,   139,   281,
     184,   253,   185,    56,   102,   103,   104,   105,   222,    87,
      80,   264,    57,    58,    77,    60,    61,   292,   305,   294,
     271,    84,   290,   272,    56,   159,    82,   314,   102,   103,
     104,   105,   291,    57,    58,   275,    60,    61,    45,   235,
      46,    83,    99,   102,   103,   104,   105,   316,    85,   242,
     167,   167,    88,     4,   127,   102,   103,   104,   105,   128,
      47,    86,    48,    49,    50,    51,    52,    53,    54,    55,
     302,   102,   103,   104,   105,   102,   103,   104,   105,   269,
      71,    72,   100,    87,    89,   101,    90,   297,   102,   103,
     104,   105,    91,   102,   103,   104,   105,    42,   323,    43,
     104,   105,   207,   208,   311,    56,   -61,   231,    96,    44,
      92,   288,   297,    93,    57,    58,    59,    60,    61,    94,
      62,    63,    95,   311,    98,   167,   108,   106,   107,   166,
      87,    48,    49,    50,    51,    52,    53,    54,    55,   109,
     110,   112,   310,   240,   111,    48,    49,    50,    51,    52,
      53,    54,    55,   174,   175,   176,   177,   178,   138,   322,
     287,   116,    48,    49,    50,    51,    52,    53,    54,    55,
     131,   115,   117,   136,    56,   139,   137,   141,     4,   149,
     144,   145,   148,    57,    58,    59,    60,    61,    56,    62,
      63,   150,   151,   152,   153,   154,   267,    57,    58,    59,
      60,    61,   155,    62,    63,    56,   164,   199,   200,   201,
     202,   203,   204,   205,    57,    58,    59,    60,    61,   170,
      62,    63,     1,     2,   171,   196,   197,     3,     4,     5,
       6,     7,     8,     9,    10,   198,   180,   199,   200,   201,
     202,   203,   204,   205,   173,   182,   160,   189,   183,   186,
     102,   103,   104,   105,    11,    12,    13,   187,   213,   193,
     218,   219,    14,    15,   220,   228,   231,   234,   247,   248,
     250,   254,   256,    16,   257,    17,   261,   262,    18,   265,
     273,   270,   274,   276,   277,   237,   282,   283,   284,   289,
     293,   299,   308,   300,   303,   313,    78,   319,   251,   217,
     286,   266,   211,   246,   325,   324,   321,   326,   315
};

static const yytype_int16 yycheck[] =
{
      47,   111,    88,    89,    90,    91,    92,   114,   162,   172,
       4,   234,   207,   208,   191,    62,    17,    17,    17,    19,
      20,    21,    22,    23,    24,    25,    26,   188,   191,    10,
      73,   193,   186,   187,    47,    52,    19,    20,    21,    22,
      23,    30,    11,    30,   206,    62,    93,    94,    95,    51,
     227,    29,    30,    52,   164,   102,   103,   104,   105,   166,
     170,    63,    62,    62,   227,   226,    35,    29,    17,    70,
     224,    71,    72,    73,    74,    75,    49,    77,    78,     0,
     281,    70,   259,    70,    73,    27,    73,   282,   311,    70,
      73,    29,   139,   294,    73,    78,   259,    73,    76,    77,
      78,    79,   209,   257,    98,    99,    29,   256,    50,   260,
     157,   218,   159,    62,    76,    77,    78,    79,    29,   166,
       3,   231,    71,    72,    58,    74,    75,   276,   295,   280,
     240,     8,    52,   240,    62,    30,    73,   304,    76,    77,
      78,    79,    62,    71,    72,   252,    74,    75,     6,   196,
       8,    73,    30,    76,    77,    78,    79,    30,    73,   206,
     207,   208,    17,    10,    73,    76,    77,    78,    79,    78,
      17,    73,    19,    20,    21,    22,    23,    24,    25,    26,
     287,    76,    77,    78,    79,    76,    77,    78,    79,   236,
       7,     8,    70,   240,    17,    73,    17,   283,    76,    77,
      78,    79,    17,    76,    77,    78,    79,     6,   318,     8,
      78,    79,    53,    54,   300,    62,    29,    30,    46,    18,
      17,   268,   308,    17,    71,    72,    73,    74,    75,    17,
      77,    78,    17,   319,    30,   282,    73,    49,    49,    17,
     287,    19,    20,    21,    22,    23,    24,    25,    26,    73,
      55,    59,   299,    17,    64,    19,    20,    21,    22,    23,
      24,    25,    26,    39,    40,    41,    42,    43,    48,   316,
      17,    73,    19,    20,    21,    22,    23,    24,    25,    26,
      73,    56,    56,    73,    62,    50,    73,    73,    10,    56,
      74,    73,    73,    71,    72,    73,    74,    75,    62,    77,
      78,    73,    29,    29,    29,    29,    52,    71,    72,    73,
      74,    75,    29,    77,    78,    62,    17,    63,    64,    65,
      66,    67,    68,    69,    71,    72,    73,    74,    75,    64,
      77,    78,     4,     5,    30,    51,    52,     9,    10,    11,
      12,    13,    14,    15,    16,    61,    30,    63,    64,    65,
      66,    67,    68,    69,    47,    17,    30,    27,    73,    73,
      76,    77,    78,    79,    36,    37,    38,    73,     6,    30,
      29,    73,    44,    45,    17,    28,    30,    29,    73,    71,
      62,    30,    73,    55,    73,    57,    73,    31,    60,    29,
      29,    62,    29,    73,    29,    63,    56,    33,    32,    29,
      29,    33,    30,    34,    62,    29,    18,    30,   217,   180,
     264,   233,   171,   211,   322,   319,   315,   324,   308
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    15,
      16,    36,    37,    38,    44,    45,    55,    57,    60,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    96,    97,   102,   107,   108,   111,   112,   132,
     133,   134,     6,     8,    18,     6,     8,    17,    19,    20,
      21,    22,    23,    24,    25,    26,    62,    71,    72,    73,
      74,    75,    77,    78,   106,   113,   114,   115,   116,   113,
      73,     7,     8,    47,    49,    73,    73,    58,    83,     0,
       3,   135,    73,    73,     8,    73,    73,   115,    17,    17,
      17,    17,    17,    17,    17,    17,    46,   115,    30,    30,
      70,    73,    76,    77,    78,    79,    49,    49,    73,    73,
      55,    64,    59,    17,    70,    56,    73,    56,    29,   116,
     116,   116,   116,   116,   115,   115,   115,    73,    78,   113,
     113,    73,   115,   115,   115,   115,    73,    73,    48,    50,
     128,    73,   109,   106,    74,    73,    99,   111,    73,    56,
      73,    29,    29,    29,    29,    29,    29,    30,    29,    30,
      30,    70,    73,   118,    17,   104,    17,   115,   129,   130,
      64,    30,   110,    47,    39,    40,    41,    42,    43,   101,
      30,    98,    17,    73,   115,   115,    73,    73,   118,    27,
     123,   124,   106,    30,   103,   111,    51,    52,    61,    63,
      64,    65,    66,    67,    68,    69,   131,    53,    54,    17,
     106,   109,   128,     6,    17,    52,    62,    99,    29,    73,
      17,    29,    29,    70,    73,   118,   118,   124,    28,   123,
     128,    30,   105,   104,    29,   115,    51,    63,    52,    62,
      17,   104,   115,   129,   129,   111,   110,    73,    71,   100,
      62,    98,    70,   111,    30,    95,    73,    73,   118,   124,
     128,    73,    31,   125,   106,    29,   103,    52,   131,   115,
      62,   106,   111,    29,    29,   111,    73,    29,    95,   118,
     128,   125,    56,    33,    32,   119,   105,    17,   115,    29,
      52,    62,    95,    29,   125,   119,   129,   116,   127,    33,
      34,   120,   111,    62,   119,   120,    11,    35,    30,   126,
     115,   116,   122,    29,   120,   127,    30,   117,   131,    30,
     121,   126,   115,   106,   122,   117,   121
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    94,    95,    95,    96,    97,
      97,    97,    97,    98,    98,    99,    99,    99,    99,    99,
      99,   100,   101,   101,   101,   101,   101,   102,   103,   103,
     104,   105,   105,   106,   106,   106,   106,   106,   107,   108,
     109,   109,   110,   110,   111,   111,   111,   111,   112,   113,
     113,   113,   113,   114,   114,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   117,   117,   118,   118,
     118,   118,   119,   119,   120,   120,   121,   121,   122,   123,
     124,   124,   124,   125,   125,   126,   126,   127,   127,   127,
     128,   128,   129,   129,   129,   129,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   131,   131,   131,   131,   131,
     131,   131,   131,   132,   133,   134,   135,   135
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     4,     2,     9,    10,     0,     3,     5,     9,
       8,     7,     5,     0,     3,     6,     7,     5,     3,     4,
       2,     1,     1,     1,     1,     1,     1,     6,     0,     3,
       4,     0,     3,     1,     1,     1,     1,     1,     4,     6,
       3,     5,     0,     3,     2,    10,    12,    11,     2,     1,
       3,     1,     3,     2,     3,     3,     3,     3,     3,     3,
       2,     1,     1,     4,     6,     4,     6,     1,     3,     1,
       3,     4,     4,     4,     4,     4,     0,     3,     0,     3,
       5,     4,     0,     4,     0,     3,     0,     3,     3,     5,
       0,     1,     2,     0,     4,     0,     3,     2,     2,     1,
       0,     2,     0,     1,     3,     3,     3,     3,     4,     3,
       4,     7,     5,     5,     3,     1,     1,     1,     1,     1,
       1,     1,     2,     7,     2,     4,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
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
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 224 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1889 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 255 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1898 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 261 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1906 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 266 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1914 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 272 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1922 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 278 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1930 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 284 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1938 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 290 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1948 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 297 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1956 "yacc_sql.cpp"
    break;

  case 32: /* show_index_stmt: SHOW INDEX FROM ID  */
#line 302 "yacc_sql.y"
                       {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1966 "yacc_sql.cpp"
    break;

  case 33: /* desc_table_stmt: DESC ID  */
#line 308 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1976 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID index_field_list RBRACE  */
#line 317 "yacc_sql.y"
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
#line 1997 "yacc_sql.cpp"
    break;

  case 35: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID index_field_list RBRACE  */
#line 334 "yacc_sql.y"
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
#line 2018 "yacc_sql.cpp"
    break;

  case 36: /* index_field_list: %empty  */
#line 354 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2026 "yacc_sql.cpp"
    break;

  case 37: /* index_field_list: COMMA ID index_field_list  */
#line 358 "yacc_sql.y"
    {
      if((yyvsp[0].relation_list) != nullptr){
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->push_back((yyvsp[-1].string));
    }
#line 2039 "yacc_sql.cpp"
    break;

  case 38: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 369 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2051 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE AS select_stmt  */
#line 379 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-6].string);
      free((yyvsp[-6].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-3].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-4].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-4].attr_info);
      create_table.select_node = (yyvsp[0].sql_node);
    }
#line 2072 "yacc_sql.cpp"
    break;

  case 40: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE select_stmt  */
#line 396 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);
      create_table.select_node = (yyvsp[0].sql_node);
    }
#line 2093 "yacc_sql.cpp"
    break;

  case 41: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 413 "yacc_sql.y"
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
#line 2113 "yacc_sql.cpp"
    break;

  case 42: /* create_table_stmt: CREATE TABLE ID AS select_stmt  */
#line 429 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
      create_table.select_node = (yyvsp[0].sql_node);
    }
#line 2125 "yacc_sql.cpp"
    break;

  case 43: /* attr_def_list: %empty  */
#line 439 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2133 "yacc_sql.cpp"
    break;

  case 44: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 443 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2147 "yacc_sql.cpp"
    break;

  case 45: /* attr_def: ID type LBRACE number RBRACE NULL_TOKEN  */
#line 456 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = true;
      if((AttrType)(yyvsp[-4].number) == AttrType::TEXTS){
        (yyval.attr_info)->length = 40;
      }
      free((yyvsp[-5].string));
    }
#line 2163 "yacc_sql.cpp"
    break;

  case 46: /* attr_def: ID type LBRACE number RBRACE NOT NULL_TOKEN  */
#line 468 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      (yyval.attr_info)->nullable = false;
      if((AttrType)(yyvsp[-5].number) == AttrType::TEXTS){
        (yyval.attr_info)->length = 40;
      }
      free((yyvsp[-6].string));
    }
#line 2179 "yacc_sql.cpp"
    break;

  case 47: /* attr_def: ID type LBRACE number RBRACE  */
#line 480 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      (yyval.attr_info)->nullable = true;
      if((AttrType)(yyvsp[-3].number) == AttrType::TEXTS){
        (yyval.attr_info)->length = 40;
      }
      free((yyvsp[-4].string));
    }
#line 2195 "yacc_sql.cpp"
    break;

  case 48: /* attr_def: ID type NULL_TOKEN  */
#line 492 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      if((AttrType)(yyvsp[-1].number) == AttrType::TEXTS){
        (yyval.attr_info)->length = 40;
      }
      free((yyvsp[-2].string));
    }
#line 2211 "yacc_sql.cpp"
    break;

  case 49: /* attr_def: ID type NOT NULL_TOKEN  */
#line 504 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = false;
      if((AttrType)(yyvsp[-2].number) == AttrType::TEXTS){
        (yyval.attr_info)->length = 40;
      }
      free((yyvsp[-3].string));
    }
#line 2227 "yacc_sql.cpp"
    break;

  case 50: /* attr_def: ID type  */
#line 516 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      if((AttrType)(yyvsp[0].number) == AttrType::TEXTS){
        (yyval.attr_info)->length = 40;
      }
      free((yyvsp[-1].string));
    }
#line 2243 "yacc_sql.cpp"
    break;

  case 51: /* number: NUMBER  */
#line 529 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2249 "yacc_sql.cpp"
    break;

  case 52: /* type: INT_T  */
#line 532 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2255 "yacc_sql.cpp"
    break;

  case 53: /* type: STRING_T  */
#line 533 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2261 "yacc_sql.cpp"
    break;

  case 54: /* type: FLOAT_T  */
#line 534 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2267 "yacc_sql.cpp"
    break;

  case 55: /* type: DATE_T  */
#line 535 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2273 "yacc_sql.cpp"
    break;

  case 56: /* type: TEXT_T  */
#line 536 "yacc_sql.y"
               { (yyval.number)=TEXTS; }
#line 2279 "yacc_sql.cpp"
    break;

  case 57: /* insert_stmt: INSERT INTO ID VALUES tuple tuple_list  */
#line 540 "yacc_sql.y"
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
#line 2295 "yacc_sql.cpp"
    break;

  case 58: /* tuple_list: %empty  */
#line 554 "yacc_sql.y"
    {
      (yyval.tuple_list) = nullptr;
    }
#line 2303 "yacc_sql.cpp"
    break;

  case 59: /* tuple_list: COMMA tuple tuple_list  */
#line 557 "yacc_sql.y"
                             {
      if ((yyvsp[0].tuple_list) != nullptr){
        (yyval.tuple_list) = (yyvsp[0].tuple_list);
      } else {
        (yyval.tuple_list) = new std::vector<std::vector<Value>>;
      }
      (yyval.tuple_list)->emplace_back(*(yyvsp[-1].tuple));
      delete (yyvsp[-1].tuple);
    }
#line 2317 "yacc_sql.cpp"
    break;

  case 60: /* tuple: LBRACE value value_list RBRACE  */
#line 567 "yacc_sql.y"
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
#line 2332 "yacc_sql.cpp"
    break;

  case 61: /* value_list: %empty  */
#line 580 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2340 "yacc_sql.cpp"
    break;

  case 62: /* value_list: COMMA value value_list  */
#line 583 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2354 "yacc_sql.cpp"
    break;

  case 63: /* value: NUMBER  */
#line 594 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2363 "yacc_sql.cpp"
    break;

  case 64: /* value: FLOAT  */
#line 598 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2372 "yacc_sql.cpp"
    break;

  case 65: /* value: SSS  */
#line 602 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2382 "yacc_sql.cpp"
    break;

  case 66: /* value: DATE_STR  */
#line 607 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2392 "yacc_sql.cpp"
    break;

  case 67: /* value: NULL_TOKEN  */
#line 612 "yacc_sql.y"
                 {
      (yyval.value) = new Value();
      (yyval.value)->set_isnull();
    }
#line 2401 "yacc_sql.cpp"
    break;

  case 68: /* delete_stmt: DELETE FROM ID where  */
#line 620 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2415 "yacc_sql.cpp"
    break;

  case 69: /* update_stmt: UPDATE ID SET update_attr update_attr_list where  */
#line 632 "yacc_sql.y"
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
#line 2442 "yacc_sql.cpp"
    break;

  case 70: /* update_attr: ID EQ value  */
#line 658 "yacc_sql.y"
    {
      (yyval.update_value) = new UpdateValue;
      (yyval.update_value)->attribute_name = (yyvsp[-2].string);
      (yyval.update_value)->value = *(yyvsp[0].value);
      (yyval.update_value)->is_stmt = false;
    }
#line 2453 "yacc_sql.cpp"
    break;

  case 71: /* update_attr: ID EQ LBRACE select_stmt RBRACE  */
#line 665 "yacc_sql.y"
    {
      (yyval.update_value) = new UpdateValue;
      (yyval.update_value)->attribute_name = (yyvsp[-4].string);
      (yyval.update_value)->is_stmt = true;
      (yyval.update_value)->stmt = (yyvsp[-1].sql_node);
    }
#line 2464 "yacc_sql.cpp"
    break;

  case 72: /* update_attr_list: %empty  */
#line 675 "yacc_sql.y"
    {
      (yyval.update_value_list) = nullptr;
    }
#line 2472 "yacc_sql.cpp"
    break;

  case 73: /* update_attr_list: COMMA update_attr update_attr_list  */
#line 679 "yacc_sql.y"
    {
      if ((yyvsp[0].update_value_list) == nullptr){
        (yyval.update_value_list) = new std::vector<UpdateValue>;
      }else {
        (yyval.update_value_list) = (yyvsp[0].update_value_list);
      }
      (yyval.update_value_list)->push_back(*(yyvsp[-1].update_value));
    }
#line 2485 "yacc_sql.cpp"
    break;

  case 74: /* select_stmt: SELECT expression_list  */
#line 689 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2497 "yacc_sql.cpp"
    break;

  case 75: /* select_stmt: SELECT expression_list FROM ID rel_list join_list where order_by group_by having  */
#line 697 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-8].expression_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-8].expression_list));
        delete (yyvsp[-8].expression_list);
      }
      if ((yyvsp[-5].relation_alias_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap((yyvsp[-5].relation_alias_list)->front());
        (yyval.sql_node)->selection.relation_alias.swap((yyvsp[-5].relation_alias_list)->back());
        delete (yyvsp[-5].relation_alias_list);
      }
      (yyval.sql_node)->selection.relations.emplace_back((yyvsp[-6].string));
      (yyval.sql_node)->selection.relation_alias.emplace_back("");
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());
      std::reverse((yyval.sql_node)->selection.relation_alias.begin(), (yyval.sql_node)->selection.relation_alias.end());
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
#line 2537 "yacc_sql.cpp"
    break;

  case 76: /* select_stmt: SELECT expression_list FROM ID AS ID rel_list join_list where order_by group_by having  */
#line 733 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-10].expression_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-10].expression_list));
        delete (yyvsp[-10].expression_list);
      }
      if ((yyvsp[-5].relation_alias_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap((yyvsp[-5].relation_alias_list)->front());
        (yyval.sql_node)->selection.relation_alias.swap((yyvsp[-5].relation_alias_list)->back());
        delete (yyvsp[-5].relation_alias_list);
      }
      (yyval.sql_node)->selection.relations.emplace_back((yyvsp[-8].string));
      (yyval.sql_node)->selection.relation_alias.emplace_back((yyvsp[-6].string));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());
      std::reverse((yyval.sql_node)->selection.relation_alias.begin(), (yyval.sql_node)->selection.relation_alias.end());
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
      free((yyvsp[-8].string));
      free((yyvsp[-6].string));
    }
#line 2578 "yacc_sql.cpp"
    break;

  case 77: /* select_stmt: SELECT expression_list FROM ID ID rel_list join_list where order_by group_by having  */
#line 770 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-9].expression_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-9].expression_list));
        delete (yyvsp[-9].expression_list);
      }
      if ((yyvsp[-5].relation_alias_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap((yyvsp[-5].relation_alias_list)->front());
        (yyval.sql_node)->selection.relation_alias.swap((yyvsp[-5].relation_alias_list)->back());
        delete (yyvsp[-5].relation_alias_list);
      }

      (yyval.sql_node)->selection.relations.emplace_back((yyvsp[-7].string));
      (yyval.sql_node)->selection.relation_alias.emplace_back((yyvsp[-6].string));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());
      std::reverse((yyval.sql_node)->selection.relation_alias.begin(), (yyval.sql_node)->selection.relation_alias.end());
      if ((yyvsp[-4].join_list) != nullptr) {
        (yyval.sql_node)->selection.joinctions.swap(*(yyvsp[-4].join_list));
        delete (yyvsp[-4].join_list);
      }
      if ((yyvsp[-3].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-3].condition_list));
        delete (yyvsp[-2].order_by_attr_list);
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
      free((yyvsp[-7].string));
      free((yyvsp[-6].string));
    }
#line 2620 "yacc_sql.cpp"
    break;

  case 78: /* calc_stmt: CALC expression_list  */
#line 810 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2631 "yacc_sql.cpp"
    break;

  case 79: /* expression_list: alias_expression  */
#line 820 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2640 "yacc_sql.cpp"
    break;

  case 80: /* expression_list: alias_expression COMMA expression_list  */
#line 825 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2653 "yacc_sql.cpp"
    break;

  case 81: /* expression_list: expression  */
#line 834 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2662 "yacc_sql.cpp"
    break;

  case 82: /* expression_list: expression COMMA expression_list  */
#line 839 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2675 "yacc_sql.cpp"
    break;

  case 83: /* alias_expression: expression ID  */
#line 851 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2684 "yacc_sql.cpp"
    break;

  case 84: /* alias_expression: expression AS ID  */
#line 856 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[-2].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2693 "yacc_sql.cpp"
    break;

  case 85: /* expression: expression '+' expression  */
#line 863 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2701 "yacc_sql.cpp"
    break;

  case 86: /* expression: expression '-' expression  */
#line 866 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2709 "yacc_sql.cpp"
    break;

  case 87: /* expression: expression '*' expression  */
#line 869 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2717 "yacc_sql.cpp"
    break;

  case 88: /* expression: expression '/' expression  */
#line 872 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2725 "yacc_sql.cpp"
    break;

  case 89: /* expression: LBRACE expression RBRACE  */
#line 875 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 90: /* expression: '-' expression  */
#line 879 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 91: /* expression: value  */
#line 882 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2752 "yacc_sql.cpp"
    break;

  case 92: /* expression: rel_attr  */
#line 887 "yacc_sql.y"
               {
      (yyval.expression) = new FieldExpr(*(yyvsp[0].rel_attr));
      delete (yyvsp[0].rel_attr); 
    }
#line 2761 "yacc_sql.cpp"
    break;

  case 93: /* expression: ROUND LBRACE expression RBRACE  */
#line 892 "yacc_sql.y"
    {
      auto zero_value = Value(0);
      (yyval.expression) = new RoundFuncExpr((yyvsp[-1].expression), new ValueExpr(zero_value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2771 "yacc_sql.cpp"
    break;

  case 94: /* expression: ROUND LBRACE expression COMMA expression RBRACE  */
#line 898 "yacc_sql.y"
    {
      (yyval.expression) = new RoundFuncExpr((yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2780 "yacc_sql.cpp"
    break;

  case 95: /* expression: LENGTH LBRACE expression RBRACE  */
#line 903 "yacc_sql.y"
    {
      (yyval.expression) = new LengthFuncExpr((yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));(yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2789 "yacc_sql.cpp"
    break;

  case 96: /* expression: DATE_FORMAT LBRACE expression COMMA expression RBRACE  */
#line 908 "yacc_sql.y"
    {
      (yyval.expression) = new DateFormatFuncExpr((yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2798 "yacc_sql.cpp"
    break;

  case 97: /* rel_attr: '*'  */
#line 914 "yacc_sql.y"
        {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = "";
      (yyval.rel_attr)->attribute_name = "*";;
    }
#line 2808 "yacc_sql.cpp"
    break;

  case 98: /* rel_attr: ID DOT '*'  */
#line 919 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = "*";
      free((yyvsp[-2].string));
    }
#line 2819 "yacc_sql.cpp"
    break;

  case 99: /* rel_attr: ID  */
#line 925 "yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2829 "yacc_sql.cpp"
    break;

  case 100: /* rel_attr: ID DOT ID  */
#line 930 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2841 "yacc_sql.cpp"
    break;

  case 101: /* rel_attr: MIN LBRACE rel_attr RBRACE  */
#line 938 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggregation_type = AggregationType::MIN;
    }
#line 2850 "yacc_sql.cpp"
    break;

  case 102: /* rel_attr: MAX LBRACE rel_attr RBRACE  */
#line 943 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggregation_type = AggregationType::MAX;
    }
#line 2859 "yacc_sql.cpp"
    break;

  case 103: /* rel_attr: COUNT LBRACE rel_attr RBRACE  */
#line 948 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggregation_type = AggregationType::COUNT;
    }
#line 2868 "yacc_sql.cpp"
    break;

  case 104: /* rel_attr: AVG LBRACE rel_attr RBRACE  */
#line 953 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggregation_type = AggregationType::AVG;
    }
#line 2877 "yacc_sql.cpp"
    break;

  case 105: /* rel_attr: SUM LBRACE rel_attr RBRACE  */
#line 958 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggregation_type = AggregationType::SUM;
    }
#line 2886 "yacc_sql.cpp"
    break;

  case 106: /* attr_list: %empty  */
#line 966 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2894 "yacc_sql.cpp"
    break;

  case 107: /* attr_list: COMMA expression attr_list  */
#line 969 "yacc_sql.y"
                                 {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 2907 "yacc_sql.cpp"
    break;

  case 108: /* rel_list: %empty  */
#line 981 "yacc_sql.y"
    {
      (yyval.relation_alias_list) = nullptr;
    }
#line 2915 "yacc_sql.cpp"
    break;

  case 109: /* rel_list: COMMA ID rel_list  */
#line 984 "yacc_sql.y"
                        {
      if ((yyvsp[0].relation_alias_list) != nullptr) {
        (yyval.relation_alias_list) = (yyvsp[0].relation_alias_list);
      } else {
        (yyval.relation_alias_list) = new std::vector<std::vector<std::string>>();
        (yyval.relation_alias_list)->emplace_back();
        (yyval.relation_alias_list)->emplace_back();
      }

      (yyval.relation_alias_list)->front().emplace_back((yyvsp[-1].string));
      (yyval.relation_alias_list)->back().emplace_back("");
      free((yyvsp[-1].string));
    }
#line 2933 "yacc_sql.cpp"
    break;

  case 110: /* rel_list: COMMA ID AS ID rel_list  */
#line 997 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_alias_list) != nullptr) {
        (yyval.relation_alias_list) = (yyvsp[0].relation_alias_list);
      } else {
        (yyval.relation_alias_list) = new std::vector<std::vector<std::string>>();
        (yyval.relation_alias_list)->emplace_back();
        (yyval.relation_alias_list)->emplace_back();
      }

      (yyval.relation_alias_list)->front().emplace_back((yyvsp[-3].string));
      (yyval.relation_alias_list)->back().emplace_back((yyvsp[-1].string));

      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 2953 "yacc_sql.cpp"
    break;

  case 111: /* rel_list: COMMA ID ID rel_list  */
#line 1012 "yacc_sql.y"
                           {
      if ((yyvsp[0].relation_alias_list) != nullptr) {
        (yyval.relation_alias_list) = (yyvsp[0].relation_alias_list);
      } else {
        (yyval.relation_alias_list) = new std::vector<std::vector<std::string>>();
        (yyval.relation_alias_list)->emplace_back();
        (yyval.relation_alias_list)->emplace_back();
      }

      (yyval.relation_alias_list)->front().emplace_back((yyvsp[-2].string));
      (yyval.relation_alias_list)->back().emplace_back((yyvsp[-1].string));

      free((yyvsp[-2].string));
      free((yyvsp[-1].string));
    }
#line 2973 "yacc_sql.cpp"
    break;

  case 112: /* group_by: %empty  */
#line 1032 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2981 "yacc_sql.cpp"
    break;

  case 113: /* group_by: GROUP BY expression attr_list  */
#line 1036 "yacc_sql.y"
    {
      if((yyvsp[0].expression_list) != nullptr){
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 2994 "yacc_sql.cpp"
    break;

  case 114: /* having: %empty  */
#line 1047 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3002 "yacc_sql.cpp"
    break;

  case 115: /* having: HAVING having_attr having_list  */
#line 1051 "yacc_sql.y"
    {
      if((yyvsp[0].condition_list) != nullptr){
        (yyval.condition_list) = (yyvsp[0].condition_list);
      } else {
        (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      }
      (yyval.condition_list)->emplace_back(*(yyvsp[-1].condition));
      delete (yyvsp[-1].condition);
    }
#line 3016 "yacc_sql.cpp"
    break;

  case 116: /* having_list: %empty  */
#line 1063 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3024 "yacc_sql.cpp"
    break;

  case 117: /* having_list: COMMA having_attr having_list  */
#line 1067 "yacc_sql.y"
    {
      if((yyvsp[0].condition_list) != nullptr){
        (yyval.condition_list) = (yyvsp[0].condition_list);
      } else {
        (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      }
      (yyval.condition_list)->emplace_back(*(yyvsp[-1].condition));
      delete (yyvsp[-1].condition);
    }
#line 3038 "yacc_sql.cpp"
    break;

  case 118: /* having_attr: rel_attr comp_op value  */
#line 1080 "yacc_sql.y"
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
#line 3054 "yacc_sql.cpp"
    break;

  case 119: /* join_node: INNER JOIN ID ON condition_list  */
#line 1093 "yacc_sql.y"
    {
      (yyval.join_node) = new JoinSqlNode{(yyvsp[-2].string),*(yyvsp[0].condition_list)};
      delete (yyvsp[-2].string);
      delete (yyvsp[0].condition_list);
    }
#line 3064 "yacc_sql.cpp"
    break;

  case 120: /* join_list: %empty  */
#line 1102 "yacc_sql.y"
    {
      (yyval.join_list) = nullptr;
    }
#line 3072 "yacc_sql.cpp"
    break;

  case 121: /* join_list: join_node  */
#line 1106 "yacc_sql.y"
    {
      (yyval.join_list) = new std::vector<JoinSqlNode>{*(yyvsp[0].join_node)};
      delete (yyvsp[0].join_node);   
    }
#line 3081 "yacc_sql.cpp"
    break;

  case 122: /* join_list: join_list join_node  */
#line 1111 "yacc_sql.y"
    {
      (yyval.join_list)->emplace_back(*(yyvsp[0].join_node));
      delete (yyvsp[0].join_node);

    }
#line 3091 "yacc_sql.cpp"
    break;

  case 123: /* order_by: %empty  */
#line 1120 "yacc_sql.y"
    {
      (yyval.order_by_attr_list) = nullptr;
    }
#line 3099 "yacc_sql.cpp"
    break;

  case 124: /* order_by: ORDER BY order_by_node order_by_node_list  */
#line 1124 "yacc_sql.y"
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
#line 3114 "yacc_sql.cpp"
    break;

  case 125: /* order_by_node_list: %empty  */
#line 1138 "yacc_sql.y"
    {
      (yyval.order_by_attr_list) = nullptr;
    }
#line 3122 "yacc_sql.cpp"
    break;

  case 126: /* order_by_node_list: COMMA order_by_node order_by_node_list  */
#line 1142 "yacc_sql.y"
    {
      if((yyvsp[0].order_by_attr_list) != nullptr){
        (yyval.order_by_attr_list) = (yyvsp[0].order_by_attr_list);
      } else {
        (yyval.order_by_attr_list) = new std::vector<OrderBySqlNode>;
      }
      (yyval.order_by_attr_list)->push_back(*(yyvsp[-1].order_by_attr));
    }
#line 3135 "yacc_sql.cpp"
    break;

  case 127: /* order_by_node: rel_attr DESC  */
#line 1153 "yacc_sql.y"
    {
      (yyval.order_by_attr) = new OrderBySqlNode;
      (yyval.order_by_attr)->relation_name = std::move((yyvsp[-1].rel_attr)->relation_name);
      (yyval.order_by_attr)->attribute_name = std::move((yyvsp[-1].rel_attr)->attribute_name);
      (yyval.order_by_attr)->is_desc = true;
      free((yyvsp[-1].rel_attr));
    }
#line 3147 "yacc_sql.cpp"
    break;

  case 128: /* order_by_node: rel_attr ASC  */
#line 1161 "yacc_sql.y"
    {
      (yyval.order_by_attr) = new OrderBySqlNode;
      (yyval.order_by_attr)->relation_name = std::move((yyvsp[-1].rel_attr)->relation_name);
      (yyval.order_by_attr)->attribute_name = std::move((yyvsp[-1].rel_attr)->attribute_name);
      (yyval.order_by_attr)->is_desc = false;
      free((yyvsp[-1].rel_attr));
    }
#line 3159 "yacc_sql.cpp"
    break;

  case 129: /* order_by_node: rel_attr  */
#line 1168 "yacc_sql.y"
    {
      (yyval.order_by_attr) = new OrderBySqlNode;
      (yyval.order_by_attr)->relation_name = std::move((yyvsp[0].rel_attr)->relation_name);
      (yyval.order_by_attr)->attribute_name = std::move((yyvsp[0].rel_attr)->attribute_name);
      (yyval.order_by_attr)->is_desc = false;
      free((yyvsp[0].rel_attr));
    }
#line 3171 "yacc_sql.cpp"
    break;

  case 130: /* where: %empty  */
#line 1177 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3179 "yacc_sql.cpp"
    break;

  case 131: /* where: WHERE condition_list  */
#line 1180 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3187 "yacc_sql.cpp"
    break;

  case 132: /* condition_list: %empty  */
#line 1186 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3195 "yacc_sql.cpp"
    break;

  case 133: /* condition_list: condition  */
#line 1189 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3205 "yacc_sql.cpp"
    break;

  case 134: /* condition_list: condition AND condition_list  */
#line 1194 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->front().link_type = 0;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3216 "yacc_sql.cpp"
    break;

  case 135: /* condition_list: condition OR condition_list  */
#line 1200 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->front().link_type = 1;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3227 "yacc_sql.cpp"
    break;

  case 136: /* condition: expression comp_op expression  */
#line 1209 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 4;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 4;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3240 "yacc_sql.cpp"
    break;

  case 137: /* condition: expression LIKE expression  */
#line 1218 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 4;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 4;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = CompOp::LIKE_OP;
    }
#line 3253 "yacc_sql.cpp"
    break;

  case 138: /* condition: expression NOT LIKE expression  */
#line 1227 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 4;
      (yyval.condition)->left_expr = (yyvsp[-3].expression);
      (yyval.condition)->right_is_attr = 4;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = CompOp::NOT_LIKE_OP;
    }
#line 3266 "yacc_sql.cpp"
    break;

  case 139: /* condition: expression IS NULL_TOKEN  */
#line 1236 "yacc_sql.y"
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
#line 3281 "yacc_sql.cpp"
    break;

  case 140: /* condition: expression IS NOT NULL_TOKEN  */
#line 1247 "yacc_sql.y"
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
#line 3296 "yacc_sql.cpp"
    break;

  case 141: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 1258 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 2;
      (yyval.condition)->left_sub_query = (yyvsp[-5].sql_node);
      (yyval.condition)->right_is_attr = 2;
      (yyval.condition)->right_sub_query = (yyvsp[-1].sql_node);
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 3309 "yacc_sql.cpp"
    break;

  case 142: /* condition: expression comp_op LBRACE select_stmt RBRACE  */
#line 1267 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 4;
      (yyval.condition)->left_expr = (yyvsp[-4].expression);
      (yyval.condition)->right_is_attr = 2;
      (yyval.condition)->right_sub_query = (yyvsp[-1].sql_node);
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 3322 "yacc_sql.cpp"
    break;

  case 143: /* condition: LBRACE select_stmt RBRACE comp_op expression  */
#line 1276 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 2;
      (yyval.condition)->left_sub_query = (yyvsp[-3].sql_node);
      (yyval.condition)->right_is_attr = 4;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3335 "yacc_sql.cpp"
    break;

  case 144: /* condition: expression comp_op tuple  */
#line 1285 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 4;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 3;
      (yyval.condition)->right_value_list = *(yyvsp[0].tuple);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3348 "yacc_sql.cpp"
    break;

  case 145: /* comp_op: EQ  */
#line 1296 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3354 "yacc_sql.cpp"
    break;

  case 146: /* comp_op: LT  */
#line 1297 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3360 "yacc_sql.cpp"
    break;

  case 147: /* comp_op: GT  */
#line 1298 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3366 "yacc_sql.cpp"
    break;

  case 148: /* comp_op: LE  */
#line 1299 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3372 "yacc_sql.cpp"
    break;

  case 149: /* comp_op: GE  */
#line 1300 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3378 "yacc_sql.cpp"
    break;

  case 150: /* comp_op: NE  */
#line 1301 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3384 "yacc_sql.cpp"
    break;

  case 151: /* comp_op: IN  */
#line 1302 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3390 "yacc_sql.cpp"
    break;

  case 152: /* comp_op: NOT IN  */
#line 1303 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP; }
#line 3396 "yacc_sql.cpp"
    break;

  case 153: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1308 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3410 "yacc_sql.cpp"
    break;

  case 154: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1321 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3419 "yacc_sql.cpp"
    break;

  case 155: /* set_variable_stmt: SET ID EQ value  */
#line 1329 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3431 "yacc_sql.cpp"
    break;


#line 3435 "yacc_sql.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1341 "yacc_sql.y"

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
