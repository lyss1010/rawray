/////////////////////////////////////////////////////////////////////////////
// Class : worley.h
//
//  Copyright 1994, 2002 by Steven Worley
//	This software may be modified and redistributed without restriction
//	provided this comment header remains intact in the source code.
//	This code is provided with no warrantee, express or implied, for
//	any purpose.
//
//	A detailed description and application examples can be found in the
//	1996 SIGGRAPH paper "A Cellular Texture Basis Function" and
//	especially in the 2002 book "Texturing and Modeling, a Procedural
//	Approach, 3rd edition." There is also extra information on the web
//	site http://www.worley.com/cellular.html .
//
//	If you do find interesting uses for this tool, and especially if
//	you enhance it, please drop me an email at steve@worley.com.
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_TOOLS_WORLEY_H
#define RAWRAY_TOOLS_WORLEY_H
#include "stdafx.h"
#include <math.h>


/////////////////////////////////////////////////////////////////////////////
namespace tools {

// Worley noise class
//
//	An implementation of the key cellular texturing basis
//	function. This function is hardwired to return an average F_1 value
//	of 1.0. It returns the <n> closest feature point distances
//	F_1, F_2, .. F_n the vector delta to those points, and a 32 bit
//	seed for each of the feature points.  This function is not
//	difficult to extend to compute alternative information such as
//	higher order F values, to use the Manhattan distance metric, or
//	other fun perversions.
//	
//	 <at>    The input sample location. 
//	<maxOrder>  Smaller values compute faster. < 5, read the book to extend it.
//	<F>     The output values of F_1, F_2, ..F[n] in F[0], F[1], F[n-1]
//	<delta> The output vector difference between the sample point and the n-th
//	            closest feature point. Thus, the feature point's location is the
//	            hit point minus this value. The DERIVATIVE of F is the unit
//	            normalized version of this vector.
//	<ID>    The output 32 bit ID number which labels the feature point. This
//	            is useful for domain partitions, especially for coloring flagstone
//	            patterns.
//	
//	This implementation is tuned for speed in a way that any order > 5
//	will likely have discontinuous artifacts in its computation of F5+.
//	This can be fixed by increasing the internal points-per-cube
//	density in the source code, at the expense of slower
//	computation. The book lists the details of this tuning.
class DllExport Worley {
public:
	static void Noise1D(float at,    long maxOrder, float *F, float (*delta),    unsigned long *ID);
	static void Noise2D(float at[2], long maxOrder, float *F, float (*delta)[2], unsigned long *ID);
	static void Noise3D(float at[3], long maxOrder, float *F, float (*delta)[3], unsigned long *ID); 

private:
	// the function to merge-sort a "cube" of samples into the current best-found
	// list of values.
	static void AddSamples(long xi,                   long maxOrder, float at, float *F, float(*delta), unsigned long *ID);
    static void AddSamples(long xi, long yi,          long maxOrder, float at[2], float *F, float(*delta)[2], unsigned long *ID);
    static void AddSamples(long xi, long yi, long zi, long maxOrder, float at[3], float *F, float(*delta)[3], unsigned long *ID);

	static const int poissonCount[256];

}; // class Worley

} // namespace tools
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_TOOLS_WORLEY_H
