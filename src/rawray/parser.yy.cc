
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
#define	CAMERA	293
#define	DIR	294
#define	LOOKAT	295
#define	UP	296
#define	FOV	297
#define	ASPECT	298
#define	MIN_DRAW	299
#define	MAX_DRAW	300
#define	P0	301
#define	SPIRAL_NUM_SPHERES	302
#define	SPIRAL_RADIUS	303
#define	LORENZ_DT	304
#define	LORENZ_MIN_DISTANCE	305
#define	LORENZ_MAX_DISTANCE	306
#define	LORENZ_SIGMA	307
#define	LORENZ_RHO	308
#define	LORENZ_BETA	309
#define	LORENZ_RADIUS	310
#define	LORENZ_NUM_SPHERES	311
#define	LORENZ_START	312
#define	TRIANGLE	313
#define	V1	314
#define	V2	315
#define	V3	316
#define	N1	317
#define	N2	318
#define	N3	319
#define	MESH	320
#define	LOAD	321
#define	INSTANCE	322
#define	GEOMETRY	323
#define	PUSHMATRIX	324
#define	POPMATRIX	325
#define	ROTATE	326
#define	TRANSLATE	327
#define	SCALE	328
#define	LIGHT	329
#define	POINTLIGHT	330
#define	WATTAGE	331
#define	COLOR	332
#define	SPHERE	333
#define	CENTER	334
#define	RADIUS	335
#define	NEG	336

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



#define	YYFINAL		384
#define	YYFLAG		-32768
#define	YYNTBASE	93

#define YYTRANSLATE(x) ((unsigned)(x) <= 336 ? yytranslate[x] : 119)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    91,
    92,    84,    83,    90,    82,     2,    85,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    81,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    87,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    88,     2,    89,     2,     2,     2,     2,     2,
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
    76,    77,    78,    79,    80,    86
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     9,    14,    18,    23,    25,    27,    28,
    34,    35,    42,    43,    49,    50,    57,    58,    64,    65,
    72,    73,    79,    80,    87,    88,    96,   104,   112,   120,
   128,   136,   137,   145,   149,   150,   154,   156,   158,   167,
   174,   181,   182,   187,   188,   196,   200,   208,   209,   212,
   213,   217,   221,   229,   237,   241,   245,   249,   253,   257,
   261,   265,   269,   273,   274,   282,   290,   298,   306,   310,
   314,   318,   322,   323,   327,   331,   335,   339,   343,   347,
   351,   355,   359,   363,   371,   373,   375,   377,   381,   385,
   389,   393,   397,   401,   405,   409,   413,   417,   421,   425,
   429,   433,   437,   440,   444,   446,   451,   456,   461,   466,
   471,   476,   481,   486,   491,   496,   498,   500,   502,   506,
   510,   514,   518,   521,   525
};

static const short yyrhs[] = {    -1,
    93,    94,     0,    23,    88,   112,    89,     0,    38,    88,
   113,    89,     0,    74,   108,    89,     0,    46,    88,   114,
    89,     0,    95,     0,   107,     0,     0,    58,    88,    96,
   104,    89,     0,     0,    58,     5,    88,    97,   104,    89,
     0,     0,    65,    88,    98,   111,    89,     0,     0,    65,
     5,    88,    99,   111,    89,     0,     0,    78,    88,   100,
   105,    89,     0,     0,    78,     5,    88,   101,   105,    89,
     0,     0,    67,    88,   102,   106,    89,     0,     0,    67,
     5,    88,   103,   106,    89,     0,     0,    59,   115,    90,
   115,    90,   115,   104,     0,    60,   115,    90,   115,    90,
   115,   104,     0,    61,   115,    90,   115,    90,   115,   104,
     0,    62,   115,    90,   115,    90,   115,   104,     0,    63,
   115,    90,   115,    90,   115,   104,     0,    64,   115,    90,
   115,    90,   115,   104,     0,     0,    79,   115,    90,   115,
    90,   115,   105,     0,    80,   115,   105,     0,     0,    68,
     5,   105,     0,    69,     0,    70,     0,    71,   115,    90,
   115,    90,   115,    90,   115,     0,    72,   115,    90,   115,
    90,   115,     0,    73,   115,    90,   115,    90,   115,     0,
     0,    75,    88,   109,   110,     0,     0,    26,   115,    90,
   115,    90,   115,   110,     0,    76,   115,   110,     0,    77,
   115,    90,   115,    90,   115,   110,     0,     0,    66,     5,
     0,     0,    25,   118,   112,     0,    24,   118,   112,     0,
    28,   115,    90,   115,    90,   115,   112,     0,    27,   115,
    90,   115,    90,   115,   112,     0,    29,   118,   112,     0,
    30,   118,   112,     0,    31,   118,   112,     0,    32,   118,
   112,     0,    33,   118,   112,     0,    34,   118,   112,     0,
    35,   118,   112,     0,    36,   115,   112,     0,    37,   115,
   112,     0,     0,    26,   115,    90,   115,    90,   115,   113,
     0,    39,   115,    90,   115,    90,   115,   113,     0,    40,
   115,    90,   115,    90,   115,   113,     0,    41,   115,    90,
   115,    90,   115,   113,     0,    42,   115,   113,     0,    43,
   115,   113,     0,    44,   115,   113,     0,    45,   115,   113,
     0,     0,    47,   118,   114,     0,    48,   115,   114,     0,
    49,   115,   114,     0,    50,   115,   114,     0,    51,   115,
   114,     0,    52,   115,   114,     0,    53,   115,   114,     0,
    54,   115,   114,     0,    55,   115,   114,     0,    56,   118,
   114,     0,    57,   115,    90,   115,    90,   115,   114,     0,
     3,     0,   118,     0,   116,     0,   115,    83,   115,     0,
   118,    83,   115,     0,   115,    83,   118,     0,   115,    82,
   115,     0,   118,    82,   115,     0,   115,    82,   118,     0,
   115,    84,   115,     0,   118,    84,   115,     0,   115,    84,
   118,     0,   115,    85,   115,     0,   118,    85,   115,     0,
   115,    85,   118,     0,   115,    87,   115,     0,   118,    87,
   115,     0,   115,    87,   118,     0,    82,   115,     0,    91,
   115,    92,     0,   117,     0,    11,    91,   115,    92,     0,
    10,    91,   115,    92,     0,    12,    91,   115,    92,     0,
    14,    91,   115,    92,     0,    13,    91,   115,    92,     0,
    15,    91,   115,    92,     0,    17,    91,   115,    92,     0,
    18,    91,   115,    92,     0,    19,    91,   115,    92,     0,
    20,    91,   115,    92,     0,    21,     0,    22,     0,     4,
     0,   118,    83,   118,     0,   118,    82,   118,     0,   118,
    84,   118,     0,   118,    85,   118,     0,    82,   118,     0,
   118,    87,   118,     0,    91,   118,    92,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   165,   166,   169,   170,   171,   172,   173,   174,   177,   186,
   192,   202,   208,   215,   221,   230,   236,   246,   252,   264,
   270,   274,   278,   282,   287,   288,   290,   292,   294,   296,
   298,   302,   303,   305,   309,   310,   320,   321,   323,   325,
   327,   331,   342,   344,   345,   347,   349,   353,   354,   362,
   363,   365,   367,   369,   371,   373,   375,   377,   379,   381,
   383,   385,   387,   391,   392,   394,   396,   398,   400,   402,
   404,   406,   410,   411,   413,   415,   417,   419,   421,   423,
   425,   427,   429,   431,   435,   436,   437,   439,   440,   441,
   443,   444,   445,   447,   448,   449,   451,   452,   453,   455,
   456,   457,   459,   460,   461,   464,   465,   466,   467,   468,
   469,   470,   471,   472,   473,   476,   478,   481,   482,   483,
   484,   485,   486,   487,   488
};

static const char * const yytname[] = {   "$","error","$undefined.","REAL","PARSE_INT",
"STRING","PARSE_TRUE","PARSE_FALSE","ENABLE","DISABLE","MATH_COS","MATH_SIN",
"MATH_TAN","MATH_ACOS","MATH_ASIN","MATH_ATAN","MATH_ATAN2","MATH_LN","MATH_LOG",
"MATH_EXP","MATH_SQRT","MATH_E","MATH_PI","GLOBAL","WIDTH","HEIGHT","POS","IMG_BGCOLOR",
"GL_BGCOLOR","GL_SPHERE_SECTIONS","NUM_THREADS","RENDER_X_BLOCK","RENDER_Y_BLOCK",
"RENDER_HANDLER_SLEEP","RENDER_THREAD_SLEEP","RENDER_SPINLOCK_SLEEP","GAUSSIAN_BLUR_MAX",
"GAUSSIAN_BLUR_SIGMA","CAMERA","DIR","LOOKAT","UP","FOV","ASPECT","MIN_DRAW",
"MAX_DRAW","P0","SPIRAL_NUM_SPHERES","SPIRAL_RADIUS","LORENZ_DT","LORENZ_MIN_DISTANCE",
"LORENZ_MAX_DISTANCE","LORENZ_SIGMA","LORENZ_RHO","LORENZ_BETA","LORENZ_RADIUS",
"LORENZ_NUM_SPHERES","LORENZ_START","TRIANGLE","V1","V2","V3","N1","N2","N3",
"MESH","LOAD","INSTANCE","GEOMETRY","PUSHMATRIX","POPMATRIX","ROTATE","TRANSLATE",
"SCALE","LIGHT","POINTLIGHT","WATTAGE","COLOR","SPHERE","CENTER","RADIUS","'='",
"'-'","'+'","'*'","'/'","NEG","'^'","'{'","'}'","','","'('","')'","input","block",
"objectTypes","@1","@2","@3","@4","@5","@6","@7","@8","triangleOptions","sphereOptions",
"instanceOptions","transform","lightTypes","@9","lightOptions","meshOptions",
"globalOptions","cameraOptions","p0Options","rExp","fExp","constantExp","iExp",
""
};
#endif

static const short yyr1[] = {     0,
    93,    93,    94,    94,    94,    94,    94,    94,    96,    95,
    97,    95,    98,    95,    99,    95,   100,    95,   101,    95,
   102,    95,   103,    95,   104,   104,   104,   104,   104,   104,
   104,   105,   105,   105,   106,   106,   107,   107,   107,   107,
   107,   109,   108,   110,   110,   110,   110,   111,   111,   112,
   112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
   112,   112,   112,   113,   113,   113,   113,   113,   113,   113,
   113,   113,   114,   114,   114,   114,   114,   114,   114,   114,
   114,   114,   114,   114,   115,   115,   115,   115,   115,   115,
   115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
   115,   115,   115,   115,   115,   116,   116,   116,   116,   116,
   116,   116,   116,   116,   116,   117,   117,   118,   118,   118,
   118,   118,   118,   118,   118
};

static const short yyr2[] = {     0,
     0,     2,     4,     4,     3,     4,     1,     1,     0,     5,
     0,     6,     0,     5,     0,     6,     0,     5,     0,     6,
     0,     5,     0,     6,     0,     7,     7,     7,     7,     7,
     7,     0,     7,     3,     0,     3,     1,     1,     8,     6,
     6,     0,     4,     0,     7,     3,     7,     0,     2,     0,
     3,     3,     7,     7,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     0,     7,     7,     7,     7,     3,     3,
     3,     3,     0,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     7,     1,     1,     1,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     2,     3,     1,     4,     4,     4,     4,     4,
     4,     4,     4,     4,     4,     1,     1,     1,     3,     3,
     3,     3,     2,     3,     3
};

static const short yydefact[] = {     1,
     0,     0,     0,     0,     0,     0,     0,    37,    38,     0,
     0,     0,     0,     0,     2,     7,     8,    50,    64,    73,
     0,     9,     0,    13,     0,    21,    85,   118,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   116,   117,
     0,     0,     0,    87,   105,    86,     0,     0,     0,     0,
     0,    17,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    11,    25,    15,
    48,    23,    35,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   103,    86,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    42,     5,    19,    32,     0,     0,    50,    50,     0,     0,
    50,    50,    50,    50,    50,    50,    50,    50,    50,     3,
     0,     0,     0,     0,    64,    64,    64,    64,     4,    73,
    73,    73,    73,    73,    73,    73,    73,    73,    73,     0,
     6,    25,     0,     0,     0,     0,     0,     0,     0,    48,
     0,     0,    35,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   104,   125,    91,    86,    88,
    86,    94,    86,    97,    86,   100,    86,     0,    92,    86,
    89,    86,    95,    86,    98,    86,   101,    86,     0,     0,
    44,    32,     0,     0,     0,   123,     0,     0,     0,     0,
     0,     0,    52,    51,     0,     0,    55,    56,    57,    58,
    59,    60,    61,    62,    63,     0,     0,     0,     0,    69,
    70,    71,    72,    74,    75,    76,    77,    78,    79,    80,
    81,    82,    83,     0,     0,     0,     0,     0,     0,     0,
     0,    10,     0,    49,    14,     0,    32,    22,   107,   106,
   108,   110,   109,   111,   112,   113,   114,   115,     0,     0,
     0,     0,     0,     0,    43,     0,     0,    32,    18,   120,
   119,   121,   122,   124,     0,     0,     0,     0,     0,     0,
     0,    12,     0,     0,     0,     0,     0,     0,    16,    24,
    36,     0,    40,    41,     0,    44,     0,    20,     0,    34,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    46,     0,     0,    50,    50,
    64,    64,    64,    64,    73,     0,     0,     0,     0,     0,
     0,    39,     0,     0,     0,    54,    53,    65,    66,    67,
    68,    84,    25,    25,    25,    25,    25,    25,     0,     0,
    32,    26,    27,    28,    29,    30,    31,    44,    44,    33,
    45,    47,     0,     0
};

static const short yydefgoto[] = {     1,
    15,    16,    89,   162,    91,   170,   124,   212,    93,   173,
   169,   215,   175,    17,    50,   211,   285,   172,    66,    75,
    87,    43,    44,    45,    46
};

static const short yypact[] = {-32768,
   123,   -66,   -60,   -37,    24,    27,    28,-32768,-32768,   107,
   107,   107,   -54,    43,-32768,-32768,-32768,   429,   407,   430,
   -33,-32768,   -12,-32768,    -7,-32768,-32768,-32768,   -41,     2,
     3,     5,    22,    45,    47,    49,    52,    53,-32768,-32768,
   107,   107,   473,-32768,-32768,   283,   482,   491,    57,    58,
    60,-32768,    48,    48,   107,   107,    48,    48,    48,    48,
    48,    48,    48,   107,   107,    61,   107,   107,   107,   107,
   107,   107,   107,   107,    62,    48,   107,   107,   107,   107,
   107,   107,   107,   107,    48,   107,    69,-32768,   227,-32768,
    75,-32768,    81,   107,   107,   107,   107,   107,   107,   107,
   107,   107,   107,    72,    73,    50,   235,   107,   107,   107,
   107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
-32768,-32768,-32768,   -73,    48,    48,   217,   217,   500,   509,
   217,   217,   217,   217,   217,   217,   217,   347,   347,-32768,
   518,   527,   536,   545,   192,   192,   192,   192,-32768,   338,
   388,   388,   388,   388,   388,   388,   388,   388,   338,   554,
-32768,   227,   107,   107,   107,   107,   107,   107,    74,    75,
   157,    77,    81,   162,    79,   270,   325,   406,   412,   431,
   437,   443,   449,   455,   461,-32768,-32768,   -67,   -38,   -67,
   -38,    72,    73,    72,    73,    72,    73,   563,   -67,   -38,
   -67,   -38,    72,    73,    72,    73,    72,    73,   572,   581,
     1,   -73,   107,   107,    85,    89,   467,    48,    48,    48,
    48,    48,-32768,-32768,   107,   107,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   107,   107,   107,   107,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,   107,    97,   590,   599,   608,   617,   626,
   635,-32768,   102,-32768,-32768,   110,   -73,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   107,   107,
   107,   107,   107,   107,-32768,   111,   644,   100,-32768,    -5,
    -5,    89,    89,    89,   653,   662,   671,   680,   689,   698,
   707,-32768,   107,   107,   107,   107,   107,   107,-32768,-32768,
-32768,   716,   418,   418,   725,    88,   734,-32768,   107,-32768,
   107,   107,   107,   107,   107,   107,   107,   743,   752,   761,
   770,   779,   788,   107,   107,-32768,   107,   797,   347,   347,
   192,   192,   192,   192,   388,   107,   107,   107,   107,   107,
   107,   418,   806,   815,   107,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   198,   198,   198,   198,   198,   198,   107,   107,
   100,-32768,-32768,-32768,-32768,-32768,-32768,    88,    88,-32768,
-32768,-32768,   177,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -159,  -193,    37,-32768,-32768,-32768,  -314,    41,  -123,  -122,
  -116,   -11,-32768,-32768,   288
};


#define	YYLAST		905


static const short yytable[] = {    47,
    48,   336,   255,   223,   224,   213,   214,   227,   228,   229,
   230,   231,   232,   233,   234,   235,   110,   111,   286,   112,
    49,    18,   240,   241,   242,   243,   282,    19,    21,   104,
   106,    23,    25,   244,   245,   246,   247,   248,   249,   250,
   251,   252,   253,   129,   130,   116,   117,    51,   118,    94,
    20,    28,   138,   139,    88,   141,   142,   143,   144,   145,
   146,   147,   148,   381,   382,   151,   152,   153,   154,   155,
   156,   157,   158,   311,   160,    90,   283,   284,   220,   221,
    92,   222,   176,   177,   178,   179,   180,   181,   182,   183,
   184,   185,    95,    96,   320,    97,   188,   190,   192,   194,
   196,   198,   199,   201,   203,   205,   207,   209,   210,    27,
    28,    22,    98,   282,    24,    26,    29,    30,    31,    32,
    33,    34,   383,    35,    36,    37,    38,    39,    40,   125,
    52,   108,   109,   110,   111,    99,   112,   100,   126,   101,
   171,   186,   102,   103,   121,     2,   122,   123,   174,   140,
   149,   256,   257,   258,   259,   260,   261,   161,   112,   118,
     3,   264,   262,   283,   284,   265,   267,   268,     4,   108,
   109,   110,   111,   289,   112,   222,   384,   380,   213,   214,
     5,   108,   109,   110,   111,   302,   112,     6,    41,     7,
   309,     8,     9,    10,    11,    12,    13,    42,   310,   318,
    14,   287,   288,   372,   373,   374,   375,   376,   377,   266,
   263,     0,     0,   295,   296,   356,   357,    67,   358,   359,
   360,   361,     0,     0,   297,   298,   299,   300,   362,     0,
    68,    69,    70,    71,    72,    73,    74,     0,     0,     0,
    53,    54,   301,    55,    56,    57,    58,    59,    60,    61,
    62,    63,    64,    65,     0,     0,   163,   164,   165,   166,
   167,   168,     0,     0,     0,     0,     0,   312,   313,   314,
   315,   316,   317,   108,   109,   110,   111,     0,   112,   108,
   109,   110,   111,     0,   112,   163,   164,   165,   166,   167,
   168,   328,   329,   330,   331,   332,   333,     0,   218,   219,
   220,   221,     0,   222,     0,     0,     0,   338,     0,   339,
   340,   341,   342,   343,   344,   345,   114,   115,   116,   117,
     0,   118,   352,   353,     0,   354,   187,     0,   105,   107,
     0,     0,     0,     0,   363,   364,   365,   366,   367,   368,
   127,   128,     0,   371,   131,   132,   133,   134,   135,   136,
   137,   108,   109,   110,   111,     0,   112,   378,   379,     0,
     0,   269,     0,   150,   114,   115,   116,   117,     0,   118,
    53,    54,   159,    55,    56,    57,    58,    59,    60,    61,
    62,    63,    64,    65,    76,    77,    78,    79,    80,    81,
    82,    83,    84,    85,    86,   189,   191,   193,   195,   197,
     0,   200,   202,   204,   206,   208,   108,   109,   110,   111,
     0,   112,   216,   217,     0,     0,   270,     0,     0,   218,
   219,   220,   221,     0,   222,     0,     0,     0,   108,   109,
   110,   111,    67,   112,    76,    77,    78,    79,    80,    81,
    82,    83,    84,    85,    86,    68,    69,    70,    71,    72,
    73,    74,    53,    54,     0,    55,    56,    57,    58,    59,
    60,    61,    62,    63,    64,    65,     0,     0,     0,   108,
   109,   110,   111,     0,   112,     0,    76,    77,    78,    79,
    80,    81,    82,    83,    84,    85,    86,   108,   109,   110,
   111,     0,   112,   108,   109,   110,   111,   271,   112,   108,
   109,   110,   111,   272,   112,   290,   291,   292,   293,   294,
     0,     0,   108,   109,   110,   111,     0,   112,   108,   109,
   110,   111,   273,   112,   108,   109,   110,   111,   274,   112,
   108,   109,   110,   111,   275,   112,   108,   109,   110,   111,
   276,   112,   108,   109,   110,   111,   277,   112,   218,   219,
   220,   221,   278,   222,   108,   109,   110,   111,   187,   112,
     0,     0,   113,   108,   109,   110,   111,     0,   112,     0,
     0,   119,   108,   109,   110,   111,     0,   112,     0,     0,
   120,   108,   109,   110,   111,     0,   112,     0,     0,   225,
   108,   109,   110,   111,     0,   112,     0,     0,   226,   108,
   109,   110,   111,     0,   112,     0,     0,   236,   108,   109,
   110,   111,     0,   112,     0,     0,   237,   108,   109,   110,
   111,     0,   112,     0,     0,   238,   108,   109,   110,   111,
     0,   112,     0,     0,   239,   108,   109,   110,   111,     0,
   112,     0,     0,   254,   108,   109,   110,   111,     0,   112,
     0,     0,   279,   108,   109,   110,   111,     0,   112,     0,
     0,   280,   108,   109,   110,   111,     0,   112,     0,     0,
   281,   108,   109,   110,   111,     0,   112,     0,     0,   303,
   108,   109,   110,   111,     0,   112,     0,     0,   304,   108,
   109,   110,   111,     0,   112,     0,     0,   305,   108,   109,
   110,   111,     0,   112,     0,     0,   306,   108,   109,   110,
   111,     0,   112,     0,     0,   307,   108,   109,   110,   111,
     0,   112,     0,     0,   308,   108,   109,   110,   111,     0,
   112,     0,     0,   319,   108,   109,   110,   111,     0,   112,
     0,     0,   321,   108,   109,   110,   111,     0,   112,     0,
     0,   322,   108,   109,   110,   111,     0,   112,     0,     0,
   323,   108,   109,   110,   111,     0,   112,     0,     0,   324,
   108,   109,   110,   111,     0,   112,     0,     0,   325,   108,
   109,   110,   111,     0,   112,     0,     0,   326,   108,   109,
   110,   111,     0,   112,     0,     0,   327,   108,   109,   110,
   111,     0,   112,     0,     0,   334,   108,   109,   110,   111,
     0,   112,     0,     0,   335,   108,   109,   110,   111,     0,
   112,     0,     0,   337,   108,   109,   110,   111,     0,   112,
     0,     0,   346,   108,   109,   110,   111,     0,   112,     0,
     0,   347,   108,   109,   110,   111,     0,   112,     0,     0,
   348,   108,   109,   110,   111,     0,   112,     0,     0,   349,
   108,   109,   110,   111,     0,   112,     0,     0,   350,   108,
   109,   110,   111,     0,   112,     0,     0,   351,   108,   109,
   110,   111,     0,   112,     0,     0,   355,   108,   109,   110,
   111,     0,   112,     0,     0,   369,   108,   109,   110,   111,
     0,   112,     0,     0,   370
};

static const short yycheck[] = {    11,
    12,   316,   162,   127,   128,    79,    80,   131,   132,   133,
   134,   135,   136,   137,   138,   139,    84,    85,   212,    87,
    75,    88,   145,   146,   147,   148,    26,    88,     5,    41,
    42,     5,     5,   150,   151,   152,   153,   154,   155,   156,
   157,   158,   159,    55,    56,    84,    85,     5,    87,    91,
    88,     4,    64,    65,    88,    67,    68,    69,    70,    71,
    72,    73,    74,   378,   379,    77,    78,    79,    80,    81,
    82,    83,    84,   267,    86,    88,    76,    77,    84,    85,
    88,    87,    94,    95,    96,    97,    98,    99,   100,   101,
   102,   103,    91,    91,   288,    91,   108,   109,   110,   111,
   112,   113,   114,   115,   116,   117,   118,   119,   120,     3,
     4,    88,    91,    26,    88,    88,    10,    11,    12,    13,
    14,    15,     0,    17,    18,    19,    20,    21,    22,    82,
    88,    82,    83,    84,    85,    91,    87,    91,    91,    91,
    66,    92,    91,    91,    88,    23,    89,    88,    68,    89,
    89,   163,   164,   165,   166,   167,   168,    89,    87,    87,
    38,     5,    89,    76,    77,    89,     5,    89,    46,    82,
    83,    84,    85,    89,    87,    87,     0,   371,    79,    80,
    58,    82,    83,    84,    85,    89,    87,    65,    82,    67,
    89,    69,    70,    71,    72,    73,    74,    91,    89,    89,
    78,   213,   214,   363,   364,   365,   366,   367,   368,   173,
   170,    -1,    -1,   225,   226,   339,   340,    26,   341,   342,
   343,   344,    -1,    -1,   236,   237,   238,   239,   345,    -1,
    39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
    24,    25,   254,    27,    28,    29,    30,    31,    32,    33,
    34,    35,    36,    37,    -1,    -1,    59,    60,    61,    62,
    63,    64,    -1,    -1,    -1,    -1,    -1,   279,   280,   281,
   282,   283,   284,    82,    83,    84,    85,    -1,    87,    82,
    83,    84,    85,    -1,    87,    59,    60,    61,    62,    63,
    64,   303,   304,   305,   306,   307,   308,    -1,    82,    83,
    84,    85,    -1,    87,    -1,    -1,    -1,   319,    -1,   321,
   322,   323,   324,   325,   326,   327,    82,    83,    84,    85,
    -1,    87,   334,   335,    -1,   337,    92,    -1,    41,    42,
    -1,    -1,    -1,    -1,   346,   347,   348,   349,   350,   351,
    53,    54,    -1,   355,    57,    58,    59,    60,    61,    62,
    63,    82,    83,    84,    85,    -1,    87,   369,   370,    -1,
    -1,    92,    -1,    76,    82,    83,    84,    85,    -1,    87,
    24,    25,    85,    27,    28,    29,    30,    31,    32,    33,
    34,    35,    36,    37,    47,    48,    49,    50,    51,    52,
    53,    54,    55,    56,    57,   108,   109,   110,   111,   112,
    -1,   114,   115,   116,   117,   118,    82,    83,    84,    85,
    -1,    87,   125,   126,    -1,    -1,    92,    -1,    -1,    82,
    83,    84,    85,    -1,    87,    -1,    -1,    -1,    82,    83,
    84,    85,    26,    87,    47,    48,    49,    50,    51,    52,
    53,    54,    55,    56,    57,    39,    40,    41,    42,    43,
    44,    45,    24,    25,    -1,    27,    28,    29,    30,    31,
    32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    82,
    83,    84,    85,    -1,    87,    -1,    47,    48,    49,    50,
    51,    52,    53,    54,    55,    56,    57,    82,    83,    84,
    85,    -1,    87,    82,    83,    84,    85,    92,    87,    82,
    83,    84,    85,    92,    87,   218,   219,   220,   221,   222,
    -1,    -1,    82,    83,    84,    85,    -1,    87,    82,    83,
    84,    85,    92,    87,    82,    83,    84,    85,    92,    87,
    82,    83,    84,    85,    92,    87,    82,    83,    84,    85,
    92,    87,    82,    83,    84,    85,    92,    87,    82,    83,
    84,    85,    92,    87,    82,    83,    84,    85,    92,    87,
    -1,    -1,    90,    82,    83,    84,    85,    -1,    87,    -1,
    -1,    90,    82,    83,    84,    85,    -1,    87,    -1,    -1,
    90,    82,    83,    84,    85,    -1,    87,    -1,    -1,    90,
    82,    83,    84,    85,    -1,    87,    -1,    -1,    90,    82,
    83,    84,    85,    -1,    87,    -1,    -1,    90,    82,    83,
    84,    85,    -1,    87,    -1,    -1,    90,    82,    83,    84,
    85,    -1,    87,    -1,    -1,    90,    82,    83,    84,    85,
    -1,    87,    -1,    -1,    90,    82,    83,    84,    85,    -1,
    87,    -1,    -1,    90,    82,    83,    84,    85,    -1,    87,
    -1,    -1,    90,    82,    83,    84,    85,    -1,    87,    -1,
    -1,    90,    82,    83,    84,    85,    -1,    87,    -1,    -1,
    90,    82,    83,    84,    85,    -1,    87,    -1,    -1,    90,
    82,    83,    84,    85,    -1,    87,    -1,    -1,    90,    82,
    83,    84,    85,    -1,    87,    -1,    -1,    90,    82,    83,
    84,    85,    -1,    87,    -1,    -1,    90,    82,    83,    84,
    85,    -1,    87,    -1,    -1,    90,    82,    83,    84,    85,
    -1,    87,    -1,    -1,    90,    82,    83,    84,    85,    -1,
    87,    -1,    -1,    90,    82,    83,    84,    85,    -1,    87,
    -1,    -1,    90,    82,    83,    84,    85,    -1,    87,    -1,
    -1,    90,    82,    83,    84,    85,    -1,    87,    -1,    -1,
    90,    82,    83,    84,    85,    -1,    87,    -1,    -1,    90,
    82,    83,    84,    85,    -1,    87,    -1,    -1,    90,    82,
    83,    84,    85,    -1,    87,    -1,    -1,    90,    82,    83,
    84,    85,    -1,    87,    -1,    -1,    90,    82,    83,    84,
    85,    -1,    87,    -1,    -1,    90,    82,    83,    84,    85,
    -1,    87,    -1,    -1,    90,    82,    83,    84,    85,    -1,
    87,    -1,    -1,    90,    82,    83,    84,    85,    -1,    87,
    -1,    -1,    90,    82,    83,    84,    85,    -1,    87,    -1,
    -1,    90,    82,    83,    84,    85,    -1,    87,    -1,    -1,
    90,    82,    83,    84,    85,    -1,    87,    -1,    -1,    90,
    82,    83,    84,    85,    -1,    87,    -1,    -1,    90,    82,
    83,    84,    85,    -1,    87,    -1,    -1,    90,    82,    83,
    84,    85,    -1,    87,    -1,    -1,    90,    82,    83,    84,
    85,    -1,    87,    -1,    -1,    90,    82,    83,    84,    85,
    -1,    87,    -1,    -1,    90
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
#line 169 "parser.y"
{ printf("\n"); ;
    break;}
case 4:
#line 170 "parser.y"
{ printf("\n"); ;
    break;}
case 5:
#line 171 "parser.y"
{ printf("\n"); g_scene->AddLight( g_light ); g_light = NULL; ;
    break;}
case 6:
#line 172 "parser.y"
{ printf("\n"); ;
    break;}
case 7:
#line 173 "parser.y"
{ printf("\n"); ;
    break;}
case 8:
#line 174 "parser.y"
{ printf("\n"); ;
    break;}
case 9:
#line 179 "parser.y"
{
                g_mesh = new rawray::TriangleMesh();
                #ifdef VERBOSE_NEW
                printf( "MESH: %x", g_mesh );
                #endif
                //((TriangleMesh*)pObj)->CreateSingleTriangle();
            ;
    break;}
case 10:
#line 187 "parser.y"
{
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            ;
    break;}
case 11:
#line 193 "parser.y"
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
#line 203 "parser.y"
{
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            ;
    break;}
case 13:
#line 209 "parser.y"
{
                g_mesh = new rawray::TriangleMesh();
                #ifdef VERBOSE_NEW
                printf( "MESH: %x", g_mesh );
                #endif
            ;
    break;}
case 14:
#line 216 "parser.y"
{
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            ;
    break;}
case 15:
#line 222 "parser.y"
{
                g_mesh = new rawray::TriangleMesh();
                #ifdef VERBOSE_NEW
                printf( "MESH: %x", g_mesh );
                #endif
                
                //g_objectMap[$2] = pObj;
            ;
    break;}
case 16:
#line 231 "parser.y"
{
                g_scene->AddMesh( g_mesh );
                rawray::AddTrianglesOfMesh();
            ;
    break;}
case 17:
#line 237 "parser.y"
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
#line 247 "parser.y"
{
                g_scene->AddObject( g_obj );
                g_obj = NULL;
            ;
    break;}
case 19:
#line 253 "parser.y"
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
#line 265 "parser.y"
{
                g_scene->AddObject( g_obj );
                g_obj = NULL;
            ;
    break;}
case 21:
#line 271 "parser.y"
{
                printf( "Instance not supported\n" );
            ;
    break;}
case 22:
#line 275 "parser.y"
{
            ;
    break;}
case 23:
#line 279 "parser.y"
{
                printf( "Named Instance not supported\n" );
            ;
    break;}
case 24:
#line 283 "parser.y"
{
            ;
    break;}
case 26:
#line 289 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 27:
#line 291 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 28:
#line 293 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 29:
#line 295 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 30:
#line 297 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 31:
#line 299 "parser.y"
{ printf( "Triangles not supported" ); ;
    break;}
case 33:
#line 304 "parser.y"
{ ((rawray::Sphere*)g_obj)->SetCenter( math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 34:
#line 306 "parser.y"
{ ((rawray::Sphere*)g_obj)->SetRadius( yyvsp[-1].real ); ;
    break;}
case 36:
#line 311 "parser.y"
{
                //std::map<std::string, Object*>::const_iterator it = g_objectMap.find ($2);
                //if (it != g_objectMap.end ())
                //{
                    //((Instance*)pObj)->SetGeometry(it->second, GetCTM());
                //}
            ;
    break;}
case 37:
#line 320 "parser.y"
{ /*PushMatrix();*/ ;
    break;}
case 38:
#line 322 "parser.y"
{ /*PopMatrix();*/ ;
    break;}
case 39:
#line 324 "parser.y"
{ /*Rotate($2, $4, $6, $8);*/ ;
    break;}
case 40:
#line 326 "parser.y"
{ /*Translate($2, $4, $6);*/ ;
    break;}
case 41:
#line 328 "parser.y"
{ /*Scale($2, $4, $6);*/ ;
    break;}
case 42:
#line 332 "parser.y"
{
                printf( "new light\n" ); 
                g_light = new rawray::Light();
                
                #ifdef VERBOSE_NEW
                printf( "LIGHT: %x\n", g_light );
                #endif
            ;
    break;}
case 45:
#line 346 "parser.y"
{ printf( "pos = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_light->SetPosition( math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 46:
#line 348 "parser.y"
{ printf( "wattage = %f\n", yyvsp[-1].real ); g_light->SetWattage( yyvsp[-1].real ); ;
    break;}
case 47:
#line 350 "parser.y"
{ printf( "color = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_light->SetColor( math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 49:
#line 355 "parser.y"
{
                yyvsp[0].str[strlen(yyvsp[0].str)-1]=0;
                printf( "Loading Mesh: '%s'\n", yyvsp[0].str+1 );
                g_mesh->LoadOBJ( yyvsp[0].str+1 );
            ;
    break;}
case 51:
#line 364 "parser.y"
{ printf( "height = %d\n", yyvsp[-1].integer ); g_image->Resize( g_image->GetWidth(), rawray::options::global::win_height = yyvsp[-1].integer ); ;
    break;}
case 52:
#line 366 "parser.y"
{ printf( "width = %d\n", yyvsp[-1].integer ); g_image->Resize( rawray::options::global::win_width = yyvsp[-1].integer, g_image->GetHeight() ); ;
    break;}
case 53:
#line 368 "parser.y"
{ printf( "gl bg color = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); rawray::options::global::gl_bg_color = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 54:
#line 370 "parser.y"
{ printf( "img bg color = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); rawray::options::global::img_bg_color = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 55:
#line 372 "parser.y"
{ printf( "gl sphere sections = %d\n", rawray::options::global::gl_sphere_sections = yyvsp[-1].integer ); ;
    break;}
case 56:
#line 374 "parser.y"
{ printf( "num threads = %d\n", rawray::options::global::num_threads = yyvsp[-1].integer ); ;
    break;}
case 57:
#line 376 "parser.y"
{ printf( "render x block = %d\n", rawray::options::global::render_x_block = yyvsp[-1].integer ); ;
    break;}
case 58:
#line 378 "parser.y"
{ printf( "render y block = %d\n", rawray::options::global::render_y_block = yyvsp[-1].integer ); ;
    break;}
case 59:
#line 380 "parser.y"
{ printf( "render handler sleep = %d\n", rawray::options::global::render_handler_sleep = yyvsp[-1].integer ); ;
    break;}
case 60:
#line 382 "parser.y"
{ printf( "render thread sleep = %d\n", rawray::options::global::render_thread_sleep = yyvsp[-1].integer ); ;
    break;}
case 61:
#line 384 "parser.y"
{ printf( "render spinlock sleep = %d\n", rawray::options::global::render_spinlock_sleep = yyvsp[-1].integer ); ;
    break;}
case 62:
#line 386 "parser.y"
{ printf( "gaussian blur max = %f\n", rawray::options::global::gaussian_blur_max = yyvsp[-1].real ); ;
    break;}
case 63:
#line 388 "parser.y"
{ printf( "gaussian blur sigma = %f\n", rawray::options::global::gaussian_blur_sigma = yyvsp[-1].real ); ;
    break;}
case 65:
#line 393 "parser.y"
{ printf( "camera pos = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_camera->SetEye( rawray::options::camera::eye = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 66:
#line 395 "parser.y"
{ printf( "camera dir = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_camera->SetViewDir( rawray::options::camera::view = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 67:
#line 397 "parser.y"
{ printf( "camera look at = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_camera->SetLookAt( rawray::options::camera::lookat = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 68:
#line 399 "parser.y"
{ printf( "camera up = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); g_camera->SetUp( rawray::options::camera::up = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real) ); ;
    break;}
case 69:
#line 401 "parser.y"
{ printf( "camera fov = %f\n", yyvsp[-1].real ); g_camera->SetFOV( rawray::options::camera::fov = yyvsp[-1].real ); ;
    break;}
case 70:
#line 403 "parser.y"
{ printf( "camera aspect ratio = %f\n", yyvsp[-1].real ); g_camera->SetAspect( rawray::options::camera::aspect = yyvsp[-1].real ); ;
    break;}
case 71:
#line 405 "parser.y"
{ printf( "camera min draw = %f\n", yyvsp[-1].real ); g_camera->SetMinDraw( rawray::options::camera::min_draw = yyvsp[-1].real ); ;
    break;}
case 72:
#line 407 "parser.y"
{ printf( "camera max draw = %f\n", yyvsp[-1].real ); g_camera->SetMaxDraw( rawray::options::camera::max_draw = yyvsp[-1].real ); ;
    break;}
case 74:
#line 412 "parser.y"
{ printf( "spiral num spheres = %d\n", rawray::options::p0::spiral_num_spheres = yyvsp[-1].integer ); ;
    break;}
case 75:
#line 414 "parser.y"
{ printf( "spiral radius = %f\n", rawray::options::p0::spiral_radius = yyvsp[-1].real ); ;
    break;}
case 76:
#line 416 "parser.y"
{ printf( "lorenz dt = %f\n", rawray::options::p0::lorenz_dt = yyvsp[-1].real ); ;
    break;}
case 77:
#line 418 "parser.y"
{ printf( "lorenz min distance = %f\n", rawray::options::p0::lorenz_min_distance = yyvsp[-1].real ); ;
    break;}
case 78:
#line 420 "parser.y"
{ printf( "lorenz max distance = %f\n", rawray::options::p0::lorenz_max_distance = yyvsp[-1].real ); ;
    break;}
case 79:
#line 422 "parser.y"
{ printf( "lorenz sigma = %f\n", rawray::options::p0::lorenz_sigma = yyvsp[-1].real ); ;
    break;}
case 80:
#line 424 "parser.y"
{ printf( "lorenz rho = %f\n", rawray::options::p0::lorenz_rho = yyvsp[-1].real ); ;
    break;}
case 81:
#line 426 "parser.y"
{ printf( "lorenz beta = %f\n", rawray::options::p0::lorenz_beta = yyvsp[-1].real ); ;
    break;}
case 82:
#line 428 "parser.y"
{ printf( "lorenz radius = %f\n", rawray::options::p0::lorenz_radius = yyvsp[-1].real ); ;
    break;}
case 83:
#line 430 "parser.y"
{ printf( "lorenz num spheres = %d\n", rawray::options::p0::lorenz_num_spheres = yyvsp[-1].integer ); ;
    break;}
case 84:
#line 432 "parser.y"
{ printf( "lorenz start = %f, %f, %f\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); rawray::options::p0::lorenz_start = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 85:
#line 435 "parser.y"
{ yyval.real = yyvsp[0].real; ;
    break;}
case 86:
#line 436 "parser.y"
{ yyval.real = yyvsp[0].integer; ;
    break;}
case 87:
#line 437 "parser.y"
{ yyval.real = yyvsp[0].real; ;
    break;}
case 88:
#line 439 "parser.y"
{ yyval.real = yyvsp[-2].real + yyvsp[0].real; ;
    break;}
case 89:
#line 440 "parser.y"
{ yyval.real = yyvsp[-2].integer + yyvsp[0].real; ;
    break;}
case 90:
#line 441 "parser.y"
{ yyval.real = yyvsp[-2].real + yyvsp[0].integer; ;
    break;}
case 91:
#line 443 "parser.y"
{ yyval.real = yyvsp[-2].real - yyvsp[0].real; ;
    break;}
case 92:
#line 444 "parser.y"
{ yyval.real = yyvsp[-2].integer - yyvsp[0].real; ;
    break;}
case 93:
#line 445 "parser.y"
{ yyval.real = yyvsp[-2].real - yyvsp[0].integer; ;
    break;}
case 94:
#line 447 "parser.y"
{ yyval.real = yyvsp[-2].real * yyvsp[0].real; ;
    break;}
case 95:
#line 448 "parser.y"
{ yyval.real = yyvsp[-2].integer * yyvsp[0].real; ;
    break;}
case 96:
#line 449 "parser.y"
{ yyval.real = yyvsp[-2].real * yyvsp[0].integer; ;
    break;}
case 97:
#line 451 "parser.y"
{ yyval.real = yyvsp[-2].real / yyvsp[0].real; ;
    break;}
case 98:
#line 452 "parser.y"
{ yyval.real = yyvsp[-2].integer / yyvsp[0].real; ;
    break;}
case 99:
#line 453 "parser.y"
{ yyval.real = yyvsp[-2].real / yyvsp[0].integer; ;
    break;}
case 100:
#line 455 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].real), float (yyvsp[0].real)); ;
    break;}
case 101:
#line 456 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].integer), float (yyvsp[0].real)); ;
    break;}
case 102:
#line 457 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].real), float (yyvsp[0].integer)); ;
    break;}
case 103:
#line 459 "parser.y"
{ yyval.real = -yyvsp[0].real; ;
    break;}
case 104:
#line 460 "parser.y"
{ yyval.real = yyvsp[-1].real; ;
    break;}
case 106:
#line 464 "parser.y"
{yyval.real = sin(yyvsp[-1].real); ;
    break;}
case 107:
#line 465 "parser.y"
{yyval.real = cos(yyvsp[-1].real); ;
    break;}
case 108:
#line 466 "parser.y"
{yyval.real = tan(yyvsp[-1].real); ;
    break;}
case 109:
#line 467 "parser.y"
{yyval.real = asin(yyvsp[-1].real); ;
    break;}
case 110:
#line 468 "parser.y"
{yyval.real = acos(yyvsp[-1].real); ;
    break;}
case 111:
#line 469 "parser.y"
{yyval.real = atan(yyvsp[-1].real); ;
    break;}
case 112:
#line 470 "parser.y"
{yyval.real = log(yyvsp[-1].real); ;
    break;}
case 113:
#line 471 "parser.y"
{yyval.real = log10(yyvsp[-1].real); ;
    break;}
case 114:
#line 472 "parser.y"
{yyval.real = exp(yyvsp[-1].real); ;
    break;}
case 115:
#line 473 "parser.y"
{yyval.real = sqrt(yyvsp[-1].real); ;
    break;}
case 116:
#line 477 "parser.y"
{ yyval.real = 2.718281828459f; ;
    break;}
case 117:
#line 478 "parser.y"
{ yyval.real = 3.141592653589793f; ;
    break;}
case 118:
#line 481 "parser.y"
{ yyval.integer = yyvsp[0].integer; ;
    break;}
case 119:
#line 482 "parser.y"
{ yyval.integer = yyvsp[-2].integer + yyvsp[0].integer; ;
    break;}
case 120:
#line 483 "parser.y"
{ yyval.integer = yyvsp[-2].integer - yyvsp[0].integer; ;
    break;}
case 121:
#line 484 "parser.y"
{ yyval.integer = yyvsp[-2].integer * yyvsp[0].integer; ;
    break;}
case 122:
#line 485 "parser.y"
{ yyval.integer = yyvsp[-2].integer / yyvsp[0].integer; ;
    break;}
case 123:
#line 486 "parser.y"
{ yyval.integer = -yyvsp[0].integer; ;
    break;}
case 124:
#line 487 "parser.y"
{ yyval.integer = (int)pow((float)yyvsp[-2].integer, (float)yyvsp[0].integer); ;
    break;}
case 125:
#line 488 "parser.y"
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
#line 492 "parser.y"

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
