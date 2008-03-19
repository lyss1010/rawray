/////////////////////////////////////////////////////////////////////////////
// bl_patch.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "bl_patch.h"

namespace rawray {

void BLPatch::RenderGL() {
}

void BLPatch::PreCalc() {
}

bool BLPatch::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    UNREFERENCED_PARAMETER(hit);
    UNREFERENCED_PARAMETER(ray);
    UNREFERENCED_PARAMETER(minDistance);
    UNREFERENCED_PARAMETER(maxDistance);

    // TODO: Write algorithm
    return false;
}


} // namespace rawray
