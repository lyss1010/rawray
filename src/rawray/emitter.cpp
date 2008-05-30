/////////////////////////////////////////////////////////////////////////////
// emitter.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "emitter.h"
#include "math/vector3.h"

namespace rawray {

Vector4 Emitter::Shade(HitInfo& hit, Scene& scene) const {
	UNREFERENCED_PARAMETER(hit);
	UNREFERENCED_PARAMETER(scene);

	return color_;
}

void Emitter::ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector4& shadedColor) const {
	UNREFERENCED_PARAMETER(hit);
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(light);
	UNREFERENCED_PARAMETER(intensity);
	
	shadedColor += color_;
}

} // namespace rawray
