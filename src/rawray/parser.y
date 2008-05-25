%{
#ifdef WIN32
#pragma warning(disable:4244) // smaller type conversion warnings
#pragma warning(disable:4701) // variable used without being initialized
#ifdef NDEBUG
#pragma warning(disable:4702) // unreachable code in <vector> in release mode
#endif
#endif

#include "parser.h"
#include <stdlib.h>
#include <math.h>
#include <stack>
#include <queue>
#include <map>
#include <string>
#include <iostream>
#include "lexer.h"
#include "math/vector2.h"
#include "math/vector3.h"
#include "math/vector4.h"
#include "math/matrix4x4.h"
#include "object.h"
#include "multi_material.h"
#include "material.h"
#include "diffuse.h"
#include "indirect_diffuse.h"
#include "phong.h"
#include "stone.h"
#include "stone_bump.h"
#include "reflective.h"
#include "refractive.h"
#include "light.h"
#include "point_light.h"
#include "square_light.h"
#include "sphere_light.h"
#include "options.h"
#include "scene.h"
#include "camera.h"
#include "image.h"
#include "triangle_factory.h"
#include "sphere.h"
#include "bl_patch.h"

//#define YYDEBUG 1

#define yyerror(x) printf("Parser error #%d on line %d: %s\n", ++yyerr, yyline, x);

extern int yylex();
extern int yyline;
extern int yyerr;
extern FILE *yyin, *yyout;


// variables for adding objects, keeping track of variables
rawray::Camera*                         g_camera = NULL;
rawray::Scene*                          g_scene = NULL;
rawray::Image*                          g_image = NULL;

rawray::Object*                         g_obj = NULL;
rawray::Material*                       g_material = NULL;
rawray::MultiMaterial*					g_multimaterial = NULL;
rawray::Light*                          g_light = NULL;
rawray::TriangleMesh*                   g_mesh = NULL;

std::map<std::string, rawray::Object*>  g_objectMap;
std::stack<math::Matrix4x4>             g_matrixStack;

%}
// BISON Declarations
%union
{
    float			real;
    int				integer;
    char*			str;
    float			vec[4];
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

%token YY_LT
%token YY_GT
%token YY_LBOX
%token YY_RBOX
%token YY_LCURLY
%token YY_RCURLY
%token YY_LPAREN
%token YY_RPAREN
%token YY_COMMA
%token YY_EQUAL
%token YY_PLUS
%token YY_MINUS
%token YY_DIV
%token YY_MUL
%token YY_CARAT
%token YY_BSLASH
%token YY_X


/* ----------------------- keywords ------------------------*/
%token YY_S_GLOBAL
%token YY_SIZE
%token YY_POS
%token YY_IMG_BGCOLOR
%token YY_IMG_FGCOLOR
%token YY_GL_BGCOLOR
%token YY_GL_SPHERE_SECTIONS
%token YY_GL_RENDER_LIGHTS
%token YY_GL_RENDER_BBOX
%token YY_HEADLESS
%token YY_NUM_THREADS
%token YY_THREAD_JOB_SIZE
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
%token YY_BOX_COST
%token YY_OBJECT_COST
%token YY_PFM
%token YY_ANTI_ALIAS

%token YY_S_CAMERA
%token YY_POS
%token YY_DIR
%token YY_LOOKAT
%token YY_UP
%token YY_FOV
%token YY_ASPECT
%token YY_MIN_DRAW
%token YY_MAX_DRAW

%token YY_S_P0
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

%token YY_S_TRIANGLE
%token YY_V1
%token YY_V2
%token YY_V3
%token YY_N1
%token YY_N2
%token YY_N3

%token YY_S_MESH
%token YY_LOAD

%token YY_S_INSTANCE
%token YY_GEOMETRY

%token YY_S_MATRIX
%token YY_PUSH
%token YY_POP
%token YY_ROTATE
%token YY_TRANSLATE
%token YY_SCALE
%token YY_SET_IDENTITY

%token YY_S_LIGHT
%token YY_S_POINTLIGHT
%token YY_S_SQUARELIGHT
%token YY_S_SPHERELIGHT
%token YY_WATTAGE
%token YY_COLOR
%token YY_NUM_SAMPLES
%token YY_P1
%token YY_P2

%token YY_S_MULTIMATERIAL
%token YY_S_MATERIAL
%token YY_S_DIFFUSE
%token YY_S_INDIRECT_DIFFUSE
%token YY_S_PHONG
%token YY_S_STONE
%token YY_S_STONEBUMP
%token YY_S_REFLECTIVE
%token YY_S_REFRACTIVE
%token YY_COLOR
%token YY_N
%token YY_AMBIENT
%token YY_COLOR_A
%token YY_COLOR_B
%token YY_AMPLITUDE
%token YY_IOR
%token YY_WEIGHT

%token YY_S_SPHERE
%token YY_CENTER
%token YY_RADIUS

%token YY_S_BLPATCH
%token YY_P00
%token YY_P01
%token YY_P10
%token YY_P11
%token YY_U_CONSTRAINT
%token YY_V_CONSTRAINT



%right YY_EQUALS
%left  YY_MINUS YY_PLUS
%left  YY_MUL YY_DIV
%left  NEG				// Negation--unary minus
%right YY_CARAT

%type <real> rExp fExp constantExp
%type <integer> iExp
%type <vec> vector2 vector3 vector4

%%

input:			/* empty */ | option_blocks;
option_blocks:	block | option_blocks block;

/* ----------------------- recursion ------------------------*/
global_stuff:			global_option			| global_stuff			global_option;
camera_stuff:			camera_option			| camera_stuff			camera_option;
pointlight_stuff:		pointlight_option		| pointlight_stuff		pointlight_option;
squarelight_stuff:		squarelight_option		| squarelight_stuff		squarelight_option;
spherelight_stuff:		spherelight_option		| spherelight_stuff		spherelight_option;
multimaterial_stuff:	multimaterial_option	| multimaterial_stuff   multimaterial_option;
diffuse_stuff:			diffuse_option			| diffuse_stuff			diffuse_option;
indirectdiffuse_stuff:	indirectdiffuse_option	| indirectdiffuse_stuff indirectdiffuse_option;
phong_stuff:			phong_option			| phong_stuff			phong_option;
stone_stuff:			stone_option			| stone_stuff			stone_option;
stonebump_stuff:		stonebump_option		| stonebump_stuff		stonebump_option;
refractive_stuff:		refractive_option		| refractive_stuff		refractive_option;
reflective_stuff:		reflective_option		| reflective_stuff		reflective_option;
p0_stuff:				p0_option				| p0_stuff				p0_option;
mesh_stuff:				mesh_option				| mesh_stuff			mesh_option;
sphere_stuff:			sphere_option			| sphere_stuff			sphere_option;
blpatch_stuff:			blpatch_option			| blpatch_stuff			blpatch_option;
matrix_stuff:			matrix_option			| matrix_stuff			matrix_option;

/* ----------------------- definitions ------------------------*/
block:
		  YY_S_GLOBAL YY_LCURLY global_stuff YY_RCURLY		{ }
		| YY_S_CAMERA YY_LCURLY camera_stuff YY_RCURLY		{ }
		| YY_S_P0 YY_LCURLY p0_stuff YY_RCURLY				{ }
		| YY_S_LIGHT light_type YY_RCURLY					{ }
		| YY_S_MATERIAL material_type YY_RCURLY				{ }
		| YY_S_MATRIX YY_LCURLY matrix_stuff YY_RCURLY		{ }
		| multimaterial_type								{ }
		| object_type										{ }
;

object_type:
		  object_mesh
		| object_sphere
		| object_blpatch
;

global_option: 
		| YY_SIZE iExp YY_X iExp							{ g_image->Resize( rawray::options::global::win_width = $2, rawray::options::global::win_height = $4 ); }
		| YY_IMG_BGCOLOR vector3							{ rawray::options::global::img_bg_color = math::Vector3( $2[0], $2[1], $2[2] ); }
		| YY_IMG_FGCOLOR vector3							{ rawray::options::global::img_fg_color = math::Vector3( $2[0], $2[1], $2[2] ); }
		| YY_GL_BGCOLOR	vector3								{ rawray::options::global::gl_bg_color = math::Vector3( $2[0], $2[1], $2[2] ); g_scene->GetBackground().SetBGColor(rawray::options::global::gl_bg_color); }
		| YY_GL_SPHERE_SECTIONS iExp						{ rawray::options::global::gl_sphere_sections = $2; }
		| YY_ENABLE YY_GL_RENDER_LIGHTS						{ rawray::options::global::gl_render_lights = true; }
		| YY_DISABLE YY_GL_RENDER_LIGHTS					{ rawray::options::global::gl_render_lights = false; }
		| YY_ENABLE YY_GL_RENDER_BBOX						{ rawray::options::global::gl_render_bbox = true; }
		| YY_DISABLE YY_GL_RENDER_BBOX  					{ rawray::options::global::gl_render_bbox = false; }
		| YY_ENABLE YY_HEADLESS								{ rawray::options::global::headless = true; }
		| YY_DISABLE YY_HEADLESS							{ rawray::options::global::headless = false; }
		| YY_NUM_THREADS iExp								{ rawray::options::global::num_threads = $2; }
		| YY_RENDER_HANDLER_SLEEP iExp						{ rawray::options::global::render_handler_sleep = $2; }
		| YY_RENDER_THREAD_SLEEP iExp 						{ rawray::options::global::render_thread_sleep = $2; }
		| YY_RENDER_SPINLOCK_SLEEP iExp						{ rawray::options::global::render_spinlock_sleep = $2; }
		| YY_THREAD_JOB_SIZE iExp YY_X iExp					{ rawray::options::global::thread_job_size_x = $2; rawray::options::global::thread_job_size_y = $4; }
		| YY_TRIANGLE_TEST YY_BARYCENTRIC					{ rawray::options::global::triangle_intersection_algorithm = rawray::options::BARYCENTRIC; }
		| YY_TRIANGLE_TEST YY_BARYCENTRIC YY_PROJECTION		{ rawray::options::global::triangle_intersection_algorithm = rawray::options::BARYCENTRIC_PROJECTION; }
		| YY_TRIANGLE_TEST YY_PLUCKER						{ rawray::options::global::triangle_intersection_algorithm = rawray::options::PLUCKER; }
		| YY_TRIANGLE_TEST YY_MOLLER						{ rawray::options::global::triangle_intersection_algorithm = rawray::options::MOLLER; }
		| YY_GAUSSIAN_BLUR_MAX iExp							{ rawray::options::global::gaussian_blur_max = $2; }
		| YY_GAUSSIAN_BLUR_SIGMA iExp						{ rawray::options::global::gaussian_blur_sigma = $2; }
		| YY_BOX_COST rExp									{ rawray::options::global::bvh_box_cost = $2; }
		| YY_OBJECT_COST rExp								{ rawray::options::global::bvh_obj_cost = $2; }
		| YY_PFM YY_STRING									{ $2[strlen($2)-1] = 0; g_scene->GetBackground().LoadPFM( $2+1 ); }
		| YY_ANTI_ALIAS iExp YY_X iExp						{ rawray::options::global::aax = $2; rawray::options::global::aay = $4; }
;

camera_option:
		  YY_POS vector3									{ g_camera->SetEye(		rawray::options::camera::eye = math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_DIR vector3									{ g_camera->SetViewDir( rawray::options::camera::view = math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_LOOKAT vector3									{ g_camera->SetLookAt(	rawray::options::camera::lookat = math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_UP vector3										{ g_camera->SetUp(		rawray::options::camera::up = math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_FOV rExp										{ g_camera->SetFOV(		rawray::options::camera::fov = $2 ); }
		| YY_ASPECT rExp									{ g_camera->SetAspect(	rawray::options::camera::aspect = $2 ); }
		| YY_MIN_DRAW rExp									{ g_camera->SetMinDraw( rawray::options::camera::min_draw = $2 ); }
		| YY_MAX_DRAW rExp									{ g_camera->SetMinDraw( rawray::options::camera::max_draw = $2 ); }
;

light_type:
		  YY_S_POINTLIGHT YY_LCURLY
			{
				g_light = new rawray::PointLight();
				g_scene->AddLight( g_light );
			}
			pointlight_stuff
		| YY_S_SQUARELIGHT YY_LCURLY
			{
				g_light = new rawray::SquareLight();
				g_scene->AddLight( g_light );
			}
			squarelight_stuff
		| YY_S_SPHERELIGHT YY_LCURLY
			{
				g_light = new rawray::SphereLight();
				g_scene->AddLight( g_light );
			}
			spherelight_stuff
;

pointlight_option:
		  YY_POS vector3		{ g_light->SetPosition( math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_WATTAGE rExp		{ g_light->SetWattage( $2 ); }
		| YY_COLOR vector3		{ g_light->SetColor( math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_NUM_SAMPLES iExp	{ g_light->SetNumSamples( $2 ); }
;

squarelight_option:
		  YY_POS vector3		{ g_light->SetPosition( math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_WATTAGE rExp		{ g_light->SetWattage( $2 ); }
		| YY_COLOR vector3		{ g_light->SetColor( math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_NUM_SAMPLES iExp	{ g_light->SetNumSamples( $2 ); }
		| YY_P1 vector3			{ ((rawray::SquareLight*)g_light)->SetP1( math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_P2 vector3			{ ((rawray::SquareLight*)g_light)->SetP2( math::Vector3( $2[0], $2[1], $2[2] ) ); }
;

spherelight_option:
		  YY_POS vector3		{ g_light->SetPosition( math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_WATTAGE rExp		{ g_light->SetWattage( $2 ); }
		| YY_COLOR vector3		{ g_light->SetColor( math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_NUM_SAMPLES iExp	{ g_light->SetNumSamples( $2 ); }
		| YY_RADIUS rExp		{ ((rawray::SphereLight*)g_light)->SetRadius( $2 ); }
;

material_type:
		  YY_S_DIFFUSE YY_LCURLY 
			{
				g_material = new rawray::Diffuse();
				AddMaterial( g_material );
			}
			diffuse_stuff
		| YY_S_PHONG YY_LCURLY
			{
				g_material = new rawray::Phong();
				AddMaterial( g_material );
			}
			phong_stuff
		| YY_S_STONE YY_LCURLY
			{
				g_material = new rawray::Stone();
				AddMaterial( g_material );
			}
			stone_stuff
		| YY_S_STONEBUMP YY_LCURLY
			{
				g_material = new rawray::StoneBump();
				AddMaterial( g_material );
			}
			stonebump_stuff
		| YY_S_REFLECTIVE YY_LCURLY
			{
				g_material = new rawray::Reflective();
				AddMaterial( g_material );
			}
			reflective_stuff
		| YY_S_REFRACTIVE YY_LCURLY
			{
				g_material = new rawray::Refractive();
				AddMaterial( g_material );
			}
			refractive_stuff
		| YY_S_INDIRECT_DIFFUSE YY_LCURLY
			{
				g_material = new rawray::IndirectDiffuse();
				AddMaterial( g_material );
			}
			indirectdiffuse_stuff
;

multimaterial_type:
		  YY_S_MULTIMATERIAL YY_LCURLY
			{
				g_multimaterial = new rawray::MultiMaterial();
				g_scene->AddMaterial( g_multimaterial );
			}
		  multimaterial_stuff YY_RCURLY
			{
				g_material = g_multimaterial;
				g_multimaterial = NULL;
			}
;

multimaterial_option:
		  YY_AMBIENT vector3							{ g_multimaterial->SetAmbient( math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| material_type YY_RCURLY						{ }
;

diffuse_option:
		  YY_COLOR vector3								{ ((rawray::Diffuse*)g_material)->SetColor( math::Vector3( $2[0], $2[1], $2[2] ) ); }
;

indirectdiffuse_option:
		  YY_WEIGHT rExp								{ ((rawray::IndirectDiffuse*)g_material)->SetWeight( $2 ); }
;

phong_option:
		  YY_COLOR vector3								{ ((rawray::Phong*)g_material)->SetColor( math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_N rExp										{ ((rawray::Phong*)g_material)->SetN( $2 ); }
;

stone_option:
		  YY_COLOR_A vector3							{ ((rawray::Stone*)g_material)->SetColorA( math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_COLOR_B vector3							{ ((rawray::Stone*)g_material)->SetColorB( math::Vector3( $2[0], $2[1], $2[2] ) ); }
;

stonebump_option:
		  YY_AMPLITUDE rExp								{ ((rawray::StoneBump*)g_material)->SetAmplitude( $2 ); }
;

reflective_option:
;

refractive_option:
		  YY_IOR rExp									{ ((rawray::Refractive*)g_material)->SetIOR( $2 ); }
;

matrix_option:
		  YY_PUSH										{ if( g_matrixStack.size() > 0 ) g_matrixStack.push( g_matrixStack.top() ); else g_matrixStack.push( math::Matrix4x4() ); }
		| YY_POP										{ if( g_matrixStack.size() > 0 )g_matrixStack.pop(); else printf( "ERROR: Popping empty stack" ); }
		| YY_SET_IDENTITY								{ g_matrixStack.top().SetIdentity(); }
		| YY_TRANSLATE vector3							{ g_matrixStack.top().Translate( $2[0], $2[1], $2[2] ); }
		| YY_SCALE vector3								{ g_matrixStack.top().Scale( $2[0], $2[1], $2[2] ); }
		| YY_ROTATE vector4								{ g_matrixStack.top().Rotate( $2[0], $2[1], $2[2], $2[3] ); }
;

p0_option:
		  YY_SPIRAL_NUM_SPHERES iExp					{ rawray::options::p0::spiral_num_spheres = $2; }
        | YY_SPIRAL_RADIUS rExp							{ rawray::options::p0::spiral_radius = $2; }
        | YY_LORENZ_DT rExp								{ rawray::options::p0::lorenz_dt = $2; }
        | YY_LORENZ_MIN_DISTANCE rExp					{ rawray::options::p0::lorenz_min_distance = $2; }
        | YY_LORENZ_MAX_DISTANCE rExp					{ rawray::options::p0::lorenz_max_distance = $2; }
        | YY_LORENZ_SIGMA rExp							{ rawray::options::p0::lorenz_sigma = $2; }
        | YY_LORENZ_RHO rExp							{ rawray::options::p0::lorenz_rho = $2; }
        | YY_LORENZ_BETA rExp							{ rawray::options::p0::lorenz_beta = $2; }
        | YY_LORENZ_RADIUS rExp							{ rawray::options::p0::lorenz_radius = $2; }
        | YY_LORENZ_NUM_SPHERES iExp					{ rawray::options::p0::lorenz_num_spheres = $2; }
        | YY_LORENZ_START vector3						{ rawray::options::p0::lorenz_start = math::Vector3( $2[0], $2[1], $2[2] ); }
;

mesh_option:
		  YY_LOAD YY_STRING
			{
				$2[strlen($2)-1] = 0;
				printf( "Loading Mesh: '%s'\n", $2+1 );
				
				if( g_matrixStack.size() == 0 )
					g_mesh->LoadOBJ( $2+1 );
				else
					g_mesh->LoadOBJ( $2+1, g_matrixStack.top() );
					
				printf( "Found %d triangles in mesh\n", g_mesh->GetNumTriangles() );
				
				delete $2;
			}
;

sphere_option:
		  YY_CENTER vector3								{ ((rawray::Sphere*)g_obj)->SetCenter( math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_RADIUS rExp								{ ((rawray::Sphere*)g_obj)->SetRadius( $2 ); }
;

blpatch_option:
		  YY_P00 vector3								{ ((rawray::BLPatch*)g_obj)->SetP00( math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_P01 vector3								{ ((rawray::BLPatch*)g_obj)->SetP01( math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_P10 vector3								{ ((rawray::BLPatch*)g_obj)->SetP10( math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_P11 vector3								{ ((rawray::BLPatch*)g_obj)->SetP11( math::Vector3( $2[0], $2[1], $2[2] ) ); }
		| YY_U_CONSTRAINT vector2                       { ((rawray::BLPatch*)g_obj)->SetUConstraint( $2[0], $2[1] ); }
		| YY_V_CONSTRAINT vector2                       { ((rawray::BLPatch*)g_obj)->SetVConstraint( $2[0], $2[1] ); }

object_mesh:
		  YY_S_MESH YY_LCURLY
			{
				g_mesh = new rawray::TriangleMesh();
			}
			mesh_stuff YY_RCURLY
			{
				if( g_mesh->GetNumTriangles() > 0 ) {
					g_scene->AddMesh( g_mesh );
					rawray::AddTrianglesOfMesh();
				} else {
					delete g_mesh;
					g_mesh = NULL;
				}
			}
		| YY_S_MESH YY_STRING YY_LCURLY
			{
				g_mesh = new rawray::TriangleMesh();
				
				// TODO: implement
				//g_objectMap[$2] = g_obj;
				
				delete $2;
			}
			mesh_stuff YY_RCURLY
			{
				if( g_mesh->GetNumTriangles() > 0 ) {
					g_scene->AddMesh( g_mesh );
					rawray::AddTrianglesOfMesh();
				} else {
					delete g_mesh;
					g_mesh = NULL;
				}
			}
;

object_sphere:
		  YY_S_SPHERE YY_LCURLY
			{
				g_obj = new rawray::Sphere( math::Vector3(0), 1.0f, g_material );
			}
			sphere_stuff YY_RCURLY
			{
				g_scene->AddObject( g_obj );
				g_obj = NULL;
			}
		| YY_S_SPHERE YY_STRING YY_LCURLY
			{
				g_obj = new rawray::Sphere( math::Vector3(0), 1.0f, g_material );
				g_objectMap[$2] = g_obj;
				
				delete $2;
			}
			sphere_stuff YY_RCURLY
			{
				g_scene->AddObject( g_obj );
				g_obj = NULL;
			}
;

object_blpatch:
		  YY_S_BLPATCH YY_LCURLY
			{
				g_obj = new rawray::BLPatch( g_material );
			}
			blpatch_stuff YY_RCURLY
			{
				g_scene->AddObject( g_obj );
				g_obj = NULL;
			}
		| YY_S_BLPATCH YY_STRING YY_LCURLY
			{
				g_obj = new rawray::BLPatch( g_material );
				g_objectMap[$2] = g_obj;
				
				delete $2;
			}
			blpatch_stuff YY_RCURLY
			{
				g_scene->AddObject( g_obj );
				g_obj = NULL;
			}
;

vector2:
          YY_LT rExp YY_COMMA rExp YY_GT                { $$[0] = $2; $$[1] = $4; }
        | YY_LT rExp YY_COMMA iExp YY_GT                { $$[0] = $2; $$[1] = $4; }
        | YY_LT iExp YY_COMMA rExp YY_GT                { $$[0] = $2; $$[1] = $4; }
        | YY_LT iExp YY_COMMA iExp YY_GT                { $$[0] = $2; $$[1] = $4; }
        | YY_LT rExp YY_GT                              { $$[0] = $2; $$[1] = $2; }
        | YY_LT iExp YY_GT                              { $$[0] = $2; $$[1] = $2; }


vector3:
		  YY_LT rExp YY_COMMA rExp YY_COMMA rExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; }
		| YY_LT rExp YY_COMMA rExp YY_COMMA iExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; }
		| YY_LT rExp YY_COMMA iExp YY_COMMA rExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; }
		| YY_LT rExp YY_COMMA iExp YY_COMMA iExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; }
		| YY_LT iExp YY_COMMA rExp YY_COMMA rExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; }
		| YY_LT iExp YY_COMMA rExp YY_COMMA iExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; }
		| YY_LT iExp YY_COMMA iExp YY_COMMA rExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; }
		| YY_LT iExp YY_COMMA iExp YY_COMMA iExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; }
		| YY_LT rExp YY_GT								{ $$[0] = $2; $$[1] = $2; $$[2] = $2; }
		| YY_LT iExp YY_GT								{ $$[0] = $2; $$[1] = $2; $$[2] = $2; }
;

vector4:
		  YY_LT rExp YY_COMMA rExp YY_COMMA rExp YY_COMMA rExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT rExp YY_COMMA rExp YY_COMMA rExp YY_COMMA iExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT rExp YY_COMMA rExp YY_COMMA iExp YY_COMMA rExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT rExp YY_COMMA rExp YY_COMMA iExp YY_COMMA iExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT rExp YY_COMMA iExp YY_COMMA rExp YY_COMMA rExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT rExp YY_COMMA iExp YY_COMMA rExp YY_COMMA iExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT rExp YY_COMMA iExp YY_COMMA iExp YY_COMMA rExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT rExp YY_COMMA iExp YY_COMMA iExp YY_COMMA iExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT iExp YY_COMMA rExp YY_COMMA rExp YY_COMMA rExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT iExp YY_COMMA rExp YY_COMMA rExp YY_COMMA iExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT iExp YY_COMMA rExp YY_COMMA iExp YY_COMMA rExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT iExp YY_COMMA rExp YY_COMMA iExp YY_COMMA iExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT iExp YY_COMMA iExp YY_COMMA rExp YY_COMMA rExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT iExp YY_COMMA iExp YY_COMMA rExp YY_COMMA iExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT iExp YY_COMMA iExp YY_COMMA iExp YY_COMMA rExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT iExp YY_COMMA iExp YY_COMMA iExp YY_COMMA iExp YY_GT	{ $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8; }
		| YY_LT rExp YY_GT												{ $$[0] = $2; $$[1] = $2; $$[2] = $2; $$[3] = $2; }
		| YY_LT iExp YY_GT												{ $$[0] = $2; $$[1] = $2; $$[2] = $2; $$[3] = $2; }

rExp:
		  YY_REAL							{ $$ = $1; }
		| fExp								{ $$ = $1; }
		| constantExp						{ $$ = $1; }
		| rExp YY_PLUS rExp					{ $$ = $1 + $3; }
		| rExp YY_MINUS rExp				{ $$ = $1 - $3; }
		| rExp YY_MUL rExp					{ $$ = $1 * $3; }
		| rExp YY_DIV rExp					{ $$ = $1 / $3; }
		| rExp YY_CARAT rExp				{ $$ = pow( (float)$1, (float)$3 ); }
		| YY_MINUS rExp %prec NEG			{ $$ = -$2; }
		| YY_LPAREN rExp YY_RPAREN			{ $$ = $2; }
;

iExp:
		  YY_PARSE_INT						{ $$ = $1; }
		| iExp YY_PLUS iExp					{ $$ = $1 + $3; }
		| iExp YY_MINUS iExp				{ $$ = $1 - $3; }
		| iExp YY_MUL iExp					{ $$ = $1 * $3; }
		| iExp YY_DIV iExp					{ $$ = $1 / $3; }
		| iExp YY_CARAT iExp				{ $$ = (int)pow( (float)$1, (float)$3 ); }
		| YY_MINUS iExp %prec NEG			{ $$ = -$2; }
		| YY_LPAREN iExp YY_RPAREN			{ $$ = $2; }
;

fExp:      
		  YY_MATH_SIN	YY_LPAREN rExp YY_RPAREN	{$$ = sin($3); }
		| YY_MATH_SIN	YY_LPAREN iExp YY_RPAREN	{$$ = sin((float)$3); }
        | YY_MATH_COS	YY_LPAREN rExp YY_RPAREN	{$$ = cos($3); }
        | YY_MATH_COS	YY_LPAREN iExp YY_RPAREN	{$$ = cos((float)$3); }
        | YY_MATH_TAN	YY_LPAREN rExp YY_RPAREN	{$$ = tan($3); }
        | YY_MATH_TAN	YY_LPAREN iExp YY_RPAREN	{$$ = tan((float)$3); }
        | YY_MATH_ASIN	YY_LPAREN rExp YY_RPAREN	{$$ = asin($3); }
        | YY_MATH_ASIN	YY_LPAREN iExp YY_RPAREN	{$$ = asin((float)$3); }
        | YY_MATH_ACOS	YY_LPAREN rExp YY_RPAREN	{$$ = acos($3); }
        | YY_MATH_ACOS	YY_LPAREN iExp YY_RPAREN	{$$ = acos((float)$3); }
        | YY_MATH_ATAN	YY_LPAREN rExp YY_RPAREN	{$$ = atan($3); }
        | YY_MATH_ATAN	YY_LPAREN iExp YY_RPAREN	{$$ = atan((float)$3); }
        | YY_MATH_LN	YY_LPAREN rExp YY_RPAREN	{$$ = log($3); }
        | YY_MATH_LN	YY_LPAREN iExp YY_RPAREN	{$$ = log((float)$3); }
        | YY_MATH_LOG	YY_LPAREN rExp YY_RPAREN	{$$ = log10($3); }
        | YY_MATH_LOG	YY_LPAREN iExp YY_RPAREN	{$$ = log10((float)$3); }
        | YY_MATH_EXP	YY_LPAREN rExp YY_RPAREN	{$$ = exp($3); }
        | YY_MATH_EXP	YY_LPAREN iExp YY_RPAREN	{$$ = exp((float)$3); }
        | YY_MATH_SQRT	YY_LPAREN rExp YY_RPAREN	{$$ = sqrt($3); }
        | YY_MATH_SQRT	YY_LPAREN iExp YY_RPAREN	{$$ = sqrt((float)$3); }
;

constantExp:
          YY_MATH_E						{ $$ = 2.718281828459f; }
        | YY_MATH_PI					{ $$ = 3.141592653589793f; }
;

// End of grammar
%%

//Additional C code

namespace rawray {

void AddTrianglesOfMesh() {
    for( int i=0; i<g_mesh->GetNumTriangles(); ++i ) {
        Triangle* t = rawray::TriangleFactory::NewTriangle( g_mesh, i, g_material );
        g_scene->AddObject( t );
    }
    
    g_mesh = NULL;
}

void SetConfigSources(Scene* scene, Camera* cam, Image* img) {
	printf( "Setting config sources\n");
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
    
    printf( "Done Parsing...\n" );
	return yyerr == 0;
}

void DoneParsing() {
	printf( "Cleaning up parser...\n" );
	yy_done_parsing();
}

void AddMaterial( Material* material ) {
	if( g_multimaterial ) {
		g_multimaterial->AddMaterial( material );
	} else {
		g_scene->AddMaterial( material );
	}
}

} // namespace rawray
