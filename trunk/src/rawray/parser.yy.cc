
/*  A Bison parser, made from parser.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	REAL	258
#define	PARSE_INT	259
#define	STRING	260
#define	PARSE_TRUE	261
#define	PARSE_FALSE	262
#define	ENABLE	263
#define	DISABLE	264
#define	MATH_COS	265
#define	MATH_SIN	266
#define	MATH_TAN	267
#define	MATH_ACOS	268
#define	MATH_ASIN	269
#define	MATH_ATAN	270
#define	MATH_ATAN2	271
#define	MATH_LN	272
#define	MATH_LOG	273
#define	MATH_EXP	274
#define	MATH_SQRT	275
#define	MATH_E	276
#define	MATH_PI	277
#define	GLOBAL	278
#define	WIDTH	279
#define	HEIGHT	280
#define	POS	281
#define	IMG_BGCOLOR	282
#define	GL_BGCOLOR	283
#define	GL_SPHERE_SECTIONS	284
#define	NUM_THREADS	285
#define	RENDER_X_BLOCK	286
#define	RENDER_Y_BLOCK	287
#define	RENDER_HANDLER_SLEEP	288
#define	RENDER_THREAD_SLEEP	289
#define	RENDER_SPINLOCK_SLEEP	290
#define	GAUSSIAN_BLUR_MAX	291
#define	GAUSSIAN_BLUR_SIGMA	292
#define	GL_RENDER_LIGHTS	293
#define	CAMERA	294
#define	DIR	295
#define	LOOKAT	296
#define	UP	297
#define	FOV	298
#define	ASPECT	299
#define	MIN_DRAW	300
#define	MAX_DRAW	301
#define	P0	302
#define	SPIRAL_NUM_SPHERES	303
#define	SPIRAL_RADIUS	304
#define	LORENZ_DT	305
#define	LORENZ_MIN_DISTANCE	306
#define	LORENZ_MAX_DISTANCE	307
#define	LORENZ_SIGMA	308
#define	LORENZ_RHO	309
#define	LORENZ_BETA	310
#define	LORENZ_RADIUS	311
#define	LORENZ_NUM_SPHERES	312
#define	LORENZ_START	313
#define	TRIANGLE	314
#define	V1	315
#define	V2	316
#define	V3	317
#define	N1	318
#define	N2	319
#define	N3	320
#define	MESH	321
#define	LOAD	322
#define	INSTANCE	323
#define	GEOMETRY	324
#define	PUSHMATRIX	325
#define	POPMATRIX	326
#define	ROTATE	327
#define	TRANSLATE	328
#define	SCALE	329
#define	LIGHT	330
#define	POINTLIGHT	331
#define	WATTAGE	332
#define	COLOR	333
#define	SPHERE	334
#define	CENTER	335
#define	RADIUS	336
#define	NEG	337

#line 1 "parser.y"

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


#line 54 "parser.y"
typedef union
{
    float real;
    int integer;
    char* str;
} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		388
#define	YYFLAG		-32768
#define	YYNTBASE	94

#define YYTRANSLATE(x) ((unsigned)(x) <= 337 ? yytranslate[x] : 120)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    92,
    93,    85,    84,    91,    83,     2,    86,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    82,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    88,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    89,     2,    90,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
    76,    77,    78,    79,    80,    81,    87
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     9,    14,    18,    23,    25,    27,    28,
    34,    35,    42,    43,    49,    50,    57,    58,    64,    65,
    72,    73,    79,    80,    87,    88,    96,   104,   112,   120,
   128,   136,   137,   145,   149,   150,   154,   156,   158,   167,
   174,   181,   182,   187,   188,   196,   200,   208,   209,   212,
   213,   217,   221,   229,   237,   241,   245,   249,   253,   257,
   261,   265,   269,   273,   276,   279,   280,   288,   296,   304,
   312,   316,   320,   324,   328,   329,   333,   337,   341,   345,
   349,   353,   357,   361,   365,   369,   377,   379,   381,   383,
   387,   391,   395,   399,   403,   407,   411,   415,   419,   423,
   427,   431,   435,   439,   443,   446,   450,   452,   457,   462,
   467,   472,   477,   482,   487,   492,   497,   502,   504,   506,
   508,   512,   516,   520,   524,   527,   531
};

static const short yyrhs[] = {    -1,
    94,    95,     0,    23,    89,   113,    90,     0,    39,    89,
   114,    90,     0,    75,   109,    90,     0,    47,    89,   115,
    90,     0,    96,     0,   108,     0,     0,    59,    89,    97,
   105,    90,     0,     0,    59,     5,    89,    98,   105,    90,
     0,     0,    66,    89,    99,   112,    90,     0,     0,    66,
     5,    89,   100,   112,    90,     0,     0,    79,    89,   101,
   106,    90,     0,     0,    79,     5,    89,   102,   106,    90,
     0,     0,    68,    89,   103,   107,    90,     0,     0,    68,
     5,    89,   104,   107,    90,     0,     0,    60,   116,    91,
   116,    91,   116,   105,     0,    61,   116,    91,   116,    91,
   116,   105,     0,    62,   116,    91,   116,    91,   116,   105,
     0,    63,   116,    91,   116,    91,   116,   105,     0,    64,
   116,    91,   116,    91,   116,   105,     0,    65,   116,    91,
   116,    91,   116,   105,     0,     0,    80,   116,    91,   116,
    91,   116,   106,     0,    81,   116,   106,     0,     0,    69,
     5,   106,     0,    70,     0,    71,     0,    72,   116,    91,
   116,    91,   116,    91,   116,     0,    73,   116,    91,   116,
    91,   116,     0,    74,   116,    91,   116,    91,   116,     0,
     0,    76,    89,   110,   111,     0,     0,    26,   116,    91,
   116,    91,   116,   111,     0,    77,   116,   111,     0,    78,
   116,    91,   116,    91,   116,   111,     0,     0,    67,     5,
     0,     0,    25,   119,   113,     0,    24,   119,   113,     0,
    28,   116,    91,   116,    91,   116,   113,     0,    27,   116,
    91,   116,    91,   116,   113,     0,    29,   119,   113,     0,
    30,   119,   113,     0,    31,   119,   113,     0,    32,   119,
   113,     0,    33,   119,   113,     0,    34,   119,   113,     0,
    35,   119,   113,     0,    36,   116,   113,     0,    37,   116,
   113,     0,     8,    38,     0,     9,    38,     0,     0,    26,
   116,    91,   116,    91,   116,   114,     0,    40,   116,    91,
   116,    91,   116,   114,     0,    41,   116,    91,   116,    91,
   116,   114,     0,    42,   116,    91,   116,    91,   116,   114,
     0,    43,   116,   114,     0,    44,   116,   114,     0,    45,
   116,   114,     0,    46,   116,   114,     0,     0,    48,   119,
   115,     0,    49,   116,   115,     0,    50,   116,   115,     0,
    51,   116,   115,     0,    52,   116,   115,     0,    53,   116,
   115,     0,    54,   116,   115,     0,    55,   116,   115,     0,
    56,   116,   115,     0,    57,   119,   115,     0,    58,   116,
    91,   116,    91,   116,   115,     0,     3,     0,   119,     0,
   117,     0,   116,    84,   116,     0,   119,    84,   116,     0,
   116,    84,   119,     0,   116,    83,   116,     0,   119,    83,
   116,     0,   116,    83,   119,     0,   116,    85,   116,     0,
   119,    85,   116,     0,   116,    85,   119,     0,   116,    86,
   116,     0,   119,    86,   116,     0,   116,    86,   119,     0,
   116,    88,   116,     0,   119,    88,   116,     0,   116,    88,
   119,     0,    83,   116,     0,    92,   116,    93,     0,   118,
     0,    11,    92,   116,    93,     0,    10,    92,   116,    93,
     0,    12,    92,   116,    93,     0,    14,    92,   116,    93,
     0,    13,    92,   116,    93,     0,    15,    92,   116,    93,
     0,    17,    92,   116,    93,     0,    18,    92,   116,    93,
     0,    19,    92,   116,    93,     0,    20,    92,   116,    93,
     0,    21,     0,    22,     0,     4,     0,   119,    84,   119,
     0,   119,    83,   119,     0,   119,    85,   119,     0,   119,
    86,   119,     0,    83,   119,     0,   119,    88,   119,     0,
    92,   119,    93,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   166,   167,   170,   171,   172,   173,   174,   175,   178,   187,
   193,   203,   209,   216,   222,   231,   237,   247,   253,   265,
   271,   275,   279,   283,   288,   289,   291,   293,   295,   297,
   299,   303,   304,   306,   310,   311,   321,   322,   324,   326,
   328,   332,   343,   345,   346,   348,   350,   354,   355,   363,
   364,   366,   368,   370,   372,   374,   376,   378,   380,   382,
   384,   386,   388,   390,   392,   396,   397,   399,   401,   403,
   405,   407,   409,   411,   415,   416,   418,   420,   422,   424,
   426,   428,   430,   432,   434,   436,   440,   441,   442,   444,
   445,   446,   448,   449,   450,   452,   453,   454,   456,   457,
   458,   460,   461,   462,   464,   465,   466,   469,   470,   471,
   472,   473,   474,   475,   476,   477,   478,   481,   483,   486,
   487,   488,   489,   490,   491,   492,   493
};

static const char * const yytname[] = {   "$","error","$undefined.","REAL","PARSE_INT",
"STRING","PARSE_TRUE","PARSE_FALSE","ENABLE","DISABLE","MATH_COS","MATH_SIN",
"MATH_TAN","MATH_ACOS","MATH_ASIN","MATH_ATAN","MATH_ATAN2","MATH_LN","MATH_LOG",
"MATH_EXP","MATH_SQRT","MATH_E","MATH_PI","GLOBAL","WIDTH","HEIGHT","POS","IMG_BGCOLOR",
"GL_BGCOLOR","GL_SPHERE_SECTIONS","NUM_THREADS","RENDER_X_BLOCK","RENDER_Y_BLOCK",
"RENDER_HANDLER_SLEEP","RENDER_THREAD_SLEEP","RENDER_SPINLOCK_SLEEP","GAUSSIAN_BLUR_MAX",
"GAUSSIAN_BLUR_SIGMA","GL_RENDER_LIGHTS","CAMERA","DIR","LOOKAT","UP","FOV",
"ASPECT","MIN_DRAW","MAX_DRAW","P0","SPIRAL_NUM_SPHERES","SPIRAL_RADIUS","LORENZ_DT",
"LORENZ_MIN_DISTANCE","LORENZ_MAX_DISTANCE","LORENZ_SIGMA","LORENZ_RHO","LORENZ_BETA",
"LORENZ_RADIUS","LORENZ_NUM_SPHERES","LORENZ_START","TRIANGLE","V1","V2","V3",
"N1","N2","N3","MESH","LOAD","INSTANCE","GEOMETRY","PUSHMATRIX","POPMATRIX",
"ROTATE","TRANSLATE","SCALE","LIGHT","POINTLIGHT","WATTAGE","COLOR","SPHERE",
"CENTER","RADIUS","'='","'-'","'+'","'*'","'/'","NEG","'^'","'{'","'}'","','",
"'('","')'","input","block","objectTypes","@1","@2","@3","@4","@5","@6","@7",
"@8","triangleOptions","sphereOptions","instanceOptions","transform","lightTypes",
"@9","lightOptions","meshOptions","globalOptions","cameraOptions","p0Options",
"rExp","fExp","constantExp","iExp",""
};
#endif

static const short yyr1[] = {     0,
    94,    94,    95,    95,    95,    95,    95,    95,    97,    96,
    98,    96,    99,    96,   100,    96,   101,    96,   102,    96,
   103,    96,   104,    96,   105,   105,   105,   105,   105,   105,
   105,   106,   106,   106,   107,   107,   108,   108,   108,   108,
   108,   110,   109,   111,   111,   111,   111,   112,   112,   113,
   113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
   113,   113,   113,   113,   113,   114,   114,   114,   114,   114,
   114,   114,   114,   114,   115,   115,   115,   115,   115,   115,
   115,   115,   115,   115,   115,   115,   116,   116,   116,   116,
   116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
   116,   116,   116,   116,   116,   116,   116,   117,   117,   117,
   117,   117,   117,   117,   117,   117,   117,   118,   118,   119,
   119,   119,   119,   119,   119,   119,   119
};

static const short yyr2[] = {     0,
     0,     2,     4,     4,     3,     4,     1,     1,     0,     5,
     0,     6,     0,     5,     0,     6,     0,     5,     0,     6,
     0,     5,     0,     6,     0,     7,     7,     7,     7,     7,
     7,     0,     7,     3,     0,     3,     1,     1,     8,     6,
     6,     0,     4,     0,     7,     3,     7,     0,     2,     0,
     3,     3,     7,     7,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     2,     2,     0,     7,     7,     7,     7,
     3,     3,     3,     3,     0,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     7,     1,     1,     1,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     2,     3,     1,     4,     4,     4,
     4,     4,     4,     4,     4,     4,     4,     1,     1,     1,
     3,     3,     3,     3,     2,     3,     3
};

static const short yydefact[] = {     1,
     0,     0,     0,     0,     0,     0,     0,    37,    38,     0,
     0,     0,     0,     0,     2,     7,     8,    50,    66,    75,
     0,     9,     0,    13,     0,    21,    87,   120,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   118,   119,
     0,     0,     0,    89,   107,    88,     0,     0,     0,     0,
     0,    17,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
    25,    15,    48,    23,    35,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   105,    88,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    42,     5,    19,    32,    64,    65,     0,     0,
    50,    50,     0,     0,    50,    50,    50,    50,    50,    50,
    50,    50,    50,     3,     0,     0,     0,     0,    66,    66,
    66,    66,     4,    75,    75,    75,    75,    75,    75,    75,
    75,    75,    75,     0,     6,    25,     0,     0,     0,     0,
     0,     0,     0,    48,     0,     0,    35,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   106,
   127,    93,    88,    90,    88,    96,    88,    99,    88,   102,
    88,     0,    94,    88,    91,    88,    97,    88,   100,    88,
   103,    88,     0,     0,    44,    32,     0,     0,     0,   125,
     0,     0,     0,     0,     0,     0,    52,    51,     0,     0,
    55,    56,    57,    58,    59,    60,    61,    62,    63,     0,
     0,     0,     0,    71,    72,    73,    74,    76,    77,    78,
    79,    80,    81,    82,    83,    84,    85,     0,     0,     0,
     0,     0,     0,     0,     0,    10,     0,    49,    14,     0,
    32,    22,   109,   108,   110,   112,   111,   113,   114,   115,
   116,   117,     0,     0,     0,     0,     0,     0,    43,     0,
     0,    32,    18,   122,   121,   123,   124,   126,     0,     0,
     0,     0,     0,     0,     0,    12,     0,     0,     0,     0,
     0,     0,    16,    24,    36,     0,    40,    41,     0,    44,
     0,    20,     0,    34,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
     0,     0,    50,    50,    66,    66,    66,    66,    75,     0,
     0,     0,     0,     0,     0,    39,     0,     0,     0,    54,
    53,    67,    68,    69,    70,    86,    25,    25,    25,    25,
    25,    25,     0,     0,    32,    26,    27,    28,    29,    30,
    31,    44,    44,    33,    45,    47,     0,     0
};

static const short yydefgoto[] = {     1,
    15,    16,    91,   166,    93,   174,   126,   216,    95,   177,
   173,   219,   179,    17,    50,   215,   289,   176,    68,    77,
    89,    43,    44,    45,    46
};

static const short yypact[] = {-32768,
   374,   -74,   -63,   -56,    36,    37,    38,-32768,-32768,   119,
   119,   119,   -48,    39,-32768,-32768,-32768,   140,     8,   230,
   -54,-32768,   -53,-32768,   -44,-32768,-32768,-32768,   -35,   -25,
   -10,    -9,    -8,    32,    43,    50,    55,    74,-32768,-32768,
   119,   119,   238,-32768,-32768,    67,   281,   499,   108,   109,
   111,-32768,   163,   167,    62,    62,   119,   119,    62,    62,
    62,    62,    62,    62,    62,   119,   119,   114,   119,   119,
   119,   119,   119,   119,   119,   119,   118,    62,   119,   119,
   119,   119,   119,   119,   119,   119,    62,   119,   120,-32768,
   229,-32768,   142,-32768,   143,   119,   119,   119,   119,   119,
   119,   119,   119,   119,   119,   125,   128,   -61,   110,   119,
   119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
   119,   119,-32768,-32768,-32768,   -76,-32768,-32768,    62,    62,
   154,   154,   508,   517,   154,   154,   154,   154,   154,   154,
   154,   351,   351,-32768,   526,   535,   544,   553,   220,   220,
   220,   220,-32768,   406,   417,   417,   417,   417,   417,   417,
   417,   417,   406,   562,-32768,   229,   119,   119,   119,   119,
   119,   119,   127,   142,   221,   137,   143,   223,   151,   306,
   339,   434,   440,   446,   452,   458,   464,   470,   476,-32768,
-32768,   -68,    10,   -68,    10,   125,   128,   125,   128,   125,
   128,   571,   -68,    10,   -68,    10,   125,   128,   125,   128,
   125,   128,   580,   589,     3,   -76,   119,   119,   155,   160,
   482,    62,    62,    62,    62,    62,-32768,-32768,   119,   119,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   119,
   119,   119,   119,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   119,   165,   598,
   607,   616,   625,   634,   643,-32768,   168,-32768,-32768,   169,
   -76,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   119,   119,   119,   119,   119,   119,-32768,   177,
   652,   493,-32768,    58,    58,   160,   160,   160,   661,   670,
   679,   688,   697,   706,   715,-32768,   119,   119,   119,   119,
   119,   119,-32768,-32768,-32768,   724,   250,   250,   733,   166,
   742,-32768,   119,-32768,   119,   119,   119,   119,   119,   119,
   119,   751,   760,   769,   778,   787,   796,   119,   119,-32768,
   119,   805,   351,   351,   220,   220,   220,   220,   417,   119,
   119,   119,   119,   119,   119,   250,   814,   823,   119,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   423,   423,   423,   423,
   423,   423,   119,   119,   493,-32768,-32768,-32768,-32768,-32768,
-32768,   166,   166,-32768,-32768,-32768,   253,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -147,  -195,    79,-32768,-32768,-32768,  -304,    83,  -129,  -112,
   -42,   -11,-32768,-32768,   290
};


#define	YYLAST		914


static const short yytable[] = {    47,
    48,   227,   228,   217,   218,   231,   232,   233,   234,   235,
   236,   237,   238,   239,    18,   340,   112,   113,   259,   114,
   290,   110,   111,   112,   113,    19,   114,    49,   286,   106,
   108,   190,    20,    69,    90,    92,   244,   245,   246,   247,
    21,    23,    25,    51,    94,   133,   134,    70,    71,    72,
    73,    74,    75,    76,   142,   143,    96,   145,   146,   147,
   148,   149,   150,   151,   152,    28,    97,   155,   156,   157,
   158,   159,   160,   161,   162,   315,   164,   385,   386,   287,
   288,    98,    99,   100,   180,   181,   182,   183,   184,   185,
   186,   187,   188,   189,   118,   119,   324,   120,   192,   194,
   196,   198,   200,   202,   203,   205,   207,   209,   211,   213,
   214,   248,   249,   250,   251,   252,   253,   254,   255,   256,
   257,    27,    28,   101,    22,    24,    26,    52,    29,    30,
    31,    32,    33,    34,   102,    35,    36,    37,    38,    39,
    40,   103,   224,   225,   129,   226,   104,    53,    54,   116,
   117,   118,   119,   130,   120,   260,   261,   262,   263,   264,
   265,    53,    54,    55,    56,   105,    57,    58,    59,    60,
    61,    62,    63,    64,    65,    66,    67,    55,    56,   384,
    57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
    67,   286,   116,   117,   118,   119,   123,   120,   124,   125,
   127,    41,   191,   144,   128,   291,   292,   153,   175,   165,
    42,   178,   114,   360,   361,   120,   266,   299,   300,   376,
   377,   378,   379,   380,   381,   268,   269,   271,   301,   302,
   303,   304,   362,   363,   364,   365,   222,   223,   224,   225,
   272,   226,   287,   288,   293,    69,   305,   226,   110,   111,
   112,   113,   388,   114,   306,   270,   267,   313,   314,    70,
    71,    72,    73,    74,    75,    76,   322,     0,     0,     0,
     0,   316,   317,   318,   319,   320,   321,    78,    79,    80,
    81,    82,    83,    84,    85,    86,    87,    88,   167,   168,
   169,   170,   171,   172,     0,   332,   333,   334,   335,   336,
   337,     0,   110,   111,   112,   113,   366,   114,     0,     0,
     0,   342,     0,   343,   344,   345,   346,   347,   348,   349,
   110,   111,   112,   113,     0,   114,   356,   357,   115,   358,
   107,   109,   110,   111,   112,   113,     0,   114,   367,   368,
   369,   370,   371,   372,   131,   132,     0,   375,   135,   136,
   137,   138,   139,   140,   141,     0,     0,     0,    53,    54,
     0,   382,   383,   110,   111,   112,   113,   154,   114,     0,
     0,   121,     0,   387,    55,    56,   163,    57,    58,    59,
    60,    61,    62,    63,    64,    65,    66,    67,   110,   111,
   112,   113,     0,   114,     0,     0,     2,     0,   273,   193,
   195,   197,   199,   201,     0,   204,   206,   208,   210,   212,
     0,     0,     3,     0,     0,     0,     0,     0,   220,   221,
     4,   110,   111,   112,   113,     0,   114,     0,     0,     0,
     0,   274,     5,   110,   111,   112,   113,     0,   114,     6,
     0,     7,     0,     8,     9,    10,    11,    12,    13,     0,
     0,     0,    14,    78,    79,    80,    81,    82,    83,    84,
    85,    86,    87,    88,    78,    79,    80,    81,    82,    83,
    84,    85,    86,    87,    88,     0,     0,     0,     0,     0,
     0,     0,   167,   168,   169,   170,   171,   172,   222,   223,
   224,   225,     0,   226,     0,     0,     0,     0,     0,   110,
   111,   112,   113,     0,   114,   110,   111,   112,   113,     0,
   114,   294,   295,   296,   297,   298,   110,   111,   112,   113,
     0,   114,   110,   111,   112,   113,   275,   114,   110,   111,
   112,   113,   276,   114,   110,   111,   112,   113,   277,   114,
   110,   111,   112,   113,   278,   114,   110,   111,   112,   113,
   279,   114,   110,   111,   112,   113,   280,   114,   110,   111,
   112,   113,   281,   114,   222,   223,   224,   225,   282,   226,
     0,     0,   217,   218,   191,   110,   111,   112,   113,     0,
   114,   110,   111,   112,   113,     0,   114,     0,     0,   122,
   110,   111,   112,   113,     0,   114,     0,     0,   229,   110,
   111,   112,   113,     0,   114,     0,     0,   230,   110,   111,
   112,   113,     0,   114,     0,     0,   240,   110,   111,   112,
   113,     0,   114,     0,     0,   241,   110,   111,   112,   113,
     0,   114,     0,     0,   242,   110,   111,   112,   113,     0,
   114,     0,     0,   243,   110,   111,   112,   113,     0,   114,
     0,     0,   258,   110,   111,   112,   113,     0,   114,     0,
     0,   283,   110,   111,   112,   113,     0,   114,     0,     0,
   284,   110,   111,   112,   113,     0,   114,     0,     0,   285,
   110,   111,   112,   113,     0,   114,     0,     0,   307,   110,
   111,   112,   113,     0,   114,     0,     0,   308,   110,   111,
   112,   113,     0,   114,     0,     0,   309,   110,   111,   112,
   113,     0,   114,     0,     0,   310,   110,   111,   112,   113,
     0,   114,     0,     0,   311,   110,   111,   112,   113,     0,
   114,     0,     0,   312,   110,   111,   112,   113,     0,   114,
     0,     0,   323,   110,   111,   112,   113,     0,   114,     0,
     0,   325,   110,   111,   112,   113,     0,   114,     0,     0,
   326,   110,   111,   112,   113,     0,   114,     0,     0,   327,
   110,   111,   112,   113,     0,   114,     0,     0,   328,   110,
   111,   112,   113,     0,   114,     0,     0,   329,   110,   111,
   112,   113,     0,   114,     0,     0,   330,   110,   111,   112,
   113,     0,   114,     0,     0,   331,   110,   111,   112,   113,
     0,   114,     0,     0,   338,   110,   111,   112,   113,     0,
   114,     0,     0,   339,   110,   111,   112,   113,     0,   114,
     0,     0,   341,   110,   111,   112,   113,     0,   114,     0,
     0,   350,   110,   111,   112,   113,     0,   114,     0,     0,
   351,   110,   111,   112,   113,     0,   114,     0,     0,   352,
   110,   111,   112,   113,     0,   114,     0,     0,   353,   110,
   111,   112,   113,     0,   114,     0,     0,   354,   110,   111,
   112,   113,     0,   114,     0,     0,   355,   110,   111,   112,
   113,     0,   114,     0,     0,   359,   110,   111,   112,   113,
     0,   114,     0,     0,   373,   110,   111,   112,   113,     0,
   114,     0,     0,   374
};

static const short yycheck[] = {    11,
    12,   131,   132,    80,    81,   135,   136,   137,   138,   139,
   140,   141,   142,   143,    89,   320,    85,    86,   166,    88,
   216,    83,    84,    85,    86,    89,    88,    76,    26,    41,
    42,    93,    89,    26,    89,    89,   149,   150,   151,   152,
     5,     5,     5,     5,    89,    57,    58,    40,    41,    42,
    43,    44,    45,    46,    66,    67,    92,    69,    70,    71,
    72,    73,    74,    75,    76,     4,    92,    79,    80,    81,
    82,    83,    84,    85,    86,   271,    88,   382,   383,    77,
    78,    92,    92,    92,    96,    97,    98,    99,   100,   101,
   102,   103,   104,   105,    85,    86,   292,    88,   110,   111,
   112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
   122,   154,   155,   156,   157,   158,   159,   160,   161,   162,
   163,     3,     4,    92,    89,    89,    89,    89,    10,    11,
    12,    13,    14,    15,    92,    17,    18,    19,    20,    21,
    22,    92,    85,    86,    83,    88,    92,     8,     9,    83,
    84,    85,    86,    92,    88,   167,   168,   169,   170,   171,
   172,     8,     9,    24,    25,    92,    27,    28,    29,    30,
    31,    32,    33,    34,    35,    36,    37,    24,    25,   375,
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
    37,    26,    83,    84,    85,    86,    89,    88,    90,    89,
    38,    83,    93,    90,    38,   217,   218,    90,    67,    90,
    92,    69,    88,   343,   344,    88,    90,   229,   230,   367,
   368,   369,   370,   371,   372,     5,    90,     5,   240,   241,
   242,   243,   345,   346,   347,   348,    83,    84,    85,    86,
    90,    88,    77,    78,    90,    26,   258,    88,    83,    84,
    85,    86,     0,    88,    90,   177,   174,    90,    90,    40,
    41,    42,    43,    44,    45,    46,    90,    -1,    -1,    -1,
    -1,   283,   284,   285,   286,   287,   288,    48,    49,    50,
    51,    52,    53,    54,    55,    56,    57,    58,    60,    61,
    62,    63,    64,    65,    -1,   307,   308,   309,   310,   311,
   312,    -1,    83,    84,    85,    86,   349,    88,    -1,    -1,
    -1,   323,    -1,   325,   326,   327,   328,   329,   330,   331,
    83,    84,    85,    86,    -1,    88,   338,   339,    91,   341,
    41,    42,    83,    84,    85,    86,    -1,    88,   350,   351,
   352,   353,   354,   355,    55,    56,    -1,   359,    59,    60,
    61,    62,    63,    64,    65,    -1,    -1,    -1,     8,     9,
    -1,   373,   374,    83,    84,    85,    86,    78,    88,    -1,
    -1,    91,    -1,     0,    24,    25,    87,    27,    28,    29,
    30,    31,    32,    33,    34,    35,    36,    37,    83,    84,
    85,    86,    -1,    88,    -1,    -1,    23,    -1,    93,   110,
   111,   112,   113,   114,    -1,   116,   117,   118,   119,   120,
    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,   129,   130,
    47,    83,    84,    85,    86,    -1,    88,    -1,    -1,    -1,
    -1,    93,    59,    83,    84,    85,    86,    -1,    88,    66,
    -1,    68,    -1,    70,    71,    72,    73,    74,    75,    -1,
    -1,    -1,    79,    48,    49,    50,    51,    52,    53,    54,
    55,    56,    57,    58,    48,    49,    50,    51,    52,    53,
    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    60,    61,    62,    63,    64,    65,    83,    84,
    85,    86,    -1,    88,    -1,    -1,    -1,    -1,    -1,    83,
    84,    85,    86,    -1,    88,    83,    84,    85,    86,    -1,
    88,   222,   223,   224,   225,   226,    83,    84,    85,    86,
    -1,    88,    83,    84,    85,    86,    93,    88,    83,    84,
    85,    86,    93,    88,    83,    84,    85,    86,    93,    88,
    83,    84,    85,    86,    93,    88,    83,    84,    85,    86,
    93,    88,    83,    84,    85,    86,    93,    88,    83,    84,
    85,    86,    93,    88,    83,    84,    85,    86,    93,    88,
    -1,    -1,    80,    81,    93,    83,    84,    85,    86,    -1,
    88,    83,    84,    85,    86,    -1,    88,    -1,    -1,    91,
    83,    84,    85,    86,    -1,    88,    -1,    -1,    91,    83,
    84,    85,    86,    -1,    88,    -1,    -1,    91,    83,    84,
    85,    86,    -1,    88,    -1,    -1,    91,    83,    84,    85,
    86,    -1,    88,    -1,    -1,    91,    83,    84,    85,    86,
    -1,    88,    -1,    -1,    91,    83,    84,    85,    86,    -1,
    88,    -1,    -1,    91,    83,    84,    85,    86,    -1,    88,
    -1,    -1,    91,    83,    84,    85,    86,    -1,    88,    -1,
    -1,    91,    83,    84,    85,    86,    -1,    88,    -1,    -1,
    91,    83,    84,    85,    86,    -1,    88,    -1,    -1,    91,
    83,    84,    85,    86,    -1,    88,    -1,    -1,    91,    83,
    84,    85,    86,    -1,    88,    -1,    -1,    91,    83,    84,
    85,    86,    -1,    88,    -1,    -1,    91,    83,    84,    85,
    86,    -1,    88,    -1,    -1,    91,    83,    84,    85,    86,
    -1,    88,    -1,    -1,    91,    83,    84,    85,    86,    -1,
    88,    -1,    -1,    91,    83,    84,    85,    86,    -1,    88,
    -1,    -1,    91,    83,    84,    85,    86,    -1,    88,    -1,
    -1,    91,    83,    84,    85,    86,    -1,    88,    -1,    -1,
    91,    83,    84,    85,    86,    -1,    88,    -1,    -1,    91,
    83,    84,    85,    86,    -1,    88,    -1,    -1,    91,    83,
    84,    85,    86,    -1,    88,    -1,    -1,    91,    83,    84,
    85,    86,    -1,    88,    -1,    -1,    91,    83,    84,    85,
    86,    -1,    88,    -1,    -1,    91,    83,    84,    85,    86,
    -1,    88,    -1,    -1,    91,    83,    84,    85,    86,    -1,
    88,    -1,    -1,    91,    83,    84,    85,    86,    -1,    88,
    -1,    -1,    91,    83,    84,    85,    86,    -1,    88,    -1,
    -1,    91,    83,    84,    85,    86,    -1,    88,    -1,    -1,
    91,    83,    84,    85,    86,    -1,    88,    -1,    -1,    91,
    83,    84,    85,    86,    -1,    88,    -1,    -1,    91,    83,
    84,    85,    86,    -1,    88,    -1,    -1,    91,    83,    84,
    85,    86,    -1,    88,    -1,    -1,    91,    83,    84,    85,
    86,    -1,    88,    -1,    -1,    91,    83,    84,    85,    86,
    -1,    88,    -1,    -1,    91,    83,    84,    85,    86,    -1,
    88,    -1,    -1,    91
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 3:
#line 170 "parser.y"
{ memmove( &yyval, &yyval, sizeof(yyval) ); printf("\n"); ;
    break;}
case 4:
#line 171 "parser.y"
{ printf("\n"); ;
    break;}
case 5:
#line 172 "parser.y"
{ printf("\n"); g_scene->AddLight( g_light ); g_light = NULL; ;
    break;}
case 6:
#line 173 "parser.y"
{ printf("\n"); ;
    break;}
case 7:
#line 174 "parser.y"
{ printf("\n"); ;
    break;}
case 8:
#line 175 "parser.y"
{ printf("\n"); ;
    break;}
case 9:
#line 180 "parser.y"
{
                g_mesh = new rawray::TriangleMesh();
                #ifdef VERBOSE_NEW
                printf( "MESH: %x", g_mesh );
                #endif
                //((TriangleMesh*)pObj)->CreateSingleTriangle();
            ;
    break;}
case 10:
#line 188 "parser.y"
{
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            ;
    break;}
case 11:
#line 194 "parser.y"
{
                g_mesh = new rawray::TriangleMesh();
                #ifdef VERBOSE_NEW
                printf( "MESH: %x", g_mesh );
                #endif
                
                //g_objectMap[$2] = pObj;
                //((TriangleMesh*)pObj)->CreateSingleTriangle();
            ;
    break;}
case 12:
#line 204 "parser.y"
{
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            ;
    break;}
case 13:
#line 210 "parser.y"
{
                g_mesh = new rawray::TriangleMesh();
                #ifdef VERBOSE_NEW
                printf( "MESH: %x", g_mesh );
                #endif
            ;
    break;}
case 14:
#line 217 "parser.y"
{
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            ;
    break;}
case 15:
#line 223 "parser.y"
{
                g_mesh = new rawray::TriangleMesh();
                #ifdef VERBOSE_NEW
                printf( "MESH: %x", g_mesh );
                #endif
                
                //g_objectMap[$2] = pObj;
            ;
    break;}
case 16:
#line 232 "parser.y"
{
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            ;
    break;}
case 17:
#line 238 "parser.y"
{
                g_obj = new rawray::Sphere( math::Vector3(0),
                                            1.0f,
                                            g_material );
                                            
                #ifdef VERBOSE_NEW
                printf( "SPHERE: %x", g_obj );
                #endif
            ;
    break;}
case 18:
#line 248 "parser.y"
{
                g_scene->AddObject( g_obj );
                g_obj = NULL;
            ;
    break;}
case 19:
#line 254 "parser.y"
{
                g_obj = new rawray::Sphere( math::Vector3(0),
                                            1.0f,
                                            g_material );
                
                #ifdef VERBOSE_NEW
                printf( "SPHERE: %x", g_obj );
                #endif
                
                g_objectMap[yyvsp[-1].str] = g_obj;
            ;
    break;}
case 20:
#line 266 "parser.y"
{
                g_scene->AddObject( g_obj );
                g_obj = NULL;
            ;
    break;}
case 21:
#line 272 "parser.y"
{
                printf( "Instance not supported\n" );
            ;
    break;}
case 22:
#line 276 "parser.y"
{
            ;
    break;}
case 23:
#line 280 "parser.y"
{
                printf( "Named Instance not supported\n" );
            ;
    break;}
case 24:
#line 284 "parser.y"
{
            ;
    break;}
case 26:
#line 290 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 27:
#line 292 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 28:
#line 294 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 29:
#line 296 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 30:
#line 298 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 31:
#line 300 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 33:
#line 305 "parser.y"
{ ((rawray::Sphere*)g_obj)->SetCenter( math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 34:
#line 307 "parser.y"
{ ((rawray::Sphere*)g_obj)->SetRadius( yyvsp[-1].real ); ;
    break;}
case 36:
#line 312 "parser.y"
{
                //std::map<std::string, Object*>::const_iterator it = g_objectMap.find ($2);
                //if (it != g_objectMap.end ())
                //{
                    //((Instance*)pObj)->SetGeometry(it->second, GetCTM());
                //}
            ;
    break;}
case 37:
#line 321 "parser.y"
{ /*PushMatrix();*/ ;
    break;}
case 38:
#line 323 "parser.y"
{ /*PopMatrix();*/ ;
    break;}
case 39:
#line 325 "parser.y"
{ /*Rotate($2, $4, $6, $8);*/ ;
    break;}
case 40:
#line 327 "parser.y"
{ /*Translate($2, $4, $6);*/ ;
    break;}
case 41:
#line 329 "parser.y"
{ /*Scale($2, $4, $6);*/ ;
    break;}
case 42:
#line 333 "parser.y"
{
                printf( "new light\n" ); 
                g_light = new rawray::Light();
                
                #ifdef VERBOSE_NEW
                printf( "LIGHT: %x\n", g_light );
                #endif
            ;
    break;}
case 45:
#line 347 "parser.y"
{ printf( "pos = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_light->SetPosition( math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 46:
#line 349 "parser.y"
{ printf( "wattage = %f\n", yyvsp[-1].real ); g_light->SetWattage( yyvsp[-1].real ); ;
    break;}
case 47:
#line 351 "parser.y"
{ printf( "color = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_light->SetColor( math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 49:
#line 356 "parser.y"
{
                yyvsp[0].str[strlen(yyvsp[0].str)-1]=0;
                printf( "Loading Mesh: '%s'\n", yyvsp[0].str+1 );
                g_mesh->LoadOBJ( yyvsp[0].str+1 );
            ;
    break;}
case 51:
#line 365 "parser.y"
{ printf( "height = %d\n", yyvsp[-1].integer ); g_image->Resize( g_image->GetWidth(), rawray::options::global::win_height = yyvsp[-1].integer ); ;
    break;}
case 52:
#line 367 "parser.y"
{ printf( "width = %d\n", yyvsp[-1].integer ); g_image->Resize( rawray::options::global::win_width = yyvsp[-1].integer, g_image->GetHeight() ); ;
    break;}
case 53:
#line 369 "parser.y"
{ printf( "gl bg color = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); rawray::options::global::gl_bg_color = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 54:
#line 371 "parser.y"
{ printf( "img bg color = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); rawray::options::global::img_bg_color = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 55:
#line 373 "parser.y"
{ printf( "gl sphere sections = %d\n", rawray::options::global::gl_sphere_sections = yyvsp[-1].integer ); ;
    break;}
case 56:
#line 375 "parser.y"
{ printf( "num threads = %d\n", rawray::options::global::num_threads = yyvsp[-1].integer ); ;
    break;}
case 57:
#line 377 "parser.y"
{ printf( "render x block = %d\n", rawray::options::global::render_x_block = yyvsp[-1].integer ); ;
    break;}
case 58:
#line 379 "parser.y"
{ printf( "render y block = %d\n", rawray::options::global::render_y_block = yyvsp[-1].integer ); ;
    break;}
case 59:
#line 381 "parser.y"
{ printf( "render handler sleep = %d\n", rawray::options::global::render_handler_sleep = yyvsp[-1].integer ); ;
    break;}
case 60:
#line 383 "parser.y"
{ printf( "render thread sleep = %d\n", rawray::options::global::render_thread_sleep = yyvsp[-1].integer ); ;
    break;}
case 61:
#line 385 "parser.y"
{ printf( "render spinlock sleep = %d\n", rawray::options::global::render_spinlock_sleep = yyvsp[-1].integer ); ;
    break;}
case 62:
#line 387 "parser.y"
{ printf( "gaussian blur max = %f\n", rawray::options::global::gaussian_blur_max = yyvsp[-1].real ); ;
    break;}
case 63:
#line 389 "parser.y"
{ printf( "gaussian blur sigma = %f\n", rawray::options::global::gaussian_blur_sigma = yyvsp[-1].real ); ;
    break;}
case 64:
#line 391 "parser.y"
{ printf( "enabling rendering of lights in gl\n" ); rawray::options::global::gl_render_lights = true; ;
    break;}
case 65:
#line 393 "parser.y"
{ printf( "disabling rendering of lights in gl\n" ); rawray::options::global::gl_render_lights = false; ;
    break;}
case 67:
#line 398 "parser.y"
{ printf( "camera pos = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_camera->SetEye( rawray::options::camera::eye = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 68:
#line 400 "parser.y"
{ printf( "camera dir = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_camera->SetViewDir( rawray::options::camera::view = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 69:
#line 402 "parser.y"
{ printf( "camera look at = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_camera->SetLookAt( rawray::options::camera::lookat = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 70:
#line 404 "parser.y"
{ printf( "camera up = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_camera->SetUp( rawray::options::camera::up = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 71:
#line 406 "parser.y"
{ printf( "camera fov = %f\n", yyvsp[-1].real ); g_camera->SetFOV( rawray::options::camera::fov = yyvsp[-1].real ); ;
    break;}
case 72:
#line 408 "parser.y"
{ printf( "camera aspect ratio = %f\n", yyvsp[-1].real ); g_camera->SetAspect( rawray::options::camera::aspect = yyvsp[-1].real ); ;
    break;}
case 73:
#line 410 "parser.y"
{ printf( "camera min draw = %f\n", yyvsp[-1].real ); g_camera->SetMinDraw( rawray::options::camera::min_draw = yyvsp[-1].real ); ;
    break;}
case 74:
#line 412 "parser.y"
{ printf( "camera max draw = %f\n", yyvsp[-1].real ); g_camera->SetMaxDraw( rawray::options::camera::max_draw = yyvsp[-1].real ); ;
    break;}
case 76:
#line 417 "parser.y"
{ printf( "spiral num spheres = %d\n", rawray::options::p0::spiral_num_spheres = yyvsp[-1].integer ); ;
    break;}
case 77:
#line 419 "parser.y"
{ printf( "spiral radius = %f\n", rawray::options::p0::spiral_radius = yyvsp[-1].real ); ;
    break;}
case 78:
#line 421 "parser.y"
{ printf( "lorenz dt = %f\n", rawray::options::p0::lorenz_dt = yyvsp[-1].real ); ;
    break;}
case 79:
#line 423 "parser.y"
{ printf( "lorenz min distance = %f\n", rawray::options::p0::lorenz_min_distance = yyvsp[-1].real ); ;
    break;}
case 80:
#line 425 "parser.y"
{ printf( "lorenz max distance = %f\n", rawray::options::p0::lorenz_max_distance = yyvsp[-1].real ); ;
    break;}
case 81:
#line 427 "parser.y"
{ printf( "lorenz sigma = %f\n", rawray::options::p0::lorenz_sigma = yyvsp[-1].real ); ;
    break;}
case 82:
#line 429 "parser.y"
{ printf( "lorenz rho = %f\n", rawray::options::p0::lorenz_rho = yyvsp[-1].real ); ;
    break;}
case 83:
#line 431 "parser.y"
{ printf( "lorenz beta = %f\n", rawray::options::p0::lorenz_beta = yyvsp[-1].real ); ;
    break;}
case 84:
#line 433 "parser.y"
{ printf( "lorenz radius = %f\n", rawray::options::p0::lorenz_radius = yyvsp[-1].real ); ;
    break;}
case 85:
#line 435 "parser.y"
{ printf( "lorenz num spheres = %d\n", rawray::options::p0::lorenz_num_spheres = yyvsp[-1].integer ); ;
    break;}
case 86:
#line 437 "parser.y"
{ printf( "lorenz start = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); rawray::options::p0::lorenz_start = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 87:
#line 440 "parser.y"
{ yyval.real = yyvsp[0].real; ;
    break;}
case 88:
#line 441 "parser.y"
{ yyval.real = yyvsp[0].integer; ;
    break;}
case 89:
#line 442 "parser.y"
{ yyval.real = yyvsp[0].real; ;
    break;}
case 90:
#line 444 "parser.y"
{ yyval.real = yyvsp[-2].real + yyvsp[0].real; ;
    break;}
case 91:
#line 445 "parser.y"
{ yyval.real = yyvsp[-2].integer + yyvsp[0].real; ;
    break;}
case 92:
#line 446 "parser.y"
{ yyval.real = yyvsp[-2].real + yyvsp[0].integer; ;
    break;}
case 93:
#line 448 "parser.y"
{ yyval.real = yyvsp[-2].real - yyvsp[0].real; ;
    break;}
case 94:
#line 449 "parser.y"
{ yyval.real = yyvsp[-2].integer - yyvsp[0].real; ;
    break;}
case 95:
#line 450 "parser.y"
{ yyval.real = yyvsp[-2].real - yyvsp[0].integer; ;
    break;}
case 96:
#line 452 "parser.y"
{ yyval.real = yyvsp[-2].real * yyvsp[0].real; ;
    break;}
case 97:
#line 453 "parser.y"
{ yyval.real = yyvsp[-2].integer * yyvsp[0].real; ;
    break;}
case 98:
#line 454 "parser.y"
{ yyval.real = yyvsp[-2].real * yyvsp[0].integer; ;
    break;}
case 99:
#line 456 "parser.y"
{ yyval.real = yyvsp[-2].real / yyvsp[0].real; ;
    break;}
case 100:
#line 457 "parser.y"
{ yyval.real = yyvsp[-2].integer / yyvsp[0].real; ;
    break;}
case 101:
#line 458 "parser.y"
{ yyval.real = yyvsp[-2].real / yyvsp[0].integer; ;
    break;}
case 102:
#line 460 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].real), float (yyvsp[0].real)); ;
    break;}
case 103:
#line 461 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].integer), float (yyvsp[0].real)); ;
    break;}
case 104:
#line 462 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].real), float (yyvsp[0].integer)); ;
    break;}
case 105:
#line 464 "parser.y"
{ yyval.real = -yyvsp[0].real; ;
    break;}
case 106:
#line 465 "parser.y"
{ yyval.real = yyvsp[-1].real; ;
    break;}
case 108:
#line 469 "parser.y"
{yyval.real = sin(yyvsp[-1].real); ;
    break;}
case 109:
#line 470 "parser.y"
{yyval.real = cos(yyvsp[-1].real); ;
    break;}
case 110:
#line 471 "parser.y"
{yyval.real = tan(yyvsp[-1].real); ;
    break;}
case 111:
#line 472 "parser.y"
{yyval.real = asin(yyvsp[-1].real); ;
    break;}
case 112:
#line 473 "parser.y"
{yyval.real = acos(yyvsp[-1].real); ;
    break;}
case 113:
#line 474 "parser.y"
{yyval.real = atan(yyvsp[-1].real); ;
    break;}
case 114:
#line 475 "parser.y"
{yyval.real = log(yyvsp[-1].real); ;
    break;}
case 115:
#line 476 "parser.y"
{yyval.real = log10(yyvsp[-1].real); ;
    break;}
case 116:
#line 477 "parser.y"
{yyval.real = exp(yyvsp[-1].real); ;
    break;}
case 117:
#line 478 "parser.y"
{yyval.real = sqrt(yyvsp[-1].real); ;
    break;}
case 118:
#line 482 "parser.y"
{ yyval.real = 2.718281828459f; ;
    break;}
case 119:
#line 483 "parser.y"
{ yyval.real = 3.141592653589793f; ;
    break;}
case 120:
#line 486 "parser.y"
{ yyval.integer = yyvsp[0].integer; ;
    break;}
case 121:
#line 487 "parser.y"
{ yyval.integer = yyvsp[-2].integer + yyvsp[0].integer; ;
    break;}
case 122:
#line 488 "parser.y"
{ yyval.integer = yyvsp[-2].integer - yyvsp[0].integer; ;
    break;}
case 123:
#line 489 "parser.y"
{ yyval.integer = yyvsp[-2].integer * yyvsp[0].integer; ;
    break;}
case 124:
#line 490 "parser.y"
{ yyval.integer = yyvsp[-2].integer / yyvsp[0].integer; ;
    break;}
case 125:
#line 491 "parser.y"
{ yyval.integer = -yyvsp[0].integer; ;
    break;}
case 126:
#line 492 "parser.y"
{ yyval.integer = (int)pow((float)yyvsp[-2].integer, (float)yyvsp[0].integer); ;
    break;}
case 127:
#line 493 "parser.y"
{ yyval.integer = yyvsp[-1].integer; ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 497 "parser.y"

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
    //yydebug = 1;
    
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
