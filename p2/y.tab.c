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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <string.h>
#include "typecheck.h"
#include "node.h"
void yyerror(char *);

extern int yylex();

// Global variables defined by lex.yy.c.
extern int yylineno;
extern char* yytext;
extern FILE *yyin;

struct ASTNode* root;

#line 87 "y.tab.c"

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
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_AND = 258,
    TOK_NEQ = 259,
    TOK_OR = 260,
    TOK_LEQ = 261,
    TOK_GEQ = 262,
    TOK_EQLEQL = 263,
    MAIN = 264,
    KW_PUBLIC = 265,
    KW_PRIVATE = 266,
    KW_STATIC = 267,
    KW_CLASS = 268,
    KW_VOID = 269,
    KW_INT = 270,
    KW_BOOL = 271,
    KW_STR = 272,
    KW_IF = 273,
    KW_ELSE = 274,
    KW_WHILE = 275,
    KW_NEW = 276,
    KW_RETURN = 277,
    KW_SYSTEM = 278,
    KW_OUT = 279,
    KW_PRINT = 280,
    KW_PRINTLN = 281,
    KW_TRUE = 282,
    KW_FALSE = 283,
    CLASS_INTEGER = 284,
    INTEGER_PARSEINT = 285,
    STRING_LENGTH = 286,
    INT_LIT = 287,
    STR_LIT = 288,
    ID = 289,
    Unary = 290,
    Paren = 291
  };
#endif
/* Tokens.  */
#define TOK_AND 258
#define TOK_NEQ 259
#define TOK_OR 260
#define TOK_LEQ 261
#define TOK_GEQ 262
#define TOK_EQLEQL 263
#define MAIN 264
#define KW_PUBLIC 265
#define KW_PRIVATE 266
#define KW_STATIC 267
#define KW_CLASS 268
#define KW_VOID 269
#define KW_INT 270
#define KW_BOOL 271
#define KW_STR 272
#define KW_IF 273
#define KW_ELSE 274
#define KW_WHILE 275
#define KW_NEW 276
#define KW_RETURN 277
#define KW_SYSTEM 278
#define KW_OUT 279
#define KW_PRINT 280
#define KW_PRINTLN 281
#define KW_TRUE 282
#define KW_FALSE 283
#define CLASS_INTEGER 284
#define INTEGER_PARSEINT 285
#define STRING_LENGTH 286
#define INT_LIT 287
#define STR_LIT 288
#define ID 289
#define Unary 290
#define Paren 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 21 "parser.y"

    struct ASTNode* node;
    int integer;
    char * string;

#line 217 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
typedef yytype_uint8 yy_state_t;

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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   226

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  177

#define YYUNDEFTOK  2
#define YYMAXUTOK   291


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
       2,     2,     2,    53,     2,     2,     2,     2,     2,     2,
      46,    49,    40,    38,    51,    39,    52,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    50,
      36,    35,    37,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    48,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,    45,     2,     2,     2,     2,
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
      42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    69,    69,    76,    86,    94,   103,   106,   111,   114,
     121,   124,   133,   136,   141,   144,   150,   153,   163,   172,
     179,   182,   187,   192,   199,   204,   211,   216,   221,   228,
     234,   239,   244,   250,   255,   262,   268,   273,   280,   286,
     293,   299,   306,   312,   318,   325,   331,   337,   343,   349,
     356,   362,   368,   375,   381,   387,   394,   401,   406,   411,
     416,   421,   426,   431,   436,   441,   446,   451,   456,   464,
     470,   477,   485,   491,   494,   499
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_AND", "TOK_NEQ", "TOK_OR",
  "TOK_LEQ", "TOK_GEQ", "TOK_EQLEQL", "MAIN", "KW_PUBLIC", "KW_PRIVATE",
  "KW_STATIC", "KW_CLASS", "KW_VOID", "KW_INT", "KW_BOOL", "KW_STR",
  "KW_IF", "KW_ELSE", "KW_WHILE", "KW_NEW", "KW_RETURN", "KW_SYSTEM",
  "KW_OUT", "KW_PRINT", "KW_PRINTLN", "KW_TRUE", "KW_FALSE",
  "CLASS_INTEGER", "INTEGER_PARSEINT", "STRING_LENGTH", "INT_LIT",
  "STR_LIT", "ID", "'='", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "Unary", "Paren", "'{'", "'}'", "'('", "'['", "']'", "')'", "';'", "','",
  "'.'", "'!'", "$accept", "Program", "MainClass", "MainMethod",
  "StaticVarDecl", "EqlExp", "StaticVarDeclTail", "StaticMethodDecl",
  "IfFormalList", "StatementList", "VarDecl", "FormalList",
  "FormalListTail", "PrimeType", "Type", "Statement", "MethodCall",
  "Exp_or", "Exp_and", "Exp_eql", "Exp_ineql", "Exp_plusminus",
  "Exp_muldiv", "Exp_factor", "Factor", "Index", "ExpList", "ExpListTail",
  "LeftValue", YY_NULLPTR
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
     285,   286,   287,   288,   289,    61,    60,    62,    43,    45,
      42,    47,   290,   291,   123,   125,    40,    91,    93,    41,
      59,    44,    46,    33
};
# endif

#define YYPACT_NINF (-119)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -7,    -8,    38,  -119,    30,  -119,  -119,    68,    32,   103,
     102,   117,    89,  -119,  -119,  -119,  -119,   -23,    90,  -119,
     105,    94,   138,   -18,    82,  -119,  -119,   106,   107,   102,
    -119,  -119,   108,  -119,  -119,   116,    82,    82,    82,    82,
    -119,   146,   151,    83,    16,    28,    54,  -119,  -119,   -15,
      72,   150,   102,   122,   142,    43,  -119,  -119,     2,  -119,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,   137,  -119,   139,   124,   125,  -119,    -6,
      82,   133,   136,  -119,   146,   140,  -119,   151,    83,    16,
      16,    28,    28,    28,    28,    54,    54,  -119,  -119,    -1,
    -119,   105,   143,   144,  -119,    13,    82,    82,   149,  -119,
    -119,  -119,   153,  -119,   156,  -119,    14,     5,    82,   145,
     121,   102,  -119,  -119,   146,   148,   147,   162,    82,   157,
    -119,  -119,  -119,    26,  -119,   152,   -14,    31,  -119,    82,
      82,    -2,   187,   141,   105,  -119,    82,  -119,   161,     7,
       8,  -119,   160,  -119,  -119,     0,  -119,   181,   181,    99,
      76,  -119,   194,  -119,   168,   170,  -119,   181,    82,    82,
    -119,     9,    10,   167,   169,  -119,  -119
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     6,    12,     0,     0,
       0,     0,     0,    21,    22,    23,    24,     0,     0,     3,
       8,     0,     0,     0,     0,    10,    25,     0,     0,     0,
      65,    66,     0,    63,    64,    74,     0,     0,     0,     0,
      67,     7,    39,    41,    44,    49,    52,    55,    56,    61,
       0,     0,    14,     0,     0,     0,    58,    59,     0,    57,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     0,     0,     0,    13,     0,
       0,    68,     0,    36,    73,     0,    60,    38,    40,    43,
      42,    47,    48,    45,    46,    50,    51,    53,    54,     0,
      62,     8,     0,     0,    20,     0,     0,     0,    71,    35,
      75,     9,     0,    16,    18,    70,     0,     0,     0,     0,
       0,     0,    69,    37,    72,     0,     0,     0,     0,     0,
      16,    11,    26,     0,    15,     0,     0,     0,    16,     0,
       0,     0,     0,     0,     8,    34,     0,    19,     0,     0,
       0,    33,     0,    27,    10,     0,     4,     0,     0,     0,
       0,    32,     0,    29,     0,     0,    17,     0,     0,     0,
      28,     0,     0,     0,     0,    31,    30
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -119,  -119,  -119,  -119,  -119,   -81,    64,  -119,  -119,  -103,
    -119,  -119,  -119,   191,    -9,   -74,  -118,   -38,   163,   165,
      70,    33,    77,    78,    49,  -119,  -119,  -119,  -112
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    12,     7,    25,    50,     9,    77,   120,
     132,    78,   114,    16,   133,   134,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    81,    85,   108,    49
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      58,    17,   135,    60,    60,    60,     1,    60,   136,    23,
      60,    20,    60,    60,    60,    60,    28,    84,    60,    60,
     111,   146,    64,    65,    21,   135,     4,   143,   104,    21,
     135,   136,    72,    72,    99,   148,   136,    73,     5,   135,
     135,    21,   105,    79,    10,   136,   136,   110,   151,   135,
     161,    86,    66,    67,   123,   136,   157,   158,   173,   174,
     144,   115,   122,   154,    29,   147,    68,    69,   116,   117,
      30,    31,    32,    21,     6,    33,    34,    35,    21,     8,
     124,    36,    37,   162,   163,    56,    57,    62,    59,    38,
     141,    63,    83,   170,    70,    71,    39,    91,    92,    93,
      94,   149,   150,    29,    22,    13,    14,    15,   155,    30,
      31,    32,   137,    11,    33,    34,    35,    13,    14,    15,
      36,    37,    74,    75,   164,   165,   166,    75,    38,    18,
     171,   172,    89,    90,    19,    39,    13,    14,    15,   126,
      24,   127,    26,   128,   129,    95,    96,    27,    97,    98,
      32,    60,    51,    52,    61,    35,    13,    14,    15,   126,
      54,   127,    55,   128,   129,   130,   131,    76,   100,    80,
      32,   102,    82,   101,   103,    35,    13,    14,    15,   126,
     106,   127,   107,   128,   129,   130,   153,   119,   113,   109,
      32,   112,   138,   139,   125,    35,    13,    14,    15,   126,
     118,   127,   145,   128,   129,   130,   156,   121,   140,   142,
      32,   152,   159,   167,   168,    35,   169,   175,   160,   176,
      53,     0,     0,    87,     0,   130,    88
};

static const yytype_int16 yycheck[] =
{
      38,    10,   120,     5,     5,     5,    13,     5,   120,    18,
       5,    34,     5,     5,     5,     5,    34,    55,     5,     5,
     101,    35,     6,     7,    47,   143,    34,   130,    34,    47,
     148,   143,    47,    47,    72,   138,   148,    52,     0,   157,
     158,    47,    80,    52,    12,   157,   158,    48,    50,   167,
      50,    49,    36,    37,    49,   167,    49,    49,    49,    49,
      34,    48,    48,   144,    21,    34,    38,    39,   106,   107,
      27,    28,    29,    47,    44,    32,    33,    34,    47,    11,
     118,    38,    39,   157,   158,    36,    37,     4,    39,    46,
     128,     8,    49,   167,    40,    41,    53,    64,    65,    66,
      67,   139,   140,    21,    14,    15,    16,    17,   146,    27,
      28,    29,   121,    10,    32,    33,    34,    15,    16,    17,
      38,    39,    50,    51,    25,    26,    50,    51,    46,    12,
     168,   169,    62,    63,    45,    53,    15,    16,    17,    18,
      35,    20,    48,    22,    23,    68,    69,     9,    70,    71,
      29,     5,    46,    46,     3,    34,    15,    16,    17,    18,
      52,    20,    46,    22,    23,    44,    45,    17,    31,    47,
      29,    47,    30,    34,    49,    34,    15,    16,    17,    18,
      47,    20,    46,    22,    23,    44,    45,    34,    44,    49,
      29,    48,    44,    46,    49,    34,    15,    16,    17,    18,
      51,    20,    50,    22,    23,    44,    45,    51,    46,    52,
      29,    24,    52,    19,    46,    34,    46,    50,   154,    50,
      29,    -1,    -1,    60,    -1,    44,    61
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    13,    55,    56,    34,     0,    44,    58,    11,    61,
      12,    10,    57,    15,    16,    17,    67,    68,    12,    45,
      34,    47,    14,    68,    35,    59,    48,     9,    34,    21,
      27,    28,    29,    32,    33,    34,    38,    39,    46,    53,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    82,
      60,    46,    46,    67,    52,    46,    78,    78,    71,    78,
       5,     3,     4,     8,     6,     7,    36,    37,    38,    39,
      40,    41,    47,    52,    50,    51,    17,    62,    65,    68,
      47,    79,    30,    49,    71,    80,    49,    72,    73,    74,
      74,    75,    75,    75,    75,    76,    76,    77,    77,    71,
      31,    34,    47,    49,    34,    71,    47,    46,    81,    49,
      48,    59,    48,    44,    66,    48,    71,    71,    51,    34,
      63,    51,    48,    49,    71,    49,    18,    20,    22,    23,
      44,    45,    64,    68,    69,    70,    82,    68,    44,    46,
      46,    71,    52,    63,    34,    50,    35,    34,    63,    71,
      71,    50,    24,    45,    59,    71,    45,    49,    49,    52,
      60,    50,    69,    69,    25,    26,    50,    19,    46,    46,
      69,    71,    71,    49,    49,    50,    50
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    54,    55,    56,    57,    58,    58,    59,    59,    60,
      60,    61,    61,    62,    62,    63,    63,    64,    65,    66,
      66,    67,    67,    67,    68,    68,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    70,    70,    70,    71,    71,
      72,    72,    73,    73,    73,    74,    74,    74,    74,    74,
      75,    75,    75,    76,    76,    76,    77,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    79,
      79,    80,    81,    81,    82,    82
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     7,    13,     8,     0,     2,     0,     4,
       0,    11,     0,     1,     0,     2,     0,     5,     3,     4,
       0,     1,     1,     1,     1,     3,     1,     3,     7,     5,
       9,     9,     4,     3,     2,     4,     3,     6,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     1,     2,     2,     2,
       3,     1,     3,     1,     1,     1,     1,     1,     3,     4,
       3,     2,     3,     0,     1,     4
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
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
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 69 "parser.y"
              {
        (yyval.node) = new_node(NODETYPE_PROGRAM);
        root = (yyval.node);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1525 "y.tab.c"
    break;

  case 3:
#line 76 "parser.y"
                                                                  {
        (yyval.node) = new_node(NODETYPE_MAINCLASS);
        set_string_value((yyval.node), (yyvsp[-5].string));
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1538 "y.tab.c"
    break;

  case 4:
#line 86 "parser.y"
                                                                                     {
        (yyval.node) = new_node(NODETYPE_MAINMETHOD);
        set_lineno((yyval.node), yylineno);
        set_string_value((yyval.node), (yyvsp[-4].string));
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1549 "y.tab.c"
    break;

  case 5:
#line 94 "parser.y"
                                                                            {
        (yyval.node) = new_node(NODETYPE_STATICVARDECL);
        set_lineno((yyval.node), yylineno);
        set_string_value((yyval.node), (yyvsp[-3].string));
        add_child((yyval.node), (yyvsp[-7].node));
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1563 "y.tab.c"
    break;

  case 6:
#line 103 "parser.y"
      { (yyval.node) = new_node(NODETYPE_EPSILON); }
#line 1569 "y.tab.c"
    break;

  case 7:
#line 106 "parser.y"
               {
        (yyval.node) = new_node(NODETYPE_EQLEXP);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1579 "y.tab.c"
    break;

  case 8:
#line 111 "parser.y"
      { (yyval.node) = new_node(NODETYPE_EPSILON); }
#line 1585 "y.tab.c"
    break;

  case 9:
#line 114 "parser.y"
                                    {
        (yyval.node) = new_node(NODETYPE_STATICVARDECLTAIL);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-3].node));
        set_string_value((yyval.node), (yyvsp[-1].string));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1597 "y.tab.c"
    break;

  case 10:
#line 121 "parser.y"
      { (yyval.node) = new_node(NODETYPE_EPSILON); }
#line 1603 "y.tab.c"
    break;

  case 11:
#line 124 "parser.y"
                                                                                            {
        (yyval.node) = new_node(NODETYPE_STATICMETHODDECL);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-10].node));
        add_child((yyval.node), (yyvsp[-7].node));
        set_string_value((yyval.node), (yyvsp[-6].string));
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1617 "y.tab.c"
    break;

  case 12:
#line 133 "parser.y"
      { (yyval.node) = new_node(NODETYPE_EPSILON); }
#line 1623 "y.tab.c"
    break;

  case 13:
#line 136 "parser.y"
               {
        (yyval.node) = new_node(NODETYPE_IFFORMALLIST);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1633 "y.tab.c"
    break;

  case 14:
#line 141 "parser.y"
      { (yyval.node) = new_node(NODETYPE_EPSILON); }
#line 1639 "y.tab.c"
    break;

  case 15:
#line 144 "parser.y"
                            {
        (yyval.node) = new_node(NODETYPE_STATEMENTLIST);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1650 "y.tab.c"
    break;

  case 16:
#line 150 "parser.y"
      { (yyval.node) = new_node(NODETYPE_EPSILON); }
#line 1656 "y.tab.c"
    break;

  case 17:
#line 153 "parser.y"
                                         {
        (yyval.node) = new_node(NODETYPE_VARDECL);
        set_lineno((yyval.node), yylineno);
        set_string_value((yyval.node), (yyvsp[-3].string));
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1669 "y.tab.c"
    break;

  case 18:
#line 163 "parser.y"
                           {
        (yyval.node) = new_node(NODETYPE_FORMALLIST);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        set_string_value((yyval.node), (yyvsp[-1].string));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1681 "y.tab.c"
    break;

  case 19:
#line 172 "parser.y"
                               {
        (yyval.node) = new_node(NODETYPE_FORMALLISTTAIL);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-1].node));
        set_string_value((yyval.node), (yyvsp[0].string));
    }
#line 1693 "y.tab.c"
    break;

  case 20:
#line 179 "parser.y"
      { (yyval.node) = new_node(NODETYPE_EPSILON); }
#line 1699 "y.tab.c"
    break;

  case 21:
#line 182 "parser.y"
           {
        (yyval.node) = new_node(NODETYPE_PRIMETYPE);
        set_lineno((yyval.node), yylineno);
        (yyval.node) -> data.type = DATATYPE_INT;
    }
#line 1709 "y.tab.c"
    break;

  case 22:
#line 187 "parser.y"
              {
        (yyval.node) = new_node(NODETYPE_PRIMETYPE);
        set_lineno((yyval.node), yylineno);
        (yyval.node) -> data.type = DATATYPE_BOOLEAN;
    }
#line 1719 "y.tab.c"
    break;

  case 23:
#line 192 "parser.y"
             {
        (yyval.node) = new_node(NODETYPE_PRIMETYPE);
        set_lineno((yyval.node), yylineno);
        (yyval.node) -> data.type = DATATYPE_STR;
    }
#line 1729 "y.tab.c"
    break;

  case 24:
#line 199 "parser.y"
              {
        (yyval.node) = new_node(NODETYPE_PRIMETYPE);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1739 "y.tab.c"
    break;

  case 25:
#line 204 "parser.y"
                   {
        (yyval.node) = new_node(NODETYPE_TYPE);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
    }
#line 1749 "y.tab.c"
    break;

  case 26:
#line 211 "parser.y"
            {
        (yyval.node) = new_node(NODETYPE_VARDECL);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1759 "y.tab.c"
    break;

  case 27:
#line 216 "parser.y"
                            {
        (yyval.node) = new_node(NODETYPE_STATEMENTLIST);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1769 "y.tab.c"
    break;

  case 28:
#line 221 "parser.y"
                                                       {
        (yyval.node) = new_node(NODETYPE_IF);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1781 "y.tab.c"
    break;

  case 29:
#line 228 "parser.y"
                                        {
        (yyval.node) = new_node(NODETYPE_WHILE);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1792 "y.tab.c"
    break;

  case 30:
#line 234 "parser.y"
                                                             {
        (yyval.node) = new_node(NODETYPE_PRINTLN);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
    }
#line 1802 "y.tab.c"
    break;

  case 31:
#line 239 "parser.y"
                                                           {
        (yyval.node) = new_node(NODETYPE_PRINT);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
    }
#line 1812 "y.tab.c"
    break;

  case 32:
#line 244 "parser.y"
                               {
        (yyval.node) = new_node(NODETYPE_LEFTVALUE);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1823 "y.tab.c"
    break;

  case 33:
#line 250 "parser.y"
                           {
        (yyval.node) = new_node(NODETYPE_RETURN);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1833 "y.tab.c"
    break;

  case 34:
#line 255 "parser.y"
                     {
        (yyval.node) = new_node(NODETYPE_METHODCALL);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1843 "y.tab.c"
    break;

  case 35:
#line 262 "parser.y"
                       {
        (yyval.node) = new_node(NODETYPE_EXPLIST);
        set_lineno((yyval.node), yylineno);
        set_string_value((yyval.node), (yyvsp[-3].string));
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1854 "y.tab.c"
    break;

  case 36:
#line 268 "parser.y"
                 {
        (yyval.node) = new_node(NODETYPE_ID);
        set_lineno((yyval.node), yylineno);
        set_string_value((yyval.node), (yyvsp[-2].string));
    }
#line 1864 "y.tab.c"
    break;

  case 37:
#line 273 "parser.y"
                                                        {
        (yyval.node) = new_node(NODETYPE_PARSEINT);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1874 "y.tab.c"
    break;

  case 38:
#line 280 "parser.y"
                          {
        (yyval.node) = new_node(NODETYPE_EXPOR);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1885 "y.tab.c"
    break;

  case 39:
#line 286 "parser.y"
              {
        (yyval.node) = new_node(NODETYPE_EXPAND);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1895 "y.tab.c"
    break;

  case 40:
#line 293 "parser.y"
                            {
        (yyval.node) = new_node(NODETYPE_EXPAND);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1906 "y.tab.c"
    break;

  case 41:
#line 299 "parser.y"
              {
        (yyval.node) = new_node(NODETYPE_EXPEQL);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1916 "y.tab.c"
    break;

  case 42:
#line 306 "parser.y"
                                 {
        (yyval.node) = new_node(NODETYPE_EXPEQL);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1927 "y.tab.c"
    break;

  case 43:
#line 312 "parser.y"
                                {
        (yyval.node) = new_node(NODETYPE_EXPNEQ);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1938 "y.tab.c"
    break;

  case 44:
#line 318 "parser.y"
                {
        (yyval.node) = new_node(NODETYPE_EXPINEQL);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1948 "y.tab.c"
    break;

  case 45:
#line 325 "parser.y"
                                {
        (yyval.node) = new_node(NODETYPE_EXPLES);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1959 "y.tab.c"
    break;

  case 46:
#line 331 "parser.y"
                                  {
        (yyval.node) = new_node(NODETYPE_EXPGRT);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1970 "y.tab.c"
    break;

  case 47:
#line 337 "parser.y"
                                      {
        (yyval.node) = new_node(NODETYPE_EXPLEQ);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1981 "y.tab.c"
    break;

  case 48:
#line 343 "parser.y"
                                      {
        (yyval.node) = new_node(NODETYPE_EXPGEQ);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1992 "y.tab.c"
    break;

  case 49:
#line 349 "parser.y"
                    {
        (yyval.node) = new_node(NODETYPE_EXPPLUSMINUS);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2002 "y.tab.c"
    break;

  case 50:
#line 356 "parser.y"
                                 {
        (yyval.node) = new_node(NODETYPE_EXPPLUS);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2013 "y.tab.c"
    break;

  case 51:
#line 362 "parser.y"
                                   {
        (yyval.node) = new_node(NODETYPE_EXPMINUS);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2024 "y.tab.c"
    break;

  case 52:
#line 368 "parser.y"
                 {
        (yyval.node) = new_node(NODETYPE_EXPMULDIV);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2034 "y.tab.c"
    break;

  case 53:
#line 375 "parser.y"
                              {
        (yyval.node) = new_node(NODETYPE_EXPMUL);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2045 "y.tab.c"
    break;

  case 54:
#line 381 "parser.y"
                                {
        (yyval.node) = new_node(NODETYPE_EXPDIV);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2056 "y.tab.c"
    break;

  case 55:
#line 387 "parser.y"
                 {
        (yyval.node) = new_node(NODETYPE_EXPFACTOR);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2066 "y.tab.c"
    break;

  case 56:
#line 394 "parser.y"
           {
        (yyval.node) = new_node(NODETYPE_FACTOR);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2076 "y.tab.c"
    break;

  case 57:
#line 401 "parser.y"
               {
        (yyval.node) = new_node(NODETYPE_NEG);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2086 "y.tab.c"
    break;

  case 58:
#line 406 "parser.y"
                 {
        (yyval.node) = new_node(NODETYPE_PLUS);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2096 "y.tab.c"
    break;

  case 59:
#line 411 "parser.y"
                 {
        (yyval.node) = new_node(NODETYPE_MINUS);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2106 "y.tab.c"
    break;

  case 60:
#line 416 "parser.y"
                                 {
        (yyval.node) = new_node(NODETYPE_FACTORRECUR);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 2116 "y.tab.c"
    break;

  case 61:
#line 421 "parser.y"
                {
        (yyval.node) = new_node(NODETYPE_LEFTVALUE);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2126 "y.tab.c"
    break;

  case 62:
#line 426 "parser.y"
                                  {
        (yyval.node) = new_node(NODETYPE_LEFTVALUELENGTH);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
    }
#line 2136 "y.tab.c"
    break;

  case 63:
#line 431 "parser.y"
              {
        (yyval.node) = new_node(NODETYPE_INT);
        set_lineno((yyval.node), yylineno);
        set_int_value((yyval.node), (yyvsp[0].integer));
    }
#line 2146 "y.tab.c"
    break;

  case 64:
#line 436 "parser.y"
              {
        (yyval.node) = new_node(NODETYPE_STR);
        set_lineno((yyval.node), yylineno);
        set_string_value((yyval.node), (yyvsp[0].string));
    }
#line 2156 "y.tab.c"
    break;

  case 65:
#line 441 "parser.y"
              {
        (yyval.node) = new_node(NODETYPE_TRUE);
        set_lineno((yyval.node), yylineno);
        set_boolean_value((yyval.node), true);
    }
#line 2166 "y.tab.c"
    break;

  case 66:
#line 446 "parser.y"
               {
        (yyval.node) = new_node(NODETYPE_FALSE);
        set_lineno((yyval.node), yylineno);
        set_boolean_value((yyval.node), false);
    }
#line 2176 "y.tab.c"
    break;

  case 67:
#line 451 "parser.y"
                 {
        (yyval.node) = new_node(NODETYPE_METHODCALL);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2186 "y.tab.c"
    break;

  case 68:
#line 456 "parser.y"
                             {
        (yyval.node) = new_node(NODETYPE_NEW);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2197 "y.tab.c"
    break;

  case 69:
#line 464 "parser.y"
                        {
        (yyval.node) = new_node(NODETYPE_INDEXRECUR);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 2208 "y.tab.c"
    break;

  case 70:
#line 470 "parser.y"
                     {
        (yyval.node) = new_node(NODETYPE_INDEX);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 2218 "y.tab.c"
    break;

  case 71:
#line 477 "parser.y"
                       {
        (yyval.node) = new_node(NODETYPE_EXPLIST);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2229 "y.tab.c"
    break;

  case 72:
#line 485 "parser.y"
                           {
        (yyval.node) = new_node(NODETYPE_EXPLISTTAIL);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2240 "y.tab.c"
    break;

  case 73:
#line 491 "parser.y"
      { (yyval.node) = new_node(NODETYPE_EPSILON); }
#line 2246 "y.tab.c"
    break;

  case 74:
#line 494 "parser.y"
       {
        (yyval.node) = new_node(NODETYPE_LEFTVALUE);
        set_lineno((yyval.node), yylineno);
        set_string_value((yyval.node), (yyvsp[0].string));
    }
#line 2256 "y.tab.c"
    break;

  case 75:
#line 499 "parser.y"
                               {
        (yyval.node) = new_node(NODETYPE_LEFTVALUERECUR);
        set_lineno((yyval.node), yylineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 2267 "y.tab.c"
    break;


#line 2271 "y.tab.c"

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
      yyerror (YY_("syntax error"));
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
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
#line 506 "parser.y"


void yyerror(char* s) {
    fprintf(stderr, "Syntax errors in line %d\n", yylineno);
}

int main(int argc, char* argv[] )
{
    yyin = fopen( argv[1], "r" );
    /*char buffer[30];
    fscanf(yyin, "%[^\n]\n", buffer);
    printf("%s\n", buffer);*/

    // Checks for syntax errors and constructs AST
    if (yyparse() != 0)
        return 1;
    /*while (yywrap() != 1) {
        if (yyparse() != 0)
            return 1;
    }*/

    // Traverse the AST to check for semantic errors if no syntac errors
    checkProgram(root);

    return 0;
}
