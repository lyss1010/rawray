%{
#ifdef WIN32
#pragma warning(disable:4244) // smaller type conversion warnings
#endif

#include <stdlib.h>
#include <math.h>
#include <stack>
#include <map>
#include <string>
#include <iostream>

#ifdef _DEBUG
#define YYDEBUG 1
#endif

#define yyerror(x) printf("Parser error on line %d: %s\n", yyline, x); 

extern int yylex();
extern int yyline;
extern FILE *yyin, *yyout;

// variables for adding objects, keeping track of variables
//Object* pObj=0;
//std::map<std::string, Object*> g_objectMap;
//Material* pMat=new Material;
// add more here

//Vector3 __parse_temp_vector;
//std::stack<Matrix4x4> g_kMatrixStack;
//PointLight* pLight=0;

//Vector3& Vertex3(const float& x, const float& y, const float& z);
//Vector3& Vertex3(const Vector3& v);
//void Translate(const float& x, const float& y, const float& z);
//void Rotate(const float& angle, float x, float y, float z); // angle is in degrees
//void Scale(const float& x, const float& y, const float& z);
//Matrix4x4& GetCTM();
//void PushMatrix();
//void PopMatrix();

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
%token GL_BGCOLOR
%token IMG_BGCOLOR

%token CAMERA
%token POS
%token DIR
%token LOOKAT
%token UP
%token FOV

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
        | objectTypes 
        | LIGHT lightTypes '}'          { printf( "Adding Light\n" ); }
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
                printf( "Load Mesh: '%s'", $2+1 );
                //if (!((TriangleMesh*)pObj)->Load(s, GetCTM()))
                    //pObj = 0;
            }
;

globalOptions: /* empty */
        | HEIGHT iExp globalOptions
            { /*g_pImage->Resize(g_pImage->Width(), $2);*/ }
        | WIDTH iExp globalOptions
            { /*g_pImage->Resize($2, g_pImage->Height());*/ }
        | GL_BGCOLOR rExp ',' rExp ',' rExp globalOptions
            { /*g_pCamera->SetBGColor(Vector3($2, $4, $6));*/ }
        | IMG_BGCOLOR rExp ',' rExp ',' rExp globalOptions
            { /*g_pCamera->SetBGColor(Vector3($2, $4, $6));*/ }
;

cameraOptions: /* empty */
        | POS rExp ',' rExp ',' rExp cameraOptions
            { /*g_pCamera->SetEye(Vector3($2, $4, $6));*/ }
        | DIR rExp ',' rExp ',' rExp cameraOptions
            { /*g_pCamera->SetViewDir(Vector3($2, $4, $6));*/ }
        | LOOKAT rExp ',' rExp ',' rExp cameraOptions
            { /*g_pCamera->SetLookAt(Vector3($2, $4, $6));*/ }
        | UP rExp ',' rExp ',' rExp cameraOptions
            { /*g_pCamera->SetUp(Vector3($2, $4, $6));*/ }
        | FOV rExp cameraOptions
            { /*g_pCamera->SetFOV($2);*/ }
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

/*
Matrix4x4& GetCTM()
{
    return g_kMatrixStack.top();
}

void PushMatrix()
{
    g_kMatrixStack.push(g_kMatrixStack.top());
}

void PopMatrix()
{
    if(g_kMatrixStack.size() == 1)
    {
        Warning("Matrix stack empty!  Too many pops!\n");
    }
    else
        g_kMatrixStack.pop();
}

void Translate(const float& x, const float& y, const float& z)
{
    Matrix4x4 m;
    m.SetIdentity();
    m.SetColumn4(Vector4(x, y, z, 1));

    Matrix4x4& ctm = GetCTM();
    ctm *= m;
}

void Scale(const float& x, const float& y, const float& z)
{
    Matrix4x4 m;
    m.SetIdentity();
    m.m11 = x;
    m.m22 = y;
    m.m33 = z;

    Matrix4x4& ctm = GetCTM();
    ctm *= m;
}

void Rotate(const float& angle, float x, float y, float z) // angle is in degrees
{

    float rad = angle*(PI/180.);

    float x2 = x*x;
    float y2 = y*y;
    float z2 = z*z;
    float c = cos(rad);
    float cinv = 1-c;
    float s = sin(rad);
    float xy = x*y;
    float xz = x*z;
    float yz = y*z;
    float xs = x*s;
    float ys = y*s;
    float zs = z*s;
    float xzcinv = xz*cinv;
    float xycinv = xy*cinv;
    float yzcinv = yz*cinv;

    Matrix4x4 m;
    m.SetIdentity();
    m.Set(x2 + c*(1-x2), xy*cinv+zs, xzcinv - ys, 0,
          xycinv - zs, y2 + c*(1-y2), yzcinv + xs, 0,
          xzcinv + ys, yzcinv - xs, z2 + c*(1-z2), 0,
          0, 0, 0, 1);

    g_kMatrixStack.top() *= m;
}

Vector3& Vertex3(const Vector3& v)
{
    __parse_temp_vector = v;
    __parse_temp_vector = g_kMatrixStack.top()*__parse_temp_vector; // do transformation

    return __parse_temp_vector;
}

Vector3& Vertex3(const float& x, const float& y, const float& z)
{
    __parse_temp_vector.Set(x, y, z);
    __parse_temp_vector = g_kMatrixStack.top()*__parse_temp_vector; // do transformation

    return __parse_temp_vector;
}

void ParseFile(FILE* fp)
{
    Matrix4x4 m;
    m.SetIdentity();
    g_kMatrixStack.push(m);

    yyin = fp;
    //yydebug = 1;
    yyparse();
    if (g_kMatrixStack.size() > 1)
        Warning("There were more matrix pushes than pops!\n");
}
*/
