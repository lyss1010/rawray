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

		float falloff = light->Falloff(direction);

		// Normalize the light direction vector before using
		direction.Normalize();

		const float intensity = std::max( 
						0.0f, 
						hit.normal.Dot(direction) * falloff * light->GetWattage() * math::INV_PI );

		Vector3 color = light->GetColor();
		color *= intensity;

		color = Vector3 (  (1-hit.texCoord.y)*(1-hit.texCoord.y),
                           hit.texCoord.x*hit.texCoord.x,
                           hit.texCoord.x );

		shadedColor += color;
	}

    return shadedColor;
}


} // namespace rawray
