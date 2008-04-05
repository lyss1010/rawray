#ifndef RAWRAY_TOOLS_SYMBOLS_YY_H
#define RAWRAY_TOOLS_SYMBOLS_YY_H

#define YY_SYM_ERR           0

// STATES
#define YY_STATE_GLOBAL         10001
#define YY_STATE_CAMERA         10002
#define YY_STATE_LIGHT          10003
#define YY_STATE_MODEL          10004
#define YY_STATE_TRIANGLE       10005
#define YY_STATE_POINTLIGHT     10006
#define YY_STATE_SPHERE         10007

// MATH
#define YY_MATH_COS             10020
#define YY_MATH_SIN             10021
#define YY_MATH_TAN             10022
#define YY_MATH_ACOS            10023
#define YY_MATH_ASIN            10024
#define YY_MATH_ATAN            10025
#define YY_MATH_LN              10026
#define YY_MATH_LOG             10027
#define YY_MATH_EXP             10028
#define YY_MATH_SQRT            10029
#define YY_MATH_E               10030
#define YY_MATH_PI              10031

// PUNCTUATION
#define YY_SYM_NE               10057
#define YY_SYM_GE               10060
#define YY_SYM_LE               10061

// OTHER
#define YY_SYM_INT              10100
#define YY_SYM_REAL             10101
#define YY_SYM_STRING           10102
#define YY_SYM_ID               10103

// GLOBAL STATE DATA
#define YY_SYM_GLOBAL_WIDTH     10150
#define YY_SYM_GLOBAL_HEIGHT    10151
#define YY_SYM_GLOBAL_GL_BG     10152
#define YY_SYM_GLOBAL_IMG_BG    10153

// CAMERA STATE DATA
#define YY_SYM_CAMERA_POS       10170
#define YY_SYM_CAMERA_VIEW_DIR  10171
#define YY_SYM_CAMERA_LOOK_AT   10172
#define YY_SYM_CAMERA_UP        10173
#define YY_SYM_CAMERA_FOV       10174

// LIGHT STATE DATA
#define YY_SYM_LIGHT_POINTLIGHT 10190
#define YY_SYM_LIGHT_POS        10191
#define YY_SYM_LIGHT_COLOR      10192
#define YY_SYM_LIGHT_WATTAGE    10193

// MODEL STATE DATA
#define YY_SYM_MODEL_LOAD        10210

// SPHERE STATE DATA
#define YY_SYM_SPHERE_POS        10240
#define YY_SYM_SPHERE_RADIUS     10241
#define YY_SYM_SPHERE_COLOR      10242

#endif
