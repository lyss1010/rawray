/////////////////////////////////////////////////////////////////////////////
// Precompiled Header : stdafx.h
//
// Common includes and definitions of tools project
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_TOOLS_STDAFX_H
#define RAWRAY_TOOLS_STDAFX_H
#include "base/global_defs.h"

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

class Matrix4x4;

} // namespace math


/////////////////////////////////////////////////////////////////////////////
// Types
/////////////////////////////////////////////////////////////////////////////
namespace tools {

typedef math::Vector2 Vector2;
typedef math::Vector3 Vector3;
typedef math::Vector4 Vector4;

typedef math::Tuple2<int> Tuple2I;
typedef math::Tuple3<int> Tuple3I;

typedef math::Matrix4x4 Matrix4x4;

} // namesace tools


#endif // RAWRAY_TOOLS_STDAFX_H
