/////////////////////////////////////////////////////////////////////////////
// bvh.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "bvh.h"

namespace rawray {
   
void BVH::Rebuild(std::vector<Object*>* objects) {
    objects_ = objects;
}

void BVH::PreCalc() {
    Rebuild(objects_);
}

void BVH::RenderGL() {
}

bool BVH::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    // TODO: Actual Bounding Volume Hierarchy, not test of all objects
    
    uint32 numHits = 0;
    HitInfo tempHit;

    hit.distance = MAX_DISTANCE;
    for (size_t i = 0; i < objects_->size(); ++i)
    {
        if( (*objects_)[i]->Intersect( tempHit, ray, minDistance, maxDistance) ) {
            ++numHits;
            if( tempHit.distance < hit.distance )
                hit = tempHit;
        }
    }
    
    return numHits > 0;
}

} // namespace rawray
