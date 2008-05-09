/////////////////////////////////////////////////////////////////////////////
// colorful.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "colorful.h"
#include "math/vector3.h"
#include "light.h"

namespace rawray {

Vector3 Colorful::Shade(const HitInfo& hit, const Scene& scene) const {
    const Ray& ray = hit.eyeRay;
    const Vector3 viewDir = -ray.direction;
    const std::vector<Light*>& lights = scene.GetLights();
    Vector3 shadedColor(0.0f, 0.0f, 0.0f);

    // Loop over all lights
    std::vector<Light*>::const_iterator light_it = lights.begin();
    for (light_it=lights.begin(); light_it != lights.end(); ++light_it) {
		Light* light = *light_it;
		Vector3 direction = light->GetPosition() - hit.point;

		float distance2 = direction.Length2();
		float falloff = light->Falloff(distance2);
		direction.Normalize();

		const float intensity = hit.normal.Dot(direction) * falloff * light->GetWattage() * math::INV_PI;
		if( intensity > 0.0f ) {
			Vector3 color = light->GetColor();
			color *= intensity;

			color = Vector3 (  (1-hit.texCoord.y)*(1-hit.texCoord.y),
							hit.texCoord.x*hit.texCoord.x,
							hit.texCoord.x );

			shadedColor += color;
		}
	}

    return shadedColor;
}


} // namespace rawray
