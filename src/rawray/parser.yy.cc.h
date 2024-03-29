typedef union
{
    float			real;
    int				integer;
    char*			str;
    float			vec[4];
    bool			boolean;
    int				tritest;
} YYSTYPE;
#define	YY_REAL	258
#define	YY_PARSE_INT	259
#define	YY_STRING	260
#define	YY_PARSE_TRUE	261
#define	YY_PARSE_FALSE	262
#define	YY_TRUE	263
#define	YY_FALSE	264
#define	YY_MATH_COS	265
#define	YY_MATH_SIN	266
#define	YY_MATH_TAN	267
#define	YY_MATH_ACOS	268
#define	YY_MATH_ASIN	269
#define	YY_MATH_ATAN	270
#define	YY_MATH_ATAN2	271
#define	YY_MATH_LN	272
#define	YY_MATH_LOG	273
#define	YY_MATH_EXP	274
#define	YY_MATH_SQRT	275
#define	YY_MATH_E	276
#define	YY_MATH_PI	277
#define	YY_LT	278
#define	YY_GT	279
#define	YY_LBOX	280
#define	YY_RBOX	281
#define	YY_LCURLY	282
#define	YY_RCURLY	283
#define	YY_LPAREN	284
#define	YY_RPAREN	285
#define	YY_COMMA	286
#define	YY_EQUAL	287
#define	YY_PLUS	288
#define	YY_MINUS	289
#define	YY_DIV	290
#define	YY_MUL	291
#define	YY_CARAT	292
#define	YY_BSLASH	293
#define	YY_X	294
#define	YY_S_GLOBAL	295
#define	YY_SIZE	296
#define	YY_POS	297
#define	YY_IMG_BGCOLOR	298
#define	YY_IMG_FGCOLOR	299
#define	YY_GL_BGCOLOR	300
#define	YY_GL_SPHERE_SECTIONS	301
#define	YY_GL_RENDER_LIGHTS	302
#define	YY_GL_RENDER_BBOX	303
#define	YY_HEADLESS	304
#define	YY_NUM_THREADS	305
#define	YY_THREAD_JOB_SIZE	306
#define	YY_RENDER_HANDLER_SLEEP	307
#define	YY_RENDER_THREAD_SLEEP	308
#define	YY_RENDER_SPINLOCK_SLEEP	309
#define	YY_GAUSSIAN_BLUR_MAX	310
#define	YY_GAUSSIAN_BLUR_SIGMA	311
#define	YY_TRIANGLE_TEST	312
#define	YY_BARYCENTRIC	313
#define	YY_PROJECTION	314
#define	YY_PLUCKER	315
#define	YY_MOLLER	316
#define	YY_BOX_COST	317
#define	YY_OBJECT_COST	318
#define	YY_PFM	319
#define	YY_ANTI_ALIAS	320
#define	YY_MAX_DIFFUSE_BOUNCE	321
#define	YY_MAX_IOR_BOUNCE	322
#define	YY_HDR_BLOOM_POWER	323
#define	YY_HDR_BLOOM_RADIUS	324
#define	YY_BCSPLINE_B	325
#define	YY_BCSPLINE_C	326
#define	YY_S_CAMERA	327
#define	YY_DIR	328
#define	YY_LOOKAT	329
#define	YY_UP	330
#define	YY_FOV	331
#define	YY_ASPECT	332
#define	YY_MIN_DRAW	333
#define	YY_MAX_DRAW	334
#define	YY_S_P0	335
#define	YY_SPIRAL_NUM_SPHERES	336
#define	YY_SPIRAL_RADIUS	337
#define	YY_LORENZ_DT	338
#define	YY_LORENZ_MIN_DISTANCE	339
#define	YY_LORENZ_MAX_DISTANCE	340
#define	YY_LORENZ_SIGMA	341
#define	YY_LORENZ_RHO	342
#define	YY_LORENZ_BETA	343
#define	YY_LORENZ_RADIUS	344
#define	YY_LORENZ_NUM_SPHERES	345
#define	YY_LORENZ_START	346
#define	YY_S_TRIANGLE	347
#define	YY_V1	348
#define	YY_V2	349
#define	YY_V3	350
#define	YY_N1	351
#define	YY_N2	352
#define	YY_N3	353
#define	YY_S_MESH	354
#define	YY_LOAD	355
#define	YY_S_INSTANCE	356
#define	YY_GEOMETRY	357
#define	YY_S_MATRIX	358
#define	YY_PUSH	359
#define	YY_POP	360
#define	YY_ROTATE	361
#define	YY_TRANSLATE	362
#define	YY_SCALE	363
#define	YY_SET_IDENTITY	364
#define	YY_S_LIGHT	365
#define	YY_S_POINTLIGHT	366
#define	YY_S_SQUARELIGHT	367
#define	YY_S_SPHERELIGHT	368
#define	YY_WATTAGE	369
#define	YY_COLOR	370
#define	YY_NUM_SAMPLES	371
#define	YY_P1	372
#define	YY_P2	373
#define	YY_S_MULTIMATERIAL	374
#define	YY_S_MATERIAL	375
#define	YY_S_DIFFUSE	376
#define	YY_S_INDIRECT_DIFFUSE	377
#define	YY_S_PHONG	378
#define	YY_S_STONE	379
#define	YY_S_STONEBUMP	380
#define	YY_S_REFLECTIVE	381
#define	YY_S_REFRACTIVE	382
#define	YY_N	383
#define	YY_AMBIENT	384
#define	YY_COLOR_A	385
#define	YY_COLOR_B	386
#define	YY_AMPLITUDE	387
#define	YY_IOR	388
#define	YY_WEIGHT	389
#define	YY_S_SPHERE	390
#define	YY_CENTER	391
#define	YY_RADIUS	392
#define	YY_S_BLPATCH	393
#define	YY_P00	394
#define	YY_P01	395
#define	YY_P10	396
#define	YY_P11	397
#define	YY_U_CONSTRAINT	398
#define	YY_V_CONSTRAINT	399
#define	YY_EQUALS	400
#define	NEG	401


extern YYSTYPE yylval;
