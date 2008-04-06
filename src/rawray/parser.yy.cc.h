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


extern YYSTYPE yylval;
