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
%x sphere
%x p0
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
<global>pos{WS}                     { return POS; }
<global>image{WS}background{WS}     { return IMG_BGCOLOR; }
<global>gl{WS}background{WS}        { return GL_BGCOLOR; }
<global>gl{WS}sphere{WS}sections    { return GL_SPHERE_SECTIONS; }
<global>num{WS}threads              { return NUM_THREADS; }
<global>render{WS}x{WS}block        { return RENDER_X_BLOCK; }
<global>render{WS}y{WS}block        { return RENDER_Y_BLOCK; }
<global>render{WS}handler{WS}sleep  { return RENDER_HANDLER_SLEEP; }
<global>render{WS}thread{WS}sleep   { return RENDER_THREAD_SLEEP; }
<global>render{WS}spinlock{WS}sleep { return RENDER_SPINLOCK_SLEEP; }
<global>gaussian{WS}blur{WS}max     { return GAUSSIAN_BLUR_MAX; }
<global>gaussian{WS}blur{WS}sigma   { return GAUSSIAN_BLUR_SIGMA; }
<global>gl{WS}render{WS}lights		{ return GL_RENDER_LIGHTS; }
<global>headless{WS}                { return HEADLESS; }

<INITIAL>camera{WS}                 { yy_push_state(camera); return CAMERA; }
<camera>pos{WS}                     { return POS; }
<camera>dir{WS}                     { return DIR; }
<camera>look{WS}at{WS}              { return LOOKAT; }
<camera>up{WS}                      { return UP; }
<camera>fov{WS}                     { return FOV; }
<camera>aspect{WS}                  { return ASPECT; }
<camera>min{WS}draw                 { return MIN_DRAW; }
<camera>max{WS}draw                 { return MAX_DRAW; }

<INITIAL>p0{WS}                     { yy_push_state(p0); return P0; }
<p0>spiral{WS}num{WS}spheres        { return SPIRAL_NUM_SPHERES; }
<p0>spiral{WS}radius                { return SPIRAL_RADIUS; }
<p0>lorenz{WS}dt                    { return LORENZ_DT; }
<p0>lorenz{WS}min{WS}distance       { return LORENZ_MIN_DISTANCE; }
<p0>lorenz{WS}max{WS}distance       { return LORENZ_MAX_DISTANCE; }
<p0>lorenz{WS}sigma                 { return LORENZ_SIGMA; }
<p0>lorenz{WS}rho                   { return LORENZ_RHO; }
<p0>lorenz{WS}beta                  { return LORENZ_BETA; }
<p0>lorenz{WS}radius                { return LORENZ_RADIUS; }
<p0>lorenz{WS}num{WS}spheres        { return LORENZ_NUM_SPHERES; }
<p0>lorenz{WS}start                 { return LORENZ_START; }

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

<*>{STRING}{WS}                     { yylval.str = _strdup(yytext); return STRING; }
<*>{INT}{WS}                        { yylval.integer = atoi(yytext); return PARSE_INT; }
<*>{REAL}{WS}                       { yylval.real = (float)atof(yytext); return REAL; }

<*>[!{,=\-+\\/*()]{WS}              { return yytext[0]; }
<*>"}"{WS}                          { yy_pop_state(); return yytext[0]; }
<*>{COMMENT}                        // eat up comments 
<*>[ ,\t\r]+                        // eat up whitespace
<*>"\n"                             { yyline++; }
.                                   { printf("\nParse error line %d near: %s\n", yyline, yytext); }

%%
