%{
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <stdlib.h>
#include <math.h>
#include <stack>
#include <map>
#include <string>
#include <iostream>
//#include "rawray/object.h"
//#include "rawray/light.h"
//#include "rawray/camera.h"
//#include "math/vector3.h"

#ifdef _DEBUG
#define YYDEBUG 1
#endif

#define yyerror(x) Fatal( "Parser error on line %d: %s\n", yyline, x ); 

extern int yylex();
extern int yyline;
extern FILE *yyin, *yyout;

// variables for adding objects, keeping track of variables
//std::map<std::string, Object*> g_objectMap;
//rawray::Object* g_object = NULL;
//rawray::Light* g_light = NULL;
//rawray::Camera* g_camera = NULL;

%}
// BISON Declarations

%union
{
    float real;
    int integer;
    char* str;
}

/* ----------------------- tokens ------------------------*/
%token <real>  YY_SYM_REAL
%token <integer>  YY_SYM_INT 
%token <str>  YY_SYM_STRING

%token YY_STATE_GLOBAL
%token YY_SYM_GLOBAL_WIDTH
%token YY_SYM_GLOBAL_HEIGHT
%token YY_SYM_GLOBAL_GL_BG
%token YY_SYM_GLOBAL_IMG_BG

%token YY_STATE_CAMERA
%token YY_SYM_CAMERA_POS
%token YY_SYM_CAMERA_VIEW_DIR
%token YY_SYM_CAMERA_LOOK_AT
%token YY_SYM_CAMERA_UP
%token YY_SYM_CAMERA_FOV

%token YY_STATE_LIGHT
%token YY_SYM_LIGHT_POINTLIGHT
%token YY_SYM_LIGHT_POS
%token YY_SYM_LIGHT_COLOR
%token YY_SYM_LIGHT_WATTAGE

%token YY_STATE_MODEL
%token YY_SYM_MODEL_LOAD

%token YY_STATE_SPHERE
%token YY_SYM_SPHERE_POS
%token YY_SYM_SPHERE_RADIUS
%token YY_SYM_SPHERE_COLOR

%token YY_MATH_COS
%token YY_MATH_SIN
%token YY_MATH_TAN
%token YY_MATH_ACOS
%token YY_MATH_ASIN
%token YY_MATH_ATAN
%token YY_MATH_LN
%token YY_MATH_LOG
%token YY_MATH_EXP
%token YY_MATH_SQRT
%token YY_MATH_E
%token YY_MATH_PI

%right '='
%left '-' '+'
%left '*' '/' // multiplication or cross product
%left NEG     // Negation--unary minus
%right '^'

%type <real> rExp fExp constantExp
%type <integer> iExp 

%%
input:  /* empty */
        | input block
;

block:    YY_STATE_GLOBAL '{' globalOptions '}'
        | YY_STATE_CAMERA '{' cameraOptions '}'
        | objectTypes 
        | YY_STATE_LIGHT lightTypes '}' { printf( "Adding Light\n" ); /*g_pScene->AddLight(pLight); pLight = 0;*/ }
;

objectTypes:
	| YY_STATE_MODEL '{'
            {
                //pObj = new TriangleMesh;
                //pObj->SetMaterial (pMat);
            }
          meshOptions '}'
            {
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            }

	| YY_STATE_SPHERE '{'
            {
                //pObj = new Sphere;
                //pObj->SetMaterial (pMat);
            }
          sphereOptions '}'
            {
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            }
;

sphereOptions: /* empty */
        | YY_SYM_SPHERE_POS rExp ',' rExp ',' rExp sphereOptions
            { printf( "Sphere Pos: %d, %d, %d\n", $2, $4, $6 ); }
        | YY_SYM_SPHERE_RADIUS rExp sphereOptions
            { printf( "Sphere Radius: %d\n", $2 ); }
;

lightTypes: YY_SYM_LIGHT_POINTLIGHT '{' { printf( "Creating Light\n" ); /*g_light = new rawray::Light();*/ } lightOptions
;

lightOptions: /* empty */ 
        | YY_SYM_LIGHT_POS rExp ',' rExp ',' rExp lightOptions
            { printf( "Light Pos: %d %d %d\n", $2, $4, $6 ); }
        | YY_SYM_LIGHT_WATTAGE rExp lightOptions
            { printf( "Light Wattage: %d\n", $2 ); }
        | YY_SYM_LIGHT_COLOR rExp ',' rExp ',' rExp lightOptions
            { printf( "Light Color: %d %d %d\n", $2, $4, $6 ); }
;


meshOptions: /* empty */
        | YY_SYM_MODEL_LOAD YY_SYM_STRING
            {
                // Remove quotes
                $2[strlen($2)-1]=0;
                char* s = &$2[1];
                
                printf( "Loading Mesh: %s", s );
                //if (!((TriangleMesh*)pObj)->Load(s, GetCTM()))
                    //pObj = 0;
                delete [] $2;
            }
;

globalOptions: /* empty */
        | YY_SYM_GLOBAL_HEIGHT iExp globalOptions
            { printf( "Found height=%d", $2); }
        | YY_SYM_GLOBAL_WIDTH iExp globalOptions
            { printf( "Found width=%d", $2); }
        | YY_SYM_GLOBAL_GL_BG rExp ',' rExp ',' rExp globalOptions
            { printf( "Found GL BG=%d, %d, %d", $2, $4, $6); }
        | YY_SYM_GLOBAL_IMG_BG rExp ',' rExp ',' rExp globalOptions
            { printf( "Found IMG BG=%d, %d, %d", $2, $4, $6); }
;

cameraOptions: /* empty */
        | YY_SYM_CAMERA_POS rExp ',' rExp ',' rExp cameraOptions
            { printf( "Camera Eye: %d, %d, %d", $2, $4, $6 ); }
        | YY_SYM_CAMERA_VIEW_DIR rExp ',' rExp ',' rExp cameraOptions
            { printf( "Camera View: %d, %d, %d", $2, $4, $6 ); }
        | YY_SYM_CAMERA_LOOK_AT rExp ',' rExp ',' rExp cameraOptions
            { printf( "Camera LookAt: %d, %d, %d", $2, $4, $6 ); }
        | YY_SYM_CAMERA_UP rExp ',' rExp ',' rExp cameraOptions
            { printf( "Camera Up: %d, %d, %d", $2, $4, $6 ); }
        | YY_SYM_CAMERA_FOV rExp cameraOptions
            { printf( "Camera FOV: %d", $2 ); }
;

rExp:     YY_SYM_REAL          { $$ = $1; }
        | iExp                 { $$ = $1; }
        | fExp                 { $$ = $1; }
        
        | rExp '+' rExp        { $$ = $1 + $3; }
        | iExp '+' rExp        { $$ = $1 + $3; }
        | rExp '+' iExp        { $$ = $1 + $3; }
        
        | rExp '-' rExp        { $$ = $1 - $3; }
        | iExp '-' rExp        { $$ = $1 - $3; }
        | rExp '-' iExp        { $$ = $1 - $3; }
        
        | rExp '*' rExp        { $$ = $1 * $3; }
        | iExp '*' rExp        { $$ = $1 * $3; }
        | rExp '*' iExp        { $$ = $1 * $3; }
        
        | rExp '/' rExp        { $$ = $1 / $3; }
        | iExp '/' rExp        { $$ = $1 / $3; }
        | rExp '/' iExp        { $$ = $1 / $3; }
        
        | rExp '^' rExp        { $$ = pow (float ($1), float ($3)); }
        | iExp '^' rExp        { $$ = pow (float ($1), float ($3)); }
        | rExp '^' iExp        { $$ = pow (float ($1), float ($3)); }
        
        | '-' rExp  %prec NEG  { $$ = -$2; }
        | '(' rExp ')'         { $$ = $2; }
        | constantExp
;

fExp:      YY_MATH_SIN '(' rExp ')'     {$$ = sin($3); }
        |  YY_MATH_COS '(' rExp ')'     {$$ = cos($3); }
        |  YY_MATH_TAN '(' rExp ')'     {$$ = tan($3); }
        |  YY_MATH_ASIN '(' rExp ')'    {$$ = asin($3); }
        |  YY_MATH_ACOS '(' rExp ')'    {$$ = acos($3); }
        |  YY_MATH_ATAN '(' rExp ')'    {$$ = atan($3); }
        |  YY_MATH_LN '(' rExp ')'      {$$ = log($3); }
        |  YY_MATH_LOG '(' rExp ')'     {$$ = log10($3); }
        |  YY_MATH_EXP '(' rExp ')'     {$$ = exp($3); }
        |  YY_MATH_SQRT '(' rExp ')'    {$$ = sqrt($3); }
;

constantExp:
           YY_MATH_E { $$ = 2.718281828459; }
        |  YY_MATH_PI { $$ = PI; }
;

iExp:     YY_SYM_INT            { $$ = $1; }
        | iExp '+' iExp         { $$ = $1 + $3; }
        | iExp '-' iExp         { $$ = $1 - $3; }
        | iExp '*' iExp         { $$ = $1 * $3; }
        | iExp '/' iExp         { $$ = $1 / $3; }
        | '-' iExp  %prec NEG   { $$ = -$2; }
        | iExp '^' iExp         { $$ = (int)pow ($1, $3); }
        | '(' iExp ')'          { $$ = $2; }
;

// End of grammar

%%

//Additional C code
