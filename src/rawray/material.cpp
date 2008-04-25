/////////////////////////////////////////////////////////////////////////////
// material.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "material.h"

namespace rawray {

Vector3 Material::Shade(const HitInfo& hit, const Scene& scene) const {
    UNREFERENCED_PARAMETER(hit);
    UNREFERENCED_PARAMETER(scene);
    
    return Vector3(1);
}

Vector3 Material::BaseColor() const {
	return Vector3(1);
}

} // namespace rawray
