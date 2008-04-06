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


COMMENT "#".* 
SPACE [ ]+
WS [ \t]*

SIGN    [+-]
DIGIT   [0-9]
FLOATARGS [eE][+-]
INT {DIGIT}+
REAL {DIGIT}*("."{DIGIT}*)?({FLOATARGS}{DIGIT}+)?
ID  ([_a-zA-Z][_a-zA-Z0-9]*[\ \t\n])+
STRING  \"[_a-zA-Z][_a-zA-Z0-9"."/\\: ]*\"

%x global
%x camera
%x triangle
%x mesh
%x instance
%x light
%x pointlight
%x sphere
%%

<*>enable{WS}       { return ENABLE; }
<*>disable{WS}      { return DISABLE; }
<*>cos{WS}          { return MATH_COS; }
<*>sin{WS}          { return MATH_SIN; }
<*>tan{WS}          { return MATH_TAN; }
<*>acos{WS}         { return MATH_ACOS; }
<*>asin{WS}         { return MATH_ASIN; }
<*>atan{WS}         { return MATH_ATAN; }
<*>atan2{WS}        { return MATH_ATAN2; }
<*>ln{WS}           { return MATH_LN; }
<*>log{WS}          { return MATH_LOG; }
<*>exp{WS}          { return MATH_EXP; }
<*>sqrt{WS}         { return MATH_SQRT; }
<*>e{WS}            { return MATH_E; }
<*>pi{WS}           { return MATH_PI; }

<INITIAL>global{WS}                 { yy_push_state(global); return GLOBAL; }
<global>width{WS}	                { return WIDTH; }
<global>height{WS}	                { return HEIGHT; }
<global>image{WS}background{WS}     { return IMG_BGCOLOR; }
<global>gl{WS}background{WS}        { return GL_BGCOLOR; }

<INITIAL>camera{WS}                 { yy_push_state(camera); return CAMERA; }
<camera>pos{WS}                     { return POS; }
<camera>dir{WS}                     { return DIR; }
<camera>look{WS}at{WS}              { return LOOKAT; }
<camera>up{WS}                      { return UP; }
<camera>fov{WS}                     { return FOV; }

<INITIAL>triangle{WS}               { yy_push_state(triangle); return TRIANGLE; }
<triangle>v1{WS}                    { return V1; }
<triangle>v2{WS}                    { return V2; }
<triangle>v3{WS}                    { return V3; }
<triangle>n1{WS}                    { return N1; }
<triangle>n2{WS}                    { return N2; }
<triangle>n3{WS}                    { return N3; }

<INITIAL>mesh{WS}                   { yy_push_state(mesh); return MESH; }
<mesh>load{WS}                      { return LOAD; }

<INITIAL>instance{WS}               { yy_push_state(instance); return INSTANCE; }
<instance>geometry{WS}              { return GEOMETRY; }

<INITIAL>push{WS}matrix{WS}         { return PUSHMATRIX; }
<INITIAL>pop{WS}matrix{WS}          { return POPMATRIX; }
<INITIAL>rotate{WS}                 { return ROTATE; }
<INITIAL>translate{WS}              { return TRANSLATE; }
<INITIAL>scale{WS}                  { return SCALE; }

<INITIAL>light{WS}                  { yy_push_state(light); return LIGHT; }
<light>point{WS}                    { yy_pop_state(); yy_push_state(pointlight); return POINTLIGHT; }
<pointlight>color{WS}               { return COLOR; }
<pointlight>pos{WS}                 { return POS; }
<pointlight>wattage{WS}             { return WATTAGE; }

<INITIAL>sphere{WS}                 { yy_push_state(sphere); return SPHERE; }
<sphere>center{WS}                  { return CENTER; }
<sphere>radius{WS}                  { return RADIUS; }

<*>{INT}                            { yylval.integer = atoi(yytext); return PARSE_INT; }
<*>{REAL}                           { yylval.real = (float)atof(yytext); return REAL; }
<*>{STRING}                         { yylval.str = _strdup(yytext); return STRING; }

<*>"/*" { // C style comments
  register int c;
  for ( ; ; ) {
    while ((c = yyinput()) != '*' && c != EOF ) if (c == '\n') yyline++;
    if ( c == '*' ) {
      while ( (c = yyinput()) == '*' ) if (c == '\n') yyline++;
	  if ( c == '/' )
	    break;    /* found the end */
      if ( c == EOF ) {
	    fprintf(stderr, "EOF in comment");
	    printf("Press Enter to continue...");
	  }
	}
  }
}

<*>[!{,=\-+\\/*()]{WS}              { return yytext[0]; }
<*>"}"                              { yy_pop_state(); return yytext[0]; }
<*>{COMMENT}                        // eat up comments 
<*>[ ,\t\r]+                        // eat up whitespace
<*>"\n"                             { yyline++; }
.                                   { printf("\nParse error line %d near: %s\n", yyline, yytext); }

%%
