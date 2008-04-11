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

}  // namespace math