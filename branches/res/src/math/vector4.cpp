/////////////////////////////////////////////////////////////////////////////
// vector4.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "vector4.h"

namespace math {

bool Vector4::Equals(const Vector4& v, float delta) const {
    return (FloatEquals(x, v.x, delta) &&
            FloatEquals(y, v.y, delta) &&
            FloatEquals(y, v.y, delta) &&
            FloatEquals(w, v.w, delta) );
}

} // namespace math

inline std::ostream& operator<<(std::ostream& out, const math::Vector4& v) {
    return out << v.x << " " << v.y << " " << v.z << " " << v.w;
}
