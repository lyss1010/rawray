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

// See: http://www.cs.utah.edu/~kpotter/pubs/bilinear.pdf
bool BLPatch::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    UNREFERENCED_PARAMETER(hit);
    UNREFERENCED_PARAMETER(ray);
    UNREFERENCED_PARAMETER(minDistance);
    UNREFERENCED_PARAMETER(maxDistance);

    // A1 = ax*qx - az*qz
    // B1 = bx*qz - bz*qx
    // C1 = cx*qz - cz*qx
    // D1 = (dx-rx)*qz - (dz-rz)*qx
    // A2 = ay*qz - az*qy
    // B2 = by*qz - bz*qy
    // C2 = cy*qz - cz*qy
    // D2 = (dy-ry)*qz - (dz-rz)*qy

    // 0 = v^2(A2C1-A1C2) + v(A2D1-A1D2+B2C1-B1C2) + (B2D1-B1D2)
    // 
    return false;
}


} // namespace rawray
