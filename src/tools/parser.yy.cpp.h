typedef union
{
    float real;
    int integer;
    char* str;
} YYSTYPE;
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


extern YYSTYPE yylval;
