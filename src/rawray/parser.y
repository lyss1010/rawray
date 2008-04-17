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
#include "lambert.h"
#include "light.h"
#include "options.h"
#include "scene.h"
#include "camera.h"
#include "image.h"
#include "triangle_factory.h"
#include "sphere.h"
#include "bl_patch.h"

//#define YYDEBUG 1

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

%token <real>       YY_REAL
%token <integer>    YY_PARSE_INT 
%token <str>        YY_STRING

%token YY_PARSE_TRUE
%token YY_PARSE_FALSE
%token YY_ENABLE
%token YY_DISABLE
%token YY_MATH_COS
%token YY_MATH_SIN
%token YY_MATH_TAN
%token YY_MATH_ACOS
%token YY_MATH_ASIN
%token YY_MATH_ATAN
%token YY_MATH_ATAN2
%token YY_MATH_LN
%token YY_MATH_LOG
%token YY_MATH_EXP
%token YY_MATH_SQRT
%token YY_MATH_E
%token YY_MATH_PI

%token YY_GLOBAL
%token YY_WIDTH
%token YY_HEIGHT
%token YY_POS
%token YY_IMG_BGCOLOR
%token YY_IMG_FGCOLOR
%token YY_GL_BGCOLOR
%token YY_GL_SPHERE_SECTIONS
%token YY_NUM_THREADS
%token YY_RENDER_X_BLOCK
%token YY_RENDER_Y_BLOCK
%token YY_RENDER_HANDLER_SLEEP
%token YY_RENDER_THREAD_SLEEP
%token YY_RENDER_SPINLOCK_SLEEP
%token YY_GAUSSIAN_BLUR_MAX
%token YY_GAUSSIAN_BLUR_SIGMA
%token YY_TRIANGLE_TEST
%token YY_BARYCENTRIC
%token YY_PROJECTION
%token YY_PLUCKER
%token YY_MOLLER

%token YY_GL_RENDER_LIGHTS
%token YY_HEADLESS

%token YY_CAMERA
%token YY_POS
%token YY_DIR
%token YY_LOOKAT
%token YY_UP
%token YY_FOV
%token YY_ASPECT
%token YY_MIN_DRAW
%token YY_MAX_DRAW

%token YY_P0
%token YY_SPIRAL_NUM_SPHERES
%token YY_SPIRAL_RADIUS
%token YY_LORENZ_DT
%token YY_LORENZ_MIN_DISTANCE
%token YY_LORENZ_MAX_DISTANCE
%token YY_LORENZ_SIGMA
%token YY_LORENZ_RHO
%token YY_LORENZ_BETA
%token YY_LORENZ_RADIUS
%token YY_LORENZ_NUM_SPHERES
%token YY_LORENZ_START

%token YY_TRIANGLE
%token YY_V1
%token YY_V2
%token YY_V3
%token YY_N1
%token YY_N2
%token YY_N3

%token YY_MESH
%token YY_LOAD

%token YY_INSTANCE
%token YY_GEOMETRY

%token YY_PUSHMATRIX
%token YY_POPMATRIX
%token YY_ROTATE
%token YY_TRANSLATE
%token YY_SCALE

%token YY_LIGHT
%token YY_POINTLIGHT
%token YY_WATTAGE
%token YY_COLOR

%token YY_MATERIAL
%token YY_LAMBERT
%token YY_DIFFUSE
%token YY_AMBIENT

%token YY_SPHERE
%token YY_CENTER
%token YY_RADIUS

%token YY_BLPATCH
%token YY_P00
%token YY_P01
%token YY_P10
%token YY_P11


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

block:    YY_GLOBAL '{' globalOptions '}'   { memmove( &yyval, &yyval, sizeof(yyval) ); printf("\n"); }
        | YY_CAMERA '{' cameraOptions '}'   { printf("\n"); }
        | YY_LIGHT lightTypes '}'           { printf("\n"); g_scene->AddLight( g_light ); g_light = NULL; }
        | YY_MATERIAL materialTypes '}'     { printf("\n"); g_scene->AddMaterial( g_material ); }
        | YY_P0 '{' p0Options '}'           { printf("\n"); }
        | objectTypes                       { printf("\n"); }
        | transform                         { printf("\n"); }
;

objectTypes:
        YY_TRIANGLE '{'
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

        | YY_TRIANGLE YY_STRING '{'
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
            
	    | YY_MESH '{'
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
            
	    | YY_MESH YY_STRING '{'
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

	    | YY_SPHERE '{'
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
            
	    | YY_SPHERE YY_STRING '{'
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
            
        | YY_BLPATCH '{'
            {
                g_obj = new rawray::BLPatch( g_material );
                                             
                #ifdef VERBOSE_NEW
                printf( "BLPATCH: %d", g_obj );
                #endif
            }
        blPatchOptions '}'
            {
                g_scene->AddObject( g_obj );
                g_obj = NULL;
            }
            
        | YY_BLPATCH YY_STRING '{'
            {
                g_obj = new rawray::BLPatch( g_material );
                #ifdef VERBOSE_NEW
                printf( "BLPATCH: %d", g_obj );
                #endif
                
                g_objectMap[$2] = g_obj;
            }
        blPatchOptions '}'
            {
                g_scene->AddObject( g_obj );
                g_obj = NULL;
            }
/*
	    | YY_INSTANCE '{'
            {
                printf( "Instance not supported\n" );
            }
          instanceOptions '}'
            {
            }
            
	    | YY_INSTANCE YY_STRING '{'
            {
                printf( "Named Instance not supported\n" );
            }
          instanceOptions '}'
            {
            }
            
*/
;

triangleOptions: /* empty */
        | YY_V1 rExp ',' rExp ',' rExp triangleOptions
            { printf( "Triangles not supported" ); }
        | YY_V2 rExp ',' rExp ',' rExp triangleOptions
            { printf( "Triangles not supported" ); }
        | YY_V3 rExp ',' rExp ',' rExp triangleOptions
            { printf( "Triangles not supported" ); }
        | YY_N1 rExp ',' rExp ',' rExp triangleOptions
            { printf( "Triangles not supported" ); }
        | YY_N2 rExp ',' rExp ',' rExp triangleOptions
            { printf( "Triangles not supported" ); }
        | YY_N3 rExp ',' rExp ',' rExp triangleOptions
            { printf( "Triangles not supported" ); }
;

sphereOptions: /* empty */
        | YY_CENTER rExp ',' rExp ',' rExp sphereOptions
            { ((rawray::Sphere*)g_obj)->SetCenter( math::Vector3($2,$4,$6) ); }
        | YY_RADIUS rExp sphereOptions
            { ((rawray::Sphere*)g_obj)->SetRadius( $2 ); }
;

blPatchOptions: /* empty /*
        | YY_P00
        | YY_P00 rExp ',' rExp ',' rExp blPatchOptions
            { ((rawray::BLPatch*)g_obj)->SetP00( math::Vector3($2,$4,$6) ); }
        | YY_P01 rExp ',' rExp ',' rExp blPatchOptions
            { ((rawray::BLPatch*)g_obj)->SetP01( math::Vector3($2,$4,$6) ); }
        | YY_P10 rExp ',' rExp ',' rExp blPatchOptions
            { ((rawray::BLPatch*)g_obj)->SetP10( math::Vector3($2,$4,$6) ); }
        | YY_P11 rExp ',' rExp ',' rExp blPatchOptions
            { ((rawray::BLPatch*)g_obj)->SetP11( math::Vector3($2,$4,$6) ); }
;

/*
instanceOptions: 
        | YY_GEOMETRY YY_STRING instanceOptions
            {
                //std::map<std::string, Object*>::const_iterator it = g_objectMap.find ($2);
                //if (it != g_objectMap.end ())
                //{
                    //((Instance*)pObj)->SetGeometry(it->second, GetCTM());
                //}
            }
;
*/

transform:  YY_PUSHMATRIX { /*PushMatrix();*/ }
        | YY_POPMATRIX
            { /*PopMatrix();*/ }
        | YY_ROTATE rExp ',' rExp ',' rExp ',' rExp
            { /*Rotate($2, $4, $6, $8);*/ }
        | YY_TRANSLATE rExp ',' rExp ',' rExp
            { /*Translate($2, $4, $6);*/ }
        | YY_SCALE rExp ',' rExp ',' rExp
            { /*Scale($2, $4, $6);*/ }
;

lightTypes: YY_POINTLIGHT '{' 
            {
                printf( "new point light\n" ); 
                g_light = new rawray::Light();
                
                #ifdef VERBOSE_NEW
                printf( "LIGHT: %x\n", g_light );
                #endif
            }
        lightOptions
                
;

materialTypes: YY_LAMBERT '{' 
            {
                printf( "new lambert material\n" ); 
                g_material = new rawray::Lambert();
                
                #ifdef VERBOSE_NEW
                printf( "LAMVERT: %x\n", g_material );
                #endif
            }
        lambertOptions
                
;

lightOptions: /* empty */ 
        | YY_POS rExp ',' rExp ',' rExp lightOptions
            { printf( "pos = %f, %f, %f\n", $2, $4, $6 ); g_light->SetPosition( math::Vector3($2,$4,$6) ); }
        | YY_WATTAGE rExp lightOptions
            { printf( "wattage = %f\n", $2 ); g_light->SetWattage( $2 ); }
        | YY_COLOR rExp ',' rExp ',' rExp lightOptions
            { printf( "color = %f, %f, %f\n", $2, $4, $6 ); g_light->SetColor( math::Vector3($2,$4,$6) ); }
;

lambertOptions: /* empty */ 
        | YY_DIFFUSE rExp ',' rExp ',' rExp lambertOptions
            { printf( "diffuse = %f, %f, %f\n", $2, $4, $6 ); ((rawray::Lambert*)g_material)->SetDiffuse( math::Vector3($2,$4,$6) ); }
        | YY_AMBIENT rExp ',' rExp ',' rExp lambertOptions
            { printf( "ambient = %f, %f, %f\n", $2, $4, $6 ); ((rawray::Lambert*)g_material)->SetAmbient( math::Vector3($2,$4,$6) ); }
;

meshOptions: /* empty */
        | YY_LOAD YY_STRING
            {
                $2[strlen($2)-1]=0;
                printf( "Loading Mesh: '%s'\n", $2+1 );
                g_mesh->LoadOBJ( $2+1 );
            }
;

globalOptions: /* empty */
        | YY_HEIGHT iExp globalOptions
            { printf( "height = %d\n", $2 ); g_image->Resize( g_image->GetWidth(), rawray::options::global::win_height = $2 ); }
        | YY_WIDTH iExp globalOptions
            { printf( "width = %d\n", $2 ); g_image->Resize( rawray::options::global::win_width = $2, g_image->GetHeight() ); }
        | YY_GL_BGCOLOR rExp ',' rExp ',' rExp globalOptions
            { printf( "gl bg color = %f, %f, %f\n", $2, $4, $6 ); rawray::options::global::gl_bg_color = math::Vector3($2,$4,$6); }
        | YY_IMG_BGCOLOR rExp ',' rExp ',' rExp globalOptions
            { printf( "img bg color = %f, %f, %f\n", $2, $4, $6 ); rawray::options::global::img_bg_color = math::Vector3($2,$4,$6); }
        | YY_IMG_FGCOLOR rExp ',' rExp ',' rExp globalOptions
            { printf( "img fg color = %f, %f, %f\n", $2, $4, $6 ); rawray::options::global::img_fg_color = math::Vector3($2,$4,$6); }
        | YY_GL_SPHERE_SECTIONS iExp globalOptions
            { printf( "gl sphere sections = %d\n", rawray::options::global::gl_sphere_sections = $2 ); }
        | YY_NUM_THREADS iExp globalOptions
            { printf( "num threads = %d\n", rawray::options::global::num_threads = $2 ); }
        | YY_TRIANGLE_TEST YY_BARYCENTRIC globalOptions
            { printf( "triangle test = barycentric\n", rawray::options::global::triangle_intersection_algorithm = rawray::options::BARYCENTRIC ); }
        | YY_TRIANGLE_TEST YY_BARYCENTRIC YY_PROJECTION globalOptions
            { printf( "triangle test = barycentric projection\n", rawray::options::global::triangle_intersection_algorithm = rawray::options::BARYCENTRIC_PROJECTION ); }
        | YY_TRIANGLE_TEST YY_PLUCKER globalOptions
            { printf( "triangle test = plucker\n", rawray::options::global::triangle_intersection_algorithm = rawray::options::PLUCKER ); }
        | YY_TRIANGLE_TEST YY_MOLLER globalOptions
            { printf( "triangle test = moller\n", rawray::options::global::triangle_intersection_algorithm = rawray::options::MOLLER ); }
        | YY_RENDER_X_BLOCK iExp globalOptions
            { printf( "render x block = %d\n", rawray::options::global::render_x_block = $2 ); }
        | YY_RENDER_Y_BLOCK iExp globalOptions
            { printf( "render y block = %d\n", rawray::options::global::render_y_block = $2 ); }
        | YY_RENDER_HANDLER_SLEEP iExp globalOptions
            { printf( "render handler sleep = %d\n", rawray::options::global::render_handler_sleep = $2 ); }
        | YY_RENDER_THREAD_SLEEP iExp globalOptions
            { printf( "render thread sleep = %d\n", rawray::options::global::render_thread_sleep = $2 ); }
        | YY_RENDER_SPINLOCK_SLEEP iExp globalOptions
            { printf( "render spinlock sleep = %d\n", rawray::options::global::render_spinlock_sleep = $2 ); }
        | YY_GAUSSIAN_BLUR_MAX rExp globalOptions
            { printf( "gaussian blur max = %f\n", rawray::options::global::gaussian_blur_max = $2 ); }
        | YY_GAUSSIAN_BLUR_SIGMA rExp globalOptions
            { printf( "gaussian blur sigma = %f\n", rawray::options::global::gaussian_blur_sigma = $2 ); }
        | YY_ENABLE YY_GL_RENDER_LIGHTS globalOptions
			{ printf( "enabling rendering of lights in gl\n" ); rawray::options::global::gl_render_lights = true; }
		| YY_DISABLE YY_GL_RENDER_LIGHTS globalOptions
			{ printf( "disabling rendering of lights in gl\n" ); rawray::options::global::gl_render_lights = false; }
		| YY_ENABLE YY_HEADLESS globalOptions
		    { printf( "enabling headless mode\n" ); rawray::options::global::headless = true; }
		| YY_DISABLE YY_HEADLESS globalOptions
		    { printf( "disabling headless mode\n" ); rawray::options::global::headless = false; }
;

cameraOptions: /* empty */
        | YY_POS rExp ',' rExp ',' rExp cameraOptions
            { printf( "camera pos = %f, %f, %f\n", $2, $4, $6 ); g_camera->SetEye( rawray::options::camera::eye = math::Vector3($2,$4,$6) ); }
        | YY_DIR rExp ',' rExp ',' rExp cameraOptions
            { printf( "camera dir = %f, %f, %f\n", $2, $4, $6 ); g_camera->SetViewDir( rawray::options::camera::view = math::Vector3($2,$4,$6) ); }
        | YY_LOOKAT rExp ',' rExp ',' rExp cameraOptions
            { printf( "camera look at = %f, %f, %f\n", $2, $4, $6 ); g_camera->SetLookAt( rawray::options::camera::lookat = math::Vector3($2,$4,$6) ); }
        | YY_UP rExp ',' rExp ',' rExp cameraOptions
            { printf( "camera up = %f, %f, %f\n", $2, $4, $6 ); g_camera->SetUp( rawray::options::camera::up = math::Vector3($2,$4,$6) ); }
        | YY_FOV rExp cameraOptions
            { printf( "camera fov = %f\n", $2 ); g_camera->SetFOV( rawray::options::camera::fov = $2 ); }
        | YY_ASPECT rExp cameraOptions
            { printf( "camera aspect ratio = %f\n", $2 ); g_camera->SetAspect( rawray::options::camera::aspect = $2 ); }
        | YY_MIN_DRAW rExp cameraOptions
            { printf( "camera min draw = %f\n", $2 ); g_camera->SetMinDraw( rawray::options::camera::min_draw = $2 ); }
        | YY_MAX_DRAW rExp cameraOptions
            { printf( "camera max draw = %f\n", $2 ); g_camera->SetMaxDraw( rawray::options::camera::max_draw = $2 ); }
;

p0Options: /* empty */
        | YY_SPIRAL_NUM_SPHERES iExp p0Options
            { printf( "spiral num spheres = %d\n", rawray::options::p0::spiral_num_spheres = $2 ); }
        | YY_SPIRAL_RADIUS rExp p0Options
            { printf( "spiral radius = %f\n", rawray::options::p0::spiral_radius = $2 ); }
        | YY_LORENZ_DT rExp p0Options
            { printf( "lorenz dt = %f\n", rawray::options::p0::lorenz_dt = $2 ); }
        | YY_LORENZ_MIN_DISTANCE rExp p0Options
            { printf( "lorenz min distance = %f\n", rawray::options::p0::lorenz_min_distance = $2 ); }
        | YY_LORENZ_MAX_DISTANCE rExp p0Options
            { printf( "lorenz max distance = %f\n", rawray::options::p0::lorenz_max_distance = $2 ); }
        | YY_LORENZ_SIGMA rExp p0Options
            { printf( "lorenz sigma = %f\n", rawray::options::p0::lorenz_sigma = $2 ); }
        | YY_LORENZ_RHO rExp p0Options
            { printf( "lorenz rho = %f\n", rawray::options::p0::lorenz_rho = $2 ); }
        | YY_LORENZ_BETA rExp p0Options
            { printf( "lorenz beta = %f\n", rawray::options::p0::lorenz_beta = $2 ); }
        | YY_LORENZ_RADIUS rExp p0Options
            { printf( "lorenz radius = %f\n", rawray::options::p0::lorenz_radius = $2 ); }
        | YY_LORENZ_NUM_SPHERES iExp p0Options
            { printf( "lorenz num spheres = %d\n", rawray::options::p0::lorenz_num_spheres = $2 ); }
        | YY_LORENZ_START rExp ',' rExp ',' rExp p0Options
            { printf( "lorenz start = %f, %f, %f\n", $2, $4, $6 ); rawray::options::p0::lorenz_start = math::Vector3($2,$4,$6); }
;

rExp:     YY_REAL              { $$ = $1; }
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

fExp:      YY_MATH_SIN '(' rExp ')'    {$$ = sin($3); }
        |  YY_MATH_COS '(' rExp ')'    {$$ = cos($3); }
        |  YY_MATH_TAN '(' rExp ')'    {$$ = tan($3); }
        |  YY_MATH_ASIN '(' rExp ')'   {$$ = asin($3); }
        |  YY_MATH_ACOS '(' rExp ')'   {$$ = acos($3); }
        |  YY_MATH_ATAN '(' rExp ')'   {$$ = atan($3); }
        |  YY_MATH_LN '(' rExp ')'     {$$ = log($3); }
        |  YY_MATH_LOG '(' rExp ')'    {$$ = log10($3); }
        |  YY_MATH_EXP '(' rExp ')'    {$$ = exp($3); }
        |  YY_MATH_SQRT '(' rExp ')'   {$$ = sqrt($3); }
;

constantExp:
           YY_MATH_E { $$ = 2.718281828459f; }
        |  YY_MATH_PI { $$ = 3.141592653589793f; }
;

iExp:     YY_PARSE_INT          { $$ = $1; }
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
        Triangle* t = rawray::TriangleFactory::NewTriangle( *g_mesh, i, g_material );
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
#ifdef YYDEBUG
#if YYDEBUG==1
    yydebug = 1;
#endif
#endif
    
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
