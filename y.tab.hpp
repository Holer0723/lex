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

#ifndef YY_YY_Y_TAB_HPP_INCLUDED
# define YY_YY_Y_TAB_HPP_INCLUDED
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
    CONST = 258,                   /* CONST  */
    IF = 259,                      /* IF  */
    ELSE = 260,                    /* ELSE  */
    WHILE = 261,                   /* WHILE  */
    FOR = 262,                     /* FOR  */
    FOREACH = 263,                 /* FOREACH  */
    RETURN = 264,                  /* RETURN  */
    PRINT = 265,                   /* PRINT  */
    PRINTLN = 266,                 /* PRINTLN  */
    READ = 267,                    /* READ  */
    TVOID = 268,                   /* TVOID  */
    ICONST = 269,                  /* ICONST  */
    FCONST = 270,                  /* FCONST  */
    SCONST = 271,                  /* SCONST  */
    BCONST = 272,                  /* BCONST  */
    EQ = 273,                      /* EQ  */
    NE = 274,                      /* NE  */
    LE = 275,                      /* LE  */
    GE = 276,                      /* GE  */
    AND = 277,                     /* AND  */
    OR = 278,                      /* OR  */
    ID = 279,                      /* ID  */
    TFLOAT = 280,                  /* TFLOAT  */
    TBOOL = 281,                   /* TBOOL  */
    TINT = 282,                    /* TINT  */
    TSTRING = 283,                 /* TSTRING  */
    UMINUS = 284,                  /* UMINUS  */
    INC = 285,                     /* INC  */
    DEC = 286                      /* DEC  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define CONST 258
#define IF 259
#define ELSE 260
#define WHILE 261
#define FOR 262
#define FOREACH 263
#define RETURN 264
#define PRINT 265
#define PRINTLN 266
#define READ 267
#define TVOID 268
#define ICONST 269
#define FCONST 270
#define SCONST 271
#define BCONST 272
#define EQ 273
#define NE 274
#define LE 275
#define GE 276
#define AND 277
#define OR 278
#define ID 279
#define TFLOAT 280
#define TBOOL 281
#define TINT 282
#define TSTRING 283
#define UMINUS 284
#define INC 285
#define DEC 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 56 "parser.y"

    int     ival;
    float   fval;
    char*   sval;
    Type    tval;

#line 136 "y.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_HPP_INCLUDED  */
