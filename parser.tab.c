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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <vector>
#include "symbolTable.h"

using namespace std;

static ExtendedType _T_STRING{Type::STRING,{}};
static ExtendedType _T_BOOL  {Type::BOOL  ,{}};
static ExtendedType _T_INT   {Type::INT   ,{}};
static ExtendedType _T_FLOAT {Type::FLOAT ,{}};
static ExtendedType _T_VOID  {Type::VOID  ,{}};
static ExtendedType _T_ERROR {Type::ERROR ,{}};

#define TRACE(t) printf(t)
#define  T_STRING (&_T_STRING)
#define  T_BOOL   (&_T_BOOL)
#define  T_INT    (&_T_INT)
#define  T_FLOAT  (&_T_FLOAT)
#define  T_VOID   (&_T_VOID)
#define  T_ERROR  (&_T_ERROR)

struct Pending_var {
    string        id;
    ExtendedType* type;
};

extern FILE* yyin;
SymbolTable symtab;
extern int linenum;                    

void yyerror(const string& msg);
int yylex(void);

vector<Pending_var> decl_vars;
vector<ExtendedType*> func_params_type;
vector<ExtendedType*> type_pool;

static void semantic_error(const string& msg, const string& id) {
    cerr << "SEMANTIC(" << linenum << "): " << msg << ' ' << id << '\n';
    for (auto& ptr : type_pool) delete ptr;
    exit(-1);
}

static bool type_compatible(const ExtendedType* dst, const ExtendedType* src) {
    if (*dst == *src)                                      return true;
    if (dst == T_STRING || src == T_STRING)                return false;
    if (dst == T_FLOAT  && src == T_INT)                   return true;
    if (dst == T_INT    && src == T_FLOAT)                 return true;
    if ((dst == T_INT || dst == T_FLOAT) && src == T_BOOL) return true;
    return false;
}

static ExtendedType* promote(const ExtendedType* a, const ExtendedType* b) {
    if (a == T_ERROR || b == T_ERROR)   return T_ERROR;
    if (a == T_STRING || b == T_STRING) return T_ERROR;
    if (a == T_FLOAT  || b == T_FLOAT)  return T_FLOAT;
    return T_INT;
}

static bool invalid_main_function(Type t, string func_id) {
    return func_id == "main" && t != Type::VOID;
}

static ExtendedType* current_func_type = T_ERROR;
static bool has_main_func = false;

#line 141 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_DO = 3,                         /* DO  */
  YYSYMBOL_WHILE = 4,                      /* WHILE  */
  YYSYMBOL_FOR = 5,                        /* FOR  */
  YYSYMBOL_FOREACH = 6,                    /* FOREACH  */
  YYSYMBOL_CONTINUE = 7,                   /* CONTINUE  */
  YYSYMBOL_BREAK = 8,                      /* BREAK  */
  YYSYMBOL_RETURN = 9,                     /* RETURN  */
  YYSYMBOL_CONST = 10,                     /* CONST  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_SWITCH = 13,                    /* SWITCH  */
  YYSYMBOL_CASE = 14,                      /* CASE  */
  YYSYMBOL_DEFAULT = 15,                   /* DEFAULT  */
  YYSYMBOL_PRINT = 16,                     /* PRINT  */
  YYSYMBOL_PRINTLN = 17,                   /* PRINTLN  */
  YYSYMBOL_READ = 18,                      /* READ  */
  YYSYMBOL_TVOID = 19,                     /* TVOID  */
  YYSYMBOL_EXTERN = 20,                    /* EXTERN  */
  YYSYMBOL_FCONST = 21,                    /* FCONST  */
  YYSYMBOL_SCONST = 22,                    /* SCONST  */
  YYSYMBOL_BCONST = 23,                    /* BCONST  */
  YYSYMBOL_TDOUBLE = 24,                   /* TDOUBLE  */
  YYSYMBOL_TCHAR = 25,                     /* TCHAR  */
  YYSYMBOL_EQ = 26,                        /* EQ  */
  YYSYMBOL_NE = 27,                        /* NE  */
  YYSYMBOL_LE = 28,                        /* LE  */
  YYSYMBOL_GE = 29,                        /* GE  */
  YYSYMBOL_AND = 30,                       /* AND  */
  YYSYMBOL_OR = 31,                        /* OR  */
  YYSYMBOL_ID = 32,                        /* ID  */
  YYSYMBOL_TFLOAT = 33,                    /* TFLOAT  */
  YYSYMBOL_TBOOL = 34,                     /* TBOOL  */
  YYSYMBOL_TINT = 35,                      /* TINT  */
  YYSYMBOL_ICONST = 36,                    /* ICONST  */
  YYSYMBOL_TSTRING = 37,                   /* TSTRING  */
  YYSYMBOL_38_ = 38,                       /* '!'  */
  YYSYMBOL_39_ = 39,                       /* '<'  */
  YYSYMBOL_40_ = 40,                       /* '>'  */
  YYSYMBOL_41_ = 41,                       /* '+'  */
  YYSYMBOL_42_ = 42,                       /* '-'  */
  YYSYMBOL_43_ = 43,                       /* '*'  */
  YYSYMBOL_44_ = 44,                       /* '/'  */
  YYSYMBOL_45_ = 45,                       /* '%'  */
  YYSYMBOL_UMINUS = 46,                    /* UMINUS  */
  YYSYMBOL_INC = 47,                       /* INC  */
  YYSYMBOL_DEC = 48,                       /* DEC  */
  YYSYMBOL_49_ = 49,                       /* '='  */
  YYSYMBOL_50_ = 50,                       /* ';'  */
  YYSYMBOL_51_ = 51,                       /* ','  */
  YYSYMBOL_52_ = 52,                       /* '['  */
  YYSYMBOL_53_ = 53,                       /* ']'  */
  YYSYMBOL_54_ = 54,                       /* '('  */
  YYSYMBOL_55_ = 55,                       /* ')'  */
  YYSYMBOL_56_ = 56,                       /* '{'  */
  YYSYMBOL_57_ = 57,                       /* '}'  */
  YYSYMBOL_58_ = 58,                       /* ':'  */
  YYSYMBOL_59_ = 59,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 60,                  /* $accept  */
  YYSYMBOL_program = 61,                   /* program  */
  YYSYMBOL_decl_list = 62,                 /* decl_list  */
  YYSYMBOL_declaration = 63,               /* declaration  */
  YYSYMBOL_const_decl = 64,                /* const_decl  */
  YYSYMBOL_var_decl = 65,                  /* var_decl  */
  YYSYMBOL_init_id_list = 66,              /* init_id_list  */
  YYSYMBOL_init_id = 67,                   /* init_id  */
  YYSYMBOL_array_block = 68,               /* array_block  */
  YYSYMBOL_func_decl = 69,                 /* func_decl  */
  YYSYMBOL_70_1 = 70,                      /* $@1  */
  YYSYMBOL_opt_param_list = 71,            /* opt_param_list  */
  YYSYMBOL_param_list = 72,                /* param_list  */
  YYSYMBOL_param = 73,                     /* param  */
  YYSYMBOL_block = 74,                     /* block  */
  YYSYMBOL_block_item_list = 75,           /* block_item_list  */
  YYSYMBOL_block_item = 76,                /* block_item  */
  YYSYMBOL_block_decl = 77,                /* block_decl  */
  YYSYMBOL_statement = 78,                 /* statement  */
  YYSYMBOL_simple_or_block_stmt = 79,      /* simple_or_block_stmt  */
  YYSYMBOL_simple_stmt = 80,               /* simple_stmt  */
  YYSYMBOL_if_stmt = 81,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 82,                /* while_stmt  */
  YYSYMBOL_for_stmt = 83,                  /* for_stmt  */
  YYSYMBOL_foreach_stmt = 84,              /* foreach_stmt  */
  YYSYMBOL_return_stmt = 85,               /* return_stmt  */
  YYSYMBOL_expr = 86,                      /* expr  */
  YYSYMBOL_integer_expr = 87,              /* integer_expr  */
  YYSYMBOL_boolean_expr = 88,              /* boolean_expr  */
  YYSYMBOL_const_expr = 89,                /* const_expr  */
  YYSYMBOL_expr_array_block = 90,          /* expr_array_block  */
  YYSYMBOL_data_type = 91,                 /* data_type  */
  YYSYMBOL_identifier = 92,                /* identifier  */
  YYSYMBOL_arg_list_opt = 93,              /* arg_list_opt  */
  YYSYMBOL_arg_list = 94                   /* arg_list  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   323

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  218

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


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
       2,     2,     2,    38,     2,     2,     2,    45,     2,     2,
      54,    55,    43,    41,    51,    42,    59,    44,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,    50,
      39,    49,    40,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    53,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    56,     2,    57,     2,     2,     2,     2,
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
      35,    36,    37,    46,    47,    48
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   114,   114,   118,   119,   123,   124,   125,   130,   141,
     155,   156,   160,   162,   167,   168,   181,   181,   201,   202,
     206,   207,   211,   221,   225,   226,   230,   231,   235,   236,
     241,   242,   243,   244,   245,   246,   247,   251,   252,   256,
     267,   278,   289,   290,   291,   296,   300,   302,   307,   312,
     317,   330,   339,   347,   355,   365,   371,   377,   383,   389,
     394,   395,   396,   405,   414,   421,   433,   434,   435,   439,
     440,   441,   442,   443,   444,   445,   446,   451,   459,   467,
     475,   482,   490,   498,   503,   508,   518,   524,   530,   536,
     542,   547,   548,   549,   550,   551,   552,   556,   557,   567,
     568,   569,   570,   571,   575,   579,   580,   585,   587
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "DO", "WHILE", "FOR",
  "FOREACH", "CONTINUE", "BREAK", "RETURN", "CONST", "IF", "ELSE",
  "SWITCH", "CASE", "DEFAULT", "PRINT", "PRINTLN", "READ", "TVOID",
  "EXTERN", "FCONST", "SCONST", "BCONST", "TDOUBLE", "TCHAR", "EQ", "NE",
  "LE", "GE", "AND", "OR", "ID", "TFLOAT", "TBOOL", "TINT", "ICONST",
  "TSTRING", "'!'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "UMINUS", "INC", "DEC", "'='", "';'", "','", "'['", "']'", "'('", "')'",
  "'{'", "'}'", "':'", "'.'", "$accept", "program", "decl_list",
  "declaration", "const_decl", "var_decl", "init_id_list", "init_id",
  "array_block", "func_decl", "$@1", "opt_param_list", "param_list",
  "param", "block", "block_item_list", "block_item", "block_decl",
  "statement", "simple_or_block_stmt", "simple_stmt", "if_stmt",
  "while_stmt", "for_stmt", "foreach_stmt", "return_stmt", "expr",
  "integer_expr", "boolean_expr", "const_expr", "expr_array_block",
  "data_type", "identifier", "arg_list_opt", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-67)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-17)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -67,    28,   138,   -67,   158,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,    -9,    -9,   -67,   -21,   -13,   127,
       0,   -67,    -9,   -18,    14,   -67,    26,   -18,   -67,   -32,
     -67,   -67,   -67,   -67,   -18,   -18,   273,    24,   158,   263,
     -67,    45,   -18,   -18,   -18,   -18,   -18,    29,    44,    46,
     -67,    -9,   -67,   -67,    65,    65,   -67,   -67,   -67,   -67,
      58,   158,    29,   -67,   -67,   -67,   -67,   107,    61,    68,
      74,   111,    81,   111,   111,    -9,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,    95,   -67,   -67,   -67,   -67,   -67,    -9,
      72,   111,    75,    -9,   -67,   111,   111,    -9,    -9,   111,
     181,   278,   -67,   273,    42,   111,   206,   206,   -67,   -67,
     -67,   -67,   111,   206,    91,   100,    93,   233,   -67,   -67,
     -67,   -67,   -67,   174,   245,    45,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   -67,
       4,     4,     4,     4,     4,     4,   111,   -67,    97,   206,
      -2,   111,    15,   -67,   -67,   240,   240,   240,   240,   233,
     213,   240,   240,   139,   139,   -67,   -67,   -67,   -67,     4,
       4,   220,   220,   -67,   -67,   -67,   250,   206,    99,   104,
      -2,   -67,   -67,   110,   112,   115,   119,   -67,   245,   134,
     -67,   111,   177,   -67,    75,   135,   147,   -67,   206,    -2,
     172,    20,    23,   -67,    -2,   173,   175,   183,   189,   -67,
      -2,    -2,    -2,    -2,   -67,   -67,   -67,   -67
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,     0,   103,   100,   101,    99,   102,
       4,     5,     6,     7,     0,     0,   104,     0,    10,    14,
       0,     9,     0,     0,     0,    12,     0,     0,    11,    14,
      94,    96,    95,    93,     0,     0,    13,     0,    18,     0,
      91,     0,     0,     0,     0,     0,     0,    14,     0,    19,
      20,     0,     8,    92,    86,    87,    88,    89,    90,    15,
       0,     0,    14,    24,    17,    21,    22,    45,     0,     0,
       0,     0,     0,     0,     0,     0,    23,    28,    29,    36,
      25,    26,    27,     0,    31,    32,    33,    34,    35,     0,
       0,     0,    45,     0,    76,     0,     0,     0,     0,     0,
       0,    68,    67,    66,    97,     0,    42,    43,    44,    30,
      40,    41,     0,     0,    67,     0,     0,    83,    60,    68,
      66,    62,    63,     0,    68,    66,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    54,
       0,     0,     0,     0,     0,     0,   105,    64,    67,    39,
      45,     0,     0,    61,    75,    77,    78,    81,    82,    84,
      85,    80,    79,    55,    56,    57,    58,    59,    76,     0,
       0,    69,    70,    71,    72,    73,     0,   107,     0,   106,
      45,    38,    48,     0,    67,     0,     0,    74,     0,    97,
      65,     0,    46,    37,    45,     0,     0,    98,   108,    45,
       0,     0,     0,    47,    45,     0,     0,     0,     0,    49,
      45,    45,    45,    45,    53,    52,    51,    50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   -67,   -67,   203,   204,   274,   -67,   -41,   -67,
     -67,   -67,   -67,   236,   -48,   -67,   -67,   -67,   -67,   -43,
     -65,   -67,   -67,   -67,   -67,   -67,   -64,   -39,   -66,    -1,
     109,     9,   -14,   -67,   -67
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    10,    11,    12,    17,    18,    25,    13,
      26,    48,    49,    50,   181,    67,    80,    81,    82,   182,
     183,    84,    85,    86,    87,    88,   113,   101,   102,   103,
     147,    51,   104,   178,   179
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      19,    20,    83,    30,    31,    32,    59,   100,    29,   106,
     107,    14,    64,    15,    73,    74,    75,    23,    33,    79,
      24,    66,    36,    16,    34,   114,    39,   115,     3,    21,
      16,   117,   118,    40,    41,   123,    35,    62,    22,   148,
     168,    54,    55,    56,    57,    58,   169,    16,   149,    27,
      37,   185,    16,    90,    63,    16,   205,   119,   170,   207,
     124,   108,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,    29,    89,    47,    90,   116,
      38,    24,   177,   121,   122,   184,    42,    43,    44,    45,
      46,    73,    74,    75,   145,   120,   146,    61,   125,    60,
      53,   171,   172,   173,   174,   175,   176,    16,    44,    45,
      46,    68,    69,    70,    63,    91,    71,     4,    72,   110,
     111,   112,    92,    73,    74,    75,     5,   198,    93,   200,
     187,   188,    30,    31,    32,   105,    90,   192,   186,    16,
       6,     7,     8,    16,     9,   109,   150,    94,     4,    95,
     151,   152,   180,    96,   190,   191,   203,     5,    97,    98,
     193,   209,   194,    63,    76,    99,    90,   214,   215,   216,
     217,     6,     7,     8,   195,     9,    23,     5,   196,    24,
      90,   -16,   136,   137,   138,    90,   145,   206,   208,   199,
      90,     6,     7,     8,   201,     9,    90,    90,    90,    90,
     126,   127,   128,   129,   130,   131,   202,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     132,   133,   134,   135,   136,   137,   138,   204,   210,   153,
     211,   139,   126,   127,   128,   129,   130,   131,   212,   126,
     127,   128,   129,   130,   213,   132,   133,   134,   135,   136,
     137,   138,   132,   133,   134,   135,   136,   137,   138,   126,
     127,   128,   129,   142,   143,   144,   -17,   -17,   -17,   -17,
      77,    78,   132,   133,   134,   135,   136,   137,   138,   -17,
     -17,   134,   135,   136,   137,   138,   140,   141,   142,   143,
     144,   140,   141,   142,   143,   144,    28,    65,   197,     0,
     154,     0,     0,   189,    42,    43,    44,    45,    46,     0,
       0,     0,     0,    52,    42,    43,    44,    45,    46,   140,
     141,   142,   143,   144
};

static const yytype_int16 yycheck[] =
{
      14,    15,    67,    21,    22,    23,    47,    71,    22,    73,
      74,     2,    60,     4,    16,    17,    18,    49,    36,    67,
      52,    62,    23,    32,    42,    91,    27,    92,     0,    50,
      32,    95,    96,    34,    35,    99,    54,    51,    51,   105,
      36,    42,    43,    44,    45,    46,    42,    32,   112,    49,
      36,    36,    32,    67,    56,    32,    36,    96,    54,    36,
      99,    75,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,    89,    67,    53,    92,    93,
      54,    52,   146,    97,    98,   151,    41,    42,    43,    44,
      45,    16,    17,    18,    52,    96,    54,    51,    99,    55,
      55,   140,   141,   142,   143,   144,   145,    32,    43,    44,
      45,     4,     5,     6,    56,    54,     9,    10,    11,    47,
      48,    49,    54,    16,    17,    18,    19,   191,    54,   194,
     169,   170,    21,    22,    23,    54,   150,   180,   152,    32,
      33,    34,    35,    32,    37,    50,    55,    36,    10,    38,
      50,    58,    55,    42,    55,    51,   199,    19,    47,    48,
      50,   204,    50,    56,    57,    54,   180,   210,   211,   212,
     213,    33,    34,    35,    59,    37,    49,    19,    59,    52,
     194,    54,    43,    44,    45,   199,    52,   201,   202,    12,
     204,    33,    34,    35,    59,    37,   210,   211,   212,   213,
      26,    27,    28,    29,    30,    31,    59,    26,    27,    28,
      29,    30,    31,    39,    40,    41,    42,    43,    44,    45,
      39,    40,    41,    42,    43,    44,    45,    55,    55,    55,
      55,    50,    26,    27,    28,    29,    30,    31,    55,    26,
      27,    28,    29,    30,    55,    39,    40,    41,    42,    43,
      44,    45,    39,    40,    41,    42,    43,    44,    45,    26,
      27,    28,    29,    43,    44,    45,    26,    27,    28,    29,
      67,    67,    39,    40,    41,    42,    43,    44,    45,    39,
      40,    41,    42,    43,    44,    45,    41,    42,    43,    44,
      45,    41,    42,    43,    44,    45,    22,    61,   189,    -1,
      55,    -1,    -1,    53,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,    50,    41,    42,    43,    44,    45,    41,
      42,    43,    44,    45
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    61,    62,     0,    10,    19,    33,    34,    35,    37,
      63,    64,    65,    69,    91,    91,    32,    66,    67,    92,
      92,    50,    51,    49,    52,    68,    70,    49,    66,    92,
      21,    22,    23,    36,    42,    54,    89,    36,    54,    89,
      89,    89,    41,    42,    43,    44,    45,    53,    71,    72,
      73,    91,    50,    55,    89,    89,    89,    89,    89,    68,
      55,    51,    92,    56,    74,    73,    68,    75,     4,     5,
       6,     9,    11,    16,    17,    18,    57,    64,    65,    74,
      76,    77,    78,    80,    81,    82,    83,    84,    85,    91,
      92,    54,    54,    54,    36,    38,    42,    47,    48,    54,
      86,    87,    88,    89,    92,    54,    86,    86,    92,    50,
      47,    48,    49,    86,    88,    80,    92,    86,    86,    87,
      89,    92,    92,    86,    87,    89,    26,    27,    28,    29,
      30,    31,    39,    40,    41,    42,    43,    44,    45,    50,
      41,    42,    43,    44,    45,    52,    54,    90,    88,    86,
      55,    50,    58,    55,    55,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    36,    42,
      54,    87,    87,    87,    87,    87,    87,    86,    93,    94,
      55,    74,    79,    80,    88,    36,    92,    87,    87,    53,
      55,    51,    79,    50,    50,    59,    59,    90,    86,    12,
      80,    59,    59,    79,    55,    36,    92,    36,    92,    79,
      55,    55,    55,    55,    79,    79,    79,    79
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    60,    61,    62,    62,    63,    63,    63,    64,    65,
      66,    66,    67,    67,    68,    68,    70,    69,    71,    71,
      72,    72,    73,    74,    75,    75,    76,    76,    77,    77,
      78,    78,    78,    78,    78,    78,    78,    79,    79,    80,
      80,    80,    80,    80,    80,    80,    81,    81,    82,    83,
      84,    84,    84,    84,    85,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    87,
      87,    87,    87,    87,    87,    87,    87,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    90,    90,    91,
      91,    91,    91,    91,    92,    93,    93,    94,    94
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     6,     3,
       1,     3,     2,     3,     0,     4,     0,     7,     0,     1,
       1,     3,     3,     3,     0,     2,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     2,     1,     3,
       2,     2,     2,     2,     2,     0,     5,     7,     5,     9,
      10,    10,    10,    10,     3,     3,     3,     3,     3,     3,
       2,     3,     2,     2,     2,     4,     1,     1,     1,     3,
       3,     3,     3,     3,     2,     3,     1,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     1,     1,     1,     0,     1,     1,     3
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
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
  case 2: /* program: decl_list  */
#line 114 "parser.y"
                              { TRACE("program OK\n"); }
#line 1388 "parser.tab.c"
    break;

  case 8: /* const_decl: CONST data_type identifier '=' const_expr ';'  */
#line 130 "parser.y"
                                                    {
        if (!symtab.insert((yyvsp[-3].sval), Kind::K_CONST, *(yyvsp[-4].tval), {}))
            semantic_error("redeclared const", (yyvsp[-3].sval));
        if ((yyvsp[-4].tval) != (yyvsp[-1].tval))
            semantic_error("const type mismatch", (yyvsp[-3].sval));
    }
#line 1399 "parser.tab.c"
    break;

  case 9: /* var_decl: data_type init_id_list ';'  */
#line 141 "parser.y"
                                 { 
        for (auto& var : decl_vars) {
            string name = var.id;
            ExtendedType* type = var.type;
            if (!symtab.insert(name, Kind::K_VAR, ExtendedType{(yyvsp[-2].tval)->t, type->dims}, {}))
                semantic_error("redeclared var", name);
            if (type->t != Type::ERROR && !type_compatible(type, (yyvsp[-2].tval)))
                semantic_error("type mismatch in init", "");
        }
        decl_vars.clear();
    }
#line 1415 "parser.tab.c"
    break;

  case 12: /* init_id: identifier array_block  */
#line 161 "parser.y"
      { decl_vars.push_back({(yyvsp[-1].sval), (yyvsp[0].tval)}); }
#line 1421 "parser.tab.c"
    break;

  case 13: /* init_id: identifier '=' const_expr  */
#line 163 "parser.y"
      { decl_vars.push_back({(yyvsp[-2].sval), (yyvsp[0].tval)}); }
#line 1427 "parser.tab.c"
    break;

  case 14: /* array_block: %empty  */
#line 167 "parser.y"
                  { (yyval.tval) = T_ERROR; }
#line 1433 "parser.tab.c"
    break;

  case 15: /* array_block: '[' ICONST ']' array_block  */
#line 168 "parser.y"
                                 {
        vector<int> dims;
        dims.push_back((yyvsp[-2].ival));
        for (auto& d : (yyvsp[0].tval)->dims)
            dims.push_back(d);
        ExtendedType* nt = new ExtendedType{Type::ERROR, dims};
        type_pool.push_back(nt);
        (yyval.tval) = nt;
    }
#line 1447 "parser.tab.c"
    break;

  case 16: /* $@1: %empty  */
#line 181 "parser.y"
                           {
        if (!symtab.insert((yyvsp[0].sval), Kind::K_FUNC, *(yyvsp[-1].tval), {})) 
            semantic_error("redeclared func", (yyvsp[0].sval));
        if (string((yyvsp[0].sval)) == "main") 
            has_main_func = true;
        if (invalid_main_function((yyvsp[-1].tval)->t, (yyvsp[0].sval))) 
            semantic_error("invalid main function type:", SymbolTable::type2Str((yyvsp[-1].tval)->t));
        current_func_type = (yyvsp[-1].tval);
        symtab.pushScope();
    }
#line 1462 "parser.tab.c"
    break;

  case 17: /* func_decl: data_type identifier $@1 '(' opt_param_list ')' block  */
#line 190 "parser.y"
                                   {
        symtab.popScope();
        Symbol *sym = symtab.lookup((yyvsp[-5].sval));
        for (auto* p : func_params_type)
            sym->params.push_back(*p);
        func_params_type.clear();
        current_func_type = T_ERROR;
    }
#line 1475 "parser.tab.c"
    break;

  case 22: /* param: data_type identifier array_block  */
#line 211 "parser.y"
                                       { 
        if (!symtab.insert((yyvsp[-1].sval), Kind::K_VAR, ExtendedType{(yyvsp[-2].tval)->t, (yyvsp[0].tval)->dims}, {}))
            semantic_error("redeclared param", (yyvsp[-1].sval));
        func_params_type.push_back(new ExtendedType{ (yyvsp[-2].tval)->t, (yyvsp[0].tval)->dims });
        type_pool.push_back(func_params_type.back());
    }
#line 1486 "parser.tab.c"
    break;

  case 39: /* simple_stmt: identifier '=' expr  */
#line 256 "parser.y"
                          {
        Symbol* sym = symtab.lookup((yyvsp[-2].sval));
        if (!sym) 
            semantic_error("undeclared id",(yyvsp[-2].sval));
        if (!type_compatible(&sym->type, (yyvsp[0].tval))) 
            semantic_error("type mismatch in assignment", (yyvsp[-2].sval));
        if (sym->kind == Kind::K_FUNC)
            semantic_error("try to assign to a function: ", (yyvsp[-2].sval));
        if (sym->kind == Kind::K_CONST)
            semantic_error("try to assign to a constant: ", (yyvsp[-2].sval));
    }
#line 1502 "parser.tab.c"
    break;

  case 40: /* simple_stmt: identifier INC  */
#line 267 "parser.y"
                     {
        Symbol* sym = symtab.lookup((yyvsp[-1].sval));
        if (!sym) 
            semantic_error("undeclared id",(yyvsp[-1].sval));
        if (sym->type != *T_INT && sym->type != *T_FLOAT) 
            semantic_error("invalid operation on", (yyvsp[-1].sval));
        if (sym->kind == Kind::K_FUNC)
            semantic_error("try to increase a function:", (yyvsp[-1].sval));
        if (sym->kind == Kind::K_CONST)
            semantic_error("try to increase a constant:", (yyvsp[-1].sval));
    }
#line 1518 "parser.tab.c"
    break;

  case 41: /* simple_stmt: identifier DEC  */
#line 278 "parser.y"
                     {
        Symbol* sym = symtab.lookup((yyvsp[-1].sval));
        if (!sym) 
            semantic_error("undeclared id",(yyvsp[-1].sval));
        if (sym->type != *T_INT && sym->type != *T_FLOAT)
            semantic_error("invalid operation on", (yyvsp[-1].sval));                                                                                                                                                                                      
        if (sym->kind == Kind::K_FUNC)
            semantic_error("try to decrease a function: ", (yyvsp[-1].sval));
        if (sym->kind == Kind::K_CONST)
            semantic_error("try to decrease a constant: ", (yyvsp[-1].sval));
    }
#line 1534 "parser.tab.c"
    break;

  case 44: /* simple_stmt: READ identifier  */
#line 291 "parser.y"
                         {
        Symbol* sym = symtab.lookup((yyvsp[0].sval));
        if (!sym) 
            semantic_error("undeclared id", (yyvsp[0].sval));
    }
#line 1544 "parser.tab.c"
    break;

  case 46: /* if_stmt: IF '(' boolean_expr ')' simple_or_block_stmt  */
#line 301 "parser.y"
      { if ((yyvsp[-2].tval) != T_BOOL) semantic_error("if cond not bool",""); }
#line 1550 "parser.tab.c"
    break;

  case 47: /* if_stmt: IF '(' boolean_expr ')' simple_or_block_stmt ELSE simple_or_block_stmt  */
#line 303 "parser.y"
      { if ((yyvsp[-4].tval) != T_BOOL) semantic_error("if cond not bool",""); }
#line 1556 "parser.tab.c"
    break;

  case 48: /* while_stmt: WHILE '(' boolean_expr ')' simple_or_block_stmt  */
#line 308 "parser.y"
      { if ((yyvsp[-2].tval) != T_BOOL) semantic_error("if cond not bool",""); }
#line 1562 "parser.tab.c"
    break;

  case 49: /* for_stmt: FOR '(' simple_stmt ';' boolean_expr ';' simple_stmt ')' simple_or_block_stmt  */
#line 313 "parser.y"
      { if ((yyvsp[-4].tval) != T_BOOL) semantic_error("if cond not bool",""); }
#line 1568 "parser.tab.c"
    break;

  case 50: /* foreach_stmt: FOREACH '(' identifier ':' identifier '.' '.' identifier ')' simple_or_block_stmt  */
#line 317 "parser.y"
                                                                                       {
        Symbol* sym = symtab.lookup((yyvsp[-7].sval));
        if (!sym) semantic_error("undeclared id", (yyvsp[-7].sval));
        if (sym->type != *T_INT) semantic_error("foreach loop variable must be of type int:", (yyvsp[-7].sval));

        Symbol* sym2 = symtab.lookup((yyvsp[-5].sval));
        if (!sym2) semantic_error("undeclared id", (yyvsp[-5].sval));
        if (sym2->type != *T_INT) semantic_error("foreach loop range must be of type int:", (yyvsp[-5].sval));
        Symbol* sym3 = symtab.lookup((yyvsp[-2].sval));
        if (!sym3) semantic_error("undeclared id", (yyvsp[-2].sval));
        if (sym3->type != *T_INT) semantic_error("foreach loop range must be of type int:", (yyvsp[-2].sval));

    }
#line 1586 "parser.tab.c"
    break;

  case 51: /* foreach_stmt: FOREACH '(' identifier ':' identifier '.' '.' ICONST ')' simple_or_block_stmt  */
#line 330 "parser.y"
                                                                                   {
        Symbol* sym = symtab.lookup((yyvsp[-7].sval));
        if (!sym) semantic_error("undeclared id", (yyvsp[-7].sval));
        if (sym->type != *T_INT) semantic_error("foreach loop variable must be of type int:", (yyvsp[-7].sval));

        Symbol* sym2 = symtab.lookup((yyvsp[-5].sval));
        if (!sym2) semantic_error("undeclared id", (yyvsp[-5].sval));
        if (sym2->type != *T_INT) semantic_error("foreach loop range must be of type int:", (yyvsp[-5].sval));
    }
#line 1600 "parser.tab.c"
    break;

  case 52: /* foreach_stmt: FOREACH '(' identifier ':' ICONST '.' '.' identifier ')' simple_or_block_stmt  */
#line 339 "parser.y"
                                                                                   {
        Symbol* sym = symtab.lookup((yyvsp[-7].sval));
        if (!sym) semantic_error("undeclared id", (yyvsp[-7].sval));
        if (sym->type != *T_INT) semantic_error("foreach loop variable must be of type int:", (yyvsp[-7].sval));
        Symbol* sym3 = symtab.lookup((yyvsp[-2].sval));
        if (!sym3) semantic_error("undeclared id", (yyvsp[-2].sval));
        if (sym3->type != *T_INT) semantic_error("foreach loop range must be of type int:", (yyvsp[-2].sval));
    }
#line 1613 "parser.tab.c"
    break;

  case 53: /* foreach_stmt: FOREACH '(' identifier ':' ICONST '.' '.' ICONST ')' simple_or_block_stmt  */
#line 347 "parser.y"
                                                                               {
        Symbol* sym = symtab.lookup((yyvsp[-7].sval));
        if (!sym) semantic_error("undeclared id", (yyvsp[-7].sval));
        if (sym->type != *T_INT) semantic_error("foreach loop variable must be of type int:", (yyvsp[-7].sval));
    }
#line 1623 "parser.tab.c"
    break;

  case 54: /* return_stmt: RETURN expr ';'  */
#line 355 "parser.y"
                      {
        if (current_func_type == T_VOID)
            semantic_error("void function should not return value", "");
        else if (!type_compatible(current_func_type, (yyvsp[-1].tval)))
            semantic_error("return type mismatch", "");
      }
#line 1634 "parser.tab.c"
    break;

  case 55: /* expr: expr '+' expr  */
#line 365 "parser.y"
                    { 
        ExtendedType* t = promote((yyvsp[-2].tval), (yyvsp[0].tval));
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        (yyval.tval) = t;
    }
#line 1645 "parser.tab.c"
    break;

  case 56: /* expr: expr '-' expr  */
#line 371 "parser.y"
                    { 
        ExtendedType* t = promote((yyvsp[-2].tval), (yyvsp[0].tval));
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        (yyval.tval) = t; 
    }
#line 1656 "parser.tab.c"
    break;

  case 57: /* expr: expr '*' expr  */
#line 377 "parser.y"
                    {
        ExtendedType* t = promote((yyvsp[-2].tval), (yyvsp[0].tval));
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        (yyval.tval) = t; 
    }
#line 1667 "parser.tab.c"
    break;

  case 58: /* expr: expr '/' expr  */
#line 383 "parser.y"
                    {
        ExtendedType* t = promote((yyvsp[-2].tval), (yyvsp[0].tval));
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        (yyval.tval) = t; 
    }
#line 1678 "parser.tab.c"
    break;

  case 59: /* expr: expr '%' expr  */
#line 389 "parser.y"
                    {
        if ((yyvsp[-2].tval) != T_INT || (yyvsp[0].tval) != T_INT)
            semantic_error("modulo operator requires integer operands", "");
        (yyval.tval) = T_INT; 
    }
#line 1688 "parser.tab.c"
    break;

  case 60: /* expr: '-' expr  */
#line 394 "parser.y"
                             { (yyval.tval) = (yyvsp[0].tval); }
#line 1694 "parser.tab.c"
    break;

  case 61: /* expr: '(' expr ')'  */
#line 395 "parser.y"
                             { (yyval.tval) = (yyvsp[-1].tval); }
#line 1700 "parser.tab.c"
    break;

  case 62: /* expr: INC identifier  */
#line 396 "parser.y"
                     {
        Symbol* sym = symtab.lookup((yyvsp[0].sval));
        if (!sym)
            semantic_error("undeclared id", (yyvsp[0].sval));
        if (sym->kind == Kind::K_FUNC) 
            semantic_error("try to change the value of a function:", (yyvsp[0].sval));
        if (sym->kind == Kind::K_CONST)
            semantic_error("try to change the value of a constant:", (yyvsp[0].sval));
    }
#line 1714 "parser.tab.c"
    break;

  case 63: /* expr: DEC identifier  */
#line 405 "parser.y"
                     {
        Symbol* sym = symtab.lookup((yyvsp[0].sval));
        if (!sym)
            semantic_error("undeclared id", (yyvsp[0].sval));
        if (sym->kind == Kind::K_FUNC) 
            semantic_error("try to change the value of a function:", (yyvsp[0].sval));
        if (sym->kind == Kind::K_CONST)
            semantic_error("try to change the value of a constant:", (yyvsp[0].sval));
    }
#line 1728 "parser.tab.c"
    break;

  case 64: /* expr: identifier expr_array_block  */
#line 414 "parser.y"
                                  {
        Symbol* sym = symtab.lookup((yyvsp[-1].sval));
        if (!sym) semantic_error("undeclared var",(yyvsp[-1].sval));
        if (sym->type.dims.size() != (yyvsp[0].tval)->dims.size())
            semantic_error("array dimension mismatch", (yyvsp[-1].sval));
        (yyval.tval) = sym ? &sym->type : (ExtendedType*)T_ERROR;
    }
#line 1740 "parser.tab.c"
    break;

  case 65: /* expr: identifier '(' arg_list_opt ')'  */
#line 421 "parser.y"
                                      {
        Symbol* sym = symtab.lookup((yyvsp[-3].sval));
        if (!sym || sym->kind != Kind::K_FUNC)
            semantic_error("call of non-function", (yyvsp[-3].sval));
        if (sym->params.size() != func_params_type.size())  
            semantic_error("function parameter count mismatch in call to function: ", (yyvsp[-3].sval));
        for (int i = 0; i < (int) sym->params.size(); ++i)
            if (sym->params[i] != *func_params_type[i]) 
                semantic_error("function parameter type mismatch in call to function: ", (yyvsp[-3].sval));
        func_params_type.clear();
        (yyval.tval) = sym ? &sym->type : (ExtendedType*)T_ERROR;
    }
#line 1757 "parser.tab.c"
    break;

  case 69: /* integer_expr: integer_expr '+' integer_expr  */
#line 439 "parser.y"
                                     { (yyval.tval) = T_INT; }
#line 1763 "parser.tab.c"
    break;

  case 70: /* integer_expr: integer_expr '-' integer_expr  */
#line 440 "parser.y"
                                     { (yyval.tval) = T_INT; }
#line 1769 "parser.tab.c"
    break;

  case 71: /* integer_expr: integer_expr '*' integer_expr  */
#line 441 "parser.y"
                                     { (yyval.tval) = T_INT; }
#line 1775 "parser.tab.c"
    break;

  case 72: /* integer_expr: integer_expr '/' integer_expr  */
#line 442 "parser.y"
                                     { (yyval.tval) = T_INT; }
#line 1781 "parser.tab.c"
    break;

  case 73: /* integer_expr: integer_expr '%' integer_expr  */
#line 443 "parser.y"
                                     { (yyval.tval) = T_INT; }
#line 1787 "parser.tab.c"
    break;

  case 74: /* integer_expr: '-' integer_expr  */
#line 444 "parser.y"
                                     { (yyval.tval) = T_INT; }
#line 1793 "parser.tab.c"
    break;

  case 75: /* integer_expr: '(' integer_expr ')'  */
#line 445 "parser.y"
                                     { (yyval.tval) = T_INT; }
#line 1799 "parser.tab.c"
    break;

  case 76: /* integer_expr: ICONST  */
#line 446 "parser.y"
             { (yyval.tval) = T_INT; }
#line 1805 "parser.tab.c"
    break;

  case 77: /* boolean_expr: expr EQ expr  */
#line 451 "parser.y"
                   {
        bool same   = ((yyvsp[-2].tval) == (yyvsp[0].tval));                                     
        bool numMix = (((yyvsp[-2].tval) == T_INT || (yyvsp[-2].tval) == T_FLOAT || (yyvsp[-2].tval) == T_BOOL) 
                    && ((yyvsp[0].tval) == T_INT || (yyvsp[0].tval) == T_FLOAT || (yyvsp[0].tval) == T_BOOL));
        if (!(same || numMix))
            semantic_error("comparison type mismatch", "");
        (yyval.tval) = T_BOOL;
    }
#line 1818 "parser.tab.c"
    break;

  case 78: /* boolean_expr: expr NE expr  */
#line 459 "parser.y"
                   {
        bool same   = ((yyvsp[-2].tval) == (yyvsp[0].tval));                                     
        bool numMix = (((yyvsp[-2].tval) == T_INT || (yyvsp[-2].tval) == T_FLOAT || (yyvsp[-2].tval) == T_BOOL) 
                    && ((yyvsp[0].tval) == T_INT || (yyvsp[0].tval) == T_FLOAT || (yyvsp[0].tval) == T_BOOL));
        if (!(same || numMix))
           semantic_error("comparison type mismatch", "");
        (yyval.tval) = T_BOOL;
    }
#line 1831 "parser.tab.c"
    break;

  case 79: /* boolean_expr: expr '>' expr  */
#line 467 "parser.y"
                    {
        bool ok = ((yyvsp[-2].tval) == (yyvsp[0].tval) && (yyvsp[-2].tval) != T_STRING) ||                 
                 (((yyvsp[-2].tval) == T_INT  || (yyvsp[-2].tval) == T_FLOAT || (yyvsp[-2].tval) == T_BOOL) &&
                  ((yyvsp[0].tval) == T_INT  || (yyvsp[0].tval) == T_FLOAT || (yyvsp[0].tval) == T_BOOL));
        if (!ok)
            semantic_error("comparison type mismatch", "");
        (yyval.tval) = T_BOOL;
    }
#line 1844 "parser.tab.c"
    break;

  case 80: /* boolean_expr: expr '<' expr  */
#line 475 "parser.y"
                    { 
        bool ok = ((yyvsp[-2].tval) == (yyvsp[0].tval) && (yyvsp[-2].tval) != T_STRING) ||                 
                 (((yyvsp[-2].tval) == T_INT  || (yyvsp[-2].tval) == T_FLOAT || (yyvsp[-2].tval) == T_BOOL) &&
                  ((yyvsp[0].tval) == T_INT  || (yyvsp[0].tval) == T_FLOAT || (yyvsp[0].tval) == T_BOOL));
        if (!ok)
            semantic_error("comparison type mismatch", "");
    }
#line 1856 "parser.tab.c"
    break;

  case 81: /* boolean_expr: expr LE expr  */
#line 482 "parser.y"
                   {
        bool ok = ((yyvsp[-2].tval) == (yyvsp[0].tval) && (yyvsp[-2].tval) != T_STRING) ||                 
                 (((yyvsp[-2].tval) == T_INT  || (yyvsp[-2].tval) == T_FLOAT || (yyvsp[-2].tval) == T_BOOL) &&
                 ((yyvsp[0].tval) == T_INT  || (yyvsp[0].tval) == T_FLOAT || (yyvsp[0].tval) == T_BOOL));
        if (!ok)
            semantic_error("comparison type mismatch", "");
        (yyval.tval) = T_BOOL;
    }
#line 1869 "parser.tab.c"
    break;

  case 82: /* boolean_expr: expr GE expr  */
#line 490 "parser.y"
                   {
        bool ok = ((yyvsp[-2].tval) == (yyvsp[0].tval) && (yyvsp[-2].tval) != T_STRING) ||                 
                 (((yyvsp[-2].tval) == T_INT  || (yyvsp[-2].tval) == T_FLOAT || (yyvsp[-2].tval) == T_BOOL) &&
                 ((yyvsp[0].tval) == T_INT  || (yyvsp[0].tval) == T_FLOAT || (yyvsp[0].tval) == T_BOOL));
        if (!ok)
            semantic_error("comparison type mismatch", "");
        (yyval.tval) = T_BOOL;
    }
#line 1882 "parser.tab.c"
    break;

  case 83: /* boolean_expr: '!' expr  */
#line 498 "parser.y"
               {
        if ((yyvsp[0].tval) != T_BOOL)
            semantic_error("logical operand not bool", "");
        (yyval.tval) = T_BOOL;
    }
#line 1892 "parser.tab.c"
    break;

  case 84: /* boolean_expr: expr AND expr  */
#line 503 "parser.y"
                    {
        if ((yyvsp[-2].tval) != T_BOOL || (yyvsp[0].tval) != T_BOOL)
            semantic_error("logical operand not bool", "");
        (yyval.tval) = T_BOOL;
    }
#line 1902 "parser.tab.c"
    break;

  case 85: /* boolean_expr: expr OR expr  */
#line 508 "parser.y"
                   {
        if ((yyvsp[-2].tval) != T_BOOL || (yyvsp[0].tval) != T_BOOL)
            semantic_error("logical operand not bool", "");
        (yyval.tval) = T_BOOL;
    }
#line 1912 "parser.tab.c"
    break;

  case 86: /* const_expr: const_expr '+' const_expr  */
#line 518 "parser.y"
                                { 
        ExtendedType* t = promote((yyvsp[-2].tval), (yyvsp[0].tval));
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        (yyval.tval) = t;
    }
#line 1923 "parser.tab.c"
    break;

  case 87: /* const_expr: const_expr '-' const_expr  */
#line 524 "parser.y"
                                { 
        ExtendedType* t = promote((yyvsp[-2].tval), (yyvsp[0].tval));
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        (yyval.tval) = t; 
    }
#line 1934 "parser.tab.c"
    break;

  case 88: /* const_expr: const_expr '*' const_expr  */
#line 530 "parser.y"
                                {
        ExtendedType* t = promote((yyvsp[-2].tval), (yyvsp[0].tval));
        if (t == T_ERROR) 
            semantic_error("invalid operation", "");
        (yyval.tval) = t; 
    }
#line 1945 "parser.tab.c"
    break;

  case 89: /* const_expr: const_expr '/' const_expr  */
#line 536 "parser.y"
                                {
          ExtendedType* t = promote((yyvsp[-2].tval), (yyvsp[0].tval));
          if (t == T_ERROR) 
              semantic_error("invalid operation", "");
          (yyval.tval) = t; 
    }
#line 1956 "parser.tab.c"
    break;

  case 90: /* const_expr: const_expr '%' const_expr  */
#line 542 "parser.y"
                                {
        if ((yyvsp[-2].tval) != T_INT || (yyvsp[0].tval) != T_INT)
            semantic_error("modulo operator requires integer operands", "");
        (yyval.tval) = T_INT; 
    }
#line 1966 "parser.tab.c"
    break;

  case 91: /* const_expr: '-' const_expr  */
#line 547 "parser.y"
                                   { (yyval.tval) = (yyvsp[0].tval); }
#line 1972 "parser.tab.c"
    break;

  case 92: /* const_expr: '(' const_expr ')'  */
#line 548 "parser.y"
                                   { (yyval.tval) = (yyvsp[-1].tval); }
#line 1978 "parser.tab.c"
    break;

  case 93: /* const_expr: ICONST  */
#line 549 "parser.y"
             { (yyval.tval) = T_INT; }
#line 1984 "parser.tab.c"
    break;

  case 94: /* const_expr: FCONST  */
#line 550 "parser.y"
             { (yyval.tval) = T_FLOAT; }
#line 1990 "parser.tab.c"
    break;

  case 95: /* const_expr: BCONST  */
#line 551 "parser.y"
             { (yyval.tval) = T_BOOL; }
#line 1996 "parser.tab.c"
    break;

  case 96: /* const_expr: SCONST  */
#line 552 "parser.y"
             { (yyval.tval) = T_STRING; }
#line 2002 "parser.tab.c"
    break;

  case 97: /* expr_array_block: %empty  */
#line 556 "parser.y"
                  { (yyval.tval) = T_ERROR; }
#line 2008 "parser.tab.c"
    break;

  case 98: /* expr_array_block: '[' integer_expr ']' expr_array_block  */
#line 557 "parser.y"
                                            {
        vector<int> dims = std::move((yyvsp[0].tval)->dims);
        dims.push_back(1);
        ExtendedType* nt = new ExtendedType{Type::ERROR, dims};
        type_pool.push_back(nt);
        (yyval.tval) = nt;
    }
#line 2020 "parser.tab.c"
    break;

  case 99: /* data_type: TINT  */
#line 567 "parser.y"
              { (yyval.tval) = T_INT; }
#line 2026 "parser.tab.c"
    break;

  case 100: /* data_type: TFLOAT  */
#line 568 "parser.y"
              { (yyval.tval) = T_FLOAT; }
#line 2032 "parser.tab.c"
    break;

  case 101: /* data_type: TBOOL  */
#line 569 "parser.y"
              { (yyval.tval) = T_BOOL; }
#line 2038 "parser.tab.c"
    break;

  case 102: /* data_type: TSTRING  */
#line 570 "parser.y"
              { (yyval.tval) = T_STRING; }
#line 2044 "parser.tab.c"
    break;

  case 103: /* data_type: TVOID  */
#line 571 "parser.y"
              { (yyval.tval) = T_VOID; }
#line 2050 "parser.tab.c"
    break;

  case 104: /* identifier: ID  */
#line 575 "parser.y"
         { (yyval.sval) = strdup((yyvsp[0].sval)); }
#line 2056 "parser.tab.c"
    break;

  case 107: /* arg_list: expr  */
#line 586 "parser.y"
      { func_params_type.push_back((yyvsp[0].tval)); }
#line 2062 "parser.tab.c"
    break;

  case 108: /* arg_list: arg_list ',' expr  */
#line 588 "parser.y"
      { func_params_type.push_back((yyvsp[0].tval)); }
#line 2068 "parser.tab.c"
    break;


#line 2072 "parser.tab.c"

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
      yyerror (YY_("syntax error"));
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 591 "parser.y"
           

void yyerror(const string& msg) {
    cerr << "SYNTAX(" << linenum << "): " << msg << '\n';
    for (auto& ptr : type_pool) delete ptr;
    exit(-1);
}

int main(int argc,char* argv[]){
    if (argc!=2) { 
        fprintf(stderr,"usage: %s file.sd\n",argv[0]); 
        return 1;
    }
    yyin=fopen(argv[1],"r");
    if (!yyin) { 
        perror(argv[1]); 
        return 1; 
    }

    if (yyparse() == 0) {
        if (!has_main_func) 
            semantic_error("has no main function", "");
        puts("PASS – no errors");
    }
    for (auto& ptr : type_pool) delete ptr;
    return 0;
}
