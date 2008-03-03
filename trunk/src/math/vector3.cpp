/////////////////////////////////////////////////////////////////////////////
// vector3.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "vector3.h"
#include "math.h"

namespace math {

bool Vector3::Equals(const Vector3& v, float delta) {
    return (FloatEquals(x, v.x, delta) &&
            FloatEquals(y, v.y, delta) &&
            FloatEquals(y, v.y, delta) );
}

Vector3 Vector3::Rotated(float theta, const Vector3& v) const {
    // NOTE: We are so verbose because we are trying to avoid copy constructors everywhere
    Vector3 v0(v);
    v0 *= math::Dot(*this, v);

    Vector3 v1(*this);
    v1 -= v0;
    v1 *= cosf(theta);

    Vector3 v2(v);
    v2.Cross(v1);
    v2 *= sinf(theta);

    v0 += v1;
    v0 += v2;

    return v0;
}

} // namespace math
