/////////////////////////////////////////////////////////////////////////////
// Precompiled Header : stdafx.h
//
// Common includes and definitions of rawray project
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_STDAFX_H
#define RAWRAY_RAWRAY_STDAFX_H
#include "global_defs.h"

#include <vector>
#include "options.h"
#include "constants.h"

/////////////////////////////////////////////////////////////////////////////
// Forward Declarations
/////////////////////////////////////////////////////////////////////////////
namespace math {

class Vector2;
class Vector3;
class Vector4;

template <class T>
class Tuple2;

template <class T>
class Tuple3;

} // namespace math


/////////////////////////////////////////////////////////////////////////////
// Types
/////////////////////////////////////////////////////////////////////////////
namespace rawray {

typedef math::Vector2 Vector2;
typedef math::Vector3 Vector3;
typedef math::Vector4 Vector4;

typedef math::Tuple2<uint32> Tuple2I;
typedef math::Tuple3<uint32> Tuple3I;

} // namesace rawray

#endif // RAWRAY_RAWRAY_STDAFX_H
