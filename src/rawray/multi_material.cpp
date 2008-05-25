/////////////////////////////////////////////////////////////////////////////
// multi_material.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "multi_material.h"
#include "math/vector3.h"
#include "light.h"
#include "stats.h"
#include "hit_info.h"


namespace rawray {

MultiMaterial::~MultiMaterial() {
	std::vector<Material*>::iterator iter = materials_.begin();
	while( iter != materials_.end() ) {
		Material* toDelete = *iter++;
		delete toDelete;
	}
}

Vector3 MultiMaterial::Shade(HitInfo& hit, Scene& scene) const {
	const Ray& ray = hit.eyeRay;
    const Vector3 viewDir = -ray.direction;
    const std::vector<Light*>& lights = scene.GetLights();
    Vector3 shadedColor(0);

	// Loop over all lights
    for (std::vector<Light*>::const_iterator light_it=lights.begin(); light_it != lights.end(); ++light_it) {
		Light* light = *light_it;
		stats::shadowRays += light->GetNumSamples();
		const float intensity = scene.GetLightIntensity(*light, hit);

		// Shade with all materials
		ShadeLight(hit, scene, *light, intensity, shadedColor);
	}

	// Add in ambient contribution
	shadedColor += ambient_;

	return shadedColor;
}

void MultiMaterial::ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector3& shadedColor) const {
	// Loop over all materials to get their contribution
	for(std::vector<Material*>::const_iterator material_it = materials_.begin(); material_it != materials_.end(); ++material_it ) {
		Material* material = *material_it;
		material->ShadeLight(hit, scene, light, intensity, shadedColor);
	}
}

// Choose base color as base color of 1st material
Vector3 MultiMaterial::BaseColor() const {
	if( materials_.size() < 1 )
		return Vector3(0);

	return materials_[0]->BaseColor();
}

} // namespace rawray
