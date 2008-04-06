%{
#ifdef WIN32
#pragma warning(disable:4244) // smaller type conversion warnings
#pragma warning(disable:4701) // variable used without being initialized
#endif

#include "parser.h"
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <stack>
#include <queue>
#include <map>
#include <string>
#include <iostream>
#include "math/vector3.h"
#include "math/matrix4x4.h"
#include "rawray/object.h"
#include "rawray/material.h"
#include "rawray/light.h"
#include "rawray/options.h"

//#define YYDEBUG 1

#define yyerror(x) printf("Parser error on line %d: %s\n", yyline, x); 

extern int yylex();
extern int yyline;
extern FILE *yyin, *yyout;


// variables for adding objects, keeping track of variables
rawray::Object*                         g_obj = NULL;
rawray::Material*                       g_material = NULL;
rawray::Light*                          g_light = NULL;
math::Vector3                           g_vector;
std::map<std::string, rawray::Object*>  g_objectMap;
//std::stack<Matrix4x4>                 g_matrixStack;


%}
// BISON Declarations
%union
{
    float real;
    int integer;
    char* str;
}

/* ----------------------- tokens ------------------------*/

%token <real>       REAL
%token <integer>    PARSE_INT 
%token <str>        STRING

%token PARSE_TRUE
%token PARSE_FALSE
%token ENABLE
%token DISABLE
%token MATH_COS
%token MATH_SIN
%token MATH_TAN
%token MATH_ACOS
%token MATH_ASIN
%token MATH_ATAN
%token MATH_ATAN2
%token MATH_LN
%token MATH_LOG
%token MATH_EXP
%token MATH_SQRT
%token MATH_E
%token MATH_PI

%token GLOBAL
%token WIDTH
%token HEIGHT
%token POS
%token IMG_BGCOLOR
%token GL_BGCOLOR
%token GL_SPHERE_SECTIONS
%token NUM_THREADS
%token RENDER_X_BLOCK
%token RENDER_Y_BLOCK
%token RENDER_HANDLER_SLEEP
%token RENDER_THREAD_SLEEP
%token RENDER_SPINLOCK_SLEEP
%token GAUSSIAN_BLUR_MAX
%token GAUSSIAN_BLUR_SIGMA

%token CAMERA
%token POS
%token DIR
%token LOOKAT
%token UP
%token FOV

%token P0
%token SPIRAL_NUM_SPHERES
%token SPIRAL_RADIUS
%token LORENZ_DT
%token LORENZ_MIN_DISTANCE
%token LORENZ_MAX_DISTANCE
%token LORENZ_SIGMA
%token LORENZ_RHO
%token LORENZ_BETA
%token LORENZ_RADIUS
%token LORENZ_NUM_SPHERES
%token LORENZ_START

%token TRIANGLE
%token V1
%token V2
%token V3
%token N1
%token N2
%token N3

%token MESH
%token LOAD

%token INSTANCE
%token GEOMETRY

%token PUSHMATRIX
%token POPMATRIX
%token ROTATE
%token TRANSLATE
%token SCALE

%token LIGHT
%token POINTLIGHT
%token WATTAGE
%token COLOR

%token SPHERE
%token CENTER
%token RADIUS

// add more tokens here!

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

block:    GLOBAL '{' globalOptions '}'
        | CAMERA '{' cameraOptions '}'
        | LIGHT lightTypes '}'          { printf( "Adding Light\n" ); }
        | P0 '{' p0Options '}'
        | objectTypes 
        | transform
;

objectTypes:
          TRIANGLE '{'
            {
                printf( "Creating Triangle\n" );
                //pObj = new Triangle;
                //pObj->SetMaterial (pMat);
                //((TriangleMesh*)pObj)->CreateSingleTriangle();
            }
          triangleOptions '}'
            {
                printf( "Adding Triangle to Scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            }

        | TRIANGLE STRING '{'
            {
                printf( "Creating named triangle '%s'\n", $2 );
                //pObj = new TriangleMesh;
                //pObj->SetMaterial (pMat);
                //g_objectMap[$2] = pObj;
                //((TriangleMesh*)pObj)->CreateSingleTriangle();
            }
          triangleOptions '}'
            {
                printf( "Adding named Triangle to Scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            }

            
	| MESH '{'
            {
                printf( "Creating new mesh\n" );
                //pObj = new TriangleMesh;
                //pObj->SetMaterial (pMat);
            }
          meshOptions '}'
            {
                printf( "Adding mesh to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            }
            
	| MESH STRING '{'
            {
                printf( "Creating new named mesh '%s'\n", $2 );
                //pObj = new TriangleMesh;
                //pObj->SetMaterial (pMat);
                //g_objectMap[$2] = pObj;
            }
          meshOptions '}'
            {
                printf( "Adding named mesh to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            }
            

	| SPHERE '{'
            {
                printf( "Creating new sphere\n" );
                //pObj = new Sphere;
                //pObj->SetMaterial (pMat);
            }
          sphereOptions '}'
            {
                printf( "Adding sphere to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            }
            
	| SPHERE STRING '{'
            {
                printf( "Creating new sphere named '%s'\n", $2 );
                //pObj = new Sphere;
                //pObj->SetMaterial (pMat);
                //g_objectMap[$2] = pObj;
            }
          sphereOptions '}'
            {
                printf( "Adding sphere to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            }
            

	| INSTANCE '{'
            {
                printf( "Creating new instance\n" );
                //pObj = new Instance;
                //pObj->SetMaterial (pMat);
            }
          instanceOptions '}'
            {
                printf( "Adding instance to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            }
            
	| INSTANCE STRING '{'
            {
                printf( "Creating new named instance '%s'\n", $2 );
                //pObj = new Instance;
                //pObj->SetMaterial (pMat);
                //g_objectMap[$2] = pObj;
            }
          instanceOptions '}'
            {
                printf( "Adding named instance to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            }
;

triangleOptions: /* empty */
        | V1 rExp ',' rExp ',' rExp triangleOptions
            { /*((TriangleMesh*)pObj)->SetV1(Vertex3($2, $4, $6));*/ }
        | V2 rExp ',' rExp ',' rExp triangleOptions
            {  }
        | V3 rExp ',' rExp ',' rExp triangleOptions
            {  }
        | N1 rExp ',' rExp ',' rExp triangleOptions
            {  }
        | N2 rExp ',' rExp ',' rExp triangleOptions
            {  }
        | N3 rExp ',' rExp ',' rExp triangleOptions
            {  }
;

sphereOptions: /* empty */
        | CENTER rExp ',' rExp ',' rExp sphereOptions
            {  }
        | RADIUS rExp sphereOptions
            {  }
;

instanceOptions: /* empty */
        | GEOMETRY STRING sphereOptions
            {
                //std::map<std::string, Object*>::const_iterator it = g_objectMap.find ($2);
                //if (it != g_objectMap.end ())
                //{
                    //((Instance*)pObj)->SetGeometry(it->second, GetCTM());
                //}
            }
;

transform:  PUSHMATRIX { /*PushMatrix();*/ }
        | POPMATRIX
            { /*PopMatrix();*/ }
        | ROTATE rExp ',' rExp ',' rExp ',' rExp
            { /*Rotate($2, $4, $6, $8);*/ }
        | TRANSLATE rExp ',' rExp ',' rExp
            { /*Translate($2, $4, $6);*/ }
        | SCALE rExp ',' rExp ',' rExp
            { /*Scale($2, $4, $6);*/ }
;

lightTypes: POINTLIGHT '{' { /*pLight = new PointLight;*/ } lightOptions
;

lightOptions: /* empty */ 
        | POS rExp ',' rExp ',' rExp lightOptions
            { /*pLight->SetPosition(Vertex3($2, $4, $6));*/ }
        | WATTAGE rExp lightOptions
            { /*pLight->SetWattage($2);*/ }
        | COLOR rExp ',' rExp ',' rExp lightOptions
            { /*pLight->SetColor(Vector3($2, $4, $6));*/ }
;


meshOptions: /* empty */
        | LOAD STRING
            {
                $2[strlen($2)-1]=0;
                printf( "Load Mesh: '%s'\n", $2+1 );
                //if (!((TriangleMesh*)pObj)->Load(s, GetCTM()))
                    //pObj = 0;
            }
;

globalOptions: /* empty */
        | HEIGHT iExp globalOptions
            { rawray::options::global::win_height = $2; }
        | WIDTH iExp globalOptions
            { rawray::options::global::win_width = $2; }
        | GL_BGCOLOR rExp ',' rExp ',' rExp globalOptions
            { rawray::options::global::gl_bg_color = math::Vector3($2,$4,$6); }
        | IMG_BGCOLOR rExp ',' rExp ',' rExp globalOptions
            { rawray::options::global::img_bg_color = math::Vector3($2,$4,$6); }
        | GL_SPHERE_SECTIONS iExp globalOptions
            { rawray::options::global::gl_sphere_sections = $2; }
        | NUM_THREADS iExp globalOptions
            { rawray::options::global::num_threads = $2; }
        | RENDER_X_BLOCK iExp globalOptions
            { rawray::options::global::render_x_block = $2; }
        | RENDER_Y_BLOCK iExp globalOptions
            { rawray::options::global::render_y_block = $2; }
        | RENDER_HANDLER_SLEEP iExp globalOptions
            { rawray::options::global::render_handler_sleep = $2; }
        | RENDER_THREAD_SLEEP iExp globalOptions
            { rawray::options::global::render_thread_sleep = $2; }
        | RENDER_SPINLOCK_SLEEP iExp globalOptions
            { rawray::options::global::render_spinlock_sleep = $2; }
        | GAUSSIAN_BLUR_MAX iExp globalOptions
            { rawray::options::global::gaussian_blur_max = $2; }
        | GAUSSIAN_BLUR_SIGMA iExp globalOptions
            { rawray::options::global::gaussian_blur_sigma = $2; }
;

cameraOptions: /* empty */
        | POS rExp ',' rExp ',' rExp cameraOptions
            { rawray::options::camera::eye = math::Vector3($2,$4,$6); }
        | DIR rExp ',' rExp ',' rExp cameraOptions
            { rawray::options::camera::view = math::Vector3($2,$4,$6); }
        | LOOKAT rExp ',' rExp ',' rExp cameraOptions
            { rawray::options::camera::lookat = math::Vector3($2,$4,$6); }
        | UP rExp ',' rExp ',' rExp cameraOptions
            { rawray::options::camera::up = math::Vector3($2,$4,$6); }
        | FOV rExp cameraOptions
            { rawray::options::camera::fov = $2; }
;

p0Options: /* empty */
        | SPIRAL_NUM_SPHERES iExp p0Options
            { rawray::options::p0::spiral_num_spheres = $2; }
        | SPIRAL_RADIUS rExp p0Options
            { rawray::options::p0::spiral_radius = $2; }
        | LORENZ_DT rExp p0Options
            { rawray::options::p0::lorenz_dt = $2; }
        | LORENZ_MIN_DISTANCE rExp p0Options
            { rawray::options::p0::lorenz_min_distance = $2; }
        | LORENZ_MAX_DISTANCE rExp p0Options
            { rawray::options::p0::lorenz_max_distance = $2; }
        | LORENZ_SIGMA rExp p0Options
            { rawray::options::p0::lorenz_sigma = $2; }
        | LORENZ_RHO rExp p0Options
            { rawray::options::p0::lorenz_rho = $2; }
        | LORENZ_BETA rExp p0Options
            { rawray::options::p0::lorenz_beta = $2; }
        | LORENZ_RADIUS rExp p0Options
            { rawray::options::p0::lorenz_radius = $2; }
        | LORENZ_NUM_SPHERES iExp p0Options
            { rawray::options::p0::lorenz_num_spheres = $2; }
        | LORENZ_START rExp ',' rExp ',' rExp p0Options
            { rawray::options::p0::lorenz_start = math::Vector3($2,$4,$6); }
;

rExp:     REAL                 { $$ = $1; }
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

fExp:      MATH_SIN '(' rExp ')'    {$$ = sin($3); }
        |  MATH_COS '(' rExp ')'    {$$ = cos($3); }
        |  MATH_TAN '(' rExp ')'    {$$ = tan($3); }
        |  MATH_ASIN '(' rExp ')'   {$$ = asin($3); }
        |  MATH_ACOS '(' rExp ')'   {$$ = acos($3); }
        |  MATH_ATAN '(' rExp ')'   {$$ = atan($3); }
        |  MATH_LN '(' rExp ')'     {$$ = log($3); }
        |  MATH_LOG '(' rExp ')'    {$$ = log10($3); }
        |  MATH_EXP '(' rExp ')'    {$$ = exp($3); }
        |  MATH_SQRT '(' rExp ')'   {$$ = sqrt($3); }
;

constantExp:
           MATH_E { $$ = 2.718281828459f; }
        |  MATH_PI { $$ = 3.141592653589793f; }
;

iExp:     PARSE_INT             { $$ = $1; }
        | iExp '+' iExp         { $$ = $1 + $3; }
        | iExp '-' iExp         { $$ = $1 - $3; }
        | iExp '*' iExp         { $$ = $1 * $3; }
        | iExp '/' iExp         { $$ = $1 / $3; }
        | '-' iExp  %prec NEG   { $$ = -$2; }
        | iExp '^' iExp         { $$ = (int)pow((float)$1, (float)$3); }
        | '(' iExp ')'          { $$ = $2; }
;

// End of grammar
%%
//Additional C code


namespace rawray {

void ConfigParser(const char* filename) {
    // yydebug = 1;
    
    yyin = fopen( filename, "r" );
    if( yyin )
        yyparse();
        
    fclose( yyin );
}

} // namespace rawray
