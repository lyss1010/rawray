/////////////////////////////////////////////////////////////////////////////
// diffuse.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "diffuse.h"
#include "math/vector3.h"
#include "light.h"
#include "stats.h"

namespace rawray {

void Diffuse::ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector4& shadedColor) const {
	UNREFERENCED_PARAMETER(scene);

	Vector3 direction = light.GetPosition() - hit.point;
	direction.Normalize();
	intensity *= hit.normal.Dot(direction);

	if( intensity > 0.0f ) {
		Vector4 lightColor = light.GetColor();
		lightColor *= color_;
		lightColor *= intensity;

		shadedColor += lightColor;
	}
}

} // namespace rawray
