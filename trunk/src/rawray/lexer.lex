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
#pragma warning(disable:4702) // unreachable code in stl library on relesae
#pragma warning(disable:4211) // defining something as extern and then later on as static
#endif

#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.yy.cc.h"

int yyline=1;
int yyerr=0;

void yy_done_parsing() {
	yy_delete_buffer( YY_CURRENT_BUFFER );
	
	delete yy_start_stack;
	yy_start_stack = 0;
	
	yy_init = 1;
}
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


%x s_global
%x s_camera
%x s_bbox
%x s_mesh
%x s_instance
%x s_light
%x s_pointlight
%x s_spherelight
%x s_squarelight
%x s_material
%x s_multimaterial
%x s_diffuse
%x s_indirectdiffuse
%x s_phong
%x s_stone
%x s_stonebump
%x s_reflective
%x s_refractive
%x s_sphere
%x s_blpatch
%x s_p0
%x s_matrix
%x s_hdr
%%

<*>true{WS}			{ return YY_TRUE; }
<*>yes{WS}			{ return YY_TRUE; }
<*>enable{WS}       { return YY_TRUE; }
<*>on{WS}			{ return YY_TRUE; }

<*>false{WS}		{ return YY_FALSE; }
<*>no{WS}			{ return YY_FALSE; }
<*>disable{WS}      { return YY_FALSE; }
<*>off{WS}			{ return YY_FALSE; }

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

<*>"<"{WS}			{ return YY_LT; }
<*>">"{WS}			{ return YY_GT; }
<*>"["{WS}          { return YY_LBOX; }
<*>"]"{WS}          { return YY_LBOX; }
<*>"{"{WS}          { return YY_LCURLY; }
<*>"}"{WS}          { yy_pop_state(); return YY_RCURLY; }
<*>"("{WS}          { return YY_LPAREN; }
<*>")"{WS}          { return YY_RPAREN; }
<*>","{WS}          { return YY_COMMA; }
<*>"="{WS}          { return YY_EQUAL; }
<*>"+"{WS}          { return YY_PLUS; }
<*>"-"{WS}          { return YY_MINUS; }
<*>"*"{WS}          { return YY_MUL; }
<*>"/"{WS}          { return YY_DIV; }
<*>"^"{WS}			{ return YY_CARAT; }
<*>"\\"{WS}         { return YY_BSLASH; }
<*>"x"				{ return YY_X; }
<*>"\n"             { yyline++; }



<INITIAL>global{WS}						{ yy_push_state(s_global); return YY_S_GLOBAL; }
<s_global>size{WS}						{ return YY_SIZE; }
<s_global>pos{WS}						{ return YY_POS; }
<s_global>image{WS}background{WS}		{ return YY_IMG_BGCOLOR; }
<s_global>image{WS}foreground{WS}		{ return YY_IMG_FGCOLOR; }
<s_global>gl{WS}background{WS}			{ return YY_GL_BGCOLOR; }
<s_global>gl{WS}sphere{WS}sections		{ return YY_GL_SPHERE_SECTIONS; }
<s_global>gl{WS}render{WS}lights		{ return YY_GL_RENDER_LIGHTS; }
<s_global>gl{WS}render{WS}bbox  		{ return YY_GL_RENDER_BBOX; }
<s_global>num{WS}threads				{ return YY_NUM_THREADS; }
<s_global>thread{WS}job{WS}size			{ return YY_THREAD_JOB_SIZE; }
<s_global>render{WS}handler{WS}sleep	{ return YY_RENDER_HANDLER_SLEEP; }
<s_global>render{WS}thread{WS}sleep		{ return YY_RENDER_THREAD_SLEEP; }
<s_global>render{WS}spinlock{WS}sleep	{ return YY_RENDER_SPINLOCK_SLEEP; }
<s_global>gaussian{WS}blur{WS}max		{ return YY_GAUSSIAN_BLUR_MAX; }
<s_global>gaussian{WS}blur{WS}sigma		{ return YY_GAUSSIAN_BLUR_SIGMA; }
<s_global>headless{WS}					{ return YY_HEADLESS; }
<s_global>triangle{WS}test{WS}			{ return YY_TRIANGLE_TEST; }
<s_global>projection					{ return YY_PROJECTION; }
<s_global>barycentric{WS}				{ return YY_BARYCENTRIC; }
<s_global>plucker{WS}					{ return YY_PLUCKER; }
<s_global>moller{WS}					{ return YY_MOLLER; }
<s_global>box{WS}cost{WS}				{ return YY_BOX_COST; }
<s_global>object{WS}cost{WS}			{ return YY_OBJECT_COST; }
<s_global>hdr{WS}pfm{WS}				{ return YY_PFM; }
<s_global>anti{WS}alias					{ return YY_ANTI_ALIAS; }
<s_global>max{WS}diffuse{WS}bounce{WS}	{ return YY_MAX_DIFFUSE_BOUNCE; }
<s_global>max{WS}ior{WS}bounce{WS}		{ return YY_MAX_IOR_BOUNCE; }
<s_global>hdr{WS}bloom{WS}power{WS}		{ return YY_HDR_BLOOM_POWER; }
<s_global>hdr{WS}bloom{WS}radius{WS}	{ return YY_HDR_BLOOM_RADIUS; }
<s_global>bcspline{WS}b{WS}				{ return YY_BCSPLINE_B; }
<s_global>bcspline{WS}c{WS}				{ return YY_BCSPLINE_C; }

<INITIAL>camera{WS}						{ yy_push_state(s_camera); return YY_S_CAMERA; }
<s_camera>pos{WS}						{ return YY_POS; }
<s_camera>dir{WS}						{ return YY_DIR; }
<s_camera>look{WS}at{WS}				{ return YY_LOOKAT; }
<s_camera>up{WS}						{ return YY_UP; }
<s_camera>fov{WS}						{ return YY_FOV; }
<s_camera>aspect{WS}					{ return YY_ASPECT; }
<s_camera>min{WS}draw					{ return YY_MIN_DRAW; }
<s_camera>max{WS}draw					{ return YY_MAX_DRAW; }

<INITIAL>p0{WS}							{ yy_push_state(s_p0); return YY_S_P0; }
<s_p0>spiral{WS}num{WS}spheres			{ return YY_SPIRAL_NUM_SPHERES; }
<s_p0>spiral{WS}radius					{ return YY_SPIRAL_RADIUS; }
<s_p0>lorenz{WS}dt						{ return YY_LORENZ_DT; }
<s_p0>lorenz{WS}min{WS}distance			{ return YY_LORENZ_MIN_DISTANCE; }
<s_p0>lorenz{WS}max{WS}distance			{ return YY_LORENZ_MAX_DISTANCE; }
<s_p0>lorenz{WS}sigma					{ return YY_LORENZ_SIGMA; }
<s_p0>lorenz{WS}rho						{ return YY_LORENZ_RHO; }
<s_p0>lorenz{WS}beta					{ return YY_LORENZ_BETA; }
<s_p0>lorenz{WS}radius					{ return YY_LORENZ_RADIUS; }
<s_p0>lorenz{WS}num{WS}spheres			{ return YY_LORENZ_NUM_SPHERES; }
<s_p0>lorenz{WS}start					{ return YY_LORENZ_START; }

<INITIAL>mesh{WS}						{ yy_push_state(s_mesh); return YY_S_MESH; }
<s_mesh>load{WS}						{ return YY_LOAD; }

<INITIAL>instance{WS}					{ yy_push_state(s_instance); return YY_S_INSTANCE; }
<s_instance>geometry{WS}				{ return YY_GEOMETRY; }

<INITIAL>light{WS}						{ yy_push_state(s_light); return YY_S_LIGHT; }
<s_light>point{WS}						{ yy_pop_state(); yy_push_state(s_pointlight); return YY_S_POINTLIGHT; }
<s_light>sphere{WS}						{ yy_pop_state(); yy_push_state(s_spherelight); return YY_S_SPHERELIGHT; }
<s_light>square{WS}						{ yy_pop_state(); yy_push_state(s_squarelight); return YY_S_SQUARELIGHT; }

<s_pointlight>pos{WS}					{ return YY_POS; }
<s_pointlight>color{WS}					{ return YY_COLOR; }
<s_pointlight>wattage{WS}				{ return YY_WATTAGE; }
<s_pointlight>num{WS}samples{WS}		{ return YY_NUM_SAMPLES; }

<s_squarelight>pos{WS}					{ return YY_POS; }
<s_squarelight>color{WS}				{ return YY_COLOR; }
<s_squarelight>wattage{WS}				{ return YY_WATTAGE; }
<s_squarelight>num{WS}samples{WS}		{ return YY_NUM_SAMPLES; }
<s_squarelight>p1{WS}					{ return YY_P1; }
<s_squarelight>p2{WS}					{ return YY_P2; }

<s_spherelight>pos{WS}					{ return YY_POS; }
<s_spherelight>color{WS}				{ return YY_COLOR; }
<s_spherelight>wattage{WS}				{ return YY_WATTAGE; }
<s_spherelight>num{WS}samples{WS}		{ return YY_NUM_SAMPLES; }
<s_spherelight>radius{WS}				{ return YY_RADIUS; }

<INITIAL>material{WS}					{ yy_push_state(s_material); return YY_S_MATERIAL; }
<INITIAL>multimaterial{WS}				{ yy_push_state(s_multimaterial); return YY_S_MULTIMATERIAL; }

<s_material>diffuse{WS}					{ yy_pop_state(); yy_push_state(s_diffuse); return YY_S_DIFFUSE; }
<s_multimaterial>diffuse{WS}			{                 yy_push_state(s_diffuse); return YY_S_DIFFUSE; }

<s_material>indirect{WS}diffuse{WS}		{ yy_pop_state(); yy_push_state(s_indirectdiffuse); return YY_S_INDIRECT_DIFFUSE; }
<s_multimaterial>indirect{WS}diffuse{WS} {                yy_push_state(s_indirectdiffuse); return YY_S_INDIRECT_DIFFUSE; }

<s_material>phong{WS}					{ yy_pop_state(); yy_push_state(s_phong); return YY_S_PHONG; }
<s_multimaterial>phong{WS}				{                 yy_push_state(s_phong); return YY_S_PHONG; }

<s_material>stone{WS}					{ yy_pop_state(); yy_push_state(s_stone); return YY_S_STONE; }
<s_multimaterial>stone{WS}				{                 yy_push_state(s_stone); return YY_S_STONE; }

<s_material>stonebump{WS}				{ yy_pop_state(); yy_push_state(s_stonebump); return YY_S_STONEBUMP; }
<s_multimaterial>stonebump{WS}			{                 yy_push_state(s_stonebump); return YY_S_STONEBUMP; }

<s_material>reflective{WS}				{ yy_pop_state(); yy_push_state(s_reflective); return YY_S_REFLECTIVE; }
<s_multimaterial>reflective{WS}			{                 yy_push_state(s_reflective); return YY_S_REFLECTIVE; }

<s_material>refractive{WS}				{ yy_pop_state(); yy_push_state(s_refractive); return YY_S_REFRACTIVE; }
<s_multimaterial>refractive{WS}			{                 yy_push_state(s_refractive); return YY_S_REFRACTIVE; }

<s_diffuse>color{WS}					{ return YY_COLOR; }
<s_diffuse>weight{WS}					{ return YY_WEIGHT; }
<s_indirectdiffuse>weight{WS}			{ return YY_WEIGHT; }
<s_multimaterial>ambient{WS}			{ return YY_AMBIENT; }
<s_phong>color{WS}						{ return YY_COLOR; }
<s_phong>n{WS}							{ return YY_N; }
<s_phong>weight{WS}						{ return YY_WEIGHT; }
<s_reflective>weight{WS}				{ return YY_WEIGHT; }
<s_refractive>ior{WS}					{ return YY_IOR; }
<s_refractive>weight{WS}				{ return YY_WEIGHT; }
<s_stone>color{WS}A{WS}					{ return YY_COLOR_A; }
<s_stone>color{WS}B{WS}					{ return YY_COLOR_B; }
<s_stone>weight{WS}						{ return YY_WEIGHT; }
<s_stonebump>amplitude{WS}				{ return YY_AMPLITUDE; }
<s_stonebump>weight{WS}					{ return YY_WEIGHT; }


<INITIAL>sphere{WS}						{ yy_push_state(s_sphere); return YY_S_SPHERE; }
<s_sphere>center{WS}					{ return YY_CENTER; }
<s_sphere>radius{WS}					{ return YY_RADIUS; }

<INITIAL>blpatch{WS}					{ yy_push_state(s_blpatch); return YY_S_BLPATCH; }
<s_blpatch>p00{WS}						{ return YY_P00; }
<s_blpatch>p01{WS}						{ return YY_P01; }
<s_blpatch>p10{WS}						{ return YY_P10; }
<s_blpatch>p11{WS}						{ return YY_P11; }
<s_blpatch>u{WS}constraint{WS}          { return YY_U_CONSTRAINT; }
<s_blpatch>v{WS}constraint{WS}          { return YY_V_CONSTRAINT; }

<INITIAL>matrix{WS}						{ yy_push_state(s_matrix); return YY_S_MATRIX; }
<s_matrix>push{WS}						{ return YY_PUSH; }
<s_matrix>pop{WS}						{ return YY_POP; }
<s_matrix>set{WS}identity{WS}			{ return YY_SET_IDENTITY; }
<s_matrix>rotate{WS}					{ return YY_ROTATE; }
<s_matrix>translate{WS}					{ return YY_TRANSLATE; }
<s_matrix>scale{WS}						{ return YY_SCALE; }

<*>{STRING} 							{ yylval.str = _strdup(yytext); return YY_STRING; }
<*>{INT}{WS}							{ yylval.integer = atoi(yytext); return YY_PARSE_INT; }
<*>{REAL}{WS}							{ yylval.real = (float)atof(yytext); return YY_REAL; }

<*>[ ,\t\r]+							// eat up whitespace
<*>{COMMENT}							// eat up comments 
.										{ printf("\nParse error #%d line %d near: %s\n", ++yyerr, yyline, yytext); }

%%
