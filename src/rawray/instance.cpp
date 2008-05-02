/////////////////////////////////////////////////////////////////////////////
// instance.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "instance.h"
#include "material.h"
#include "ray.h"
#include <new>

namespace rawray {

void Instance::deleteObject() {
    instancedObject_->deleteObject();
}

void Instance::RenderGL() {
    glPushMatrix();

    //glLoadMatrixf( matrix_ );
    instancedObject_->RenderGL();

    glPopMatrix();
}

void Instance::PreCalc() {
    instancedObject_->PreCalc();
}

bool Instance::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
    // TODO: Incorporate matrix in the ray direction
    return instancedObject_->Intersect(hit, minDistance, maxDistance);
}

void Instance::IntersectPack(HitPack& hitpack, float minDistance, float maxDistance) {
    // TODO: Incorporate matrix in the ray direction
    return instancedObject_->IntersectPack(hitpack, minDistance, maxDistance);
}

} // namespace rawray
