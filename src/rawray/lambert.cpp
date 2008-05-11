/////////////////////////////////////////////////////////////////////////////
// lambert.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "lambert.h"
#include "math/vector3.h"
#include "light.h"
#include "stats.h"

namespace rawray {

Vector3 Lambert::Shade(const HitInfo& hit, const Scene& scene) const {
	const Ray& ray = hit.eyeRay;
    const Vector3 viewDir = -ray.direction;
    const std::vector<Light*>& lights = scene.GetLights();
    Vector3 shadedColor(0.0f, 0.0f, 0.0f);

	stats::shadowRays += lights.size();

	// Loop over all lights
    std::vector<Light*>::const_iterator light_it = lights.begin();
    for (light_it=lights.begin(); light_it != lights.end(); ++light_it) {
		Light* light = *light_it;
		Vector3 direction = light->GetPosition() - hit.point;

		float distance2 = direction.Length2();
		float falloff = light->Falloff(distance2);
		direction.Normalize();

		// See if we are in shadow
		//Ray shadowRay = Ray( hit.point, direction );
		//if( scene.Hit( shadowRay, MIN_DISTANCE, sqrt(distance2) ) )
		//	continue;

		HitInfo tmp;
		tmp.eyeRay = Ray( hit.point, direction );
		Scene& s = const_cast<Scene&>(scene);
		if( scene.Hit( Ray( hit.point, direction ), MIN_DISTANCE, sqrt(distance2) ) ) {
			continue;
		}
		
		const float intensity = hit.normal.Dot(direction) * falloff * light->GetWattage() * math::INV_PI;
		if( intensity > 0.0f ) {
			Vector3 color = light->GetColor();
			color *= diffuse_;
			color *= intensity;

			shadedColor += color;
		}
	}

    // Add in ambient component regardless of lights
    shadedColor += ambient_;

    return shadedColor;
}


} // namespace rawray
