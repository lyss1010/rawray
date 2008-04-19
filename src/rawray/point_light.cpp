/////////////////////////////////////////////////////////////////////////////
// point_light.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "point_light.h"

namespace rawray {

float PointLight::Falloff(const Vector3& direction) {
	// Inverse square falloff
	return 1.0f / direction.Length2();
}


} // namespace rawray
