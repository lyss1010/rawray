/////////////////////////////////////////////////////////////////////////////
// tuple3.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "tuple3.h"

namespace math {

} // namespace math

template <class T>
inline std::ostream& operator<<(std::ostream& out, const math::Tuple3<T>& t) {
    return out << t.x << " " << t.y << " " << t.z;
}
