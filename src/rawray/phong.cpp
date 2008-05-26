/////////////////////////////////////////////////////////////////////////////
// phong.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "phong.h"
#include "math/vector3.h"
#include "light.h"
#include "stats.h"

namespace rawray {

// Blinn-Phong model
void Phong::ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector4& shadedColor) const {
	UNREFERENCED_PARAMETER(scene);

	Vector3 l = light.GetPosition() - hit.point;
	Vector3 v = hit.eyeRay.origin - hit.point;
	l.Normalize();
	v.Normalize();
	
	Vector3 h = l + v;
	h *= 0.5f;

	intensity *= pow( hit.normal.Dot(h), n_ );

	Vector4 lightColor = light.GetColor();
	lightColor *= color_;
	lightColor *= intensity;

	shadedColor += lightColor;
}

} // namespace rawray
