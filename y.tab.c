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

#define TRACE(t) printf(t)


using namespace std;
extern FILE* yyin;

#define YYSTYPE_IS_DECLARED 1
typedef union {
    int          ival;
    float        fval;
    char*        sval;
    ExtendedType tval;    
} YYSTYPE;

SymbolTable symtab;
extern int linenum;                    
void yyerror(const string& msg);
const static ExtendedType T_STRING = ExtendedType{Type::T_STRING, {}};
const static ExtendedType T_BOOL   = ExtendedType{Type::T_BOOL, {}};
const static ExtendedType T_INT    = ExtendedType{Type::T_INT, {}};
const static ExtendedType T_FLOAT  = ExtendedType{Type::T_FLOAT, {}};
const static ExtendedType T_VOID   = ExtendedType{Type::T_VOID, {}};
const static ExtendedType T_ERROR  = ExtendedType{Type::T_ERROR, {}};

static void semantic_error(const string& msg, const string& id){
    cerr << "SEMANTIC(" << linenum << "): " << msg << ' ' << id << '\n';
    exit(-1);
}

static bool type_compatible(ExtendedType dst, ExtendedType src) {
    if (dst == src)                                  return true;
    if (dst == T_STRING || src == T_STRING)  return false;
    if (dst == T_FLOAT && src == T_INT)      return true;
    if (dst == T_INT && src == T_FLOAT)      return true;
    if ((dst == T_INT || dst == T_FLOAT) && src == T_BOOL) return true;
    return false;
}

static ExtendedType promote(ExtendedType ta, ExtendedType tb) {
    if (ta == T_ERROR || tb == T_ERROR)   return T_ERROR;
    if (ta == T_STRING || tb == T_STRING) return T_ERROR;
    if (ta == T_FLOAT || tb == T_FLOAT)   return T_FLOAT;
    return T_INT;
}

static bool invalid_main_function(Type t, string func_id) {
    return func_id == "main" && t != Type::T_VOID;
}

static ExtendedType current_func_type = T_ERROR;
static bool has_main_func = false;

struct Pending_var {
    string       id;
    ExtendedType type;
};

vector<Pending_var> decl_vars;
vector<ExtendedType> func_params_type;
int yylex(void);

#line 140 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    DO = 258,                      /* DO  */
    WHILE = 259,                   /* WHILE  */
    FOR = 260,                     /* FOR  */
    FOREACH = 261,                 /* FOREACH  */
    CONTINUE = 262,                /* CONTINUE  */
    BREAK = 263,                   /* BREAK  */
    RETURN = 264,                  /* RETURN  */
    CONST = 265,                   /* CONST  */
    IF = 266,                      /* IF  */
    ELSE = 267,                    /* ELSE  */
    SWITCH = 268,                  /* SWITCH  */
    CASE = 269,                    /* CASE  */
    DEFAULT = 270,                 /* DEFAULT  */
    PRINT = 271,                   /* PRINT  */
    PRINTLN = 272,                 /* PRINTLN  */
    READ = 273,                    /* READ  */
    TVOID = 274,                   /* TVOID  */
    EXTERN = 275,                  /* EXTERN  */
    FCONST = 276,                  /* FCONST  */
    SCONST = 277,                  /* SCONST  */
    BCONST = 278,                  /* BCONST  */
    TDOUBLE = 279,                 /* TDOUBLE  */
    TCHAR = 280,                   /* TCHAR  */
    EQ = 281,                      /* EQ  */
    NE = 282,                      /* NE  */
    LE = 283,                      /* LE  */
    GE = 284,                      /* GE  */
    AND = 285,                     /* AND  */
    OR = 286,                      /* OR  */
    ID = 287,                      /* ID  */
    TFLOAT = 288,                  /* TFLOAT  */
    TBOOL = 289,                   /* TBOOL  */
    TINT = 290,                    /* TINT  */
    ICONST = 291,                  /* ICONST  */
    TSTRING = 292,                 /* TSTRING  */
    UMINUS = 293,                  /* UMINUS  */
    INC = 294,                     /* INC  */
    DEC = 295                      /* DEC  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define DO 258
#define WHILE 259
#define FOR 260
#define FOREACH 261
#define CONTINUE 262
#define BREAK 263
#define RETURN 264
#define CONST 265
#define IF 266
#define ELSE 267
#define SWITCH 268
#define CASE 269
#define DEFAULT 270
#define PRINT 271
#define PRINTLN 272
#define READ 273
#define TVOID 274
#define EXTERN 275
#define FCONST 276
#define SCONST 277
#define BCONST 278
#define TDOUBLE 279
#define TCHAR 280
#define EQ 281
#define NE 282
#define LE 283
#define GE 284
#define AND 285
#define OR 286
#define ID 287
#define TFLOAT 288
#define TBOOL 289
#define TINT 290
#define ICONST 291
#define TSTRING 292
#define UMINUS 293
#define INC 294
#define DEC 295

/* Value type.  */


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
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
  YYSYMBOL_ident_init_list = 66,           /* ident_init_list  */
  YYSYMBOL_ident_init = 67,                /* ident_init  */
  YYSYMBOL_array_block = 68,               /* array_block  */
  YYSYMBOL_func_def = 69,                  /* func_def  */
  YYSYMBOL_70_1 = 70,                      /* $@1  */
  YYSYMBOL_param_list_opt = 71,            /* param_list_opt  */
  YYSYMBOL_param_list = 72,                /* param_list  */
  YYSYMBOL_param = 73,                     /* param  */
  YYSYMBOL_block = 74,                     /* block  */
  YYSYMBOL_block_item_list = 75,           /* block_item_list  */
  YYSYMBOL_block_item = 76,                /* block_item  */
  YYSYMBOL_statement = 77,                 /* statement  */
  YYSYMBOL_simple_or_block_stmt = 78,      /* simple_or_block_stmt  */
  YYSYMBOL_simple_stmt = 79,               /* simple_stmt  */
  YYSYMBOL_if_stmt = 80,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 81,                /* while_stmt  */
  YYSYMBOL_for_stmt = 82,                  /* for_stmt  */
  YYSYMBOL_foreach_stmt = 83,              /* foreach_stmt  */
  YYSYMBOL_return_stmt = 84,               /* return_stmt  */
  YYSYMBOL_expr = 85,                      /* expr  */
  YYSYMBOL_boolean_expr = 86,              /* boolean_expr  */
  YYSYMBOL_const_expr = 87,                /* const_expr  */
  YYSYMBOL_type_spec = 88,                 /* type_spec  */
  YYSYMBOL_identifier = 89,                /* identifier  */
  YYSYMBOL_arg_list_opt = 90,              /* arg_list_opt  */
  YYSYMBOL_arg_list = 91                   /* arg_list  */
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
#define YYLAST   243

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  172

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
       0,   111,   111,   116,   117,   121,   122,   123,   128,   139,
     153,   154,   158,   161,   167,   170,   180,   180,   198,   198,
     201,   202,   206,   215,   219,   220,   224,   225,   230,   231,
     232,   233,   234,   235,   236,   240,   241,   245,   254,   255,
     256,   257,   258,   259,   263,   265,   270,   275,   280,   293,
     302,   310,   318,   328,   334,   340,   346,   352,   358,   359,
     360,   361,   362,   363,   364,   369,   375,   379,   383,   387,
     391,   395,   399,   403,   406,   409,   415,   416,   417,   418,
     422,   423,   424,   425,   426,   430,   434,   435,   440,   441
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
  "declaration", "const_decl", "var_decl", "ident_init_list", "ident_init",
  "array_block", "func_def", "$@1", "param_list_opt", "param_list",
  "param", "block", "block_item_list", "block_item", "statement",
  "simple_or_block_stmt", "simple_stmt", "if_stmt", "while_stmt",
  "for_stmt", "foreach_stmt", "return_stmt", "expr", "boolean_expr",
  "const_expr", "type_spec", "identifier", "arg_list_opt", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-132)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-17)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -132,     6,    86,  -132,   112,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,   -28,   -28,  -132,   -27,   -12,     3,
      -9,  -132,   -28,     9,    12,  -132,     5,     9,  -132,     4,
    -132,  -132,  -132,  -132,  -132,    24,   112,     8,    26,    28,
      46,  -132,   -28,  -132,  -132,    44,   112,    26,  -132,  -132,
    -132,  -132,    76,    60,    61,    63,    80,    74,    80,    80,
     -28,  -132,  -132,  -132,  -132,  -132,    48,  -132,  -132,  -132,
    -132,  -132,    42,    80,    -3,   -28,  -132,  -132,  -132,  -132,
      80,    80,    80,   135,  -132,    75,    80,   160,   160,  -132,
    -132,  -132,  -132,    80,   160,    81,    87,    72,   187,  -132,
     128,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,  -132,    80,    83,   160,    -6,    80,
     -11,  -132,   194,   194,   194,   194,   187,   167,   194,   194,
      82,    82,  -132,  -132,  -132,   160,    85,    92,    -6,  -132,
    -132,    98,   110,   122,   123,  -132,    80,   172,  -132,    -3,
     133,   139,   160,    -6,   162,    43,    52,  -132,    -6,   163,
     164,   169,   170,  -132,    -6,    -6,    -6,    -6,  -132,  -132,
    -132,  -132
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,     0,    84,    81,    82,    80,    83,
       4,     5,     6,     7,     0,     0,    85,     0,    10,    14,
       0,     9,     0,     0,     0,    12,     0,     0,    11,    14,
      77,    79,    78,    76,    13,     0,    18,     0,    14,     0,
      19,    20,     0,     8,    15,     0,     0,    14,    24,    17,
      21,    22,    43,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    26,    34,    25,    27,     0,    29,    30,    31,
      32,    33,     0,     0,    43,     0,    61,    62,    63,    60,
       0,     0,     0,     0,    66,    64,     0,    40,    41,    42,
      28,    38,    39,     0,     0,    66,     0,     0,    73,    58,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    52,    86,    66,    37,    43,     0,
       0,    59,    67,    68,    71,    72,    74,    75,    70,    69,
      53,    54,    55,    56,    57,    88,     0,    87,    43,    36,
      46,     0,    66,     0,     0,    65,     0,    44,    35,    43,
       0,     0,    89,    43,     0,     0,     0,    45,    43,     0,
       0,     0,     0,    47,    43,    43,    43,    43,    51,    50,
      49,    48
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -132,  -132,  -132,   188,  -132,  -132,   219,  -132,   -29,  -132,
    -132,  -132,  -132,   196,    -1,  -132,  -132,  -132,  -131,   -50,
    -132,  -132,  -132,  -132,  -132,   -39,   -70,   216,     1,   -14,
    -132,  -132
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    10,    11,    12,    17,    18,    25,    13,
      26,    39,    40,    41,   139,    52,    64,    65,   140,   141,
      67,    68,    69,    70,    71,    94,    84,    34,    14,    85,
     136,   137
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      19,    20,    66,    95,    16,    15,     3,   147,    29,    44,
      58,    59,    60,    58,    59,    60,   116,    83,    51,    87,
      88,    16,   157,    21,    96,   143,    16,   163,    47,    16,
      30,    31,    32,   168,   169,   170,   171,    42,    72,    22,
      27,    98,    99,   100,    49,    33,    89,    42,    35,   142,
      48,    63,    23,    23,   117,    24,    24,   -16,    43,    36,
      72,    97,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,    16,   135,    38,    24,   159,
      53,    54,    55,    45,    16,    56,     4,    57,   161,    91,
      92,    93,    58,    59,    60,     5,     4,    46,    90,   154,
      48,    76,    77,    78,    72,     5,   144,   152,    16,     6,
       7,     8,    16,     9,    73,    74,    79,    75,    80,     6,
       7,     8,    81,     9,    72,   111,   112,   113,    86,   115,
     120,     5,    48,    61,    82,    72,   118,   119,   138,    72,
     145,   160,   162,   146,    72,     6,     7,     8,   148,     9,
      72,    72,    72,    72,   101,   102,   103,   104,   105,   106,
     149,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   107,   108,   109,   110,   111,   112,
     113,   150,   151,   121,   153,   114,   101,   102,   103,   104,
     105,   106,   155,   101,   102,   103,   104,   105,   156,   107,
     108,   109,   110,   111,   112,   113,   107,   108,   109,   110,
     111,   112,   113,   101,   102,   103,   104,   158,   164,   165,
     -17,   -17,   -17,   -17,   166,   167,   107,   108,   109,   110,
     111,   112,   113,   -17,   -17,   109,   110,   111,   112,   113,
      62,    28,    50,    37
};

static const yytype_uint8 yycheck[] =
{
      14,    15,    52,    73,    32,     4,     0,   138,    22,    38,
      16,    17,    18,    16,    17,    18,    86,    56,    47,    58,
      59,    32,   153,    50,    74,    36,    32,   158,    42,    32,
      21,    22,    23,   164,   165,   166,   167,    36,    52,    51,
      49,    80,    81,    82,    45,    36,    60,    46,    36,   119,
      56,    52,    49,    49,    93,    52,    52,    54,    50,    54,
      74,    75,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,    32,   115,    53,    52,    36,
       4,     5,     6,    55,    32,     9,    10,    11,    36,    47,
      48,    49,    16,    17,    18,    19,    10,    51,    50,   149,
      56,    21,    22,    23,   118,    19,   120,   146,    32,    33,
      34,    35,    32,    37,    54,    54,    36,    54,    38,    33,
      34,    35,    42,    37,   138,    43,    44,    45,    54,    54,
      58,    19,    56,    57,    54,   149,    55,    50,    55,   153,
      55,   155,   156,    51,   158,    33,    34,    35,    50,    37,
     164,   165,   166,   167,    26,    27,    28,    29,    30,    31,
      50,    26,    27,    28,    29,    30,    31,    39,    40,    41,
      42,    43,    44,    45,    39,    40,    41,    42,    43,    44,
      45,    59,    59,    55,    12,    50,    26,    27,    28,    29,
      30,    31,    59,    26,    27,    28,    29,    30,    59,    39,
      40,    41,    42,    43,    44,    45,    39,    40,    41,    42,
      43,    44,    45,    26,    27,    28,    29,    55,    55,    55,
      26,    27,    28,    29,    55,    55,    39,    40,    41,    42,
      43,    44,    45,    39,    40,    41,    42,    43,    44,    45,
      52,    22,    46,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    61,    62,     0,    10,    19,    33,    34,    35,    37,
      63,    64,    65,    69,    88,    88,    32,    66,    67,    89,
      89,    50,    51,    49,    52,    68,    70,    49,    66,    89,
      21,    22,    23,    36,    87,    36,    54,    87,    53,    71,
      72,    73,    88,    50,    68,    55,    51,    89,    56,    74,
      73,    68,    75,     4,     5,     6,     9,    11,    16,    17,
      18,    57,    63,    74,    76,    77,    79,    80,    81,    82,
      83,    84,    89,    54,    54,    54,    21,    22,    23,    36,
      38,    42,    54,    85,    86,    89,    54,    85,    85,    89,
      50,    47,    48,    49,    85,    86,    79,    89,    85,    85,
      85,    26,    27,    28,    29,    30,    31,    39,    40,    41,
      42,    43,    44,    45,    50,    54,    86,    85,    55,    50,
      58,    55,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    90,    91,    55,    74,
      78,    79,    86,    36,    89,    55,    51,    78,    50,    50,
      59,    59,    85,    12,    79,    59,    59,    78,    55,    36,
      89,    36,    89,    78,    55,    55,    55,    55,    78,    78,
      78,    78
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    60,    61,    62,    62,    63,    63,    63,    64,    65,
      66,    66,    67,    67,    68,    68,    70,    69,    71,    71,
      72,    72,    73,    74,    75,    75,    76,    76,    77,    77,
      77,    77,    77,    77,    77,    78,    78,    79,    79,    79,
      79,    79,    79,    79,    80,    80,    81,    82,    83,    83,
      83,    83,    84,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    87,    87,    87,    87,
      88,    88,    88,    88,    88,    89,    90,    90,    91,    91
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     6,     3,
       1,     3,     2,     3,     0,     4,     0,     7,     0,     1,
       1,     3,     3,     3,     0,     2,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     2,     1,     3,     2,     2,
       2,     2,     2,     0,     5,     7,     5,     9,    10,    10,
      10,    10,     3,     3,     3,     3,     3,     3,     2,     3,
       1,     1,     1,     1,     1,     4,     1,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     1,     1,     3
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
#line 111 "parser.y"
                              { TRACE("program OK\n"); }
#line 1464 "y.tab.c"
    break;

  case 8: /* const_decl: CONST type_spec identifier '=' const_expr ';'  */
#line 128 "parser.y"
                                                    {
        if (!symtab.insert((yyvsp[-3].sval), Kind::K_CONST, (yyvsp[-4].tval), {}))
            semantic_error("redeclared const",(yyvsp[-3].sval));
        if ((yyvsp[-4].tval) != (yyvsp[-1].tval))
            semantic_error("const type mismatch",(yyvsp[-3].sval));
      }
#line 1475 "y.tab.c"
    break;

  case 9: /* var_decl: type_spec ident_init_list ';'  */
#line 139 "parser.y"
                                    { 
        for (auto& var : decl_vars) {
            string name = var.id;
            ExtendedType type = var.type;
            if (!symtab.insert(name, Kind::K_VAR, ExtendedType{(yyvsp[-2].tval).t, type.dims}, {}))
                semantic_error("redeclared var", name);
            if (type.t != Type::T_ERROR && !type_compatible(type, (yyvsp[-2].tval)))
                semantic_error("type mismatch in init", "");
        }
        decl_vars.clear();
      }
#line 1491 "y.tab.c"
    break;

  case 12: /* ident_init: identifier array_block  */
#line 158 "parser.y"
                             {
        decl_vars.push_back({(yyvsp[-1].sval), (yyvsp[0].tval)});
      }
#line 1499 "y.tab.c"
    break;

  case 13: /* ident_init: identifier '=' const_expr  */
#line 161 "parser.y"
                                { 
        decl_vars.push_back({(yyvsp[-2].sval), (yyvsp[0].tval)});
      }
#line 1507 "y.tab.c"
    break;

  case 14: /* array_block: %empty  */
#line 167 "parser.y"
                  {
        (yyval.tval) = ExtendedType{Type::T_ERROR, {}};
    }
#line 1515 "y.tab.c"
    break;

  case 15: /* array_block: '[' ICONST ']' array_block  */
#line 170 "parser.y"
                                 {
        vector<int> dims;
        dims.push_back((yyvsp[-2].ival));
        for (auto& d : (yyvsp[0].tval).dims)
            dims.push_back(d);
        (yyval.tval) = ExtendedType{Type::T_ERROR, dims};
    }
#line 1527 "y.tab.c"
    break;

  case 16: /* $@1: %empty  */
#line 180 "parser.y"
                           {
          if (!symtab.insert((yyvsp[0].sval), Kind::K_FUNC, (yyvsp[-1].tval), {})) 
              semantic_error("redeclared func", (yyvsp[0].sval));
          if (string((yyvsp[0].sval)) == "main") 
              has_main_func = true;
          if (invalid_main_function((yyvsp[-1].tval).t, (yyvsp[0].sval))) 
              semantic_error("invalid main function type:", SymbolTable::type2Str((yyvsp[-1].tval).t));
          current_func_type = (yyvsp[-1].tval);
          symtab.pushScope();
      }
#line 1542 "y.tab.c"
    break;

  case 17: /* func_def: type_spec identifier $@1 '(' param_list_opt ')' block  */
#line 189 "parser.y"
                                     {
          symtab.popScope();
          const Symbol *sym = symtab.lookup((yyvsp[-5].sval));
          sym->params = std::move(func_params_type);
          func_params_type.clear();
          current_func_type = T_ERROR;
      }
#line 1554 "y.tab.c"
    break;

  case 22: /* param: type_spec identifier array_block  */
#line 206 "parser.y"
                                       { 
          if (!symtab.insert((yyvsp[-1].sval), Kind::K_VAR, ExtendedType{(yyvsp[-2].tval).t, (yyvsp[0].tval).dims}, {}))
              semantic_error("redeclared param", (yyvsp[-1].sval));
          func_params_type.emplace_back((yyvsp[-2].tval).t, (yyvsp[0].tval).dims);
      }
#line 1564 "y.tab.c"
    break;

  case 37: /* simple_stmt: identifier '=' expr  */
#line 245 "parser.y"
                          {
        // cout << $1 << "<here>";
        const Symbol* sym = symtab.lookup((yyvsp[-2].sval));
        if (!sym) semantic_error("undeclared id",(yyvsp[-2].sval));
          else if (!type_compatible(sym->type, (yyvsp[0].tval))) {
              // cout << SymbolTable::type2Str(sym->type) << ' ' << SymbolTable::type2Str($3) << '\n';
              semantic_error("type mismatch in assignment", (yyvsp[-2].sval));
          }
      }
#line 1578 "y.tab.c"
    break;

  case 44: /* if_stmt: IF '(' boolean_expr ')' simple_or_block_stmt  */
#line 264 "parser.y"
      { if ((yyvsp[-2].tval) != T_BOOL) semantic_error("if cond not bool",""); }
#line 1584 "y.tab.c"
    break;

  case 45: /* if_stmt: IF '(' boolean_expr ')' simple_or_block_stmt ELSE simple_or_block_stmt  */
#line 266 "parser.y"
      { if ((yyvsp[-4].tval) != T_BOOL) semantic_error("if cond not bool",""); }
#line 1590 "y.tab.c"
    break;

  case 46: /* while_stmt: WHILE '(' boolean_expr ')' simple_or_block_stmt  */
#line 271 "parser.y"
      { if ((yyvsp[-2].tval) != T_BOOL) semantic_error("if cond not bool",""); }
#line 1596 "y.tab.c"
    break;

  case 47: /* for_stmt: FOR '(' simple_stmt ';' boolean_expr ';' simple_stmt ')' simple_or_block_stmt  */
#line 276 "parser.y"
      { if ((yyvsp[-4].tval) != T_BOOL) semantic_error("if cond not bool",""); }
#line 1602 "y.tab.c"
    break;

  case 48: /* foreach_stmt: FOREACH '(' identifier ':' identifier '.' '.' identifier ')' simple_or_block_stmt  */
#line 280 "parser.y"
                                                                                       {
        const Symbol* sym = symtab.lookup((yyvsp[-7].sval));
        if (!sym) semantic_error("undeclared id", (yyvsp[-7].sval));
        if (sym->type != T_INT) semantic_error("foreach loop variable must be of type int:", (yyvsp[-7].sval));

        const Symbol* sym2 = symtab.lookup((yyvsp[-5].sval));
        if (!sym2) semantic_error("undeclared id", (yyvsp[-5].sval));
        if (sym2->type != T_INT) semantic_error("foreach loop range must be of type int:", (yyvsp[-5].sval));
        const Symbol* sym3 = symtab.lookup((yyvsp[-2].sval));
        if (!sym3) semantic_error("undeclared id", (yyvsp[-2].sval));
        if (sym3->type != T_INT) semantic_error("foreach loop range must be of type int:", (yyvsp[-2].sval));

    }
#line 1620 "y.tab.c"
    break;

  case 49: /* foreach_stmt: FOREACH '(' identifier ':' identifier '.' '.' ICONST ')' simple_or_block_stmt  */
#line 293 "parser.y"
                                                                                   {
        const Symbol* sym = symtab.lookup((yyvsp[-7].sval));
        if (!sym) semantic_error("undeclared id", (yyvsp[-7].sval));
        if (sym->type != T_INT) semantic_error("foreach loop variable must be of type int:", (yyvsp[-7].sval));

        const Symbol* sym2 = symtab.lookup((yyvsp[-5].sval));
        if (!sym2) semantic_error("undeclared id", (yyvsp[-5].sval));
        if (sym2->type != T_INT) semantic_error("foreach loop range must be of type int:", (yyvsp[-5].sval));
    }
#line 1634 "y.tab.c"
    break;

  case 50: /* foreach_stmt: FOREACH '(' identifier ':' ICONST '.' '.' identifier ')' simple_or_block_stmt  */
#line 302 "parser.y"
                                                                                   {
        const Symbol* sym = symtab.lookup((yyvsp[-7].sval));
        if (!sym) semantic_error("undeclared id", (yyvsp[-7].sval));
        if (sym->type != T_INT) semantic_error("foreach loop variable must be of type int:", (yyvsp[-7].sval));
        const Symbol* sym3 = symtab.lookup((yyvsp[-2].sval));
        if (!sym3) semantic_error("undeclared id", (yyvsp[-2].sval));
        if (sym3->type != T_INT) semantic_error("foreach loop range must be of type int:", (yyvsp[-2].sval));
    }
#line 1647 "y.tab.c"
    break;

  case 51: /* foreach_stmt: FOREACH '(' identifier ':' ICONST '.' '.' ICONST ')' simple_or_block_stmt  */
#line 310 "parser.y"
                                                                               {
        const Symbol* sym = symtab.lookup((yyvsp[-7].sval));
        if (!sym) semantic_error("undeclared id", (yyvsp[-7].sval));
        if (sym->type != T_INT) semantic_error("foreach loop variable must be of type int:", (yyvsp[-7].sval));
    }
#line 1657 "y.tab.c"
    break;

  case 52: /* return_stmt: RETURN expr ';'  */
#line 318 "parser.y"
                      {
          if (current_func_type == T_VOID)
              semantic_error("void function should not return value", "");
          else if (!type_compatible(current_func_type, (yyvsp[-1].tval)))
              semantic_error("return type mismatch", "");
      }
#line 1668 "y.tab.c"
    break;

  case 53: /* expr: expr '+' expr  */
#line 328 "parser.y"
                    { 
          ExtendedType t = promote((yyvsp[-2].tval), (yyvsp[0].tval));
          if (t == T_ERROR) 
              semantic_error("invalid operation", "");
          (yyval.tval) = t;
      }
#line 1679 "y.tab.c"
    break;

  case 54: /* expr: expr '-' expr  */
#line 334 "parser.y"
                    { 
          ExtendedType t = promote((yyvsp[-2].tval), (yyvsp[0].tval));
          if (t == T_ERROR) 
              semantic_error("invalid operation", "");
          (yyval.tval) = t; 
      }
#line 1690 "y.tab.c"
    break;

  case 55: /* expr: expr '*' expr  */
#line 340 "parser.y"
                    {
          ExtendedType t = promote((yyvsp[-2].tval), (yyvsp[0].tval));
          if (t == T_ERROR) 
              semantic_error("invalid operation", "");
          (yyval.tval) = t; 
      }
#line 1701 "y.tab.c"
    break;

  case 56: /* expr: expr '/' expr  */
#line 346 "parser.y"
                    {
          ExtendedType t = promote((yyvsp[-2].tval), (yyvsp[0].tval));
          if (t == T_ERROR) 
              semantic_error("invalid operation", "");
          (yyval.tval) = t; 
    }
#line 1712 "y.tab.c"
    break;

  case 57: /* expr: expr '%' expr  */
#line 352 "parser.y"
                    {
          ExtendedType t = promote((yyvsp[-2].tval), (yyvsp[0].tval));
          if (t == T_ERROR) 
              semantic_error("invalid operation", "");
          (yyval.tval) = t; 
    }
#line 1723 "y.tab.c"
    break;

  case 58: /* expr: '-' expr  */
#line 358 "parser.y"
                             { (yyval.tval) = (yyvsp[0].tval); }
#line 1729 "y.tab.c"
    break;

  case 59: /* expr: '(' expr ')'  */
#line 359 "parser.y"
                             { (yyval.tval) = (yyvsp[-1].tval); }
#line 1735 "y.tab.c"
    break;

  case 60: /* expr: ICONST  */
#line 360 "parser.y"
                             { (yyval.tval) = T_INT;   }
#line 1741 "y.tab.c"
    break;

  case 61: /* expr: FCONST  */
#line 361 "parser.y"
                             { (yyval.tval) = T_FLOAT; }
#line 1747 "y.tab.c"
    break;

  case 62: /* expr: SCONST  */
#line 362 "parser.y"
                             { (yyval.tval) = T_STRING;}
#line 1753 "y.tab.c"
    break;

  case 63: /* expr: BCONST  */
#line 363 "parser.y"
                             { (yyval.tval) = T_BOOL;  }
#line 1759 "y.tab.c"
    break;

  case 64: /* expr: identifier  */
#line 364 "parser.y"
                 {
        const Symbol* sym = symtab.lookup((yyvsp[0].sval));
        if (!sym) semantic_error("undeclared var",(yyvsp[0].sval));
        (yyval.tval) = sym ? sym->type : T_ERROR;
      }
#line 1769 "y.tab.c"
    break;

  case 65: /* expr: identifier '(' arg_list_opt ')'  */
#line 369 "parser.y"
                                      {
        const Symbol* sym = symtab.lookup((yyvsp[-3].sval));
        if (!sym || sym->kind != Kind::K_FUNC)
            semantic_error("call of non-function", (yyvsp[-3].sval));
        (yyval.tval) = sym ? sym->type : T_ERROR;
      }
#line 1780 "y.tab.c"
    break;

  case 67: /* boolean_expr: expr EQ expr  */
#line 379 "parser.y"
                   { 
        if (!type_compatible((yyvsp[-2].tval), (yyvsp[0].tval))) semantic_error("expression type mismatch", ""); 
        (yyval.tval) = T_BOOL;
      }
#line 1789 "y.tab.c"
    break;

  case 68: /* boolean_expr: expr NE expr  */
#line 383 "parser.y"
                   { 
        if (!type_compatible((yyvsp[-2].tval), (yyvsp[0].tval))) semantic_error("expression type mismatch", ""); 
        (yyval.tval) = T_BOOL;
      }
#line 1798 "y.tab.c"
    break;

  case 69: /* boolean_expr: expr '>' expr  */
#line 387 "parser.y"
                    { 
        if (!type_compatible((yyvsp[-2].tval), (yyvsp[0].tval))) semantic_error("expression type mismatch", ""); 
        (yyval.tval) = T_BOOL;
      }
#line 1807 "y.tab.c"
    break;

  case 70: /* boolean_expr: expr '<' expr  */
#line 391 "parser.y"
                    { 
        if (!type_compatible((yyvsp[-2].tval), (yyvsp[0].tval))) semantic_error("expression type mismatch", ""); 
        (yyval.tval) = T_BOOL;
      }
#line 1816 "y.tab.c"
    break;

  case 71: /* boolean_expr: expr LE expr  */
#line 395 "parser.y"
                    { 
        if (!type_compatible((yyvsp[-2].tval), (yyvsp[0].tval))) semantic_error("expression type mismatch", ""); 
        (yyval.tval) = T_BOOL;
      }
#line 1825 "y.tab.c"
    break;

  case 72: /* boolean_expr: expr GE expr  */
#line 399 "parser.y"
                    { 
        if (!type_compatible((yyvsp[-2].tval), (yyvsp[0].tval))) semantic_error("expression type mismatch", ""); 
        (yyval.tval) = T_BOOL;
      }
#line 1834 "y.tab.c"
    break;

  case 73: /* boolean_expr: '!' expr  */
#line 403 "parser.y"
               {
        (yyval.tval) = T_BOOL;
      }
#line 1842 "y.tab.c"
    break;

  case 74: /* boolean_expr: expr AND expr  */
#line 406 "parser.y"
                    {
        (yyval.tval) = T_BOOL;
    }
#line 1850 "y.tab.c"
    break;

  case 75: /* boolean_expr: expr OR expr  */
#line 409 "parser.y"
                   {
        (yyval.tval) = T_BOOL;
    }
#line 1858 "y.tab.c"
    break;

  case 76: /* const_expr: ICONST  */
#line 415 "parser.y"
             { (yyval.tval) = T_INT; }
#line 1864 "y.tab.c"
    break;

  case 77: /* const_expr: FCONST  */
#line 416 "parser.y"
             { (yyval.tval) = T_FLOAT; }
#line 1870 "y.tab.c"
    break;

  case 78: /* const_expr: BCONST  */
#line 417 "parser.y"
             { (yyval.tval) = T_BOOL; }
#line 1876 "y.tab.c"
    break;

  case 79: /* const_expr: SCONST  */
#line 418 "parser.y"
             { (yyval.tval) = T_STRING; }
#line 1882 "y.tab.c"
    break;

  case 80: /* type_spec: TINT  */
#line 422 "parser.y"
              { (yyval.tval) = T_INT; }
#line 1888 "y.tab.c"
    break;

  case 81: /* type_spec: TFLOAT  */
#line 423 "parser.y"
              { (yyval.tval) = T_FLOAT; }
#line 1894 "y.tab.c"
    break;

  case 82: /* type_spec: TBOOL  */
#line 424 "parser.y"
              { (yyval.tval) = T_BOOL; }
#line 1900 "y.tab.c"
    break;

  case 83: /* type_spec: TSTRING  */
#line 425 "parser.y"
              { (yyval.tval) = T_STRING; }
#line 1906 "y.tab.c"
    break;

  case 84: /* type_spec: TVOID  */
#line 426 "parser.y"
              { (yyval.tval) = T_VOID; }
#line 1912 "y.tab.c"
    break;

  case 85: /* identifier: ID  */
#line 430 "parser.y"
         { (yyval.sval) = strdup((yyvsp[0].sval)); }
#line 1918 "y.tab.c"
    break;


#line 1922 "y.tab.c"

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

#line 444 "parser.y"
           

void yyerror(const string& msg) {
    cerr << "SYNTAX(" << linenum << "): " << msg << '\n';
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
    return 0;
}
