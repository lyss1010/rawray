/////////////////////////////////////////////////////////////////////////////
// basic_math.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "basic_math.h"

namespace math {

bool FloatEquals(float a, float b, float delta) {
    if( a > b ) {
        a -= b;
        return a <= delta;
    }
    else {
        b -= a;
        return b <= delta;
    }
}

}  // namespace math