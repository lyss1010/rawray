/////////////////////////////////////////////////////////////////////////////
// vector2.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "vector2.h"

namespace math {

bool Vector2::Equals(const Vector2& v, float delta) const {
    return (FloatEquals(x, v.x, delta) &&
            FloatEquals(y, v.y, delta) );
}

} // namespace math

inline std::ostream& operator<<(std::ostream& out, const math::Vector2& v) {
    return out << v.x << " " << v.y;
}
