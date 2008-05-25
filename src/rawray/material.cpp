/////////////////////////////////////////////////////////////////////////////
// material.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "material.h"
#include "math/vector3.h"
#include "light.h"
#include "stats.h"

namespace rawray {

Vector3 Material::Shade(HitInfo& hit, Scene& scene) const {
	const Ray& ray = hit.eyeRay;
    const Vector3 viewDir = -ray.direction;
    const std::vector<Light*>& lights = scene.GetLights();
    Vector3 shadedColor(0);

	// Loop over all lights
    std::vector<Light*>::const_iterator light_it = lights.begin();
    for (light_it=lights.begin(); light_it != lights.end(); ++light_it) {
		Light* light = *light_it;
		stats::shadowRays += light->GetNumSamples();

		ShadeLight(	hit, 
					scene,
					*light, 
					scene.GetLightIntensity(*light, hit), 
					shadedColor );
	}

    return shadedColor;
}

} // namespace rawray
