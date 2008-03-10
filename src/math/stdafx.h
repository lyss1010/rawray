/////////////////////////////////////////////////////////////////////////////
// Precompiled Header : stdafx.h
//
// Common includes and definitions of math project
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_MATH_STDAFX_H
#define RAWRAY_MATH_STDAFX_H
#include "global_defs.h"


/////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////
namespace math {

const float EPSILON = 0.001f;
const float PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706f;
const float DEG_TO_RAD = PI / 180.0f;
const float RAD_TO_DEG = 180.0f / PI;
const float HALF_DEG_TO_RAD = PI / 360.0f;
const float HALF_RAD_TO_DEG = 90.0f / PI;

} // namespace math



/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

// Standard C Runtime Libraries
#include <math.h>
#include <iostream>

// Common project wide includes
#include "basic_math.h"


#endif // RAWRAY_MATH_STDAFX_H
