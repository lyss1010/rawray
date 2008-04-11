/////////////////////////////////////////////////////////////////////////////
// lambert.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "lambert.h"
#include "math/vector3.h"
#include "light.h"

namespace rawray {

Vector3 Lambert::Shade(const Ray& ray, const HitInfo& hit, const Scene& scene) const {
    const Vector3 viewDir = -ray.direction;
    const std::vector<Light*>& lights = scene.GetLights();
    Vector3 shadedColor(0.0f, 0.0f, 0.0f);

    // Loop over all lights
    std::vector<Light*>::const_iterator light_it = lights.begin();
    for (light_it=lights.begin(); light_it != lights.end(); ++light_it) {
        const Light* light = *light_it;
        Vector3 l = light->GetPosition() - hit.point;

        // Inverse square falloff
        const float falloff = l.Length2();

        // Normalize direction of light
        l /= sqrtf(falloff);
        
        // Diffuse component
        const float intensity = std::max( 0.0f, hit.normal.Dot(l)/falloff * light->GetWattage() / math::PI );
        Vector3 color = light->GetColor();
        color *= diffuse_;
        color *= intensity;

        shadedColor += color;
    }

    // Add in ambient component regardless of lights
    shadedColor += ambient_;

    return shadedColor;
}


} // namespace rawray
