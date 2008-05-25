/////////////////////////////////////////////////////////////////////////////
// random.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "random.h"

namespace tools {
namespace random {

// See: http://mathworld.wolfram.com/SpherePointPicking.html
Vector3 RandomUnitCircleLoc() {
	float a, a2, b, b2, a2_plus_b2;

	do {
		a = 1.0f - (rand() / float(RAND_MAX/2)); // [-1,1]
		b = 1.0f - (rand() / float(RAND_MAX/2)); // [-1,1]

		a2 = a*a;
		b2 = b*b;
		a2_plus_b2 = a2 + b2;
	} while( a2_plus_b2 >= 1 );

	const float c = sqrtf( 1.0f - a2 - b2 );

	return Vector3(
		2.0f * a * c,
		2.0f * b * c,
		1.0f - 2.0f * a2_plus_b2 );
}

} // namespace tools::random
} // namespace tools