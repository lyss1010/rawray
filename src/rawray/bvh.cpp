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
    // TODO: Actual Bounding Volume Hierarchy, not test of all objects
    HitPack tempHitpack = hitpack;

    tempHitpack.hits[0].distance = MAX_DISTANCE;
    tempHitpack.hits[1].distance = MAX_DISTANCE;
    tempHitpack.hits[2].distance = MAX_DISTANCE;
    tempHitpack.hits[3].distance = MAX_DISTANCE;

    for( size_t i=0; i< objects_->size(); ++i ) {
        (*objects_)[i]->IntersectPack( tempHitpack, minDistance, maxDistance );

        if( tempHitpack.hit_result[0] && tempHitpack.hits[0].distance < hitpack.hits[0].distance ) {
            hitpack.hits[0] = tempHitpack.hits[0];
            hitpack.hit_result[0] = tempHitpack.hit_result[0];
        }

        if( tempHitpack.hit_result[1] && tempHitpack.hits[1].distance < hitpack.hits[1].distance ) {
            hitpack.hits[1] = tempHitpack.hits[1];
            hitpack.hit_result[1] = tempHitpack.hit_result[1];
        }

        if( tempHitpack.hit_result[2] && tempHitpack.hits[2].distance < hitpack.hits[2].distance ) {
            hitpack.hits[2] = tempHitpack.hits[2];
            hitpack.hit_result[2] = tempHitpack.hit_result[2];
        }

        if( tempHitpack.hit_result[3] && tempHitpack.hits[3].distance < hitpack.hits[3].distance ) {
            hitpack.hits[3] = tempHitpack.hits[3];
            hitpack.hit_result[3] = tempHitpack.hit_result[3];
        }
    }
}

bool BVH::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
    // TODO: Actual Bounding Volume Hierarchy, not test of all objects
    uint32 numHits = 0;
    HitInfo tempHit = hit;
    
    tempHit.distance = MAX_DISTANCE;
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
