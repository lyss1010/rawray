%option noyywrap 
%option never-interactive 
%option stack
%option batch
%option case-insensitive
%option yylineno
%option outfile="lexer.yy.cc"

%{
#ifdef WIN32
#pragma warning(disable:4127) // while(1) warning
#pragma warning(disable:4102) // unreferenced label warning
#pragma warning(disable:4505) // unreferenced local function
#pragma warning(disable:4267) // smaller type conversion warnings
#pragma warning(disable:4244) // smaller type conversion warnings
#endif

#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "parser.yy.cc.h"

int yyline=1;
%}


COMMENT     "#".* 
SPACE       [ ]+
WS          [ \t]*

SIGN        [+-]
DIGIT       [0-9]
INT         {DIGIT}+
REAL        {DIGIT}*("."{DIGIT}*)
ID          ([_a-zA-Z][_a-zA-Z0-9]*[\ \t\n])+
STRING      '([^']*)'|\"([^\"]*)\"


%x global
%x camera
%x triangle
%x mesh
%x instance
%x light
%x pointlight
%x material
%x lambert
%x sphere
%x blpatch
%x p0
%%

<INITIAL>global{WS}                 { yy_push_state(global); return YY_GLOBAL; }

<*>enable{WS}       { return YY_ENABLE; }
<*>disable{WS}      { return YY_DISABLE; }
<*>cos{WS}          { return YY_MATH_COS; }
<*>sin{WS}          { return YY_MATH_SIN; }
<*>tan{WS}          { return YY_MATH_TAN; }
<*>acos{WS}         { return YY_MATH_ACOS; }
<*>asin{WS}         { return YY_MATH_ASIN; }
<*>atan{WS}         { return YY_MATH_ATAN; }
<*>atan2{WS}        { return YY_MATH_ATAN2; }
<*>ln{WS}           { return YY_MATH_LN; }
<*>log{WS}          { return YY_MATH_LOG; }
<*>exp{WS}          { return YY_MATH_EXP; }
<*>sqrt{WS}         { return YY_MATH_SQRT; }
<*>e{WS}            { return YY_MATH_E; }
<*>pi{WS}           { return YY_MATH_PI; }
<*>[{WS}            { return YY_LBOX; }
<*>]{WS}            { return YY_LBOX; }
<*>{{WS}            { return YY_LCURLY; }
<*>}{WS}            { yy_pop_state(); return YY_RCURLY; }
<*>({WS}            { return YY_LPAREN; }
<*>){WS}            { return YY_RPAREN; }
<*>!{WS}            { return YY_EXCLAMATION; }
<*>,{WS}            { return YY_COMMA; }
<*>={WS}            { return YY_EQUAL; }
<*>+{WS}            { return YY_PLUS; }
<*>*{WS}            { return YY_MUL; }
<*>/{WS}            { return YY_DIV; }
<*>\\{WS}           { return YY_BSLASH; }
<*>"\n"             { yyline++; }

<*>{STRING}{WS}                     { yylval.str = _strdup(yytext); return YY_STRING; }
<*>{INT}{WS}                        { yylval.integer = atoi(yytext); return YY_PARSE_INT; }
<*>{REAL}{WS}                       { yylval.real = (float)atof(yytext); return YY_REAL; }

<*>[ ,\t\r]+        // eat up whitespace
<*>{COMMENT}        // eat up comments 
.                                   { printf("\nParse error line %d near: %s\n", yyline, yytext); }

%%
