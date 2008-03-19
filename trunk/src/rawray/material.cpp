/////////////////////////////////////////////////////////////////////////////
// material.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "material.h"

namespace rawray {

Vector3 Material::Shade(const Ray& ray, const HitInfo& hit, const Scene& scene) const {
    UNREFERENCED_PARAMETER(ray);
    UNREFERENCED_PARAMETER(hit);
    UNREFERENCED_PARAMETER(scene);
    
    return Vector3(1.0f, 1.0f, 1.0f);
}


} // namespace rawray
