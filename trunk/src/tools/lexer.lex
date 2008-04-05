%option noyywrap
%option never-interactive
%option stack

%{
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "symbols.yy.h"

int yyline=1;
%}

COMMENT "#".*
WS [ \t\r]+
OPTWS [ \t\r]*
SIGN [+-]
DIGIT [0-9]
INT {DIGIT}+
REAL {DIGIT}*("."{DIGIT}*)?([eE][+-]{DIGIT}+)?
ID ([_a-zA-Z][_a-zA-Z0-9]*[\ \t\n])+
STRING  \"[_a-zA-Z][_a-zA-Z0-9"."/\\: ]*\"
NEWLINE ("\n"|"\r\n")

%x global
%x camera
%x light
%x model
%x sphere
%%

<*>cos{WS} { return YY_MATH_COS; }
<*>sin{WS} { return YY_MATH_SIN; }
<*>tan{WS} { return YY_MATH_TAN; }
<*>acos{WS} { return YY_MATH_ACOS; }
<*>asin{WS} { return YY_MATH_ASIN; }
<*>atan{WS} { return YY_MATH_ATAN; }
<*>ln{WS} { return YY_MATH_LN; }
<*>log{WS} { return YY_MATH_LOG; }
<*>exp{WS} { return YY_MATH_EXP; }
<*>sqrt{WS} { return YY_MATH_SQRT; }
<*>e{WS} { return YY_MATH_E; }
<*>pi{WS} { return YY_MATH_PI; }

<INITIAL>global{OPTWS}  { yy_push_state(global); return YY_STATE_GLOBAL; }
<global>width{WS}       { return YY_SYM_WIDTH; }
<global>height{WS}      { return YY_SYM_HEIGHT; }
<global>gl_bg{WS}       { return YY_SYM_GL_BG; }
<global>img_bg{WS}      { return YY_SYM_IMG_BG; }

<INITIAL>camera{WS}     { yy_push_state(camera); return YY_STATE_CAMERA; }
<camera>pos{WS}         { return YY_SYM_CAMERA_POS; }
<camera>view_dir{WS}    { return YY_SYM_CAMERA_DIR; }
<camera>look_at{WS}     { return YY_SYM_CAMERA_LOOK_AT; }
<camera>up{WS}          { return YY_SYM_CAMREA_UP; }
<camera>fov{WS}         { return YY_SYM_CAMERA_FOV; }

<INITIAL>light{WS}      { yy_push_state(light); return YY_STATE_LIGHT; }
<light>pointlight{WS}   { return YY_SYM_LIGHT_POINTLIGHT; }
<light>pos{WS}          { return YY_SYM_LIGHT_POS; }
<light>diffuse{WS}      { return YY_SYM_LIGHT_DIFFUSE; }
<light>ambient{WS}      { return YY_SYM_LIGHT_AMBIENT; }
<light>wattage{WS}      { return YY_SYM_LIGHT_WATTAGE; }

<INITIAL>model{WS}      { yy_push_state(model); return YY_STATE_MODEL; }
<model>LOAD{WS}         { return YY_SYM_MODEL; }

<INITIAL>sphere{WS}     { yy_push_state(sphere); return YY_STATE_SPHERE; }
<sphere>pos{WS}         { return YY_SYM_SPHERE_POS; }
<sphere>radius{WS}      { return YY_SYM_SPHERE_RADIUS; }
<sphere>color{WS}       { return YY_SYM_SPHERE_COLOR; }

<*>{INT}                { yyval.integer = atoi(yytext); }
<*>{REAL}               { yyval.real = atof(yytext); }
<*>{STRING}             { yyval.string = strdup(yytext); }

<*>"/*"  { // C style comments
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

<*>[!{,=\-+\\/*()]{WS}  { return yytext[0]; }

<*>"}"          { yy_pop_state(); return yytext[0]; }

<*>{COMMENT}    // eat up comments

<*>[ ,\t\r]+         // eat up whitespace

<*>{NEWLINE}    { yyline++; }

.               { printf( "\nParse error line %d near %s\n", yyline, yytext ); }

%%
