/////////////////////////////////////////////////////////////////////////////
// Class : perlin.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_TOOLS_PERLIN_H
#define RAWRAY_TOOLS_PERLIN_H
#include "stdafx.h"
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
namespace tools {


// Based on Java reference implementation of:
// Improved Noise - Copyright 2002 Ken Perlin.
// See: http://mrl.nyu.edu/~perlin/noise/
class DllExport Perlin {
public:
   static float Noise(float x, float y, float z);

private:
   static float Fade(float t);
   static float Lerp(float t, float a, float b);
   static float Grad(int hash, float x, float y, float z);

   static const unsigned char p[512];
}; // class Perlin

} // namespace tools
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_TOOLS_PERLIN_H
