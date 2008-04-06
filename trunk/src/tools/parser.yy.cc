
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
#define	GL_BGCOLOR	281
#define	IMG_BGCOLOR	282
#define	CAMERA	283
#define	POS	284
#define	DIR	285
#define	LOOKAT	286
#define	UP	287
#define	FOV	288
#define	TRIANGLE	289
#define	V1	290
#define	V2	291
#define	V3	292
#define	N1	293
#define	N2	294
#define	N3	295
#define	MESH	296
#define	LOAD	297
#define	INSTANCE	298
#define	GEOMETRY	299
#define	PUSHMATRIX	300
#define	POPMATRIX	301
#define	ROTATE	302
#define	TRANSLATE	303
#define	SCALE	304
#define	LIGHT	305
#define	POINTLIGHT	306
#define	WATTAGE	307
#define	COLOR	308
#define	SPHERE	309
#define	CENTER	310
#define	RADIUS	311
#define	NEG	312

#line 1 "parser.y"

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


#line 44 "parser.y"
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



#define	YYFINAL		307
#define	YYFLAG		-32768
#define	YYNTBASE	69

#define YYTRANSLATE(x) ((unsigned)(x) <= 312 ? yytranslate[x] : 94)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    67,
    68,    60,    59,    66,    58,     2,    61,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    57,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    63,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    64,     2,    65,     2,     2,     2,     2,     2,
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
    56,    62
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     9,    14,    16,    20,    22,    23,    29,
    30,    37,    38,    44,    45,    52,    53,    59,    60,    67,
    68,    74,    75,    82,    83,    91,    99,   107,   115,   123,
   131,   132,   140,   144,   145,   149,   151,   153,   162,   169,
   176,   177,   182,   183,   191,   195,   203,   204,   207,   208,
   212,   216,   224,   232,   233,   241,   249,   257,   265,   269,
   271,   273,   275,   279,   283,   287,   291,   295,   299,   303,
   307,   311,   315,   319,   323,   327,   331,   335,   338,   342,
   344,   349,   354,   359,   364,   369,   374,   379,   384,   389,
   394,   396,   398,   400,   404,   408,   412,   416,   419,   423
};

static const short yyrhs[] = {    -1,
    69,    70,     0,    23,    64,    88,    65,     0,    28,    64,
    89,    65,     0,    71,     0,    50,    84,    65,     0,    83,
     0,     0,    34,    64,    72,    80,    65,     0,     0,    34,
     5,    64,    73,    80,    65,     0,     0,    41,    64,    74,
    87,    65,     0,     0,    41,     5,    64,    75,    87,    65,
     0,     0,    54,    64,    76,    81,    65,     0,     0,    54,
     5,    64,    77,    81,    65,     0,     0,    43,    64,    78,
    82,    65,     0,     0,    43,     5,    64,    79,    82,    65,
     0,     0,    35,    90,    66,    90,    66,    90,    80,     0,
    36,    90,    66,    90,    66,    90,    80,     0,    37,    90,
    66,    90,    66,    90,    80,     0,    38,    90,    66,    90,
    66,    90,    80,     0,    39,    90,    66,    90,    66,    90,
    80,     0,    40,    90,    66,    90,    66,    90,    80,     0,
     0,    55,    90,    66,    90,    66,    90,    81,     0,    56,
    90,    81,     0,     0,    44,     5,    81,     0,    45,     0,
    46,     0,    47,    90,    66,    90,    66,    90,    66,    90,
     0,    48,    90,    66,    90,    66,    90,     0,    49,    90,
    66,    90,    66,    90,     0,     0,    51,    64,    85,    86,
     0,     0,    29,    90,    66,    90,    66,    90,    86,     0,
    52,    90,    86,     0,    53,    90,    66,    90,    66,    90,
    86,     0,     0,    42,     5,     0,     0,    25,    93,    88,
     0,    24,    93,    88,     0,    26,    90,    66,    90,    66,
    90,    88,     0,    27,    90,    66,    90,    66,    90,    88,
     0,     0,    29,    90,    66,    90,    66,    90,    89,     0,
    30,    90,    66,    90,    66,    90,    89,     0,    31,    90,
    66,    90,    66,    90,    89,     0,    32,    90,    66,    90,
    66,    90,    89,     0,    33,    90,    89,     0,     3,     0,
    93,     0,    91,     0,    90,    59,    90,     0,    93,    59,
    90,     0,    90,    59,    93,     0,    90,    58,    90,     0,
    93,    58,    90,     0,    90,    58,    93,     0,    90,    60,
    90,     0,    93,    60,    90,     0,    90,    60,    93,     0,
    90,    61,    90,     0,    93,    61,    90,     0,    90,    61,
    93,     0,    90,    63,    90,     0,    93,    63,    90,     0,
    90,    63,    93,     0,    58,    90,     0,    67,    90,    68,
     0,    92,     0,    11,    67,    90,    68,     0,    10,    67,
    90,    68,     0,    12,    67,    90,    68,     0,    14,    67,
    90,    68,     0,    13,    67,    90,    68,     0,    15,    67,
    90,    68,     0,    17,    67,    90,    68,     0,    18,    67,
    90,    68,     0,    19,    67,    90,    68,     0,    20,    67,
    90,    68,     0,    21,     0,    22,     0,     4,     0,    93,
    59,    93,     0,    93,    58,    93,     0,    93,    60,    93,
     0,    93,    61,    93,     0,    58,    93,     0,    93,    63,
    93,     0,    67,    93,    68,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   129,   130,   133,   134,   135,   136,   137,   140,   148,   156,
   164,   173,   179,   187,   194,   203,   209,   217,   224,   233,
   239,   247,   254,   263,   264,   266,   268,   270,   272,   274,
   278,   279,   281,   285,   286,   296,   297,   299,   301,   303,
   307,   308,   310,   311,   313,   315,   320,   321,   330,   331,
   333,   335,   337,   341,   342,   344,   346,   348,   350,   354,
   355,   356,   358,   359,   360,   362,   363,   364,   366,   367,
   368,   370,   371,   372,   374,   375,   376,   378,   379,   380,
   383,   384,   385,   386,   387,   388,   389,   390,   391,   392,
   395,   397,   400,   401,   402,   403,   404,   405,   406,   407
};

static const char * const yytname[] = {   "$","error","$undefined.","REAL","PARSE_INT",
"STRING","PARSE_TRUE","PARSE_FALSE","ENABLE","DISABLE","MATH_COS","MATH_SIN",
"MATH_TAN","MATH_ACOS","MATH_ASIN","MATH_ATAN","MATH_ATAN2","MATH_LN","MATH_LOG",
"MATH_EXP","MATH_SQRT","MATH_E","MATH_PI","GLOBAL","WIDTH","HEIGHT","GL_BGCOLOR",
"IMG_BGCOLOR","CAMERA","POS","DIR","LOOKAT","UP","FOV","TRIANGLE","V1","V2",
"V3","N1","N2","N3","MESH","LOAD","INSTANCE","GEOMETRY","PUSHMATRIX","POPMATRIX",
"ROTATE","TRANSLATE","SCALE","LIGHT","POINTLIGHT","WATTAGE","COLOR","SPHERE",
"CENTER","RADIUS","'='","'-'","'+'","'*'","'/'","NEG","'^'","'{'","'}'","','",
"'('","')'","input","block","objectTypes","@1","@2","@3","@4","@5","@6","@7",
"@8","triangleOptions","sphereOptions","instanceOptions","transform","lightTypes",
"@9","lightOptions","meshOptions","globalOptions","cameraOptions","rExp","fExp",
"constantExp","iExp",""
};
#endif

static const short yyr1[] = {     0,
    69,    69,    70,    70,    70,    70,    70,    72,    71,    73,
    71,    74,    71,    75,    71,    76,    71,    77,    71,    78,
    71,    79,    71,    80,    80,    80,    80,    80,    80,    80,
    81,    81,    81,    82,    82,    83,    83,    83,    83,    83,
    85,    84,    86,    86,    86,    86,    87,    87,    88,    88,
    88,    88,    88,    89,    89,    89,    89,    89,    89,    90,
    90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
    90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
    91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
    92,    92,    93,    93,    93,    93,    93,    93,    93,    93
};

static const short yyr2[] = {     0,
     0,     2,     4,     4,     1,     3,     1,     0,     5,     0,
     6,     0,     5,     0,     6,     0,     5,     0,     6,     0,
     5,     0,     6,     0,     7,     7,     7,     7,     7,     7,
     0,     7,     3,     0,     3,     1,     1,     8,     6,     6,
     0,     4,     0,     7,     3,     7,     0,     2,     0,     3,
     3,     7,     7,     0,     7,     7,     7,     7,     3,     1,
     1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     2,     3,     1,
     4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     1,     1,     1,     3,     3,     3,     3,     2,     3,     3
};

static const short yydefact[] = {     1,
     0,     0,     0,     0,     0,     0,    36,    37,     0,     0,
     0,     0,     0,     2,     5,     7,    49,    54,     0,     8,
     0,    12,     0,    20,    60,    93,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    91,    92,     0,     0,
     0,    62,    80,    61,     0,     0,     0,     0,     0,    16,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    10,    24,    14,    47,    22,    34,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    78,    61,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    41,     6,    18,    31,     0,     0,
    49,    49,     0,     0,     3,     0,     0,     0,     0,    54,
     4,    24,     0,     0,     0,     0,     0,     0,     0,    47,
     0,     0,    34,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    79,   100,    66,    61,    63,
    61,    69,    61,    72,    61,    75,    61,     0,    67,    61,
    64,    61,    70,    61,    73,    61,    76,    61,     0,     0,
    43,    31,     0,     0,     0,    98,     0,     0,     0,     0,
     0,     0,    51,    50,     0,     0,     0,     0,     0,     0,
    59,     0,     0,     0,     0,     0,     0,     0,     9,     0,
    48,    13,     0,    31,    21,    82,    81,    83,    85,    84,
    86,    87,    88,    89,    90,     0,     0,     0,     0,     0,
     0,    42,     0,     0,    31,    17,    95,    94,    96,    97,
    99,     0,     0,     0,     0,     0,     0,    11,     0,     0,
     0,     0,     0,     0,    15,    23,    35,     0,    39,    40,
     0,    43,     0,    19,     0,    33,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    45,     0,     0,    49,    49,    54,    54,    54,    54,     0,
     0,     0,     0,     0,     0,    38,     0,     0,     0,    52,
    53,    55,    56,    57,    58,    24,    24,    24,    24,    24,
    24,     0,     0,    31,    25,    26,    27,    28,    29,    30,
    43,    43,    32,    44,    46,     0,     0
};

static const short yydefgoto[] = {     1,
    14,    15,    63,   112,    65,   120,    98,   162,    67,   123,
   119,   165,   125,    16,    48,   161,   212,   122,    55,    61,
    41,    42,    43,    44
};

static const short yypact[] = {-32768,
   225,   -57,   -53,     7,    26,    27,-32768,-32768,   274,   274,
   274,   -17,    30,-32768,-32768,-32768,    -2,   -16,   -38,-32768,
   -28,-32768,   -23,-32768,-32768,-32768,     1,    22,    34,    43,
    44,    45,    54,    58,    66,    84,-32768,-32768,   274,   274,
   -21,-32768,-32768,   149,   349,   358,   -13,    90,    92,-32768,
    29,    29,   274,   274,    93,   274,   274,   274,   274,   274,
    98,-32768,   104,-32768,   115,-32768,   120,   274,   274,   274,
   274,   274,   274,   274,   274,   274,   274,   110,   111,    59,
   124,   274,   274,   274,   274,   274,   274,   274,   274,   274,
   274,   274,   274,   274,-32768,-32768,-32768,   -50,    29,    29,
    -6,    -6,   367,   376,-32768,   385,   394,   403,   412,   173,
-32768,   104,   274,   274,   274,   274,   274,   274,   121,   115,
   170,   125,   120,   184,   126,   259,   265,   284,   290,   296,
   302,   308,   314,   320,   326,-32768,-32768,    32,    39,    32,
    39,   110,   111,   110,   111,   110,   111,   421,    32,    39,
    32,    39,   110,   111,   110,   111,   110,   111,   430,   439,
   -25,   -50,   274,   274,   128,   131,   332,    29,    29,    29,
    29,    29,-32768,-32768,   274,   274,   274,   274,   274,   274,
-32768,   130,   448,   457,   466,   475,   484,   493,-32768,   146,
-32768,-32768,   148,   -50,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   274,   274,   274,   274,   274,
   274,-32768,   161,   502,   343,-32768,    63,    63,   131,   131,
   131,   511,   520,   529,   538,   547,   556,-32768,   274,   274,
   274,   274,   274,   274,-32768,-32768,-32768,   565,   673,   673,
   574,   247,   583,-32768,   274,-32768,   274,   274,   274,   274,
   274,   274,   592,   601,   610,   619,   628,   637,   274,   274,
-32768,   274,   646,    89,    89,   173,   173,   173,   173,   274,
   274,   274,   274,   274,   274,   673,   655,   664,   274,-32768,
-32768,-32768,-32768,-32768,-32768,   276,   276,   276,   276,   276,
   276,   274,   274,   343,-32768,-32768,-32768,-32768,-32768,-32768,
   247,   247,-32768,-32768,-32768,   227,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -110,  -106,   105,-32768,-32768,-32768,  -232,   109,   -93,  -107,
   -10,-32768,-32768,    46
};


#define	YYLAST		736


static const short yytable[] = {    45,
    46,   182,   181,   209,   163,   164,    17,   173,   174,   261,
    18,    19,    56,    57,    58,    59,    60,    51,    52,    53,
    54,    51,    52,    53,    54,    62,   210,   211,    78,    80,
    21,    23,    26,    47,    49,    64,    82,    83,    84,    85,
    66,    86,   103,   104,    87,   106,   107,   108,   109,   110,
    95,   168,   169,   170,   171,   213,   172,   126,   127,   128,
   129,   130,   131,   132,   133,   134,   135,    68,   304,   305,
    20,   138,   140,   142,   144,   146,   148,   149,   151,   153,
   155,   157,   159,   160,    79,    81,    99,   237,    69,    22,
    24,    84,    85,    50,    86,   100,   101,   102,    90,    91,
    70,    92,   183,   184,   185,   186,   187,   188,   246,    71,
    72,    73,    51,    52,    53,    54,    82,    83,    84,    85,
    74,    86,   170,   171,    75,   172,   136,   139,   141,   143,
   145,   147,    76,   150,   152,   154,   156,   158,   113,   114,
   115,   116,   117,   118,   166,   167,    82,    83,    84,    85,
    77,    86,   214,   215,    96,    97,   121,   105,   282,   283,
   284,   285,   111,   124,   222,   223,   224,   225,   226,   227,
   280,   281,    86,    92,   191,   295,   296,   297,   298,   299,
   300,    88,    89,    90,    91,   189,    92,   303,   194,   192,
   195,   137,   216,   172,   228,   238,   239,   240,   241,   242,
   243,    56,    57,    58,    59,    60,    88,    89,    90,    91,
   235,    92,   236,   217,   218,   219,   220,   221,   253,   254,
   255,   256,   257,   258,   306,   244,   307,   193,   190,     0,
    82,    83,    84,    85,   263,    86,   264,   265,   266,   267,
   268,   269,     0,     0,     0,     0,     0,     2,   276,   277,
     0,   278,     3,     0,     0,     0,     0,     0,     4,   286,
   287,   288,   289,   290,   291,     5,     0,     6,   294,     7,
     8,     9,    10,    11,    12,   209,    25,    26,    13,     0,
     0,   301,   302,    27,    28,    29,    30,    31,    32,     0,
    33,    34,    35,    36,    37,    38,     0,     0,   210,   211,
     0,     0,     0,     0,    82,    83,    84,    85,     0,    86,
   113,   114,   115,   116,   117,   118,    82,    83,    84,    85,
     0,    86,    82,    83,    84,    85,   196,    86,     0,     0,
     0,    39,   197,    82,    83,    84,    85,     0,    86,     0,
    40,    82,    83,    84,    85,     0,    86,    82,    83,    84,
    85,   198,    86,    82,    83,    84,    85,   199,    86,    82,
    83,    84,    85,   200,    86,    82,    83,    84,    85,   201,
    86,    82,    83,    84,    85,   202,    86,    82,    83,    84,
    85,   203,    86,    82,    83,    84,    85,   204,    86,   168,
   169,   170,   171,   205,   172,     0,     0,   163,   164,   137,
    82,    83,    84,    85,     0,    86,    82,    83,    84,    85,
     0,    86,     0,     0,    93,    82,    83,    84,    85,     0,
    86,     0,     0,    94,    82,    83,    84,    85,     0,    86,
     0,     0,   175,    82,    83,    84,    85,     0,    86,     0,
     0,   176,    82,    83,    84,    85,     0,    86,     0,     0,
   177,    82,    83,    84,    85,     0,    86,     0,     0,   178,
    82,    83,    84,    85,     0,    86,     0,     0,   179,    82,
    83,    84,    85,     0,    86,     0,     0,   180,    82,    83,
    84,    85,     0,    86,     0,     0,   206,    82,    83,    84,
    85,     0,    86,     0,     0,   207,    82,    83,    84,    85,
     0,    86,     0,     0,   208,    82,    83,    84,    85,     0,
    86,     0,     0,   229,    82,    83,    84,    85,     0,    86,
     0,     0,   230,    82,    83,    84,    85,     0,    86,     0,
     0,   231,    82,    83,    84,    85,     0,    86,     0,     0,
   232,    82,    83,    84,    85,     0,    86,     0,     0,   233,
    82,    83,    84,    85,     0,    86,     0,     0,   234,    82,
    83,    84,    85,     0,    86,     0,     0,   245,    82,    83,
    84,    85,     0,    86,     0,     0,   247,    82,    83,    84,
    85,     0,    86,     0,     0,   248,    82,    83,    84,    85,
     0,    86,     0,     0,   249,    82,    83,    84,    85,     0,
    86,     0,     0,   250,    82,    83,    84,    85,     0,    86,
     0,     0,   251,    82,    83,    84,    85,     0,    86,     0,
     0,   252,    82,    83,    84,    85,     0,    86,     0,     0,
   259,    82,    83,    84,    85,     0,    86,     0,     0,   260,
    82,    83,    84,    85,     0,    86,     0,     0,   262,    82,
    83,    84,    85,     0,    86,     0,     0,   270,    82,    83,
    84,    85,     0,    86,     0,     0,   271,    82,    83,    84,
    85,     0,    86,     0,     0,   272,    82,    83,    84,    85,
     0,    86,     0,     0,   273,    82,    83,    84,    85,     0,
    86,     0,     0,   274,    82,    83,    84,    85,     0,    86,
     0,     0,   275,    82,    83,    84,    85,     0,    86,     0,
     0,   279,    82,    83,    84,    85,     0,    86,     0,     0,
   292,    82,    83,    84,    85,     0,    86,     0,     0,   293,
    82,    83,    84,    85,     0,    86
};

static const short yycheck[] = {    10,
    11,   112,   110,    29,    55,    56,    64,   101,   102,   242,
    64,     5,    29,    30,    31,    32,    33,    24,    25,    26,
    27,    24,    25,    26,    27,    64,    52,    53,    39,    40,
     5,     5,     4,    51,     5,    64,    58,    59,    60,    61,
    64,    63,    53,    54,    66,    56,    57,    58,    59,    60,
    64,    58,    59,    60,    61,   162,    63,    68,    69,    70,
    71,    72,    73,    74,    75,    76,    77,    67,   301,   302,
    64,    82,    83,    84,    85,    86,    87,    88,    89,    90,
    91,    92,    93,    94,    39,    40,    58,   194,    67,    64,
    64,    60,    61,    64,    63,    67,    51,    52,    60,    61,
    67,    63,   113,   114,   115,   116,   117,   118,   215,    67,
    67,    67,    24,    25,    26,    27,    58,    59,    60,    61,
    67,    63,    60,    61,    67,    63,    68,    82,    83,    84,
    85,    86,    67,    88,    89,    90,    91,    92,    35,    36,
    37,    38,    39,    40,    99,   100,    58,    59,    60,    61,
    67,    63,   163,   164,    65,    64,    42,    65,   266,   267,
   268,   269,    65,    44,   175,   176,   177,   178,   179,   180,
   264,   265,    63,    63,     5,   286,   287,   288,   289,   290,
   291,    58,    59,    60,    61,    65,    63,   294,     5,    65,
    65,    68,    65,    63,    65,   206,   207,   208,   209,   210,
   211,    29,    30,    31,    32,    33,    58,    59,    60,    61,
    65,    63,    65,   168,   169,   170,   171,   172,   229,   230,
   231,   232,   233,   234,     0,    65,     0,   123,   120,    -1,
    58,    59,    60,    61,   245,    63,   247,   248,   249,   250,
   251,   252,    -1,    -1,    -1,    -1,    -1,    23,   259,   260,
    -1,   262,    28,    -1,    -1,    -1,    -1,    -1,    34,   270,
   271,   272,   273,   274,   275,    41,    -1,    43,   279,    45,
    46,    47,    48,    49,    50,    29,     3,     4,    54,    -1,
    -1,   292,   293,    10,    11,    12,    13,    14,    15,    -1,
    17,    18,    19,    20,    21,    22,    -1,    -1,    52,    53,
    -1,    -1,    -1,    -1,    58,    59,    60,    61,    -1,    63,
    35,    36,    37,    38,    39,    40,    58,    59,    60,    61,
    -1,    63,    58,    59,    60,    61,    68,    63,    -1,    -1,
    -1,    58,    68,    58,    59,    60,    61,    -1,    63,    -1,
    67,    58,    59,    60,    61,    -1,    63,    58,    59,    60,
    61,    68,    63,    58,    59,    60,    61,    68,    63,    58,
    59,    60,    61,    68,    63,    58,    59,    60,    61,    68,
    63,    58,    59,    60,    61,    68,    63,    58,    59,    60,
    61,    68,    63,    58,    59,    60,    61,    68,    63,    58,
    59,    60,    61,    68,    63,    -1,    -1,    55,    56,    68,
    58,    59,    60,    61,    -1,    63,    58,    59,    60,    61,
    -1,    63,    -1,    -1,    66,    58,    59,    60,    61,    -1,
    63,    -1,    -1,    66,    58,    59,    60,    61,    -1,    63,
    -1,    -1,    66,    58,    59,    60,    61,    -1,    63,    -1,
    -1,    66,    58,    59,    60,    61,    -1,    63,    -1,    -1,
    66,    58,    59,    60,    61,    -1,    63,    -1,    -1,    66,
    58,    59,    60,    61,    -1,    63,    -1,    -1,    66,    58,
    59,    60,    61,    -1,    63,    -1,    -1,    66,    58,    59,
    60,    61,    -1,    63,    -1,    -1,    66,    58,    59,    60,
    61,    -1,    63,    -1,    -1,    66,    58,    59,    60,    61,
    -1,    63,    -1,    -1,    66,    58,    59,    60,    61,    -1,
    63,    -1,    -1,    66,    58,    59,    60,    61,    -1,    63,
    -1,    -1,    66,    58,    59,    60,    61,    -1,    63,    -1,
    -1,    66,    58,    59,    60,    61,    -1,    63,    -1,    -1,
    66,    58,    59,    60,    61,    -1,    63,    -1,    -1,    66,
    58,    59,    60,    61,    -1,    63,    -1,    -1,    66,    58,
    59,    60,    61,    -1,    63,    -1,    -1,    66,    58,    59,
    60,    61,    -1,    63,    -1,    -1,    66,    58,    59,    60,
    61,    -1,    63,    -1,    -1,    66,    58,    59,    60,    61,
    -1,    63,    -1,    -1,    66,    58,    59,    60,    61,    -1,
    63,    -1,    -1,    66,    58,    59,    60,    61,    -1,    63,
    -1,    -1,    66,    58,    59,    60,    61,    -1,    63,    -1,
    -1,    66,    58,    59,    60,    61,    -1,    63,    -1,    -1,
    66,    58,    59,    60,    61,    -1,    63,    -1,    -1,    66,
    58,    59,    60,    61,    -1,    63,    -1,    -1,    66,    58,
    59,    60,    61,    -1,    63,    -1,    -1,    66,    58,    59,
    60,    61,    -1,    63,    -1,    -1,    66,    58,    59,    60,
    61,    -1,    63,    -1,    -1,    66,    58,    59,    60,    61,
    -1,    63,    -1,    -1,    66,    58,    59,    60,    61,    -1,
    63,    -1,    -1,    66,    58,    59,    60,    61,    -1,    63,
    -1,    -1,    66,    58,    59,    60,    61,    -1,    63,    -1,
    -1,    66,    58,    59,    60,    61,    -1,    63,    -1,    -1,
    66,    58,    59,    60,    61,    -1,    63,    -1,    -1,    66,
    58,    59,    60,    61,    -1,    63
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
#line 136 "parser.y"
{ printf( "Adding Light\n" ); ;
    break;}
case 8:
#line 142 "parser.y"
{
                printf( "Creating Triangle\n" );
                //pObj = new Triangle;
                //pObj->SetMaterial (pMat);
                //((TriangleMesh*)pObj)->CreateSingleTriangle();
            ;
    break;}
case 9:
#line 149 "parser.y"
{
                printf( "Adding Triangle to Scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 10:
#line 157 "parser.y"
{
                printf( "Creating named triangle '%s'\n", yyvsp[-1].str );
                //pObj = new TriangleMesh;
                //pObj->SetMaterial (pMat);
                //g_objectMap[$2] = pObj;
                //((TriangleMesh*)pObj)->CreateSingleTriangle();
            ;
    break;}
case 11:
#line 165 "parser.y"
{
                printf( "Adding named Triangle to Scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 12:
#line 174 "parser.y"
{
                printf( "Creating new mesh\n" );
                //pObj = new TriangleMesh;
                //pObj->SetMaterial (pMat);
            ;
    break;}
case 13:
#line 180 "parser.y"
{
                printf( "Adding mesh to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 14:
#line 188 "parser.y"
{
                printf( "Creating new named mesh '%s'\n", yyvsp[-1].str );
                //pObj = new TriangleMesh;
                //pObj->SetMaterial (pMat);
                //g_objectMap[$2] = pObj;
            ;
    break;}
case 15:
#line 195 "parser.y"
{
                printf( "Adding named mesh to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 16:
#line 204 "parser.y"
{
                printf( "Creating new sphere\n" );
                //pObj = new Sphere;
                //pObj->SetMaterial (pMat);
            ;
    break;}
case 17:
#line 210 "parser.y"
{
                printf( "Adding sphere to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 18:
#line 218 "parser.y"
{
                printf( "Creating new sphere named '%s'\n", yyvsp[-1].str );
                //pObj = new Sphere;
                //pObj->SetMaterial (pMat);
                //g_objectMap[$2] = pObj;
            ;
    break;}
case 19:
#line 225 "parser.y"
{
                printf( "Adding sphere to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 20:
#line 234 "parser.y"
{
                printf( "Creating new instance\n" );
                //pObj = new Instance;
                //pObj->SetMaterial (pMat);
            ;
    break;}
case 21:
#line 240 "parser.y"
{
                printf( "Adding instance to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 22:
#line 248 "parser.y"
{
                printf( "Creating new named instance '%s'\n", yyvsp[-1].str );
                //pObj = new Instance;
                //pObj->SetMaterial (pMat);
                //g_objectMap[$2] = pObj;
            ;
    break;}
case 23:
#line 255 "parser.y"
{
                printf( "Adding named instance to scene\n" );
                //if (pObj)
                    //g_pScene->AddObject(pObj);
                //pObj = 0;
            ;
    break;}
case 25:
#line 265 "parser.y"
{ /*((TriangleMesh*)pObj)->SetV1(Vertex3($2, $4, $6));*/ ;
    break;}
case 26:
#line 267 "parser.y"
{  ;
    break;}
case 27:
#line 269 "parser.y"
{  ;
    break;}
case 28:
#line 271 "parser.y"
{  ;
    break;}
case 29:
#line 273 "parser.y"
{  ;
    break;}
case 30:
#line 275 "parser.y"
{  ;
    break;}
case 32:
#line 280 "parser.y"
{  ;
    break;}
case 33:
#line 282 "parser.y"
{  ;
    break;}
case 35:
#line 287 "parser.y"
{
                //std::map<std::string, Object*>::const_iterator it = g_objectMap.find ($2);
                //if (it != g_objectMap.end ())
                //{
                    //((Instance*)pObj)->SetGeometry(it->second, GetCTM());
                //}
            ;
    break;}
case 36:
#line 296 "parser.y"
{ /*PushMatrix();*/ ;
    break;}
case 37:
#line 298 "parser.y"
{ /*PopMatrix();*/ ;
    break;}
case 38:
#line 300 "parser.y"
{ /*Rotate($2, $4, $6, $8);*/ ;
    break;}
case 39:
#line 302 "parser.y"
{ /*Translate($2, $4, $6);*/ ;
    break;}
case 40:
#line 304 "parser.y"
{ /*Scale($2, $4, $6);*/ ;
    break;}
case 41:
#line 307 "parser.y"
{ /*pLight = new PointLight;*/ ;
    break;}
case 44:
#line 312 "parser.y"
{ /*pLight->SetPosition(Vertex3($2, $4, $6));*/ ;
    break;}
case 45:
#line 314 "parser.y"
{ /*pLight->SetWattage($2);*/ ;
    break;}
case 46:
#line 316 "parser.y"
{ /*pLight->SetColor(Vector3($2, $4, $6));*/ ;
    break;}
case 48:
#line 322 "parser.y"
{
                yyvsp[0].str[strlen(yyvsp[0].str)-1]=0;
                printf( "Load Mesh: '%s'", yyvsp[0].str+1 );
                //if (!((TriangleMesh*)pObj)->Load(s, GetCTM()))
                    //pObj = 0;
            ;
    break;}
case 50:
#line 332 "parser.y"
{ /*g_pImage->Resize(g_pImage->Width(), $2);*/ ;
    break;}
case 51:
#line 334 "parser.y"
{ /*g_pImage->Resize($2, g_pImage->Height());*/ ;
    break;}
case 52:
#line 336 "parser.y"
{ /*g_pCamera->SetBGColor(Vector3($2, $4, $6));*/ ;
    break;}
case 53:
#line 338 "parser.y"
{ /*g_pCamera->SetBGColor(Vector3($2, $4, $6));*/ ;
    break;}
case 55:
#line 343 "parser.y"
{ /*g_pCamera->SetEye(Vector3($2, $4, $6));*/ ;
    break;}
case 56:
#line 345 "parser.y"
{ /*g_pCamera->SetViewDir(Vector3($2, $4, $6));*/ ;
    break;}
case 57:
#line 347 "parser.y"
{ /*g_pCamera->SetLookAt(Vector3($2, $4, $6));*/ ;
    break;}
case 58:
#line 349 "parser.y"
{ /*g_pCamera->SetUp(Vector3($2, $4, $6));*/ ;
    break;}
case 59:
#line 351 "parser.y"
{ /*g_pCamera->SetFOV($2);*/ ;
    break;}
case 60:
#line 354 "parser.y"
{ yyval.real = yyvsp[0].real; ;
    break;}
case 61:
#line 355 "parser.y"
{ yyval.real = yyvsp[0].integer; ;
    break;}
case 62:
#line 356 "parser.y"
{ yyval.real = yyvsp[0].real; ;
    break;}
case 63:
#line 358 "parser.y"
{ yyval.real = yyvsp[-2].real + yyvsp[0].real; ;
    break;}
case 64:
#line 359 "parser.y"
{ yyval.real = yyvsp[-2].integer + yyvsp[0].real; ;
    break;}
case 65:
#line 360 "parser.y"
{ yyval.real = yyvsp[-2].real + yyvsp[0].integer; ;
    break;}
case 66:
#line 362 "parser.y"
{ yyval.real = yyvsp[-2].real - yyvsp[0].real; ;
    break;}
case 67:
#line 363 "parser.y"
{ yyval.real = yyvsp[-2].integer - yyvsp[0].real; ;
    break;}
case 68:
#line 364 "parser.y"
{ yyval.real = yyvsp[-2].real - yyvsp[0].integer; ;
    break;}
case 69:
#line 366 "parser.y"
{ yyval.real = yyvsp[-2].real * yyvsp[0].real; ;
    break;}
case 70:
#line 367 "parser.y"
{ yyval.real = yyvsp[-2].integer * yyvsp[0].real; ;
    break;}
case 71:
#line 368 "parser.y"
{ yyval.real = yyvsp[-2].real * yyvsp[0].integer; ;
    break;}
case 72:
#line 370 "parser.y"
{ yyval.real = yyvsp[-2].real / yyvsp[0].real; ;
    break;}
case 73:
#line 371 "parser.y"
{ yyval.real = yyvsp[-2].integer / yyvsp[0].real; ;
    break;}
case 74:
#line 372 "parser.y"
{ yyval.real = yyvsp[-2].real / yyvsp[0].integer; ;
    break;}
case 75:
#line 374 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].real), float (yyvsp[0].real)); ;
    break;}
case 76:
#line 375 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].integer), float (yyvsp[0].real)); ;
    break;}
case 77:
#line 376 "parser.y"
{ yyval.real = pow (float (yyvsp[-2].real), float (yyvsp[0].integer)); ;
    break;}
case 78:
#line 378 "parser.y"
{ yyval.real = -yyvsp[0].real; ;
    break;}
case 79:
#line 379 "parser.y"
{ yyval.real = yyvsp[-1].real; ;
    break;}
case 81:
#line 383 "parser.y"
{yyval.real = sin(yyvsp[-1].real); ;
    break;}
case 82:
#line 384 "parser.y"
{yyval.real = cos(yyvsp[-1].real); ;
    break;}
case 83:
#line 385 "parser.y"
{yyval.real = tan(yyvsp[-1].real); ;
    break;}
case 84:
#line 386 "parser.y"
{yyval.real = asin(yyvsp[-1].real); ;
    break;}
case 85:
#line 387 "parser.y"
{yyval.real = acos(yyvsp[-1].real); ;
    break;}
case 86:
#line 388 "parser.y"
{yyval.real = atan(yyvsp[-1].real); ;
    break;}
case 87:
#line 389 "parser.y"
{yyval.real = log(yyvsp[-1].real); ;
    break;}
case 88:
#line 390 "parser.y"
{yyval.real = log10(yyvsp[-1].real); ;
    break;}
case 89:
#line 391 "parser.y"
{yyval.real = exp(yyvsp[-1].real); ;
    break;}
case 90:
#line 392 "parser.y"
{yyval.real = sqrt(yyvsp[-1].real); ;
    break;}
case 91:
#line 396 "parser.y"
{ yyval.real = 2.718281828459f; ;
    break;}
case 92:
#line 397 "parser.y"
{ yyval.real = 3.141592653589793f; ;
    break;}
case 93:
#line 400 "parser.y"
{ yyval.integer = yyvsp[0].integer; ;
    break;}
case 94:
#line 401 "parser.y"
{ yyval.integer = yyvsp[-2].integer + yyvsp[0].integer; ;
    break;}
case 95:
#line 402 "parser.y"
{ yyval.integer = yyvsp[-2].integer - yyvsp[0].integer; ;
    break;}
case 96:
#line 403 "parser.y"
{ yyval.integer = yyvsp[-2].integer * yyvsp[0].integer; ;
    break;}
case 97:
#line 404 "parser.y"
{ yyval.integer = yyvsp[-2].integer / yyvsp[0].integer; ;
    break;}
case 98:
#line 405 "parser.y"
{ yyval.integer = -yyvsp[0].integer; ;
    break;}
case 99:
#line 406 "parser.y"
{ yyval.integer = (int)pow((float)yyvsp[-2].integer, (float)yyvsp[0].integer); ;
    break;}
case 100:
#line 407 "parser.y"
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
#line 411 "parser.y"

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
