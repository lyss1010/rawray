
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
#define	HEADLESS	294
#define	CAMERA	295
#define	DIR	296
#define	LOOKAT	297
#define	UP	298
#define	FOV	299
#define	ASPECT	300
#define	MIN_DRAW	301
#define	MAX_DRAW	302
#define	P0	303
#define	SPIRAL_NUM_SPHERES	304
#define	SPIRAL_RADIUS	305
#define	LORENZ_DT	306
#define	LORENZ_MIN_DISTANCE	307
#define	LORENZ_MAX_DISTANCE	308
#define	LORENZ_SIGMA	309
#define	LORENZ_RHO	310
#define	LORENZ_BETA	311
#define	LORENZ_RADIUS	312
#define	LORENZ_NUM_SPHERES	313
#define	LORENZ_START	314
#define	TRIANGLE	315
#define	V1	316
#define	V2	317
#define	V3	318
#define	N1	319
#define	N2	320
#define	N3	321
#define	MESH	322
#define	LOAD	323
#define	INSTANCE	324
#define	GEOMETRY	325
#define	PUSHMATRIX	326
#define	POPMATRIX	327
#define	ROTATE	328
#define	TRANSLATE	329
#define	SCALE	330
#define	LIGHT	331
#define	POINTLIGHT	332
#define	WATTAGE	333
#define	COLOR	334
#define	SPHERE	335
#define	CENTER	336
#define	RADIUS	337
#define	NEG	338

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



#define	YYFINAL		394
#define	YYFLAG		-32768
#define	YYNTBASE	95

#define YYTRANSLATE(x) ((unsigned)(x) <= 338 ? yytranslate[x] : 121)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    93,
    94,    86,    85,    92,    84,     2,    87,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    83,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    89,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    90,     2,    91,     2,     2,     2,     2,     2,
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
    76,    77,    78,    79,    80,    81,    82,    88
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     9,    14,    18,    23,    25,    27,    28,
    34,    35,    42,    43,    49,    50,    57,    58,    64,    65,
    72,    73,    79,    80,    87,    88,    96,   104,   112,   120,
   128,   136,   137,   145,   149,   150,   154,   156,   158,   167,
   174,   181,   182,   187,   188,   196,   200,   208,   209,   212,
   213,   217,   221,   229,   237,   241,   245,   249,   253,   257,
   261,   265,   269,   273,   277,   281,   285,   289,   290,   298,
   306,   314,   322,   326,   330,   334,   338,   339,   343,   347,
   351,   355,   359,   363,   367,   371,   375,   379,   387,   389,
   391,   393,   397,   401,   405,   409,   413,   417,   421,   425,
   429,   433,   437,   441,   445,   449,   453,   456,   460,   462,
   467,   472,   477,   482,   487,   492,   497,   502,   507,   512,
   514,   516,   518,   522,   526,   530,   534,   537,   541
};

static const short yyrhs[] = {    -1,
    95,    96,     0,    23,    90,   114,    91,     0,    40,    90,
   115,    91,     0,    76,   110,    91,     0,    48,    90,   116,
    91,     0,    97,     0,   109,     0,     0,    60,    90,    98,
   106,    91,     0,     0,    60,     5,    90,    99,   106,    91,
     0,     0,    67,    90,   100,   113,    91,     0,     0,    67,
     5,    90,   101,   113,    91,     0,     0,    80,    90,   102,
   107,    91,     0,     0,    80,     5,    90,   103,   107,    91,
     0,     0,    69,    90,   104,   108,    91,     0,     0,    69,
     5,    90,   105,   108,    91,     0,     0,    61,   117,    92,
   117,    92,   117,   106,     0,    62,   117,    92,   117,    92,
   117,   106,     0,    63,   117,    92,   117,    92,   117,   106,
     0,    64,   117,    92,   117,    92,   117,   106,     0,    65,
   117,    92,   117,    92,   117,   106,     0,    66,   117,    92,
   117,    92,   117,   106,     0,     0,    81,   117,    92,   117,
    92,   117,   107,     0,    82,   117,   107,     0,     0,    70,
     5,   107,     0,    71,     0,    72,     0,    73,   117,    92,
   117,    92,   117,    92,   117,     0,    74,   117,    92,   117,
    92,   117,     0,    75,   117,    92,   117,    92,   117,     0,
     0,    77,    90,   111,   112,     0,     0,    26,   117,    92,
   117,    92,   117,   112,     0,    78,   117,   112,     0,    79,
   117,    92,   117,    92,   117,   112,     0,     0,    68,     5,
     0,     0,    25,   120,   114,     0,    24,   120,   114,     0,
    28,   117,    92,   117,    92,   117,   114,     0,    27,   117,
    92,   117,    92,   117,   114,     0,    29,   120,   114,     0,
    30,   120,   114,     0,    31,   120,   114,     0,    32,   120,
   114,     0,    33,   120,   114,     0,    34,   120,   114,     0,
    35,   120,   114,     0,    36,   117,   114,     0,    37,   117,
   114,     0,     8,    38,   114,     0,     9,    38,   114,     0,
     8,    39,   114,     0,     9,    39,   114,     0,     0,    26,
   117,    92,   117,    92,   117,   115,     0,    41,   117,    92,
   117,    92,   117,   115,     0,    42,   117,    92,   117,    92,
   117,   115,     0,    43,   117,    92,   117,    92,   117,   115,
     0,    44,   117,   115,     0,    45,   117,   115,     0,    46,
   117,   115,     0,    47,   117,   115,     0,     0,    49,   120,
   116,     0,    50,   117,   116,     0,    51,   117,   116,     0,
    52,   117,   116,     0,    53,   117,   116,     0,    54,   117,
   116,     0,    55,   117,   116,     0,    56,   117,   116,     0,
    57,   117,   116,     0,    58,   120,   116,     0,    59,   117,
    92,   117,    92,   117,   116,     0,     3,     0,   120,     0,
   118,     0,   117,    85,   117,     0,   120,    85,   117,     0,
   117,    85,   120,     0,   117,    84,   117,     0,   120,    84,
   117,     0,   117,    84,   120,     0,   117,    86,   117,     0,
   120,    86,   117,     0,   117,    86,   120,     0,   117,    87,
   117,     0,   120,    87,   117,     0,   117,    87,   120,     0,
   117,    89,   117,     0,   120,    89,   117,     0,   117,    89,
   120,     0,    84,   117,     0,    93,   117,    94,     0,   119,
     0,    11,    93,   117,    94,     0,    10,    93,   117,    94,
     0,    12,    93,   117,    94,     0,    14,    93,   117,    94,
     0,    13,    93,   117,    94,     0,    15,    93,   117,    94,
     0,    17,    93,   117,    94,     0,    18,    93,   117,    94,
     0,    19,    93,   117,    94,     0,    20,    93,   117,    94,
     0,    21,     0,    22,     0,     4,     0,   120,    85,   120,
     0,   120,    84,   120,     0,   120,    86,   120,     0,   120,
    87,   120,     0,    84,   120,     0,   120,    89,   120,     0,
    93,   120,    94,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   168,   169,   172,   173,   174,   175,   176,   177,   180,   189,
   195,   205,   211,   218,   224,   233,   239,   249,   255,   267,
   273,   277,   281,   285,   290,   291,   293,   295,   297,   299,
   301,   305,   306,   308,   312,   313,   323,   324,   326,   328,
   330,   334,   345,   347,   348,   350,   352,   356,   357,   365,
   366,   368,   370,   372,   374,   376,   378,   380,   382,   384,
   386,   388,   390,   392,   394,   396,   398,   402,   403,   405,
   407,   409,   411,   413,   415,   417,   421,   422,   424,   426,
   428,   430,   432,   434,   436,   438,   440,   442,   446,   447,
   448,   450,   451,   452,   454,   455,   456,   458,   459,   460,
   462,   463,   464,   466,   467,   468,   470,   471,   472,   475,
   476,   477,   478,   479,   480,   481,   482,   483,   484,   487,
   489,   492,   493,   494,   495,   496,   497,   498,   499
};

static const char * const yytname[] = {   "$","error","$undefined.","REAL","PARSE_INT",
"STRING","PARSE_TRUE","PARSE_FALSE","ENABLE","DISABLE","MATH_COS","MATH_SIN",
"MATH_TAN","MATH_ACOS","MATH_ASIN","MATH_ATAN","MATH_ATAN2","MATH_LN","MATH_LOG",
"MATH_EXP","MATH_SQRT","MATH_E","MATH_PI","GLOBAL","WIDTH","HEIGHT","POS","IMG_BGCOLOR",
"GL_BGCOLOR","GL_SPHERE_SECTIONS","NUM_THREADS","RENDER_X_BLOCK","RENDER_Y_BLOCK",
"RENDER_HANDLER_SLEEP","RENDER_THREAD_SLEEP","RENDER_SPINLOCK_SLEEP","GAUSSIAN_BLUR_MAX",
"GAUSSIAN_BLUR_SIGMA","GL_RENDER_LIGHTS","HEADLESS","CAMERA","DIR","LOOKAT",
"UP","FOV","ASPECT","MIN_DRAW","MAX_DRAW","P0","SPIRAL_NUM_SPHERES","SPIRAL_RADIUS",
"LORENZ_DT","LORENZ_MIN_DISTANCE","LORENZ_MAX_DISTANCE","LORENZ_SIGMA","LORENZ_RHO",
"LORENZ_BETA","LORENZ_RADIUS","LORENZ_NUM_SPHERES","LORENZ_START","TRIANGLE",
"V1","V2","V3","N1","N2","N3","MESH","LOAD","INSTANCE","GEOMETRY","PUSHMATRIX",
"POPMATRIX","ROTATE","TRANSLATE","SCALE","LIGHT","POINTLIGHT","WATTAGE","COLOR",
"SPHERE","CENTER","RADIUS","'='","'-'","'+'","'*'","'/'","NEG","'^'","'{'","'}'",
"','","'('","')'","input","block","objectTypes","@1","@2","@3","@4","@5","@6",
"@7","@8","triangleOptions","sphereOptions","instanceOptions","transform","lightTypes",
"@9","lightOptions","meshOptions","globalOptions","cameraOptions","p0Options",
"rExp","fExp","constantExp","iExp",""
};
#endif

static const short yyr1[] = {     0,
    95,    95,    96,    96,    96,    96,    96,    96,    98,    97,
    99,    97,   100,    97,   101,    97,   102,    97,   103,    97,
   104,    97,   105,    97,   106,   106,   106,   106,   106,   106,
   106,   107,   107,   107,   108,   108,   109,   109,   109,   109,
   109,   111,   110,   112,   112,   112,   112,   113,   113,   114,
   114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
   114,   114,   114,   114,   114,   114,   114,   115,   115,   115,
   115,   115,   115,   115,   115,   115,   116,   116,   116,   116,
   116,   116,   116,   116,   116,   116,   116,   116,   117,   117,
   117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
   117,   117,   117,   117,   117,   117,   117,   117,   117,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   119,
   119,   120,   120,   120,   120,   120,   120,   120,   120
};

static const short yyr2[] = {     0,
     0,     2,     4,     4,     3,     4,     1,     1,     0,     5,
     0,     6,     0,     5,     0,     6,     0,     5,     0,     6,
     0,     5,     0,     6,     0,     7,     7,     7,     7,     7,
     7,     0,     7,     3,     0,     3,     1,     1,     8,     6,
     6,     0,     4,     0,     7,     3,     7,     0,     2,     0,
     3,     3,     7,     7,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     0,     7,     7,
     7,     7,     3,     3,     3,     3,     0,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     7,     1,     1,
     1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     2,     3,     1,     4,
     4,     4,     4,     4,     4,     4,     4,     4,     4,     1,
     1,     1,     3,     3,     3,     3,     2,     3,     3
};

static const short yydefact[] = {     1,
     0,     0,     0,     0,     0,     0,     0,    37,    38,     0,
     0,     0,     0,     0,     2,     7,     8,    50,    68,    77,
     0,     9,     0,    13,     0,    21,    89,   122,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   120,   121,
     0,     0,     0,    91,   109,    90,     0,     0,     0,     0,
     0,    17,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
    25,    15,    48,    23,    35,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   107,    90,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    42,     5,    19,    32,    50,    50,    50,    50,
     0,     0,    50,    50,     0,     0,    50,    50,    50,    50,
    50,    50,    50,    50,    50,     3,     0,     0,     0,     0,
    68,    68,    68,    68,     4,    77,    77,    77,    77,    77,
    77,    77,    77,    77,    77,     0,     6,    25,     0,     0,
     0,     0,     0,     0,     0,    48,     0,     0,    35,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   108,   129,    95,    90,    92,    90,    98,    90,   101,
    90,   104,    90,     0,    96,    90,    93,    90,    99,    90,
   102,    90,   105,    90,     0,     0,    44,    32,     0,     0,
     0,    64,    66,    65,    67,   127,     0,     0,     0,     0,
     0,     0,    52,    51,     0,     0,    55,    56,    57,    58,
    59,    60,    61,    62,    63,     0,     0,     0,     0,    73,
    74,    75,    76,    78,    79,    80,    81,    82,    83,    84,
    85,    86,    87,     0,     0,     0,     0,     0,     0,     0,
     0,    10,     0,    49,    14,     0,    32,    22,   111,   110,
   112,   114,   113,   115,   116,   117,   118,   119,     0,     0,
     0,     0,     0,     0,    43,     0,     0,    32,    18,   124,
   123,   125,   126,   128,     0,     0,     0,     0,     0,     0,
     0,    12,     0,     0,     0,     0,     0,     0,    16,    24,
    36,     0,    40,    41,     0,    44,     0,    20,     0,    34,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    46,     0,     0,    50,    50,
    68,    68,    68,    68,    77,     0,     0,     0,     0,     0,
     0,    39,     0,     0,     0,    54,    53,    69,    70,    71,
    72,    88,    25,    25,    25,    25,    25,    25,     0,     0,
    32,    26,    27,    28,    29,    30,    31,    44,    44,    33,
    45,    47,     0,     0
};

static const short yydefgoto[] = {     1,
    15,    16,    91,   168,    93,   176,   126,   218,    95,   179,
   175,   221,   181,    17,    50,   217,   295,   178,    68,    77,
    89,    43,    44,    45,    46
};

static const short yypact[] = {-32768,
   378,   -81,   -67,   -58,     7,     8,    38,-32768,-32768,   119,
   119,   119,   -41,    45,-32768,-32768,-32768,   145,   250,   432,
   -33,-32768,   -14,-32768,    -9,-32768,-32768,-32768,   -55,   -40,
   -39,   -13,    31,    33,    34,    49,    50,    51,-32768,-32768,
   119,   119,   115,-32768,-32768,   433,   243,   504,    -8,    -7,
    55,-32768,   -36,   -10,    63,    63,   119,   119,    63,    63,
    63,    63,    63,    63,    63,   119,   119,    57,   119,   119,
   119,   119,   119,   119,   119,   119,    58,    63,   119,   119,
   119,   119,   119,   119,   119,   119,    63,   119,    59,-32768,
   278,-32768,   -16,-32768,    13,   119,   119,   119,   119,   119,
   119,   119,   119,   119,   119,    62,    66,   286,   311,   119,
   119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
   119,   119,-32768,-32768,-32768,   -37,   145,   145,   145,   145,
    63,    63,   159,   159,   513,   522,   159,   159,   159,   159,
   159,   159,   159,   357,   357,-32768,   531,   540,   549,   558,
   228,   228,   228,   228,-32768,   410,   421,   421,   421,   421,
   421,   421,   421,   421,   410,   567,-32768,   278,   119,   119,
   119,   119,   119,   119,    61,   -16,   152,    73,    13,   160,
    75,   335,   346,   427,   445,   451,   457,   463,   469,   475,
   481,-32768,-32768,   -62,   -52,   -62,   -52,    62,    66,    62,
    66,    62,    66,   576,   -62,   -52,   -62,   -52,    62,    66,
    62,    66,    62,    66,   585,   594,     0,   -37,   119,   119,
    80,-32768,-32768,-32768,-32768,    96,   487,    63,    63,    63,
    63,    63,-32768,-32768,   119,   119,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   119,   119,   119,   119,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,   119,   107,   603,   612,   621,   630,   639,
   648,-32768,   114,-32768,-32768,   120,   -37,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   119,   119,
   119,   119,   119,   119,-32768,   128,   657,   498,-32768,   -38,
   -38,    96,    96,    96,   666,   675,   684,   693,   702,   711,
   720,-32768,   119,   119,   119,   119,   119,   119,-32768,-32768,
-32768,   729,   837,   837,   738,   171,   747,-32768,   119,-32768,
   119,   119,   119,   119,   119,   119,   119,   756,   765,   774,
   783,   792,   801,   119,   119,-32768,   119,   810,   357,   357,
   228,   228,   228,   228,   421,   119,   119,   119,   119,   119,
   119,   837,   819,   828,   119,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   200,   200,   200,   200,   200,   200,   119,   119,
   498,-32768,-32768,-32768,-32768,-32768,-32768,   171,   171,-32768,
-32768,-32768,   206,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -160,  -152,    41,-32768,-32768,-32768,  -293,    46,  -123,  -112,
   -44,   -11,-32768,-32768,   296
};


#define	YYLAST		926


static const short yytable[] = {    47,
    48,   127,   128,   222,   223,   224,   225,   265,    18,   233,
   234,    21,    23,   237,   238,   239,   240,   241,   242,   243,
   244,   245,    19,   112,   113,   292,   114,   129,   130,   106,
   108,    20,   346,   118,   119,    49,   120,    96,   250,   251,
   252,   253,    25,   219,   220,   135,   136,   230,   231,    51,
   232,   177,    97,    98,   144,   145,    90,   147,   148,   149,
   150,   151,   152,   153,   154,   296,    28,   157,   158,   159,
   160,   161,   162,   163,   164,    92,   166,   293,   294,    99,
    94,   123,   180,   124,   182,   183,   184,   185,   186,   187,
   188,   189,   190,   191,   391,   392,    22,    24,   194,   196,
   198,   200,   202,   204,   205,   207,   209,   211,   213,   215,
   216,   254,   255,   256,   257,   258,   259,   260,   261,   262,
   263,    27,    28,   100,   321,   101,   102,    26,    29,    30,
    31,    32,    33,    34,    52,    35,    36,    37,    38,    39,
    40,   103,   104,   105,   125,   330,   131,   146,   155,   167,
   114,   272,    53,    54,   120,   132,   274,   266,   267,   268,
   269,   270,   271,   275,   277,   278,    53,    54,    55,    56,
   299,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    55,    56,   232,    57,    58,    59,    60,    61,
    62,    63,    64,    65,    66,    67,   292,   312,   110,   111,
   112,   113,    41,   114,   319,   394,   115,   297,   298,     0,
   320,    42,   382,   383,   384,   385,   386,   387,   328,   276,
     0,   273,     0,   305,   306,   366,   367,     0,   390,     0,
     0,     0,     0,     0,   307,   308,   309,   310,   368,   369,
   370,   371,   228,   229,   230,   231,     0,   232,   293,   294,
     0,     0,   311,    69,   110,   111,   112,   113,     0,   114,
   169,   170,   171,   172,   173,   174,     0,     0,    70,    71,
    72,    73,    74,    75,    76,    69,     0,   322,   323,   324,
   325,   326,   327,   110,   111,   112,   113,     0,   114,     0,
    70,    71,    72,    73,    74,    75,    76,     0,     0,     0,
     0,   338,   339,   340,   341,   342,   343,     0,     0,     0,
   372,   110,   111,   112,   113,     0,   114,   348,     0,   349,
   350,   351,   352,   353,   354,   355,   110,   111,   112,   113,
     0,   114,   362,   363,   121,   364,   107,   109,   169,   170,
   171,   172,   173,   174,   373,   374,   375,   376,   377,   378,
   133,   134,     0,   381,   137,   138,   139,   140,   141,   142,
   143,     0,     0,     0,    53,    54,     0,   388,   389,   110,
   111,   112,   113,   156,   114,     0,     0,   393,     0,   192,
    55,    56,   165,    57,    58,    59,    60,    61,    62,    63,
    64,    65,    66,    67,   116,   117,   118,   119,     0,   120,
     2,     0,     0,     0,   193,   195,   197,   199,   201,   203,
     0,   206,   208,   210,   212,   214,     0,     3,   110,   111,
   112,   113,     0,   114,     0,     4,   226,   227,   279,   110,
   111,   112,   113,     0,   114,     0,     0,     5,     0,   280,
   110,   111,   112,   113,     6,   114,     7,     0,     8,     9,
    10,    11,    12,    13,     0,     0,     0,    14,    78,    79,
    80,    81,    82,    83,    84,    85,    86,    87,    88,    78,
    79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
    78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
    88,     0,     0,   228,   229,   230,   231,     0,   232,     0,
     0,     0,     0,     0,   110,   111,   112,   113,     0,   114,
   110,   111,   112,   113,     0,   114,   116,   117,   118,   119,
   281,   120,     0,   300,   301,   302,   303,   304,   110,   111,
   112,   113,     0,   114,   110,   111,   112,   113,   282,   114,
   110,   111,   112,   113,   283,   114,   110,   111,   112,   113,
   284,   114,   110,   111,   112,   113,   285,   114,   110,   111,
   112,   113,   286,   114,   110,   111,   112,   113,   287,   114,
   228,   229,   230,   231,   288,   232,     0,     0,   219,   220,
   193,   110,   111,   112,   113,     0,   114,   110,   111,   112,
   113,     0,   114,     0,     0,   122,   110,   111,   112,   113,
     0,   114,     0,     0,   235,   110,   111,   112,   113,     0,
   114,     0,     0,   236,   110,   111,   112,   113,     0,   114,
     0,     0,   246,   110,   111,   112,   113,     0,   114,     0,
     0,   247,   110,   111,   112,   113,     0,   114,     0,     0,
   248,   110,   111,   112,   113,     0,   114,     0,     0,   249,
   110,   111,   112,   113,     0,   114,     0,     0,   264,   110,
   111,   112,   113,     0,   114,     0,     0,   289,   110,   111,
   112,   113,     0,   114,     0,     0,   290,   110,   111,   112,
   113,     0,   114,     0,     0,   291,   110,   111,   112,   113,
     0,   114,     0,     0,   313,   110,   111,   112,   113,     0,
   114,     0,     0,   314,   110,   111,   112,   113,     0,   114,
     0,     0,   315,   110,   111,   112,   113,     0,   114,     0,
     0,   316,   110,   111,   112,   113,     0,   114,     0,     0,
   317,   110,   111,   112,   113,     0,   114,     0,     0,   318,
   110,   111,   112,   113,     0,   114,     0,     0,   329,   110,
   111,   112,   113,     0,   114,     0,     0,   331,   110,   111,
   112,   113,     0,   114,     0,     0,   332,   110,   111,   112,
   113,     0,   114,     0,     0,   333,   110,   111,   112,   113,
     0,   114,     0,     0,   334,   110,   111,   112,   113,     0,
   114,     0,     0,   335,   110,   111,   112,   113,     0,   114,
     0,     0,   336,   110,   111,   112,   113,     0,   114,     0,
     0,   337,   110,   111,   112,   113,     0,   114,     0,     0,
   344,   110,   111,   112,   113,     0,   114,     0,     0,   345,
   110,   111,   112,   113,     0,   114,     0,     0,   347,   110,
   111,   112,   113,     0,   114,     0,     0,   356,   110,   111,
   112,   113,     0,   114,     0,     0,   357,   110,   111,   112,
   113,     0,   114,     0,     0,   358,   110,   111,   112,   113,
     0,   114,     0,     0,   359,   110,   111,   112,   113,     0,
   114,     0,     0,   360,   110,   111,   112,   113,     0,   114,
     0,     0,   361,   110,   111,   112,   113,     0,   114,     0,
     0,   365,   110,   111,   112,   113,     0,   114,     0,     0,
   379,   110,   111,   112,   113,     0,   114,     0,     0,   380,
   110,   111,   112,   113,     0,   114
};

static const short yycheck[] = {    11,
    12,    38,    39,   127,   128,   129,   130,   168,    90,   133,
   134,     5,     5,   137,   138,   139,   140,   141,   142,   143,
   144,   145,    90,    86,    87,    26,    89,    38,    39,    41,
    42,    90,   326,    86,    87,    77,    89,    93,   151,   152,
   153,   154,     5,    81,    82,    57,    58,    86,    87,     5,
    89,    68,    93,    93,    66,    67,    90,    69,    70,    71,
    72,    73,    74,    75,    76,   218,     4,    79,    80,    81,
    82,    83,    84,    85,    86,    90,    88,    78,    79,    93,
    90,    90,    70,    91,    96,    97,    98,    99,   100,   101,
   102,   103,   104,   105,   388,   389,    90,    90,   110,   111,
   112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
   122,   156,   157,   158,   159,   160,   161,   162,   163,   164,
   165,     3,     4,    93,   277,    93,    93,    90,    10,    11,
    12,    13,    14,    15,    90,    17,    18,    19,    20,    21,
    22,    93,    93,    93,    90,   298,    84,    91,    91,    91,
    89,    91,     8,     9,    89,    93,     5,   169,   170,   171,
   172,   173,   174,    91,     5,    91,     8,     9,    24,    25,
    91,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    24,    25,    89,    27,    28,    29,    30,    31,
    32,    33,    34,    35,    36,    37,    26,    91,    84,    85,
    86,    87,    84,    89,    91,     0,    92,   219,   220,    -1,
    91,    93,   373,   374,   375,   376,   377,   378,    91,   179,
    -1,   176,    -1,   235,   236,   349,   350,    -1,   381,    -1,
    -1,    -1,    -1,    -1,   246,   247,   248,   249,   351,   352,
   353,   354,    84,    85,    86,    87,    -1,    89,    78,    79,
    -1,    -1,   264,    26,    84,    85,    86,    87,    -1,    89,
    61,    62,    63,    64,    65,    66,    -1,    -1,    41,    42,
    43,    44,    45,    46,    47,    26,    -1,   289,   290,   291,
   292,   293,   294,    84,    85,    86,    87,    -1,    89,    -1,
    41,    42,    43,    44,    45,    46,    47,    -1,    -1,    -1,
    -1,   313,   314,   315,   316,   317,   318,    -1,    -1,    -1,
   355,    84,    85,    86,    87,    -1,    89,   329,    -1,   331,
   332,   333,   334,   335,   336,   337,    84,    85,    86,    87,
    -1,    89,   344,   345,    92,   347,    41,    42,    61,    62,
    63,    64,    65,    66,   356,   357,   358,   359,   360,   361,
    55,    56,    -1,   365,    59,    60,    61,    62,    63,    64,
    65,    -1,    -1,    -1,     8,     9,    -1,   379,   380,    84,
    85,    86,    87,    78,    89,    -1,    -1,     0,    -1,    94,
    24,    25,    87,    27,    28,    29,    30,    31,    32,    33,
    34,    35,    36,    37,    84,    85,    86,    87,    -1,    89,
    23,    -1,    -1,    -1,    94,   110,   111,   112,   113,   114,
    -1,   116,   117,   118,   119,   120,    -1,    40,    84,    85,
    86,    87,    -1,    89,    -1,    48,   131,   132,    94,    84,
    85,    86,    87,    -1,    89,    -1,    -1,    60,    -1,    94,
    84,    85,    86,    87,    67,    89,    69,    -1,    71,    72,
    73,    74,    75,    76,    -1,    -1,    -1,    80,    49,    50,
    51,    52,    53,    54,    55,    56,    57,    58,    59,    49,
    50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
    49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
    59,    -1,    -1,    84,    85,    86,    87,    -1,    89,    -1,
    -1,    -1,    -1,    -1,    84,    85,    86,    87,    -1,    89,
    84,    85,    86,    87,    -1,    89,    84,    85,    86,    87,
    94,    89,    -1,   228,   229,   230,   231,   232,    84,    85,
    86,    87,    -1,    89,    84,    85,    86,    87,    94,    89,
    84,    85,    86,    87,    94,    89,    84,    85,    86,    87,
    94,    89,    84,    85,    86,    87,    94,    89,    84,    85,
    86,    87,    94,    89,    84,    85,    86,    87,    94,    89,
    84,    85,    86,    87,    94,    89,    -1,    -1,    81,    82,
    94,    84,    85,    86,    87,    -1,    89,    84,    85,    86,
    87,    -1,    89,    -1,    -1,    92,    84,    85,    86,    87,
    -1,    89,    -1,    -1,    92,    84,    85,    86,    87,    -1,
    89,    -1,    -1,    92,    84,    85,    86,    87,    -1,    89,
    -1,    -1,    92,    84,    85,    86,    87,    -1,    89,    -1,
    -1,    92,    84,    85,    86,    87,    -1,    89,    -1,    -1,
    92,    84,    85,    86,    87,    -1,    89,    -1,    -1,    92,
    84,    85,    86,    87,    -1,    89,    -1,    -1,    92,    84,
    85,    86,    87,    -1,    89,    -1,    -1,    92,    84,    85,
    86,    87,    -1,    89,    -1,    -1,    92,    84,    85,    86,
    87,    -1,    89,    -1,    -1,    92,    84,    85,    86,    87,
    -1,    89,    -1,    -1,    92,    84,    85,    86,    87,    -1,
    89,    -1,    -1,    92,    84,    85,    86,    87,    -1,    89,
    -1,    -1,    92,    84,    85,    86,    87,    -1,    89,    -1,
    -1,    92,    84,    85,    86,    87,    -1,    89,    -1,    -1,
    92,    84,    85,    86,    87,    -1,    89,    -1,    -1,    92,
    84,    85,    86,    87,    -1,    89,    -1,    -1,    92,    84,
    85,    86,    87,    -1,    89,    -1,    -1,    92,    84,    85,
    86,    87,    -1,    89,    -1,    -1,    92,    84,    85,    86,
    87,    -1,    89,    -1,    -1,    92,    84,    85,    86,    87,
    -1,    89,    -1,    -1,    92,    84,    85,    86,    87,    -1,
    89,    -1,    -1,    92,    84,    85,    86,    87,    -1,    89,
    -1,    -1,    92,    84,    85,    86,    87,    -1,    89,    -1,
    -1,    92,    84,    85,    86,    87,    -1,    89,    -1,    -1,
    92,    84,    85,    86,    87,    -1,    89,    -1,    -1,    92,
    84,    85,    86,    87,    -1,    89,    -1,    -1,    92,    84,
    85,    86,    87,    -1,    89,    -1,    -1,    92,    84,    85,
    86,    87,    -1,    89,    -1,    -1,    92,    84,    85,    86,
    87,    -1,    89,    -1,    -1,    92,    84,    85,    86,    87,
    -1,    89,    -1,    -1,    92,    84,    85,    86,    87,    -1,
    89,    -1,    -1,    92,    84,    85,    86,    87,    -1,    89,
    -1,    -1,    92,    84,    85,    86,    87,    -1,    89,    -1,
    -1,    92,    84,    85,    86,    87,    -1,    89,    -1,    -1,
    92,    84,    85,    86,    87,    -1,    89,    -1,    -1,    92,
    84,    85,    86,    87,    -1,    89
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
#line 172 "parser.y"
{ memmove( &yyval, &yyval, sizeof(yyval) ); printf("\n"); ;
    break;}
case 4:
#line 173 "parser.y"
{ printf("\n"); ;
    break;}
case 5:
#line 174 "parser.y"
{ printf("\n"); g_scene->AddLight( g_light ); g_light = NULL; ;
    break;}
case 6:
#line 175 "parser.y"
{ printf("\n"); ;
    break;}
case 7:
#line 176 "parser.y"
{ printf("\n"); ;
    break;}
case 8:
#line 177 "parser.y"
{ printf("\n"); ;
    break;}
case 9:
#line 182 "parser.y"
{
                g_mesh = new rawray::TriangleMesh();
                #ifdef VERBOSE_NEW
                printf( "MESH: %x", g_mesh );
                #endif
                //((TriangleMesh*)pObj)->CreateSingleTriangle();
            ;
    break;}
case 10:
#line 190 "parser.y"
{
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            ;
    break;}
case 11:
#line 196 "parser.y"
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
#line 206 "parser.y"
{
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            ;
    break;}
case 13:
#line 212 "parser.y"
{
                g_mesh = new rawray::TriangleMesh();
                #ifdef VERBOSE_NEW
                printf( "MESH: %x", g_mesh );
                #endif
            ;
    break;}
case 14:
#line 219 "parser.y"
{
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            ;
    break;}
case 15:
#line 225 "parser.y"
{
                g_mesh = new rawray::TriangleMesh();
                #ifdef VERBOSE_NEW
                printf( "MESH: %x", g_mesh );
                #endif
                
                //g_objectMap[$2] = pObj;
            ;
    break;}
case 16:
#line 234 "parser.y"
{
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            ;
    break;}
case 17:
#line 240 "parser.y"
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
#line 250 "parser.y"
{
                g_scene->AddObject( g_obj );
                g_obj = NULL;
            ;
    break;}
case 19:
#line 256 "parser.y"
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
#line 268 "parser.y"
{
                g_scene->AddObject( g_obj );
                g_obj = NULL;
            ;
    break;}
case 21:
#line 274 "parser.y"
{
                printf( "Instance not supported\n" );
            ;
    break;}
case 22:
#line 278 "parser.y"
{
            ;
    break;}
case 23:
#line 282 "parser.y"
{
                printf( "Named Instance not supported\n" );
            ;
    break;}
case 24:
#line 286 "parser.y"
{
            ;
    break;}
case 26:
#line 292 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 27:
#line 294 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 28:
#line 296 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 29:
#line 298 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 30:
#line 300 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 31:
#line 302 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 33:
#line 307 "parser.y"
{ ((rawray::Sphere*)g_obj)->SetCenter( math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 34:
#line 309 "parser.y"
{ ((rawray::Sphere*)g_obj)->SetRadius( yyvsp[-1].real ); ;
    break;}
case 36:
#line 314 "parser.y"
{
                //std::map<std::string, Object*>::const_iterator it = g_objectMap.find ($2);
                //if (it != g_objectMap.end ())
                //{
                    //((Instance*)pObj)->SetGeometry(it->second, GetCTM());
                //}
            ;
    break;}
case 37:
#line 323 "parser.y"
{ /*PushMatrix();*/ ;
    break;}
case 38:
#line 325 "parser.y"
{ /*PopMatrix();*/ ;
    break;}
case 39:
#line 327 "parser.y"
{ /*Rotate($2, $4, $6, $8);*/ ;
    break;}
case 40:
#line 329 "parser.y"
{ /*Translate($2, $4, $6);*/ ;
    break;}
case 41:
#line 331 "parser.y"
{ /*Scale($2, $4, $6);*/ ;
    break;}
case 42:
#line 335 "parser.y"
{
                printf( "new light\n" ); 
                g_light = new rawray::Light();
                
                #ifdef VERBOSE_NEW
                printf( "LIGHT: %x\n", g_light );
                #endif
            ;
    break;}
case 45:
#line 349 "parser.y"
{ printf( "pos = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_light->SetPosition( math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 46:
#line 351 "parser.y"
{ printf( "wattage = %f\n", yyvsp[-1].real ); g_light->SetWattage( yyvsp[-1].real ); ;
    break;}
case 47:
#line 353 "parser.y"
{ printf( "color = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_light->SetColor( math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 49:
#line 358 "parser.y"
{
                yyvsp[0].str[strlen(yyvsp[0].str)-1]=0;
                printf( "Loading Mesh: '%s'\n", yyvsp[0].str+1 );
                g_mesh->LoadOBJ( yyvsp[0].str+1 );
            ;
    break;}
case 51:
#line 367 "parser.y"
{ printf( "height = %d\n", yyvsp[-1].integer ); g_image->Resize( g_image->GetWidth(), rawray::options::global::win_height = yyvsp[-1].integer ); ;
    break;}
case 52:
#line 369 "parser.y"
{ printf( "width = %d\n", yyvsp[-1].integer ); g_image->Resize( rawray::options::global::win_width = yyvsp[-1].integer, g_image->GetHeight() ); ;
    break;}
case 53:
#line 371 "parser.y"
{ printf( "gl bg color = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); rawray::options::global::gl_bg_color = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 54:
#line 373 "parser.y"
{ printf( "img bg color = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); rawray::options::global::img_bg_color = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 55:
#line 375 "parser.y"
{ printf( "gl sphere sections = %d\n", rawray::options::global::gl_sphere_sections = yyvsp[-1].integer ); ;
    break;}
case 56:
#line 377 "parser.y"
{ printf( "num threads = %d\n", rawray::options::global::num_threads = yyvsp[-1].integer ); ;
    break;}
case 57:
#line 379 "parser.y"
{ printf( "render x block = %d\n", rawray::options::global::render_x_block = yyvsp[-1].integer ); ;
    break;}
case 58:
#line 381 "parser.y"
{ printf( "render y block = %d\n", rawray::options::global::render_y_block = yyvsp[-1].integer ); ;
    break;}
case 59:
#line 383 "parser.y"
{ printf( "render handler sleep = %d\n", rawray::options::global::render_handler_sleep = yyvsp[-1].integer ); ;
    break;}
case 60:
#line 385 "parser.y"
{ printf( "render thread sleep = %d\n", rawray::options::global::render_thread_sleep = yyvsp[-1].integer ); ;
    break;}
case 61:
#line 387 "parser.y"
{ printf( "render spinlock sleep = %d\n", rawray::options::global::render_spinlock_sleep = yyvsp[-1].integer ); ;
    break;}
case 62:
#line 389 "parser.y"
{ printf( "gaussian blur max = %f\n", rawray::options::global::gaussian_blur_max = yyvsp[-1].real ); ;
    break;}
case 63:
#line 391 "parser.y"
{ printf( "gaussian blur sigma = %f\n", rawray::options::global::gaussian_blur_sigma = yyvsp[-1].real ); ;
    break;}
case 64:
#line 393 "parser.y"
{ printf( "enabling rendering of lights in gl\n" ); rawray::options::global::gl_render_lights = true; ;
    break;}
case 65:
#line 395 "parser.y"
{ printf( "disabling rendering of lights in gl\n" ); rawray::options::global::gl_render_lights = false; ;
    break;}
case 66:
#line 397 "parser.y"
{ printf( "enabling headless mode\n" ); rawray::options::global::headless = true; ;
    break;}
case 67:
#line 399 "parser.y"
{ printf( "disabling headless mode\n" ); rawray::options::global::headless = false; ;
    break;}
case 69:
#line 404 "parser.y"
{ printf( "camera pos = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_camera->SetEye( rawray::options::camera::eye = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 70:
#line 406 "parser.y"
{ printf( "camera dir = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_camera->SetViewDir( rawray::options::camera::view = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 71:
#line 408 "parser.y"
{ printf( "camera look at = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_camera->SetLookAt( rawray::options::camera::lookat = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 72:
#line 410 "parser.y"
{ printf( "camera up = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_camera->SetUp( rawray::options::camera::up = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 73:
#line 412 "parser.y"
{ printf( "camera fov = %f\n", yyvsp[-1].real ); g_camera->SetFOV( rawray::options::camera::fov = yyvsp[-1].real ); ;
    break;}
case 74:
#line 414 "parser.y"
{ printf( "camera aspect ratio = %f\n", yyvsp[-1].real ); g_camera->SetAspect( rawray::options::camera::aspect = yyvsp[-1].real ); ;
    break;}
case 75:
#line 416 "parser.y"
{ printf( "camera min draw = %f\n", yyvsp[-1].real ); g_camera->SetMinDraw( rawray::options::camera::min_draw = yyvsp[-1].real ); ;
    break;}
case 76:
#line 418 "parser.y"
{ printf( "camera max draw = %f\n", yyvsp[-1].real ); g_camera->SetMaxDraw( rawray::options::camera::max_draw = yyvsp[-1].real ); ;
    break;}
case 78:
#line 423 "parser.y"
{ printf( "spiral num spheres = %d\n", rawray::options::p0::spiral_num_spheres = yyvsp[-1].integer ); ;
    break;}
case 79:
#line 425 "parser.y"
{ printf( "spiral radius = %f\n", rawray::options::p0::spiral_radius = yyvsp[-1].real ); ;
    break;}
case 80:
#line 427 "parser.y"
{ printf( "lorenz dt = %f\n", rawray::options::p0::lorenz_dt = yyvsp[-1].real ); ;
    break;}
case 81:
#line 429 "parser.y"
{ printf( "lorenz min distance = %f\n", rawray::options::p0::lorenz_min_distance = yyvsp[-1].real ); ;
    break;}
case 82:
#line 431 "parser.y"
{ printf( "lorenz max distance = %f\n", rawray::options::p0::lorenz_max_distance = yyvsp[-1].real ); ;
    break;}
case 83:
#line 433 "parser.y"
{ printf( "lorenz sigma = %f\n", rawray::options::p0::lorenz_sigma = yyvsp[-1].real ); ;
    break;}
case 84:
#line 435 "parser.y"
{ printf( "lorenz rho = %f\n", rawray::options::p0::lorenz_rho = yyvsp[-1].real ); ;
    break;}
case 85:
#line 437 "parser.y"
{ printf( "lorenz beta = %f\n", rawray::options::p0::lorenz_beta = yyvsp[-1].real ); ;
    break;}
case 86:
#line 439 "parser.y"
{ printf( "lorenz radius = %f\n", rawray::options::p0::lorenz_radius = yyvsp[-1].real ); ;
    break;}
case 87:
#line 441 "parser.y"
{ printf( "lorenz num spheres = %d\n", rawray::options::p0::lorenz_num_spheres = yyvsp[-1].integer ); ;
    break;}
case 88:
#line 443 "parser.y"
{ printf( "lorenz start = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); rawray::options::p0::lorenz_start = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 89:
#line 446 "parser.y"
{ yyval.real = yyvsp[0].real; ;
    break;}
case 90:
#line 447 "parser.y"
{ yyval.real = yyvsp[0].integer; ;
    break;}
case 91:
#line 448 "parser.y"
{ yyval.real = yyvsp[0].real; ;
    break;}
case 92:
#line 450 "parser.y"
{ yyval.real = yyvsp[-2].real + yyvsp[0].real; ;
    break;}
case 93:
#line 451 "parser.y"
{ yyval.real = yyvsp[-2].integer + yyvsp[0].real; ;
    break;}
case 94:
#line 452 "parser.y"
{ yyval.real = yyvsp[-2].real + yyvsp[0].integer; ;
    break;}
case 95:
#line 454 "parser.y"
{ yyval.real = yyvsp[-2].real - yyvsp[0].real; ;
    break;}
case 96:
#line 455 "parser.y"
{ yyval.real = yyvsp[-2].integer - yyvsp[0].real; ;
    break;}
case 97:
#line 456 "parser.y"
{ yyval.real = yyvsp[-2].real - yyvsp[0].integer; ;
    break;}
case 98:
#line 458 "parser.y"
{ yyval.real = yyvsp[-2].real * yyvsp[0].real; ;
    break;}
case 99:
#line 459 "parser.y"
{ yyval.real = yyvsp[-2].integer * yyvsp[0].real; ;
    break;}
case 100:
#line 460 "parser.y"
{ yyval.real = yyvsp[-2].real * yyvsp[0].integer; ;
    break;}
case 101:
#line 462 "parser.y"
{ yyval.real = yyvsp[-2].real / yyvsp[0].real; ;
    break;}
case 102:
#line 463 "parser.y"
{ yyval.real = yyvsp[-2].integer / yyvsp[0].real; ;
    break;}
case 103:
#line 464 "parser.y"
{ yyval.real = yyvsp[-2].real / yyvsp[0].integer; ;
    break;}
case 104:
#line 466 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].real), float (yyvsp[0].real)); ;
    break;}
case 105:
#line 467 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].integer), float (yyvsp[0].real)); ;
    break;}
case 106:
#line 468 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].real), float (yyvsp[0].integer)); ;
    break;}
case 107:
#line 470 "parser.y"
{ yyval.real = -yyvsp[0].real; ;
    break;}
case 108:
#line 471 "parser.y"
{ yyval.real = yyvsp[-1].real; ;
    break;}
case 110:
#line 475 "parser.y"
{yyval.real = sin(yyvsp[-1].real); ;
    break;}
case 111:
#line 476 "parser.y"
{yyval.real = cos(yyvsp[-1].real); ;
    break;}
case 112:
#line 477 "parser.y"
{yyval.real = tan(yyvsp[-1].real); ;
    break;}
case 113:
#line 478 "parser.y"
{yyval.real = asin(yyvsp[-1].real); ;
    break;}
case 114:
#line 479 "parser.y"
{yyval.real = acos(yyvsp[-1].real); ;
    break;}
case 115:
#line 480 "parser.y"
{yyval.real = atan(yyvsp[-1].real); ;
    break;}
case 116:
#line 481 "parser.y"
{yyval.real = log(yyvsp[-1].real); ;
    break;}
case 117:
#line 482 "parser.y"
{yyval.real = log10(yyvsp[-1].real); ;
    break;}
case 118:
#line 483 "parser.y"
{yyval.real = exp(yyvsp[-1].real); ;
    break;}
case 119:
#line 484 "parser.y"
{yyval.real = sqrt(yyvsp[-1].real); ;
    break;}
case 120:
#line 488 "parser.y"
{ yyval.real = 2.718281828459f; ;
    break;}
case 121:
#line 489 "parser.y"
{ yyval.real = 3.141592653589793f; ;
    break;}
case 122:
#line 492 "parser.y"
{ yyval.integer = yyvsp[0].integer; ;
    break;}
case 123:
#line 493 "parser.y"
{ yyval.integer = yyvsp[-2].integer + yyvsp[0].integer; ;
    break;}
case 124:
#line 494 "parser.y"
{ yyval.integer = yyvsp[-2].integer - yyvsp[0].integer; ;
    break;}
case 125:
#line 495 "parser.y"
{ yyval.integer = yyvsp[-2].integer * yyvsp[0].integer; ;
    break;}
case 126:
#line 496 "parser.y"
{ yyval.integer = yyvsp[-2].integer / yyvsp[0].integer; ;
    break;}
case 127:
#line 497 "parser.y"
{ yyval.integer = -yyvsp[0].integer; ;
    break;}
case 128:
#line 498 "parser.y"
{ yyval.integer = (int)pow((float)yyvsp[-2].integer, (float)yyvsp[0].integer); ;
    break;}
case 129:
#line 499 "parser.y"
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
#line 503 "parser.y"

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