/////////////////////////////////////////////////////////////////////////////
// tuple2.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "tuple2.h"

namespace math {

} // namespace math

template <class T>
inline std::ostream& operator<<(std::ostream& out, const math::Tuple2<T>& t) {
    return out << t.x << " " << t.y;
}
