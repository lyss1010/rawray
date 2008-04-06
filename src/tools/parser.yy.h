typedef union
{
    float real;
    int integer;
    char* str;
} YYSTYPE;
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


extern YYSTYPE yylval;
