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


extern YYSTYPE yylval;
