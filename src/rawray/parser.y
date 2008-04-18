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

%token YY_LBOX
%token YY_RBOX
%token YY_LCURLY
%token YY_RCURLY
%token YY_LPAREN
%token YY_RPAREN

%token YY_GLOBAL


%right '='
%left '-' '+'
%left '*' '/' // multiplication or cross product
%left NEG     // Negation--unary minus
%right '^'

%type <real> rExp fExp constantExp
%type <integer> iExp 

%%

input:  block input | block
;

block: YY_GLOBAL
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
           YY_MATH_E  { $$ = 2.718281828459f; }
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
