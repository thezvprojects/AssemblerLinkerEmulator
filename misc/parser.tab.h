/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_MISC_PARSER_TAB_H_INCLUDED
# define YY_YY_MISC_PARSER_TAB_H_INCLUDED
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
    ASMD_GLOBAL = 258,
    ASMD_EXTERN = 259,
    ASMD_SECTION = 260,
    ASMD_WORD = 261,
    ASMD_SKIP = 262,
    ASMD_END = 263,
    ASMC_HALT = 264,
    ASMC_INT = 265,
    ASMC_IRET = 266,
    ASMC_RET = 267,
    ASMC_CALL = 268,
    ASMC_JMP = 269,
    ASMC_BEQ = 270,
    ASMC_BNE = 271,
    ASMC_BGT = 272,
    ASMC_PUSH = 273,
    ASMC_POP = 274,
    ASMC_XCHG = 275,
    ASMC_ADD = 276,
    ASMC_SUB = 277,
    ASMC_MUL = 278,
    ASMC_DIV = 279,
    ASMC_NOT = 280,
    ASMC_AND = 281,
    ASMC_OR = 282,
    ASMC_XOR = 283,
    ASMC_SHL = 284,
    ASMC_SHR = 285,
    ASMC_LD = 286,
    ASMC_ST = 287,
    ASMC_CSRRD = 288,
    ASMC_CSRWR = 289,
    COMMA = 290,
    NEWLINE = 291,
    LABEL = 292,
    PARAMETER = 293,
    LITERAL = 294,
    VALUE_OPERAND = 295,
    MEM_REG_OPERAND = 296,
    REG_VALUE = 297,
    CSR_VALUE = 298,
    HEXA_LITERAL = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "misc/parser.y"

    char *str;  // string values type
    ParametersElement* paramElements;

#line 107 "misc/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MISC_PARSER_TAB_H_INCLUDED  */
