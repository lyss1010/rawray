
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
#define	P0	298
#define	SPIRAL_NUM_SPHERES	299
#define	SPIRAL_RADIUS	300
#define	LORENZ_DT	301
#define	LORENZ_MIN_DISTANCE	302
#define	LORENZ_MAX_DISTANCE	303
#define	LORENZ_SIGMA	304
#define	LORENZ_RHO	305
#define	LORENZ_BETA	306
#define	LORENZ_RADIUS	307
#define	LORENZ_NUM_SPHERES	308
#define	LORENZ_START	309
#define	TRIANGLE	310
#define	V1	311
#define	V2	312
#define	V3	313
#define	N1	314
#define	N2	315
#define	N3	316
#define	MESH	317
#define	LOAD	318
#define	INSTANCE	319
#define	GEOMETRY	320
#define	PUSHMATRIX	321
#define	POPMATRIX	322
#define	ROTATE	323
#define	TRANSLATE	324
#define	SCALE	325
#define	LIGHT	326
#define	POINTLIGHT	327
#define	WATTAGE	328
#define	COLOR	329
#define	SPHERE	330
#define	CENTER	331
#define	RADIUS	332
#define	NEG	333

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



#line 43 "parser.y"
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



#define	YYFINAL		375
#define	YYFLAG		-32768
#define	YYNTBASE	90

#define YYTRANSLATE(x) ((unsigned)(x) <= 333 ? yytranslate[x] : 116)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    88,
    89,    81,    80,    87,    79,     2,    82,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    78,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    84,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    85,     2,    86,     2,     2,     2,     2,     2,
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
    76,    77,    83
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
   311,   315,   319,   323,   327,   331,   335,   339,   343,   347,
   351,   359,   361,   363,   365,   369,   373,   377,   381,   385,
   389,   393,   397,   401,   405,   409,   413,   417,   421,   425,
   428,   432,   434,   439,   444,   449,   454,   459,   464,   469,
   474,   479,   484,   486,   488,   490,   494,   498,   502,   506,
   509,   513
};

static const short yyrhs[] = {    -1,
    90,    91,     0,    23,    85,   109,    86,     0,    38,    85,
   110,    86,     0,    71,   105,    86,     0,    43,    85,   111,
    86,     0,    92,     0,   104,     0,     0,    55,    85,    93,
   101,    86,     0,     0,    55,     5,    85,    94,   101,    86,
     0,     0,    62,    85,    95,   108,    86,     0,     0,    62,
     5,    85,    96,   108,    86,     0,     0,    75,    85,    97,
   102,    86,     0,     0,    75,     5,    85,    98,   102,    86,
     0,     0,    64,    85,    99,   103,    86,     0,     0,    64,
     5,    85,   100,   103,    86,     0,     0,    56,   112,    87,
   112,    87,   112,   101,     0,    57,   112,    87,   112,    87,
   112,   101,     0,    58,   112,    87,   112,    87,   112,   101,
     0,    59,   112,    87,   112,    87,   112,   101,     0,    60,
   112,    87,   112,    87,   112,   101,     0,    61,   112,    87,
   112,    87,   112,   101,     0,     0,    76,   112,    87,   112,
    87,   112,   102,     0,    77,   112,   102,     0,     0,    65,
     5,   102,     0,    66,     0,    67,     0,    68,   112,    87,
   112,    87,   112,    87,   112,     0,    69,   112,    87,   112,
    87,   112,     0,    70,   112,    87,   112,    87,   112,     0,
     0,    72,    85,   106,   107,     0,     0,    26,   112,    87,
   112,    87,   112,   107,     0,    73,   112,   107,     0,    74,
   112,    87,   112,    87,   112,   107,     0,     0,    63,     5,
     0,     0,    25,   115,   109,     0,    24,   115,   109,     0,
    28,   112,    87,   112,    87,   112,   109,     0,    27,   112,
    87,   112,    87,   112,   109,     0,    29,   115,   109,     0,
    30,   115,   109,     0,    31,   115,   109,     0,    32,   115,
   109,     0,    33,   115,   109,     0,    34,   115,   109,     0,
    35,   115,   109,     0,    36,   115,   109,     0,    37,   115,
   109,     0,     0,    26,   112,    87,   112,    87,   112,   110,
     0,    39,   112,    87,   112,    87,   112,   110,     0,    40,
   112,    87,   112,    87,   112,   110,     0,    41,   112,    87,
   112,    87,   112,   110,     0,    42,   112,   110,     0,     0,
    44,   115,   111,     0,    45,   112,   111,     0,    46,   112,
   111,     0,    47,   112,   111,     0,    48,   112,   111,     0,
    49,   112,   111,     0,    50,   112,   111,     0,    51,   112,
   111,     0,    52,   112,   111,     0,    53,   115,   111,     0,
    54,   112,    87,   112,    87,   112,   111,     0,     3,     0,
   115,     0,   113,     0,   112,    80,   112,     0,   115,    80,
   112,     0,   112,    80,   115,     0,   112,    79,   112,     0,
   115,    79,   112,     0,   112,    79,   115,     0,   112,    81,
   112,     0,   115,    81,   112,     0,   112,    81,   115,     0,
   112,    82,   112,     0,   115,    82,   112,     0,   112,    82,
   115,     0,   112,    84,   112,     0,   115,    84,   112,     0,
   112,    84,   115,     0,    79,   112,     0,    88,   112,    89,
     0,   114,     0,    11,    88,   112,    89,     0,    10,    88,
   112,    89,     0,    12,    88,   112,    89,     0,    14,    88,
   112,    89,     0,    13,    88,   112,    89,     0,    15,    88,
   112,    89,     0,    17,    88,   112,    89,     0,    18,    88,
   112,    89,     0,    19,    88,   112,    89,     0,    20,    88,
   112,    89,     0,    21,     0,    22,     0,     4,     0,   115,
    80,   115,     0,   115,    79,   115,     0,   115,    81,   115,
     0,   115,    82,   115,     0,    79,   115,     0,   115,    84,
   115,     0,    88,   115,    89,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   151,   152,   155,   156,   157,   158,   159,   160,   163,   171,
   179,   187,   196,   202,   210,   217,   226,   232,   240,   247,
   256,   262,   270,   277,   286,   287,   289,   291,   293,   295,
   297,   301,   302,   304,   308,   309,   319,   320,   322,   324,
   326,   330,   331,   333,   334,   336,   338,   343,   344,   353,
   354,   356,   358,   360,   362,   364,   366,   368,   370,   372,
   374,   376,   378,   382,   383,   385,   387,   389,   391,   395,
   396,   398,   400,   402,   404,   406,   408,   410,   412,   414,
   416,   420,   421,   422,   424,   425,   426,   428,   429,   430,
   432,   433,   434,   436,   437,   438,   440,   441,   442,   444,
   445,   446,   449,   450,   451,   452,   453,   454,   455,   456,
   457,   458,   461,   463,   466,   467,   468,   469,   470,   471,
   472,   473
};

static const char * const yytname[] = {   "$","error","$undefined.","REAL","PARSE_INT",
"STRING","PARSE_TRUE","PARSE_FALSE","ENABLE","DISABLE","MATH_COS","MATH_SIN",
"MATH_TAN","MATH_ACOS","MATH_ASIN","MATH_ATAN","MATH_ATAN2","MATH_LN","MATH_LOG",
"MATH_EXP","MATH_SQRT","MATH_E","MATH_PI","GLOBAL","WIDTH","HEIGHT","POS","IMG_BGCOLOR",
"GL_BGCOLOR","GL_SPHERE_SECTIONS","NUM_THREADS","RENDER_X_BLOCK","RENDER_Y_BLOCK",
"RENDER_HANDLER_SLEEP","RENDER_THREAD_SLEEP","RENDER_SPINLOCK_SLEEP","GAUSSIAN_BLUR_MAX",
"GAUSSIAN_BLUR_SIGMA","CAMERA","DIR","LOOKAT","UP","FOV","P0","SPIRAL_NUM_SPHERES",
"SPIRAL_RADIUS","LORENZ_DT","LORENZ_MIN_DISTANCE","LORENZ_MAX_DISTANCE","LORENZ_SIGMA",
"LORENZ_RHO","LORENZ_BETA","LORENZ_RADIUS","LORENZ_NUM_SPHERES","LORENZ_START",
"TRIANGLE","V1","V2","V3","N1","N2","N3","MESH","LOAD","INSTANCE","GEOMETRY",
"PUSHMATRIX","POPMATRIX","ROTATE","TRANSLATE","SCALE","LIGHT","POINTLIGHT","WATTAGE",
"COLOR","SPHERE","CENTER","RADIUS","'='","'-'","'+'","'*'","'/'","NEG","'^'",
"'{'","'}'","','","'('","')'","input","block","objectTypes","@1","@2","@3","@4",
"@5","@6","@7","@8","triangleOptions","sphereOptions","instanceOptions","transform",
"lightTypes","@9","lightOptions","meshOptions","globalOptions","cameraOptions",
"p0Options","rExp","fExp","constantExp","iExp",""
};
#endif

static const short yyr1[] = {     0,
    90,    90,    91,    91,    91,    91,    91,    91,    93,    92,
    94,    92,    95,    92,    96,    92,    97,    92,    98,    92,
    99,    92,   100,    92,   101,   101,   101,   101,   101,   101,
   101,   102,   102,   102,   103,   103,   104,   104,   104,   104,
   104,   106,   105,   107,   107,   107,   107,   108,   108,   109,
   109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
   109,   109,   109,   110,   110,   110,   110,   110,   110,   111,
   111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
   111,   112,   112,   112,   112,   112,   112,   112,   112,   112,
   112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
   112,   112,   113,   113,   113,   113,   113,   113,   113,   113,
   113,   113,   114,   114,   115,   115,   115,   115,   115,   115,
   115,   115
};

static const short yyr2[] = {     0,
     0,     2,     4,     4,     3,     4,     1,     1,     0,     5,
     0,     6,     0,     5,     0,     6,     0,     5,     0,     6,
     0,     5,     0,     6,     0,     7,     7,     7,     7,     7,
     7,     0,     7,     3,     0,     3,     1,     1,     8,     6,
     6,     0,     4,     0,     7,     3,     7,     0,     2,     0,
     3,     3,     7,     7,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     0,     7,     7,     7,     7,     3,     0,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     7,     1,     1,     1,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
     3,     1,     4,     4,     4,     4,     4,     4,     4,     4,
     4,     4,     1,     1,     1,     3,     3,     3,     3,     2,
     3,     3
};

static const short yydefact[] = {     1,
     0,     0,     0,     0,     0,     0,     0,    37,    38,     0,
     0,     0,     0,     0,     2,     7,     8,    50,    64,    70,
     0,     9,     0,    13,     0,    21,    82,   115,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   113,   114,
     0,     0,     0,    84,   102,    83,     0,     0,     0,     0,
     0,    17,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    11,    25,    15,    48,    23,    35,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   100,    83,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    42,     5,    19,
    32,     0,     0,    50,    50,     0,     0,    50,    50,    50,
    50,    50,    50,    50,    50,    50,     3,     0,     0,     0,
     0,    64,     4,    70,    70,    70,    70,    70,    70,    70,
    70,    70,    70,     0,     6,    25,     0,     0,     0,     0,
     0,     0,     0,    48,     0,     0,    35,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   101,
   122,    88,    83,    85,    83,    91,    83,    94,    83,    97,
    83,     0,    89,    83,    86,    83,    92,    83,    95,    83,
    98,    83,     0,     0,    44,    32,     0,     0,     0,   120,
     0,     0,     0,     0,     0,     0,    52,    51,     0,     0,
    55,    56,    57,    58,    59,    60,    61,    62,    63,     0,
     0,     0,     0,    69,    71,    72,    73,    74,    75,    76,
    77,    78,    79,    80,     0,     0,     0,     0,     0,     0,
     0,     0,    10,     0,    49,    14,     0,    32,    22,   104,
   103,   105,   107,   106,   108,   109,   110,   111,   112,     0,
     0,     0,     0,     0,     0,    43,     0,     0,    32,    18,
   117,   116,   118,   119,   121,     0,     0,     0,     0,     0,
     0,     0,    12,     0,     0,     0,     0,     0,     0,    16,
    24,    36,     0,    40,    41,     0,    44,     0,    20,     0,
    34,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    46,     0,     0,    50,
    50,    64,    64,    64,    64,    70,     0,     0,     0,     0,
     0,     0,    39,     0,     0,     0,    54,    53,    65,    66,
    67,    68,    81,    25,    25,    25,    25,    25,    25,     0,
     0,    32,    26,    27,    28,    29,    30,    31,    44,    44,
    33,    45,    47,     0,     0
};

static const short yydefgoto[] = {     1,
    15,    16,    86,   156,    88,   164,   121,   206,    90,   167,
   163,   209,   169,    17,    50,   205,   276,   166,    66,    72,
    84,    43,    44,    45,    46
};

static const short yypact[] = {-32768,
   120,   -78,   -64,   -59,    24,    43,    44,-32768,-32768,   104,
   104,   104,   -30,    45,-32768,-32768,-32768,   407,   113,   417,
   -42,-32768,   -39,-32768,   -38,-32768,-32768,-32768,   -37,   -27,
   -26,   -17,   -15,   -10,    -9,     4,     5,    22,-32768,-32768,
   104,   104,   454,-32768,-32768,   405,   463,   472,    26,    52,
    27,-32768,    48,    48,   104,   104,    48,    48,    48,    48,
    48,    48,    48,    48,    48,    54,   104,   104,   104,   104,
   104,    55,    48,   104,   104,   104,   104,   104,   104,   104,
   104,    48,   104,    58,-32768,   297,-32768,    68,-32768,    80,
   104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
    72,    73,   -62,    53,   104,   104,   104,   104,   104,   104,
   104,   104,   104,   104,   104,   104,   104,-32768,-32768,-32768,
   -52,    48,    48,   211,   211,   481,   490,   211,   211,   211,
   211,   211,   211,   211,   211,   211,-32768,   499,   508,   517,
   526,   186,-32768,   329,   376,   376,   376,   376,   376,   376,
   376,   376,   329,   535,-32768,   297,   104,   104,   104,   104,
   104,   104,    76,    68,   159,    79,    80,   165,    86,   229,
   316,   370,   393,   399,   418,   424,   430,   436,   442,-32768,
-32768,    -7,   148,    -7,   148,    72,    73,    72,    73,    72,
    73,   544,    -7,   148,    -7,   148,    72,    73,    72,    73,
    72,    73,   553,   562,   -20,   -52,   104,   104,    94,   101,
   448,    48,    48,    48,    48,    48,-32768,-32768,   104,   104,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   104,
   104,   104,   104,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,   104,   107,   571,   580,   589,   598,
   607,   616,-32768,   108,-32768,-32768,   112,   -52,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   104,
   104,   104,   104,   104,   104,-32768,   121,   625,    97,-32768,
   174,   174,   101,   101,   101,   634,   643,   652,   661,   670,
   679,   688,-32768,   104,   104,   104,   104,   104,   104,-32768,
-32768,-32768,   697,   805,   805,   706,    87,   715,-32768,   104,
-32768,   104,   104,   104,   104,   104,   104,   104,   724,   733,
   742,   751,   760,   769,   104,   104,-32768,   104,   778,   335,
   335,   186,   186,   186,   186,   376,   104,   104,   104,   104,
   104,   104,   805,   787,   796,   104,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,   193,   193,   193,   193,   193,   193,   104,
   104,    97,-32768,-32768,-32768,-32768,-32768,-32768,    87,    87,
-32768,-32768,-32768,   199,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -154,  -203,    39,-32768,-32768,-32768,  -279,    59,  -120,  -119,
  -112,   -11,-32768,-32768,   279
};


#define	YYLAST		889


static const short yytable[] = {    47,
    48,   246,   277,   217,   218,   273,    18,   221,   222,   223,
   224,   225,   226,   227,   228,   229,   105,   106,   107,   108,
    19,   109,   234,   207,   208,    20,   180,   327,    21,   101,
   103,   235,   236,   237,   238,   239,   240,   241,   242,   243,
   244,    49,    85,   126,   127,    87,    89,    23,    25,    51,
    91,    28,   274,   275,   302,   138,   139,   140,   141,   142,
    92,    93,   145,   146,   147,   148,   149,   150,   151,   152,
    94,   154,    95,   107,   108,   311,   109,    96,    97,   170,
   171,   172,   173,   174,   175,   176,   177,   178,   179,   372,
   373,    98,    99,   182,   184,   186,   188,   190,   192,   193,
   195,   197,   199,   201,   203,   204,    27,    28,    22,   100,
   118,   120,   273,    29,    30,    31,    32,    33,    34,   374,
    35,    36,    37,    38,    39,    40,   122,    24,    26,    52,
   165,   111,   112,   113,   114,   123,   115,   119,    67,   137,
   143,   181,     2,   155,   168,   247,   248,   249,   250,   251,
   252,    68,    69,    70,    71,   109,   115,     3,   371,   274,
   275,   253,     4,   255,   256,   105,   106,   107,   108,   258,
   109,   259,   207,   208,     5,   105,   106,   107,   108,   280,
   109,     6,    41,     7,   216,     8,     9,    10,    11,    12,
    13,    42,   293,   300,    14,   278,   279,   301,   375,   363,
   364,   365,   366,   367,   368,   257,   309,   286,   287,   347,
   348,    67,   349,   350,   351,   352,     0,     0,   288,   289,
   290,   291,   254,   353,    68,    69,    70,    71,   113,   114,
     0,   115,     0,   292,    53,    54,     0,    55,    56,    57,
    58,    59,    60,    61,    62,    63,    64,    65,   157,   158,
   159,   160,   161,   162,   214,   215,     0,   216,   303,   304,
   305,   306,   307,   308,   105,   106,   107,   108,     0,   109,
     0,   105,   106,   107,   108,     0,   109,     0,     0,     0,
     0,     0,   319,   320,   321,   322,   323,   324,     0,   212,
   213,   214,   215,     0,   216,     0,     0,     0,   329,     0,
   330,   331,   332,   333,   334,   335,   336,   105,   106,   107,
   108,     0,   109,   343,   344,     0,   345,   260,     0,   102,
   104,     0,     0,     0,     0,   354,   355,   356,   357,   358,
   359,   124,   125,     0,   362,   128,   129,   130,   131,   132,
   133,   134,   135,   136,     0,     0,     0,     0,   369,   370,
     0,   144,   157,   158,   159,   160,   161,   162,    53,    54,
   153,    55,    56,    57,    58,    59,    60,    61,    62,    63,
    64,    65,    73,    74,    75,    76,    77,    78,    79,    80,
    81,    82,    83,   183,   185,   187,   189,   191,     0,   194,
   196,   198,   200,   202,   105,   106,   107,   108,     0,   109,
   210,   211,     0,     0,   261,     0,     0,   212,   213,   214,
   215,     0,   216,   105,   106,   107,   108,     0,   109,    73,
    74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
    53,    54,     0,    55,    56,    57,    58,    59,    60,    61,
    62,    63,    64,    65,     0,     0,     0,     0,   105,   106,
   107,   108,     0,   109,   105,   106,   107,   108,   262,   109,
    73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
    83,   105,   106,   107,   108,     0,   109,   105,   106,   107,
   108,   263,   109,   111,   112,   113,   114,   264,   115,     0,
   281,   282,   283,   284,   285,     0,   105,   106,   107,   108,
     0,   109,   105,   106,   107,   108,   265,   109,   105,   106,
   107,   108,   266,   109,   105,   106,   107,   108,   267,   109,
   105,   106,   107,   108,   268,   109,   212,   213,   214,   215,
   269,   216,   105,   106,   107,   108,   181,   109,     0,     0,
   110,   105,   106,   107,   108,     0,   109,     0,     0,   116,
   105,   106,   107,   108,     0,   109,     0,     0,   117,   105,
   106,   107,   108,     0,   109,     0,     0,   219,   105,   106,
   107,   108,     0,   109,     0,     0,   220,   105,   106,   107,
   108,     0,   109,     0,     0,   230,   105,   106,   107,   108,
     0,   109,     0,     0,   231,   105,   106,   107,   108,     0,
   109,     0,     0,   232,   105,   106,   107,   108,     0,   109,
     0,     0,   233,   105,   106,   107,   108,     0,   109,     0,
     0,   245,   105,   106,   107,   108,     0,   109,     0,     0,
   270,   105,   106,   107,   108,     0,   109,     0,     0,   271,
   105,   106,   107,   108,     0,   109,     0,     0,   272,   105,
   106,   107,   108,     0,   109,     0,     0,   294,   105,   106,
   107,   108,     0,   109,     0,     0,   295,   105,   106,   107,
   108,     0,   109,     0,     0,   296,   105,   106,   107,   108,
     0,   109,     0,     0,   297,   105,   106,   107,   108,     0,
   109,     0,     0,   298,   105,   106,   107,   108,     0,   109,
     0,     0,   299,   105,   106,   107,   108,     0,   109,     0,
     0,   310,   105,   106,   107,   108,     0,   109,     0,     0,
   312,   105,   106,   107,   108,     0,   109,     0,     0,   313,
   105,   106,   107,   108,     0,   109,     0,     0,   314,   105,
   106,   107,   108,     0,   109,     0,     0,   315,   105,   106,
   107,   108,     0,   109,     0,     0,   316,   105,   106,   107,
   108,     0,   109,     0,     0,   317,   105,   106,   107,   108,
     0,   109,     0,     0,   318,   105,   106,   107,   108,     0,
   109,     0,     0,   325,   105,   106,   107,   108,     0,   109,
     0,     0,   326,   105,   106,   107,   108,     0,   109,     0,
     0,   328,   105,   106,   107,   108,     0,   109,     0,     0,
   337,   105,   106,   107,   108,     0,   109,     0,     0,   338,
   105,   106,   107,   108,     0,   109,     0,     0,   339,   105,
   106,   107,   108,     0,   109,     0,     0,   340,   105,   106,
   107,   108,     0,   109,     0,     0,   341,   105,   106,   107,
   108,     0,   109,     0,     0,   342,   105,   106,   107,   108,
     0,   109,     0,     0,   346,   105,   106,   107,   108,     0,
   109,     0,     0,   360,   105,   106,   107,   108,     0,   109,
     0,     0,   361,   105,   106,   107,   108,     0,   109
};

static const short yycheck[] = {    11,
    12,   156,   206,   124,   125,    26,    85,   128,   129,   130,
   131,   132,   133,   134,   135,   136,    79,    80,    81,    82,
    85,    84,   142,    76,    77,    85,    89,   307,     5,    41,
    42,   144,   145,   146,   147,   148,   149,   150,   151,   152,
   153,    72,    85,    55,    56,    85,    85,     5,     5,     5,
    88,     4,    73,    74,   258,    67,    68,    69,    70,    71,
    88,    88,    74,    75,    76,    77,    78,    79,    80,    81,
    88,    83,    88,    81,    82,   279,    84,    88,    88,    91,
    92,    93,    94,    95,    96,    97,    98,    99,   100,   369,
   370,    88,    88,   105,   106,   107,   108,   109,   110,   111,
   112,   113,   114,   115,   116,   117,     3,     4,    85,    88,
    85,    85,    26,    10,    11,    12,    13,    14,    15,     0,
    17,    18,    19,    20,    21,    22,    79,    85,    85,    85,
    63,    79,    80,    81,    82,    88,    84,    86,    26,    86,
    86,    89,    23,    86,    65,   157,   158,   159,   160,   161,
   162,    39,    40,    41,    42,    84,    84,    38,   362,    73,
    74,    86,    43,     5,    86,    79,    80,    81,    82,     5,
    84,    86,    76,    77,    55,    79,    80,    81,    82,    86,
    84,    62,    79,    64,    84,    66,    67,    68,    69,    70,
    71,    88,    86,    86,    75,   207,   208,    86,     0,   354,
   355,   356,   357,   358,   359,   167,    86,   219,   220,   330,
   331,    26,   332,   333,   334,   335,    -1,    -1,   230,   231,
   232,   233,   164,   336,    39,    40,    41,    42,    81,    82,
    -1,    84,    -1,   245,    24,    25,    -1,    27,    28,    29,
    30,    31,    32,    33,    34,    35,    36,    37,    56,    57,
    58,    59,    60,    61,    81,    82,    -1,    84,   270,   271,
   272,   273,   274,   275,    79,    80,    81,    82,    -1,    84,
    -1,    79,    80,    81,    82,    -1,    84,    -1,    -1,    -1,
    -1,    -1,   294,   295,   296,   297,   298,   299,    -1,    79,
    80,    81,    82,    -1,    84,    -1,    -1,    -1,   310,    -1,
   312,   313,   314,   315,   316,   317,   318,    79,    80,    81,
    82,    -1,    84,   325,   326,    -1,   328,    89,    -1,    41,
    42,    -1,    -1,    -1,    -1,   337,   338,   339,   340,   341,
   342,    53,    54,    -1,   346,    57,    58,    59,    60,    61,
    62,    63,    64,    65,    -1,    -1,    -1,    -1,   360,   361,
    -1,    73,    56,    57,    58,    59,    60,    61,    24,    25,
    82,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    44,    45,    46,    47,    48,    49,    50,    51,
    52,    53,    54,   105,   106,   107,   108,   109,    -1,   111,
   112,   113,   114,   115,    79,    80,    81,    82,    -1,    84,
   122,   123,    -1,    -1,    89,    -1,    -1,    79,    80,    81,
    82,    -1,    84,    79,    80,    81,    82,    -1,    84,    44,
    45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
    24,    25,    -1,    27,    28,    29,    30,    31,    32,    33,
    34,    35,    36,    37,    -1,    -1,    -1,    -1,    79,    80,
    81,    82,    -1,    84,    79,    80,    81,    82,    89,    84,
    44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
    54,    79,    80,    81,    82,    -1,    84,    79,    80,    81,
    82,    89,    84,    79,    80,    81,    82,    89,    84,    -1,
   212,   213,   214,   215,   216,    -1,    79,    80,    81,    82,
    -1,    84,    79,    80,    81,    82,    89,    84,    79,    80,
    81,    82,    89,    84,    79,    80,    81,    82,    89,    84,
    79,    80,    81,    82,    89,    84,    79,    80,    81,    82,
    89,    84,    79,    80,    81,    82,    89,    84,    -1,    -1,
    87,    79,    80,    81,    82,    -1,    84,    -1,    -1,    87,
    79,    80,    81,    82,    -1,    84,    -1,    -1,    87,    79,
    80,    81,    82,    -1,    84,    -1,    -1,    87,    79,    80,
    81,    82,    -1,    84,    -1,    -1,    87,    79,    80,    81,
    82,    -1,    84,    -1,    -1,    87,    79,    80,    81,    82,
    -1,    84,    -1,    -1,    87,    79,    80,    81,    82,    -1,
    84,    -1,    -1,    87,    79,    80,    81,    82,    -1,    84,
    -1,    -1,    87,    79,    80,    81,    82,    -1,    84,    -1,
    -1,    87,    79,    80,    81,    82,    -1,    84,    -1,    -1,
    87,    79,    80,    81,    82,    -1,    84,    -1,    -1,    87,
    79,    80,    81,    82,    -1,    84,    -1,    -1,    87,    79,
    80,    81,    82,    -1,    84,    -1,    -1,    87,    79,    80,
    81,    82,    -1,    84,    -1,    -1,    87,    79,    80,    81,
    82,    -1,    84,    -1,    -1,    87,    79,    80,    81,    82,
    -1,    84,    -1,    -1,    87,    79,    80,    81,    82,    -1,
    84,    -1,    -1,    87,    79,    80,    81,    82,    -1,    84,
    -1,    -1,    87,    79,    80,    81,    82,    -1,    84,    -1,
    -1,    87,    79,    80,    81,    82,    -1,    84,    -1,    -1,
    87,    79,    80,    81,    82,    -1,    84,    -1,    -1,    87,
    79,    80,    81,    82,    -1,    84,    -1,    -1,    87,    79,
    80,    81,    82,    -1,    84,    -1,    -1,    87,    79,    80,
    81,    82,    -1,    84,    -1,    -1,    87,    79,    80,    81,
    82,    -1,    84,    -1,    -1,    87,    79,    80,    81,    82,
    -1,    84,    -1,    -1,    87,    79,    80,    81,    82,    -1,
    84,    -1,    -1,    87,    79,    80,    81,    82,    -1,    84,
    -1,    -1,    87,    79,    80,    81,    82,    -1,    84,    -1,
    -1,    87,    79,    80,    81,    82,    -1,    84,    -1,    -1,
    87,    79,    80,    81,    82,    -1,    84,    -1,    -1,    87,
    79,    80,    81,    82,    -1,    84,    -1,    -1,    87,    79,
    80,    81,    82,    -1,    84,    -1,    -1,    87,    79,    80,
    81,    82,    -1,    84,    -1,    -1,    87,    79,    80,    81,
    82,    -1,    84,    -1,    -1,    87,    79,    80,    81,    82,
    -1,    84,    -1,    -1,    87,    79,    80,    81,    82,    -1,
    84,    -1,    -1,    87,    79,    80,    81,    82,    -1,    84,
    -1,    -1,    87,    79,    80,    81,    82,    -1,    84
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

case 5:
#line 157 "parser.y"
{ printf( "Adding Light\n" ); ;
    break;}
case 9:
#line 165 "parser.y"
{
                printf( "Creating Triangle\n" );
                //pObj = new Triangle;
                //pObj->SetMaterial (pMat);
                //((TriangleMesh*)pObj)->CreateSingleTriangle();
            ;
    break;}
case 10:
#line 172 "parser.y"
{
                printf( "Adding Triangle to Scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 11:
#line 180 "parser.y"
{
                printf( "Creating named triangle '%s'\n", yyvsp[-1].str );
                //pObj = new TriangleMesh;
                //pObj->SetMaterial (pMat);
                //g_objectMap[$2] = pObj;
                //((TriangleMesh*)pObj)->CreateSingleTriangle();
            ;
    break;}
case 12:
#line 188 "parser.y"
{
                printf( "Adding named Triangle to Scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 13:
#line 197 "parser.y"
{
                printf( "Creating new mesh\n" );
                //pObj = new TriangleMesh;
                //pObj->SetMaterial (pMat);
            ;
    break;}
case 14:
#line 203 "parser.y"
{
                printf( "Adding mesh to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 15:
#line 211 "parser.y"
{
                printf( "Creating new named mesh '%s'\n", yyvsp[-1].str );
                //pObj = new TriangleMesh;
                //pObj->SetMaterial (pMat);
                //g_objectMap[$2] = pObj;
            ;
    break;}
case 16:
#line 218 "parser.y"
{
                printf( "Adding named mesh to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 17:
#line 227 "parser.y"
{
                printf( "Creating new sphere\n" );
                //pObj = new Sphere;
                //pObj->SetMaterial (pMat);
            ;
    break;}
case 18:
#line 233 "parser.y"
{
                printf( "Adding sphere to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 19:
#line 241 "parser.y"
{
                printf( "Creating new sphere named '%s'\n", yyvsp[-1].str );
                //pObj = new Sphere;
                //pObj->SetMaterial (pMat);
                //g_objectMap[$2] = pObj;
            ;
    break;}
case 20:
#line 248 "parser.y"
{
                printf( "Adding sphere to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 21:
#line 257 "parser.y"
{
                printf( "Creating new instance\n" );
                //pObj = new Instance;
                //pObj->SetMaterial (pMat);
            ;
    break;}
case 22:
#line 263 "parser.y"
{
                printf( "Adding instance to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 23:
#line 271 "parser.y"
{
                printf( "Creating new named instance '%s'\n", yyvsp[-1].str );
                //pObj = new Instance;
                //pObj->SetMaterial (pMat);
                //g_objectMap[$2] = pObj;
            ;
    break;}
case 24:
#line 278 "parser.y"
{
                printf( "Adding named instance to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 26:
#line 288 "parser.y"
{ /*((TriangleMesh*)pObj)->SetV1(Vertex3($2, $4, $6));*/ ;
    break;}
case 27:
#line 290 "parser.y"
{  ;
    break;}
case 28:
#line 292 "parser.y"
{  ;
    break;}
case 29:
#line 294 "parser.y"
{  ;
    break;}
case 30:
#line 296 "parser.y"
{  ;
    break;}
case 31:
#line 298 "parser.y"
{  ;
    break;}
case 33:
#line 303 "parser.y"
{  ;
    break;}
case 34:
#line 305 "parser.y"
{  ;
    break;}
case 36:
#line 310 "parser.y"
{
                //std::map<std::string, Object*>::const_iterator it = g_objectMap.find ($2);
                //if (it != g_objectMap.end ())
                //{
                    //((Instance*)pObj)->SetGeometry(it->second, GetCTM());
                //}
            ;
    break;}
case 37:
#line 319 "parser.y"
{ /*PushMatrix();*/ ;
    break;}
case 38:
#line 321 "parser.y"
{ /*PopMatrix();*/ ;
    break;}
case 39:
#line 323 "parser.y"
{ /*Rotate($2, $4, $6, $8);*/ ;
    break;}
case 40:
#line 325 "parser.y"
{ /*Translate($2, $4, $6);*/ ;
    break;}
case 41:
#line 327 "parser.y"
{ /*Scale($2, $4, $6);*/ ;
    break;}
case 42:
#line 330 "parser.y"
{ /*pLight = new PointLight;*/ ;
    break;}
case 45:
#line 335 "parser.y"
{ /*pLight->SetPosition(Vertex3($2, $4, $6));*/ ;
    break;}
case 46:
#line 337 "parser.y"
{ /*pLight->SetWattage($2);*/ ;
    break;}
case 47:
#line 339 "parser.y"
{ /*pLight->SetColor(Vector3($2, $4, $6));*/ ;
    break;}
case 49:
#line 345 "parser.y"
{
                yyvsp[0].str[strlen(yyvsp[0].str)-1]=0;
                printf( "Load Mesh: '%s'\n", yyvsp[0].str+1 );
                //if (!((TriangleMesh*)pObj)->Load(s, GetCTM()))
                    //pObj = 0;
            ;
    break;}
case 51:
#line 355 "parser.y"
{ rawray::options::global::win_height = yyvsp[-1].integer; ;
    break;}
case 52:
#line 357 "parser.y"
{ rawray::options::global::win_width = yyvsp[-1].integer; ;
    break;}
case 53:
#line 359 "parser.y"
{ rawray::options::global::gl_bg_color = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 54:
#line 361 "parser.y"
{ rawray::options::global::img_bg_color = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 55:
#line 363 "parser.y"
{ rawray::options::global::gl_sphere_sections = yyvsp[-1].integer; ;
    break;}
case 56:
#line 365 "parser.y"
{ rawray::options::global::num_threads = yyvsp[-1].integer; ;
    break;}
case 57:
#line 367 "parser.y"
{ rawray::options::global::render_x_block = yyvsp[-1].integer; ;
    break;}
case 58:
#line 369 "parser.y"
{ rawray::options::global::render_y_block = yyvsp[-1].integer; ;
    break;}
case 59:
#line 371 "parser.y"
{ rawray::options::global::render_handler_sleep = yyvsp[-1].integer; ;
    break;}
case 60:
#line 373 "parser.y"
{ rawray::options::global::render_thread_sleep = yyvsp[-1].integer; ;
    break;}
case 61:
#line 375 "parser.y"
{ rawray::options::global::render_spinlock_sleep = yyvsp[-1].integer; ;
    break;}
case 62:
#line 377 "parser.y"
{ rawray::options::global::gaussian_blur_max = yyvsp[-1].integer; ;
    break;}
case 63:
#line 379 "parser.y"
{ rawray::options::global::gaussian_blur_sigma = yyvsp[-1].integer; ;
    break;}
case 65:
#line 384 "parser.y"
{ rawray::options::camera::eye = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 66:
#line 386 "parser.y"
{ rawray::options::camera::view = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 67:
#line 388 "parser.y"
{ rawray::options::camera::lookat = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 68:
#line 390 "parser.y"
{ rawray::options::camera::up = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 69:
#line 392 "parser.y"
{ rawray::options::camera::fov = yyvsp[-1].real; ;
    break;}
case 71:
#line 397 "parser.y"
{ rawray::options::p0::spiral_num_spheres = yyvsp[-1].integer; ;
    break;}
case 72:
#line 399 "parser.y"
{ rawray::options::p0::spiral_radius = yyvsp[-1].real; ;
    break;}
case 73:
#line 401 "parser.y"
{ rawray::options::p0::lorenz_dt = yyvsp[-1].real; ;
    break;}
case 74:
#line 403 "parser.y"
{ rawray::options::p0::lorenz_min_distance = yyvsp[-1].real; ;
    break;}
case 75:
#line 405 "parser.y"
{ rawray::options::p0::lorenz_max_distance = yyvsp[-1].real; ;
    break;}
case 76:
#line 407 "parser.y"
{ rawray::options::p0::lorenz_sigma = yyvsp[-1].real; ;
    break;}
case 77:
#line 409 "parser.y"
{ rawray::options::p0::lorenz_rho = yyvsp[-1].real; ;
    break;}
case 78:
#line 411 "parser.y"
{ rawray::options::p0::lorenz_beta = yyvsp[-1].real; ;
    break;}
case 79:
#line 413 "parser.y"
{ rawray::options::p0::lorenz_radius = yyvsp[-1].real; ;
    break;}
case 80:
#line 415 "parser.y"
{ rawray::options::p0::lorenz_num_spheres = yyvsp[-1].integer; ;
    break;}
case 81:
#line 417 "parser.y"
{ rawray::options::p0::lorenz_start = math::Vector3(yyvsp[-5].real,yyvsp[-3].real,yyvsp[-1].real); ;
    break;}
case 82:
#line 420 "parser.y"
{ yyval.real = yyvsp[0].real; ;
    break;}
case 83:
#line 421 "parser.y"
{ yyval.real = yyvsp[0].integer; ;
    break;}
case 84:
#line 422 "parser.y"
{ yyval.real = yyvsp[0].real; ;
    break;}
case 85:
#line 424 "parser.y"
{ yyval.real = yyvsp[-2].real + yyvsp[0].real; ;
    break;}
case 86:
#line 425 "parser.y"
{ yyval.real = yyvsp[-2].integer + yyvsp[0].real; ;
    break;}
case 87:
#line 426 "parser.y"
{ yyval.real = yyvsp[-2].real + yyvsp[0].integer; ;
    break;}
case 88:
#line 428 "parser.y"
{ yyval.real = yyvsp[-2].real - yyvsp[0].real; ;
    break;}
case 89:
#line 429 "parser.y"
{ yyval.real = yyvsp[-2].integer - yyvsp[0].real; ;
    break;}
case 90:
#line 430 "parser.y"
{ yyval.real = yyvsp[-2].real - yyvsp[0].integer; ;
    break;}
case 91:
#line 432 "parser.y"
{ yyval.real = yyvsp[-2].real * yyvsp[0].real; ;
    break;}
case 92:
#line 433 "parser.y"
{ yyval.real = yyvsp[-2].integer * yyvsp[0].real; ;
    break;}
case 93:
#line 434 "parser.y"
{ yyval.real = yyvsp[-2].real * yyvsp[0].integer; ;
    break;}
case 94:
#line 436 "parser.y"
{ yyval.real = yyvsp[-2].real / yyvsp[0].real; ;
    break;}
case 95:
#line 437 "parser.y"
{ yyval.real = yyvsp[-2].integer / yyvsp[0].real; ;
    break;}
case 96:
#line 438 "parser.y"
{ yyval.real = yyvsp[-2].real / yyvsp[0].integer; ;
    break;}
case 97:
#line 440 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].real), float (yyvsp[0].real)); ;
    break;}
case 98:
#line 441 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].integer), float (yyvsp[0].real)); ;
    break;}
case 99:
#line 442 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].real), float (yyvsp[0].integer)); ;
    break;}
case 100:
#line 444 "parser.y"
{ yyval.real = -yyvsp[0].real; ;
    break;}
case 101:
#line 445 "parser.y"
{ yyval.real = yyvsp[-1].real; ;
    break;}
case 103:
#line 449 "parser.y"
{yyval.real = sin(yyvsp[-1].real); ;
    break;}
case 104:
#line 450 "parser.y"
{yyval.real = cos(yyvsp[-1].real); ;
    break;}
case 105:
#line 451 "parser.y"
{yyval.real = tan(yyvsp[-1].real); ;
    break;}
case 106:
#line 452 "parser.y"
{yyval.real = asin(yyvsp[-1].real); ;
    break;}
case 107:
#line 453 "parser.y"
{yyval.real = acos(yyvsp[-1].real); ;
    break;}
case 108:
#line 454 "parser.y"
{yyval.real = atan(yyvsp[-1].real); ;
    break;}
case 109:
#line 455 "parser.y"
{yyval.real = log(yyvsp[-1].real); ;
    break;}
case 110:
#line 456 "parser.y"
{yyval.real = log10(yyvsp[-1].real); ;
    break;}
case 111:
#line 457 "parser.y"
{yyval.real = exp(yyvsp[-1].real); ;
    break;}
case 112:
#line 458 "parser.y"
{yyval.real = sqrt(yyvsp[-1].real); ;
    break;}
case 113:
#line 462 "parser.y"
{ yyval.real = 2.718281828459f; ;
    break;}
case 114:
#line 463 "parser.y"
{ yyval.real = 3.141592653589793f; ;
    break;}
case 115:
#line 466 "parser.y"
{ yyval.integer = yyvsp[0].integer; ;
    break;}
case 116:
#line 467 "parser.y"
{ yyval.integer = yyvsp[-2].integer + yyvsp[0].integer; ;
    break;}
case 117:
#line 468 "parser.y"
{ yyval.integer = yyvsp[-2].integer - yyvsp[0].integer; ;
    break;}
case 118:
#line 469 "parser.y"
{ yyval.integer = yyvsp[-2].integer * yyvsp[0].integer; ;
    break;}
case 119:
#line 470 "parser.y"
{ yyval.integer = yyvsp[-2].integer / yyvsp[0].integer; ;
    break;}
case 120:
#line 471 "parser.y"
{ yyval.integer = -yyvsp[0].integer; ;
    break;}
case 121:
#line 472 "parser.y"
{ yyval.integer = (int)pow((float)yyvsp[-2].integer, (float)yyvsp[0].integer); ;
    break;}
case 122:
#line 473 "parser.y"
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
#line 477 "parser.y"

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
