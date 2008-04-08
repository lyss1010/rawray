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
#include "object.h"
#include "material.h"
#include "light.h"
#include "options.h"
#include "scene.h"
#include "camera.h"
#include "image.h"
#include "triangle.h"
#include "triangle_mesh.h"
#include "sphere.h"

#define YYDEBUG 1

#define yyerror(x) printf("Parser error on line %d: %s\n", yyline, x); 

extern int yylex();
extern int yyline;
extern FILE *yyin, *yyout;


// variables for adding objects, keeping track of variables
rawray::Camera*                         g_camera = NULL;
rawray::Scene*                          g_scene = NULL;
rawray::Image*                          g_image = NULL;

rawray::Object*                         g_obj = NULL;
rawray::Material*                       g_material = NULL;
rawray::Light*                          g_light = NULL;
rawray::TriangleMesh*                   g_mesh = NULL;

math::Vector3                           g_vector;
std::map<std::string, rawray::Object*>  g_objectMap;
std::stack<math::Matrix4x4>             g_matrixStack;

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

%token GL_RENDER_LIGHTS
%token HEADLESS

%token CAMERA
%token POS
%token DIR
%token LOOKAT
%token UP
%token FOV
%token ASPECT
%token MIN_DRAW
%token MAX_DRAW

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

block:    GLOBAL '{' globalOptions '}'  { memmove( &yyval, &yyval, sizeof(yyval) ); printf("\n"); }
        | CAMERA '{' cameraOptions '}'  { printf("\n"); }
        | LIGHT lightTypes '}'          { printf("\n"); g_scene->AddLight( g_light ); g_light = NULL; }
        | P0 '{' p0Options '}'          { printf("\n"); }
        | objectTypes                   { printf("\n"); }
        | transform                     { printf("\n"); }
;

objectTypes:
          TRIANGLE '{'
            {
                g_mesh = new rawray::TriangleMesh();
                #ifdef VERBOSE_NEW
                printf( "MESH: %x", g_mesh );
                #endif
                //((TriangleMesh*)pObj)->CreateSingleTriangle();
            }
          triangleOptions '}'
            {
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            }

        | TRIANGLE STRING '{'
            {
                g_mesh = new rawray::TriangleMesh();
                #ifdef VERBOSE_NEW
                printf( "MESH: %x", g_mesh );
                #endif
                
                //g_objectMap[$2] = pObj;
                //((TriangleMesh*)pObj)->CreateSingleTriangle();
            }
          triangleOptions '}'
            {
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            }
            
	| MESH '{'
            {
                g_mesh = new rawray::TriangleMesh();
                #ifdef VERBOSE_NEW
                printf( "MESH: %x", g_mesh );
                #endif
            }
          meshOptions '}'
            {
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            }
            
	| MESH STRING '{'
            {
                g_mesh = new rawray::TriangleMesh();
                #ifdef VERBOSE_NEW
                printf( "MESH: %x", g_mesh );
                #endif
                
                //g_objectMap[$2] = pObj;
            }
          meshOptions '}'
            {
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            }

	| SPHERE '{'
            {
                g_obj = new rawray::Sphere( math::Vector3(0),
                                            1.0f,
                                            g_material );
                                            
                #ifdef VERBOSE_NEW
                printf( "SPHERE: %x", g_obj );
                #endif
            }
          sphereOptions '}'
            {
                g_scene->AddObject( g_obj );
                g_obj = NULL;
            }
            
	| SPHERE STRING '{'
            {
                g_obj = new rawray::Sphere( math::Vector3(0),
                                            1.0f,
                                            g_material );
                
                #ifdef VERBOSE_NEW
                printf( "SPHERE: %x", g_obj );
                #endif
                
                g_objectMap[$2] = g_obj;
            }
          sphereOptions '}'
            {
                g_scene->AddObject( g_obj );
                g_obj = NULL;
            }

	| INSTANCE '{'
            {
                printf( "Instance not supported\n" );
            }
          instanceOptions '}'
            {
            }
            
	| INSTANCE STRING '{'
            {
                printf( "Named Instance not supported\n" );
            }
          instanceOptions '}'
            {
            }
;

triangleOptions: /* empty */
        | V1 rExp ',' rExp ',' rExp triangleOptions
            { printf( "Triangles not supported" ); }
        | V2 rExp ',' rExp ',' rExp triangleOptions
            { printf( "Triangles not supported" ); }
        | V3 rExp ',' rExp ',' rExp triangleOptions
            { printf( "Triangles not supported" ); }
        | N1 rExp ',' rExp ',' rExp triangleOptions
            { printf( "Triangles not supported" ); }
        | N2 rExp ',' rExp ',' rExp triangleOptions
            { printf( "Triangles not supported" ); }
        | N3 rExp ',' rExp ',' rExp triangleOptions
            { printf( "Triangles not supported" ); }
;

sphereOptions: /* empty */
        | CENTER rExp ',' rExp ',' rExp sphereOptions
            { ((rawray::Sphere*)g_obj)->SetCenter( math::Vector3($2,$4,$6) ); }
        | RADIUS rExp sphereOptions
            { ((rawray::Sphere*)g_obj)->SetRadius( $2 ); }
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

lightTypes: POINTLIGHT '{' 
            {
                printf( "new light\n" ); 
                g_light = new rawray::Light();
                
                #ifdef VERBOSE_NEW
                printf( "LIGHT: %x\n", g_light );
                #endif
            }
        lightOptions
                
;

lightOptions: /* empty */ 
        | POS rExp ',' rExp ',' rExp lightOptions
            { printf( "pos = %f, %f, %f\n", $2, $4, $6 ); g_light->SetPosition( math::Vector3($2,$4,$6) ); }
        | WATTAGE rExp lightOptions
            { printf( "wattage = %f\n", $2 ); g_light->SetWattage( $2 ); }
        | COLOR rExp ',' rExp ',' rExp lightOptions
            { printf( "color = %f, %f, %f\n", $2, $4, $6 ); g_light->SetColor( math::Vector3($2,$4,$6) ); }
;

meshOptions: /* empty */
        | LOAD STRING
            {
                $2[strlen($2)-1]=0;
                printf( "Loading Mesh: '%s'\n", $2+1 );
                g_mesh->LoadOBJ( $2+1 );
            }
;

globalOptions: /* empty */
        | HEIGHT iExp globalOptions
            { printf( "height = %d\n", $2 ); g_image->Resize( g_image->GetWidth(), rawray::options::global::win_height = $2 ); }
        | WIDTH iExp globalOptions
            { printf( "width = %d\n", $2 ); g_image->Resize( rawray::options::global::win_width = $2, g_image->GetHeight() ); }
        | GL_BGCOLOR rExp ',' rExp ',' rExp globalOptions
            { printf( "gl bg color = %f, %f, %f\n", $2, $4, $6 ); rawray::options::global::gl_bg_color = math::Vector3($2,$4,$6); }
        | IMG_BGCOLOR rExp ',' rExp ',' rExp globalOptions
            { printf( "img bg color = %f, %f, %f\n", $2, $4, $6 ); rawray::options::global::img_bg_color = math::Vector3($2,$4,$6); }
        | GL_SPHERE_SECTIONS iExp globalOptions
            { printf( "gl sphere sections = %d\n", rawray::options::global::gl_sphere_sections = $2 ); }
        | NUM_THREADS iExp globalOptions
            { printf( "num threads = %d\n", rawray::options::global::num_threads = $2 ); }
        | RENDER_X_BLOCK iExp globalOptions
            { printf( "render x block = %d\n", rawray::options::global::render_x_block = $2 ); }
        | RENDER_Y_BLOCK iExp globalOptions
            { printf( "render y block = %d\n", rawray::options::global::render_y_block = $2 ); }
        | RENDER_HANDLER_SLEEP iExp globalOptions
            { printf( "render handler sleep = %d\n", rawray::options::global::render_handler_sleep = $2 ); }
        | RENDER_THREAD_SLEEP iExp globalOptions
            { printf( "render thread sleep = %d\n", rawray::options::global::render_thread_sleep = $2 ); }
        | RENDER_SPINLOCK_SLEEP iExp globalOptions
            { printf( "render spinlock sleep = %d\n", rawray::options::global::render_spinlock_sleep = $2 ); }
        | GAUSSIAN_BLUR_MAX rExp globalOptions
            { printf( "gaussian blur max = %f\n", rawray::options::global::gaussian_blur_max = $2 ); }
        | GAUSSIAN_BLUR_SIGMA rExp globalOptions
            { printf( "gaussian blur sigma = %f\n", rawray::options::global::gaussian_blur_sigma = $2 ); }
        | ENABLE GL_RENDER_LIGHTS globalOptions
			{ printf( "enabling rendering of lights in gl\n" ); rawray::options::global::gl_render_lights = true; }
		| DISABLE GL_RENDER_LIGHTS globalOptions
			{ printf( "disabling rendering of lights in gl\n" ); rawray::options::global::gl_render_lights = false; }
		| ENABLE HEADLESS globalOptions
		    { printf( "enabling headless mode\n" ); rawray::options::global::headless = true; }
		| DISABLE HEADLESS globalOptions
		    { printf( "disabling headless mode\n" ); rawray::options::global::headless = false; }
;

cameraOptions: /* empty */
        | POS rExp ',' rExp ',' rExp cameraOptions
            { printf( "camera pos = %f, %f, %f\n", $2, $4, $6 ); g_camera->SetEye( rawray::options::camera::eye = math::Vector3($2,$4,$6) ); }
        | DIR rExp ',' rExp ',' rExp cameraOptions
            { printf( "camera dir = %f, %f, %f\n", $2, $4, $6 ); g_camera->SetViewDir( rawray::options::camera::view = math::Vector3($2,$4,$6) ); }
        | LOOKAT rExp ',' rExp ',' rExp cameraOptions
            { printf( "camera look at = %f, %f, %f\n", $2, $4, $6 ); g_camera->SetLookAt( rawray::options::camera::lookat = math::Vector3($2,$4,$6) ); }
        | UP rExp ',' rExp ',' rExp cameraOptions
            { printf( "camera up = %f, %f, %f\n", $2, $4, $6 ); g_camera->SetUp( rawray::options::camera::up = math::Vector3($2,$4,$6) ); }
        | FOV rExp cameraOptions
            { printf( "camera fov = %f\n", $2 ); g_camera->SetFOV( rawray::options::camera::fov = $2 ); }
        | ASPECT rExp cameraOptions
            { printf( "camera aspect ratio = %f\n", $2 ); g_camera->SetAspect( rawray::options::camera::aspect = $2 ); }
        | MIN_DRAW rExp cameraOptions
            { printf( "camera min draw = %f\n", $2 ); g_camera->SetMinDraw( rawray::options::camera::min_draw = $2 ); }
        | MAX_DRAW rExp cameraOptions
            { printf( "camera max draw = %f\n", $2 ); g_camera->SetMaxDraw( rawray::options::camera::max_draw = $2 ); }
;

p0Options: /* empty */
        | SPIRAL_NUM_SPHERES iExp p0Options
            { printf( "spiral num spheres = %d\n", rawray::options::p0::spiral_num_spheres = $2 ); }
        | SPIRAL_RADIUS rExp p0Options
            { printf( "spiral radius = %f\n", rawray::options::p0::spiral_radius = $2 ); }
        | LORENZ_DT rExp p0Options
            { printf( "lorenz dt = %f\n", rawray::options::p0::lorenz_dt = $2 ); }
        | LORENZ_MIN_DISTANCE rExp p0Options
            { printf( "lorenz min distance = %f\n", rawray::options::p0::lorenz_min_distance = $2 ); }
        | LORENZ_MAX_DISTANCE rExp p0Options
            { printf( "lorenz max distance = %f\n", rawray::options::p0::lorenz_max_distance = $2 ); }
        | LORENZ_SIGMA rExp p0Options
            { printf( "lorenz sigma = %f\n", rawray::options::p0::lorenz_sigma = $2 ); }
        | LORENZ_RHO rExp p0Options
            { printf( "lorenz rho = %f\n", rawray::options::p0::lorenz_rho = $2 ); }
        | LORENZ_BETA rExp p0Options
            { printf( "lorenz beta = %f\n", rawray::options::p0::lorenz_beta = $2 ); }
        | LORENZ_RADIUS rExp p0Options
            { printf( "lorenz radius = %f\n", rawray::options::p0::lorenz_radius = $2 ); }
        | LORENZ_NUM_SPHERES iExp p0Options
            { printf( "lorenz num spheres = %d\n", rawray::options::p0::lorenz_num_spheres = $2 ); }
        | LORENZ_START rExp ',' rExp ',' rExp p0Options
            { printf( "lorenz start = %f, %f, %f\n", $2, $4, $6 ); rawray::options::p0::lorenz_start = math::Vector3($2,$4,$6); }
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

void AddTrianglesOfMesh() {
    for( uint32 i=0; i<g_mesh->GetNumTriangles(); ++i ) {
        Triangle* t = new Triangle( *g_mesh, i, g_material );
        g_scene->AddObject( t );
        
        #ifdef VERBOSE_NEW
        printf( "TRIANGLE: %x\n", t );
        #endif
    }
    
    g_mesh = NULL;
}

void SetConfigSources(Scene* scene, Camera* cam, Image* img) {
    g_scene = scene;
    g_camera = cam;
    g_image = img;
}

bool ConfigParser(const char* filename) {
    yydebug = 1;
    
    if( !g_scene || !g_camera || !g_image )
        return false;
    
    yyin = fopen( filename, "r" );
    if( !yyin )
        return false;

    yyparse();
    fclose( yyin );

    printf( "Parse of '%s' success\n", filename );
    return true;
}

} // namespace rawray
