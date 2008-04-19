/////////////////////////////////////////////////////////////////////////////
// basic_math.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "basic_math.h"

namespace math {

inline bool FloatEquals(float a, float b, float delta) {
    if( a > b ) {
        a -= b;
        return a <= delta;
    }
    else {
        b -= a;
        return b <= delta;
    }
}

inline bool FloatZero(float f, float epsilon) {
    return f < epsilon && f > -epsilon;
}

int SolveQuadratic(float* out1, float* out2, float a, float b, float c) {
    if( a == 0.0f ) return 0;

    int numRoots = 2;
    float discrim = b*b - 4*a*c;
    if( discrim < 0.0f ) return 0;
    if( discrim > 0.0f )
        discrim = sqrtf( discrim );
    else
        numRoots = 1;

    float divisor = 1.0f / (2*a);
    *out1 = (-b + discrim) * divisor;
    *out2 = (-b - discrim) * divisor;

    return numRoots;
}

}  // namespace math