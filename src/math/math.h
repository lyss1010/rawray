/////////////////////////////////////////////////////////////////////////////
// Helper Functions : math.h
// 
// Basic mathmatical functions
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_MATH_MATH_H
#define RAWRAY_MATH_MATH_H
#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////
namespace math {

    // Checks if two floats are within delta of each other (NOTE: Assumes positive delta)
    DllExport bool FloatEquals(float a, float b, float delta);

} // namespace math


#endif // RAWRAY_MATH_MATH_H