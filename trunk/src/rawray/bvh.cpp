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

void BVH::IntersectPack(HitPack& hitpack, float minDistance, float maxDistance) {
    hitpack.hit_result[0] = Intersect( hitpack.hits[0], minDistance, maxDistance );
    hitpack.hit_result[1] = Intersect( hitpack.hits[1], minDistance, maxDistance );
    hitpack.hit_result[2] = Intersect( hitpack.hits[2], minDistance, maxDistance );
    hitpack.hit_result[3] = Intersect( hitpack.hits[3], minDistance, maxDistance );
}

bool BVH::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
    // TODO: Actual Bounding Volume Hierarchy, not test of all objects
    uint32 numHits = 0;
    HitInfo tempHit = hit;

    hit.distance = MAX_DISTANCE;
    for (size_t i = 0; i < objects_->size(); ++i)
    {
        if( (*objects_)[i]->Intersect( tempHit, minDistance, maxDistance) ) {
            ++numHits;
            if( tempHit.distance < hit.distance )
                hit = tempHit;
        }
    }
    
    return numHits > 0;
}

} // namespace rawray
