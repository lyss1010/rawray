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

<INITIAL>global{WS}                 { yy_push_state(global); return YY_GLOBAL; }
<global>width{WS}	                { return YY_WIDTH; }
<global>height{WS}	                { return YY_HEIGHT; }
<global>pos{WS}                     { return YY_POS; }
<global>image{WS}background{WS}     { return YY_IMG_BGCOLOR; }
<global>image{WS}foreground{WS}     { return YY_IMG_FGCOLOR; }
<global>gl{WS}background{WS}        { return YY_GL_BGCOLOR; }
<global>gl{WS}sphere{WS}sections    { return YY_GL_SPHERE_SECTIONS; }
<global>num{WS}threads              { return YY_NUM_THREADS; }
<global>render{WS}x{WS}block        { return YY_RENDER_X_BLOCK; }
<global>render{WS}y{WS}block        { return YY_RENDER_Y_BLOCK; }
<global>render{WS}handler{WS}sleep  { return YY_RENDER_HANDLER_SLEEP; }
<global>render{WS}thread{WS}sleep   { return YY_RENDER_THREAD_SLEEP; }
<global>render{WS}spinlock{WS}sleep { return YY_RENDER_SPINLOCK_SLEEP; }
<global>gaussian{WS}blur{WS}max     { return YY_GAUSSIAN_BLUR_MAX; }
<global>gaussian{WS}blur{WS}sigma   { return YY_GAUSSIAN_BLUR_SIGMA; }
<global>gl{WS}render{WS}lights		{ return YY_GL_RENDER_LIGHTS; }
<global>headless{WS}                { return YY_HEADLESS; }
<global>triangle{WS}test{WS}        { return YY_TRIANGLE_TEST; }
<global>projection                  { return YY_PROJECTION; }
<global>barycentric{WS}             { return YY_BARYCENTRIC; }
<global>plucker{WS}                 { return YY_PLUCKER; }
<global>moller{WS}                  { return YY_MOLLER; }


<INITIAL>camera{WS}                 { yy_push_state(camera); return YY_CAMERA; }
<camera>pos{WS}                     { return YY_POS; }
<camera>dir{WS}                     { return YY_DIR; }
<camera>look{WS}at{WS}              { return YY_LOOKAT; }
<camera>up{WS}                      { return YY_UP; }
<camera>fov{WS}                     { return YY_FOV; }
<camera>aspect{WS}                  { return YY_ASPECT; }
<camera>min{WS}draw                 { return YY_MIN_DRAW; }
<camera>max{WS}draw                 { return YY_MAX_DRAW; }

<INITIAL>p0{WS}                     { yy_push_state(p0); return YY_P0; }
<p0>spiral{WS}num{WS}spheres        { return YY_SPIRAL_NUM_SPHERES; }
<p0>spiral{WS}radius                { return YY_SPIRAL_RADIUS; }
<p0>lorenz{WS}dt                    { return YY_LORENZ_DT; }
<p0>lorenz{WS}min{WS}distance       { return YY_LORENZ_MIN_DISTANCE; }
<p0>lorenz{WS}max{WS}distance       { return YY_LORENZ_MAX_DISTANCE; }
<p0>lorenz{WS}sigma                 { return YY_LORENZ_SIGMA; }
<p0>lorenz{WS}rho                   { return YY_LORENZ_RHO; }
<p0>lorenz{WS}beta                  { return YY_LORENZ_BETA; }
<p0>lorenz{WS}radius                { return YY_LORENZ_RADIUS; }
<p0>lorenz{WS}num{WS}spheres        { return YY_LORENZ_NUM_SPHERES; }
<p0>lorenz{WS}start                 { return YY_LORENZ_START; }

<INITIAL>triangle{WS}               { yy_push_state(triangle); return YY_TRIANGLE; }
<triangle>v1{WS}                    { return YY_V1; }
<triangle>v2{WS}                    { return YY_V2; }
<triangle>v3{WS}                    { return YY_V3; }
<triangle>n1{WS}                    { return YY_N1; }
<triangle>n2{WS}                    { return YY_N2; }
<triangle>n3{WS}                    { return YY_N3; }

<INITIAL>mesh{WS}                   { yy_push_state(mesh); return YY_MESH; }
<mesh>load{WS}                      { return YY_LOAD; }

<INITIAL>instance{WS}               { yy_push_state(instance); return YY_INSTANCE; }
<instance>geometry{WS}              { return YY_GEOMETRY; }

<INITIAL>push{WS}matrix{WS}         { return YY_PUSHMATRIX; }
<INITIAL>pop{WS}matrix{WS}          { return YY_POPMATRIX; }
<INITIAL>rotate{WS}                 { return YY_ROTATE; }
<INITIAL>translate{WS}              { return YY_TRANSLATE; }
<INITIAL>scale{WS}                  { return YY_SCALE; }

<INITIAL>light{WS}                  { yy_push_state(light); return YY_LIGHT; }
<light>point{WS}                    { yy_pop_state(); yy_push_state(pointlight); return YY_POINTLIGHT; }
<pointlight>color{WS}               { return YY_COLOR; }
<pointlight>pos{WS}                 { return YY_POS; }
<pointlight>wattage{WS}             { return YY_WATTAGE; }

<INITIAL>material{WS}               { yy_push_state(material); return YY_MATERIAL; }
<material>lambert{WS}               { yy_pop_state(); yy_push_state(lambert); return YY_LAMBERT; }
<lambert>diffuse{WS}                { return YY_DIFFUSE; }
<lambert>ambient{WS}                { return YY_AMBIENT; }

<INITIAL>sphere{WS}                 { yy_push_state(sphere); return YY_SPHERE; }
<sphere>center{WS}                  { return YY_CENTER; }
<sphere>radius{WS}                  { return YY_RADIUS; }

<INITIAL>blpatch{WS}                { yy_push_state(blpatch); return YY_BLPATCH; }
<blpatch>blah{WS}                   { return YY_P00; }
<blpatch>foo{WS}                    { return YY_P01; }
<blpatch>p10{WS}                    { return YY_P10; }
<blpatch>p11{WS}                    { return YY_P11; }

<*>{STRING}{WS}                     { yylval.str = _strdup(yytext); return YY_STRING; }
<*>{INT}{WS}                        { yylval.integer = atoi(yytext); return YY_PARSE_INT; }
<*>{REAL}{WS}                       { yylval.real = (float)atof(yytext); return YY_REAL; }

<*>[!{,=\-+\\/*()]{WS}              { return yytext[0]; }
<*>"}"{WS}                          { yy_pop_state(); return yytext[0]; }
<*>{COMMENT}                        // eat up comments 
<*>[ ,\t\r]+                        // eat up whitespace
<*>"\n"                             { yyline++; }
.                                   { printf("\nParse error line %d near: %s\n", yyline, yytext); }

%%
