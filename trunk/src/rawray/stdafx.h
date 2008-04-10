/////////////////////////////////////////////////////////////////////////////
// Precompiled Header : stdafx.h
//
// Common includes and definitions of rawray project
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_STDAFX_H
#define RAWRAY_RAWRAY_STDAFX_H
#include "base/global_defs.h"


// Windows Includes
#include <Windows.h>
#include <winsock.h>


// STD Includes
#pragma warning(push)
#pragma warning(disable:4702) // Unreachable code warning in <vector>
#include <vector>
#pragma warning(pop)

#include <list>
#include <stack>
#include <algorithm>
#include <iostream>
#include <assert.h>

// OpenGL Includes
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#undef GLUT_DISABLE_ATEXIT_HACK

#include "options.h"
#include "constants.h"
#include "math/constants.h"

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
namespace rawray {

typedef math::Vector2 Vector2;
typedef math::Vector3 Vector3;
typedef math::Vector4 Vector4;

typedef math::Tuple2<uint32> Tuple2I;
typedef math::Tuple3<uint32> Tuple3I;

typedef math::Matrix4x4 Matrix4x4;

} // namesace rawray


#endif // RAWRAY_RAWRAY_STDAFX_H
