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


extern YYSTYPE yylval;
