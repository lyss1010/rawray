
/*  A Bison parser, made from parser.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	YY_SYM_REAL	258
#define	YY_SYM_INT	259
#define	YY_SYM_STRING	260
#define	YY_STATE_GLOBAL	261
#define	YY_SYM_GLOBAL_WIDTH	262
#define	YY_SYM_GLOBAL_HEIGHT	263
#define	YY_SYM_GLOBAL_GL_BG	264
#define	YY_SYM_GLOBAL_IMG_BG	265
#define	YY_STATE_CAMERA	266
#define	YY_SYM_CAMERA_POS	267
#define	YY_SYM_CAMERA_VIEW_DIR	268
#define	YY_SYM_CAMERA_LOOK_AT	269
#define	YY_SYM_CAMERA_UP	270
#define	YY_SYM_CAMERA_FOV	271
#define	YY_STATE_LIGHT	272
#define	YY_SYM_LIGHT_POINTLIGHT	273
#define	YY_SYM_LIGHT_POS	274
#define	YY_SYM_LIGHT_COLOR	275
#define	YY_SYM_LIGHT_WATTAGE	276
#define	YY_STATE_MODEL	277
#define	YY_SYM_MODEL_LOAD	278
#define	YY_STATE_SPHERE	279
#define	YY_SYM_SPHERE_POS	280
#define	YY_SYM_SPHERE_RADIUS	281
#define	YY_SYM_SPHERE_COLOR	282
#define	YY_MATH_COS	283
#define	YY_MATH_SIN	284
#define	YY_MATH_TAN	285
#define	YY_MATH_ACOS	286
#define	YY_MATH_ASIN	287
#define	YY_MATH_ATAN	288
#define	YY_MATH_LN	289
#define	YY_MATH_LOG	290
#define	YY_MATH_EXP	291
#define	YY_MATH_SQRT	292
#define	YY_MATH_E	293
#define	YY_MATH_PI	294
#define	NEG	295

#line 1 "parser.y"

#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <stdlib.h>
#include <math.h>
#include <stack>
#include <map>
#include <string>
#include <iostream>
//#include "rawray/object.h"
//#include "rawray/light.h"
//#include "rawray/camera.h"
//#include "math/vector3.h"

#ifdef _DEBUG
#define YYDEBUG 1
#endif

#define yyerror(x) Fatal( "Parser error on line %d: %s\n", yyline, x ); 

extern int yylex();
extern int yyline;
extern FILE *yyin, *yyout;

// variables for adding objects, keeping track of variables
//std::map<std::string, Object*> g_objectMap;
//rawray::Object* g_object = NULL;
//rawray::Light* g_light = NULL;
//rawray::Camera* g_camera = NULL;


#line 36 "parser.y"
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



#define	YYFINAL		209
#define	YYFLAG		-32768
#define	YYNTBASE	52

#define YYTRANSLATE(x) ((unsigned)(x) <= 295 ? yytranslate[x] : 68)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    50,
    51,    43,    42,    49,    41,     2,    44,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    40,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    46,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    47,     2,    48,     2,     2,     2,     2,     2,
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
    36,    37,    38,    39,    45
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     9,    14,    16,    20,    21,    22,    28,
    29,    35,    36,    44,    48,    49,    54,    55,    63,    67,
    75,    76,    79,    80,    84,    88,    96,   104,   105,   113,
   121,   129,   137,   141,   143,   145,   147,   151,   155,   159,
   163,   167,   171,   175,   179,   183,   187,   191,   195,   199,
   203,   207,   210,   214,   216,   221,   226,   231,   236,   241,
   246,   251,   256,   261,   266,   268,   270,   272,   276,   280,
   284,   288,   291,   295
};

static const short yyrhs[] = {    -1,
    52,    53,     0,     6,    47,    62,    48,     0,    11,    47,
    63,    48,     0,    54,     0,    17,    58,    48,     0,     0,
     0,    22,    47,    55,    61,    48,     0,     0,    24,    47,
    56,    57,    48,     0,     0,    25,    64,    49,    64,    49,
    64,    57,     0,    26,    64,    57,     0,     0,    18,    47,
    59,    60,     0,     0,    19,    64,    49,    64,    49,    64,
    60,     0,    21,    64,    60,     0,    20,    64,    49,    64,
    49,    64,    60,     0,     0,    23,     5,     0,     0,     8,
    67,    62,     0,     7,    67,    62,     0,     9,    64,    49,
    64,    49,    64,    62,     0,    10,    64,    49,    64,    49,
    64,    62,     0,     0,    12,    64,    49,    64,    49,    64,
    63,     0,    13,    64,    49,    64,    49,    64,    63,     0,
    14,    64,    49,    64,    49,    64,    63,     0,    15,    64,
    49,    64,    49,    64,    63,     0,    16,    64,    63,     0,
     3,     0,    67,     0,    65,     0,    64,    42,    64,     0,
    67,    42,    64,     0,    64,    42,    67,     0,    64,    41,
    64,     0,    67,    41,    64,     0,    64,    41,    67,     0,
    64,    43,    64,     0,    67,    43,    64,     0,    64,    43,
    67,     0,    64,    44,    64,     0,    67,    44,    64,     0,
    64,    44,    67,     0,    64,    46,    64,     0,    67,    46,
    64,     0,    64,    46,    67,     0,    41,    64,     0,    50,
    64,    51,     0,    66,     0,    29,    50,    64,    51,     0,
    28,    50,    64,    51,     0,    30,    50,    64,    51,     0,
    32,    50,    64,    51,     0,    31,    50,    64,    51,     0,
    33,    50,    64,    51,     0,    34,    50,    64,    51,     0,
    35,    50,    64,    51,     0,    36,    50,    64,    51,     0,
    37,    50,    64,    51,     0,    38,     0,    39,     0,     4,
     0,    67,    42,    67,     0,    67,    41,    67,     0,    67,
    43,    67,     0,    67,    44,    67,     0,    41,    67,     0,
    67,    46,    67,     0,    50,    67,    51,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    98,    99,   102,   103,   104,   105,   108,   109,   114,   121,
   126,   134,   135,   137,   141,   142,   144,   145,   147,   149,
   154,   155,   168,   169,   171,   173,   175,   179,   180,   182,
   184,   186,   188,   192,   193,   194,   196,   197,   198,   200,
   201,   202,   204,   205,   206,   208,   209,   210,   212,   213,
   214,   216,   217,   218,   221,   222,   223,   224,   225,   226,
   227,   228,   229,   230,   233,   235,   238,   239,   240,   241,
   242,   243,   244,   245
};

static const char * const yytname[] = {   "$","error","$undefined.","YY_SYM_REAL",
"YY_SYM_INT","YY_SYM_STRING","YY_STATE_GLOBAL","YY_SYM_GLOBAL_WIDTH","YY_SYM_GLOBAL_HEIGHT",
"YY_SYM_GLOBAL_GL_BG","YY_SYM_GLOBAL_IMG_BG","YY_STATE_CAMERA","YY_SYM_CAMERA_POS",
"YY_SYM_CAMERA_VIEW_DIR","YY_SYM_CAMERA_LOOK_AT","YY_SYM_CAMERA_UP","YY_SYM_CAMERA_FOV",
"YY_STATE_LIGHT","YY_SYM_LIGHT_POINTLIGHT","YY_SYM_LIGHT_POS","YY_SYM_LIGHT_COLOR",
"YY_SYM_LIGHT_WATTAGE","YY_STATE_MODEL","YY_SYM_MODEL_LOAD","YY_STATE_SPHERE",
"YY_SYM_SPHERE_POS","YY_SYM_SPHERE_RADIUS","YY_SYM_SPHERE_COLOR","YY_MATH_COS",
"YY_MATH_SIN","YY_MATH_TAN","YY_MATH_ACOS","YY_MATH_ASIN","YY_MATH_ATAN","YY_MATH_LN",
"YY_MATH_LOG","YY_MATH_EXP","YY_MATH_SQRT","YY_MATH_E","YY_MATH_PI","'='","'-'",
"'+'","'*'","'/'","NEG","'^'","'{'","'}'","','","'('","')'","input","block",
"objectTypes","@1","@2","sphereOptions","lightTypes","@3","lightOptions","meshOptions",
"globalOptions","cameraOptions","rExp","fExp","constantExp","iExp",""
};
#endif

static const short yyr1[] = {     0,
    52,    52,    53,    53,    53,    53,    54,    55,    54,    56,
    54,    57,    57,    57,    59,    58,    60,    60,    60,    60,
    61,    61,    62,    62,    62,    62,    62,    63,    63,    63,
    63,    63,    63,    64,    64,    64,    64,    64,    64,    64,
    64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
    64,    64,    64,    64,    65,    65,    65,    65,    65,    65,
    65,    65,    65,    65,    66,    66,    67,    67,    67,    67,
    67,    67,    67,    67
};

static const short yyr2[] = {     0,
     0,     2,     4,     4,     1,     3,     0,     0,     5,     0,
     5,     0,     7,     3,     0,     4,     0,     7,     3,     7,
     0,     2,     0,     3,     3,     7,     7,     0,     7,     7,
     7,     7,     3,     1,     1,     1,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     2,     3,     1,     4,     4,     4,     4,     4,     4,
     4,     4,     4,     4,     1,     1,     1,     3,     3,     3,
     3,     2,     3,     3
};

static const short yydefact[] = {     1,
     0,     0,     0,     0,     0,     0,     2,     5,    23,    28,
     0,     0,     8,    10,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    15,     6,    21,    12,    67,
     0,     0,    23,    23,    34,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    65,    66,     0,     0,     0,
    36,    54,    35,     0,     3,     0,     0,     0,     0,    28,
     4,    17,     0,     0,     0,     0,     0,    72,     0,     0,
     0,     0,     0,     0,    25,    24,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    52,    35,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
    16,    22,     9,     0,    12,    11,    74,    69,    68,    70,
    71,    73,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    53,    40,    35,    37,    35,    43,    35,    46,
    35,    49,    35,     0,    41,    35,    38,    35,    44,    35,
    47,    35,    50,    35,     0,     0,     0,     0,     0,     0,
     0,    17,     0,    14,    56,    55,    57,    59,    58,    60,
    61,    62,    63,    64,     0,     0,     0,     0,     0,     0,
     0,     0,    19,     0,    23,    23,    28,    28,    28,    28,
     0,     0,     0,    26,    27,    29,    30,    31,    32,     0,
     0,    12,    17,    17,    13,    18,    20,     0,     0
};

static const short yydefgoto[] = {     1,
     7,     8,    28,    29,    67,    12,    62,   111,    64,    19,
    25,    50,    51,    52,    53
};

static const short yypact[] = {-32768,
   212,   -36,   -28,    27,   -19,   -15,-32768,-32768,    14,   104,
     3,     9,-32768,-32768,     8,     8,     5,     5,    41,     5,
     5,     5,     5,     5,    45,-32768,-32768,    78,    70,-32768,
     8,     8,    62,    62,-32768,    75,    77,    82,    83,    84,
    85,    86,    94,   100,   102,-32768,-32768,     5,     5,   178,
-32768,-32768,   148,   262,-32768,   271,   280,   289,   298,   127,
-32768,    90,   151,   119,     5,     5,   124,   107,   -26,     8,
     8,     8,     8,     8,-32768,-32768,     5,     5,     5,     5,
     5,     5,     5,     5,     5,     5,   128,   135,    56,   196,
     5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
     5,     5,     5,     5,     5,     5,-32768,     5,     5,     5,
-32768,-32768,-32768,   307,   189,-32768,-32768,   -17,   -17,   107,
   107,   107,   202,   208,   214,   220,   226,   232,   238,   244,
   250,   256,-32768,    10,    80,    10,    80,   128,   135,   128,
   135,   128,   135,   316,    10,    80,    10,    80,   128,   135,
   128,   135,   128,   135,   325,   334,   343,   352,   361,   370,
   379,   167,     5,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,     5,     5,     5,     5,     5,     5,
     5,     5,-32768,   388,   105,   105,   127,   127,   127,   127,
   397,   406,     5,-32768,-32768,-32768,-32768,-32768,-32768,     5,
     5,   189,   167,   167,-32768,-32768,-32768,   184,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,  -108,-32768,-32768,  -152,-32768,   -20,
   -59,   -18,-32768,-32768,   106
};


#define	YYLAST		455


static const short yytable[] = {    54,
   107,    56,    57,    58,    59,    60,   164,    35,    30,   183,
     9,    30,    75,    76,    70,    71,    72,    73,    10,    74,
    15,    16,    17,    18,   117,    72,    73,    13,    74,    87,
    89,    14,    36,    37,    38,    39,    40,    41,    42,    43,
    44,    45,    46,    47,    11,    48,   114,   115,    31,    26,
   206,   207,    93,    94,    49,    95,    27,    32,   123,   124,
   125,   126,   127,   128,   129,   130,   131,   132,    15,    16,
    17,    18,   134,   136,   138,   140,   142,   144,   145,   147,
   149,   151,   153,   155,   156,   157,   158,   159,    55,   160,
   161,   162,    61,   205,    65,    66,    91,    92,    93,    94,
    63,    95,    70,    71,    72,    73,   133,    74,   108,   109,
   110,    15,    16,    17,    18,    20,    21,    22,    23,    24,
    33,    34,    99,   100,    77,   101,    78,   196,   197,   198,
   199,    79,    80,    81,    82,    83,    68,    69,    20,    21,
    22,    23,    24,    84,   184,    91,    92,    93,    94,    85,
    95,    86,    74,    88,    90,   112,   185,   186,   187,   188,
   189,   190,   191,   192,   194,   195,   113,    91,    92,    93,
    94,   116,    95,    95,   202,   118,   119,   120,   121,   122,
   101,   203,   204,   209,     0,   108,   109,   110,    97,    98,
    99,   100,     0,   101,     0,     0,   135,   137,   139,   141,
   143,     0,   146,   148,   150,   152,   154,    91,    92,    93,
    94,   208,    95,    65,    66,     0,     0,     2,    91,    92,
    93,    94,     3,    95,     0,     0,    96,     0,     4,    91,
    92,    93,    94,     5,    95,     6,    97,    98,    99,   100,
     0,   101,    91,    92,    93,    94,   117,    95,    91,    92,
    93,    94,   165,    95,    91,    92,    93,    94,   166,    95,
    91,    92,    93,    94,   167,    95,    91,    92,    93,    94,
   168,    95,    91,    92,    93,    94,   169,    95,    91,    92,
    93,    94,   170,    95,    91,    92,    93,    94,   171,    95,
    91,    92,    93,    94,   172,    95,    91,    92,    93,    94,
   173,    95,    91,    92,    93,    94,   174,    95,     0,     0,
   102,    91,    92,    93,    94,     0,    95,     0,     0,   103,
    91,    92,    93,    94,     0,    95,     0,     0,   104,    91,
    92,    93,    94,     0,    95,     0,     0,   105,    91,    92,
    93,    94,     0,    95,     0,     0,   106,    91,    92,    93,
    94,     0,    95,     0,     0,   163,    91,    92,    93,    94,
     0,    95,     0,     0,   175,    91,    92,    93,    94,     0,
    95,     0,     0,   176,    91,    92,    93,    94,     0,    95,
     0,     0,   177,    91,    92,    93,    94,     0,    95,     0,
     0,   178,    91,    92,    93,    94,     0,    95,     0,     0,
   179,    91,    92,    93,    94,     0,    95,     0,     0,   180,
    91,    92,    93,    94,     0,    95,     0,     0,   181,    91,
    92,    93,    94,     0,    95,     0,     0,   182,    91,    92,
    93,    94,     0,    95,     0,     0,   193,    91,    92,    93,
    94,     0,    95,     0,     0,   200,    91,    92,    93,    94,
     0,    95,     0,     0,   201
};

static const short yycheck[] = {    18,
    60,    20,    21,    22,    23,    24,   115,     3,     4,   162,
    47,     4,    33,    34,    41,    42,    43,    44,    47,    46,
     7,     8,     9,    10,    51,    43,    44,    47,    46,    48,
    49,    47,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    18,    41,    65,    66,    41,    47,
   203,   204,    43,    44,    50,    46,    48,    50,    77,    78,
    79,    80,    81,    82,    83,    84,    85,    86,     7,     8,
     9,    10,    91,    92,    93,    94,    95,    96,    97,    98,
    99,   100,   101,   102,   103,   104,   105,   106,    48,   108,
   109,   110,    48,   202,    25,    26,    41,    42,    43,    44,
    23,    46,    41,    42,    43,    44,    51,    46,    19,    20,
    21,     7,     8,     9,    10,    12,    13,    14,    15,    16,
    15,    16,    43,    44,    50,    46,    50,   187,   188,   189,
   190,    50,    50,    50,    50,    50,    31,    32,    12,    13,
    14,    15,    16,    50,   163,    41,    42,    43,    44,    50,
    46,    50,    46,    48,    49,     5,   175,   176,   177,   178,
   179,   180,   181,   182,   185,   186,    48,    41,    42,    43,
    44,    48,    46,    46,   193,    70,    71,    72,    73,    74,
    46,   200,   201,     0,    -1,    19,    20,    21,    41,    42,
    43,    44,    -1,    46,    -1,    -1,    91,    92,    93,    94,
    95,    -1,    97,    98,    99,   100,   101,    41,    42,    43,
    44,     0,    46,    25,    26,    -1,    -1,     6,    41,    42,
    43,    44,    11,    46,    -1,    -1,    49,    -1,    17,    41,
    42,    43,    44,    22,    46,    24,    41,    42,    43,    44,
    -1,    46,    41,    42,    43,    44,    51,    46,    41,    42,
    43,    44,    51,    46,    41,    42,    43,    44,    51,    46,
    41,    42,    43,    44,    51,    46,    41,    42,    43,    44,
    51,    46,    41,    42,    43,    44,    51,    46,    41,    42,
    43,    44,    51,    46,    41,    42,    43,    44,    51,    46,
    41,    42,    43,    44,    51,    46,    41,    42,    43,    44,
    51,    46,    41,    42,    43,    44,    51,    46,    -1,    -1,
    49,    41,    42,    43,    44,    -1,    46,    -1,    -1,    49,
    41,    42,    43,    44,    -1,    46,    -1,    -1,    49,    41,
    42,    43,    44,    -1,    46,    -1,    -1,    49,    41,    42,
    43,    44,    -1,    46,    -1,    -1,    49,    41,    42,    43,
    44,    -1,    46,    -1,    -1,    49,    41,    42,    43,    44,
    -1,    46,    -1,    -1,    49,    41,    42,    43,    44,    -1,
    46,    -1,    -1,    49,    41,    42,    43,    44,    -1,    46,
    -1,    -1,    49,    41,    42,    43,    44,    -1,    46,    -1,
    -1,    49,    41,    42,    43,    44,    -1,    46,    -1,    -1,
    49,    41,    42,    43,    44,    -1,    46,    -1,    -1,    49,
    41,    42,    43,    44,    -1,    46,    -1,    -1,    49,    41,
    42,    43,    44,    -1,    46,    -1,    -1,    49,    41,    42,
    43,    44,    -1,    46,    -1,    -1,    49,    41,    42,    43,
    44,    -1,    46,    -1,    -1,    49,    41,    42,    43,    44,
    -1,    46,    -1,    -1,    49
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

case 6:
#line 105 "parser.y"
{ printf( "Adding Light\n" ); /*g_pScene->AddLight(pLight); pLight = 0;*/ ;
    break;}
case 8:
#line 110 "parser.y"
{
                //pObj = new TriangleMesh;
                //pObj->SetMaterial (pMat);
            ;
    break;}
case 9:
#line 115 "parser.y"
{
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 10:
#line 122 "parser.y"
{
                //pObj = new Sphere;
                //pObj->SetMaterial (pMat);
            ;
    break;}
case 11:
#line 127 "parser.y"
{
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 13:
#line 136 "parser.y"
{ printf( "Sphere Pos: %d, %d, %d\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); ;
    break;}
case 14:
#line 138 "parser.y"
{ printf( "Sphere Radius: %d\n", yyvsp[-1].real ); ;
    break;}
case 15:
#line 141 "parser.y"
{ printf( "Creating Light\n" ); /*g_light = new rawray::Light();*/ ;
    break;}
case 18:
#line 146 "parser.y"
{ printf( "Light Pos: %d %d %d\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); ;
    break;}
case 19:
#line 148 "parser.y"
{ printf( "Light Wattage: %d\n", yyvsp[-1].real ); ;
    break;}
case 20:
#line 150 "parser.y"
{ printf( "Light Color: %d %d %d\n", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); ;
    break;}
case 22:
#line 156 "parser.y"
{
                // Remove quotes
                yyvsp[0].str[strlen(yyvsp[0].str)-1]=0;
                char* s = &yyvsp[0].str[1];
                
                printf( "Loading Mesh: %s", s );
                //if (!((TriangleMesh*)pObj)->Load(s, GetCTM()))
                    //pObj = 0;
                delete [] yyvsp[0].str;
            ;
    break;}
case 24:
#line 170 "parser.y"
{ printf( "Found height=%d", yyvsp[-1].integer); ;
    break;}
case 25:
#line 172 "parser.y"
{ printf( "Found width=%d", yyvsp[-1].integer); ;
    break;}
case 26:
#line 174 "parser.y"
{ printf( "Found GL BG=%d, %d, %d", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real); ;
    break;}
case 27:
#line 176 "parser.y"
{ printf( "Found IMG BG=%d, %d, %d", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real); ;
    break;}
case 29:
#line 181 "parser.y"
{ printf( "Camera Eye: %d, %d, %d", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); ;
    break;}
case 30:
#line 183 "parser.y"
{ printf( "Camera View: %d, %d, %d", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); ;
    break;}
case 31:
#line 185 "parser.y"
{ printf( "Camera LookAt: %d, %d, %d", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); ;
    break;}
case 32:
#line 187 "parser.y"
{ printf( "Camera Up: %d, %d, %d", yyvsp[-5].real, yyvsp[-3].real, yyvsp[-1].real ); ;
    break;}
case 33:
#line 189 "parser.y"
{ printf( "Camera FOV: %d", yyvsp[-1].real ); ;
    break;}
case 34:
#line 192 "parser.y"
{ yyval.real = yyvsp[0].real; ;
    break;}
case 35:
#line 193 "parser.y"
{ yyval.real = yyvsp[0].integer; ;
    break;}
case 36:
#line 194 "parser.y"
{ yyval.real = yyvsp[0].real; ;
    break;}
case 37:
#line 196 "parser.y"
{ yyval.real = yyvsp[-2].real + yyvsp[0].real; ;
    break;}
case 38:
#line 197 "parser.y"
{ yyval.real = yyvsp[-2].integer + yyvsp[0].real; ;
    break;}
case 39:
#line 198 "parser.y"
{ yyval.real = yyvsp[-2].real + yyvsp[0].integer; ;
    break;}
case 40:
#line 200 "parser.y"
{ yyval.real = yyvsp[-2].real - yyvsp[0].real; ;
    break;}
case 41:
#line 201 "parser.y"
{ yyval.real = yyvsp[-2].integer - yyvsp[0].real; ;
    break;}
case 42:
#line 202 "parser.y"
{ yyval.real = yyvsp[-2].real - yyvsp[0].integer; ;
    break;}
case 43:
#line 204 "parser.y"
{ yyval.real = yyvsp[-2].real * yyvsp[0].real; ;
    break;}
case 44:
#line 205 "parser.y"
{ yyval.real = yyvsp[-2].integer * yyvsp[0].real; ;
    break;}
case 45:
#line 206 "parser.y"
{ yyval.real = yyvsp[-2].real * yyvsp[0].integer; ;
    break;}
case 46:
#line 208 "parser.y"
{ yyval.real = yyvsp[-2].real / yyvsp[0].real; ;
    break;}
case 47:
#line 209 "parser.y"
{ yyval.real = yyvsp[-2].integer / yyvsp[0].real; ;
    break;}
case 48:
#line 210 "parser.y"
{ yyval.real = yyvsp[-2].real / yyvsp[0].integer; ;
    break;}
case 49:
#line 212 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].real), float (yyvsp[0].real)); ;
    break;}
case 50:
#line 213 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].integer), float (yyvsp[0].real)); ;
    break;}
case 51:
#line 214 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].real), float (yyvsp[0].integer)); ;
    break;}
case 52:
#line 216 "parser.y"
{ yyval.real = -yyvsp[0].real; ;
    break;}
case 53:
#line 217 "parser.y"
{ yyval.real = yyvsp[-1].real; ;
    break;}
case 55:
#line 221 "parser.y"
{yyval.real = sin(yyvsp[-1].real); ;
    break;}
case 56:
#line 222 "parser.y"
{yyval.real = cos(yyvsp[-1].real); ;
    break;}
case 57:
#line 223 "parser.y"
{yyval.real = tan(yyvsp[-1].real); ;
    break;}
case 58:
#line 224 "parser.y"
{yyval.real = asin(yyvsp[-1].real); ;
    break;}
case 59:
#line 225 "parser.y"
{yyval.real = acos(yyvsp[-1].real); ;
    break;}
case 60:
#line 226 "parser.y"
{yyval.real = atan(yyvsp[-1].real); ;
    break;}
case 61:
#line 227 "parser.y"
{yyval.real = log(yyvsp[-1].real); ;
    break;}
case 62:
#line 228 "parser.y"
{yyval.real = log10(yyvsp[-1].real); ;
    break;}
case 63:
#line 229 "parser.y"
{yyval.real = exp(yyvsp[-1].real); ;
    break;}
case 64:
#line 230 "parser.y"
{yyval.real = sqrt(yyvsp[-1].real); ;
    break;}
case 65:
#line 234 "parser.y"
{ yyval.real = 2.718281828459; ;
    break;}
case 66:
#line 235 "parser.y"
{ yyval.real = PI; ;
    break;}
case 67:
#line 238 "parser.y"
{ yyval.integer = yyvsp[0].integer; ;
    break;}
case 68:
#line 239 "parser.y"
{ yyval.integer = yyvsp[-2].integer + yyvsp[0].integer; ;
    break;}
case 69:
#line 240 "parser.y"
{ yyval.integer = yyvsp[-2].integer - yyvsp[0].integer; ;
    break;}
case 70:
#line 241 "parser.y"
{ yyval.integer = yyvsp[-2].integer * yyvsp[0].integer; ;
    break;}
case 71:
#line 242 "parser.y"
{ yyval.integer = yyvsp[-2].integer / yyvsp[0].integer; ;
    break;}
case 72:
#line 243 "parser.y"
{ yyval.integer = -yyvsp[0].integer; ;
    break;}
case 73:
#line 244 "parser.y"
{ yyval.integer = (int)pow (yyvsp[-2].integer, yyvsp[0].integer); ;
    break;}
case 74:
#line 245 "parser.y"
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
}#line 250 "parser.y"


//Additional C code
