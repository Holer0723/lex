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
