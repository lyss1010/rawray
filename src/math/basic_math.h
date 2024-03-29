/////////////////////////////////////////////////////////////////////////////
// Helper Functions : basic_math.h
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
    DllExport bool FloatZero(float f, float epsilon);
    DllExport int SolveQuadratic(float* out1, float* out2, float a, float b, float c);

} // namespace math


#endif // RAWRAY_MATH_BASIC_MATH_H