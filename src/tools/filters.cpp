/////////////////////////////////////////////////////////////////////////////
// filters.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "filters.h"

namespace tools {
namespace filters {

// See: http://www.cg.tuwien.ac.at/~theussl/DA/node33.html
float DllExport Reconstruction(float x, float b, float c) {
	x = fabs(x);
	if( x > 2.0f )
		return 0.0f;

	const float x_2 = x*x;
	const float x_3 = x*x_2;

	if( x < 1.0f )
		x = x_3 * (12 - 9*b - 6*c) + 
			x_2 * (-18 + 12*b + 6*c) + 
			      (6 - 2*b);
	else
		x = x_3 * (-b - 6*c) + 
			x_2 * (6*b + 30*c) + 
			x   * (-12*b - 48*c) + 
			      (8*b + 24*c);

	return x / 6.0f;
}

} // namespace tools::filters
} // namespace tools