/////////////////////////////////////////////////////////////////////////////
// vector3.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "vector3.h"

namespace math {

bool Vector3::Equals(const Vector3& v, float delta) const {
    return (FloatEquals(x, v.x, delta) &&
            FloatEquals(y, v.y, delta) &&
            FloatEquals(y, v.y, delta) );
}

Vector3 Vector3::Rotated(float theta, const Vector3& v) const {
    const float c = cosf(theta);
    const float s = sinf(theta);
    const float x = math::Dot(*this, v);

    Vector3 v0 = x * v;
    Vector3 v1 = *this - v0;
    Vector3 v2 = math::Cross(v, v1);

    return v0 + c*v1 + s*v2;
}

uint8 Vector3::GetDominantAxis() const {
    const float absX = fabs(x);
    const float absY = fabs(y);
    const float absZ = fabs(z);

    if( absX > absY )
        return ( (absX > absZ) ? 0 : 2 );
    else
        return ( (absY > absZ) ? 1 : 2 );
}

} // namespace math

inline std::ostream& operator<<(std::ostream& out, const math::Vector3& v) {
    return out << v.x << " " << v.y << " " << v.z;
}
