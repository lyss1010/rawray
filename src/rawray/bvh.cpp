/////////////////////////////////////////////////////////////////////////////
// bvh.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "bvh.h"
#include "bbox_aa.h"

namespace rawray {

void BVH::Rebuild(std::vector<Object*>* objects) {
    // Skip hierarchy if we have only 1 object
    singleton_ = ( objects.size() > 1 ) ? NULL : objects

    // Create forrests of all objects bounded by single boxes
    std::vector<BBoxAA*> xSorted, ySorted, zSorted;
    for( std::vector<Object*>::iterator iter = objects->begin(); iter != objects->end(); ++iter ) {
        Object* obj = (*iter);
        BBoxAA* box = BBoxAA::newBBoxAA(obj);
        xSorted.push_back( box );
        ySorted.push_back( box );
        zSorted.push_back( box );
    }

    // Sort forrests by each axis
    std::sort( xSorted.begin(), xSorted.end(), BBoxAA::GreaterX );
    std::sort( ySorted.begin(), xSorted.end(), BBoxAA::GreaterY );
    std::sort( zSorted.begin(), xSorted.end(), BBoxAA::GreaterZ );

    // TODO: loop end condition
    // Continually find appropriate split points
    while( true ) {
        // Last element in the left bounding volume
        std::vector<BBoxAA*>::iterator last_left[3];
        last_left[0] = FindSplit( xSorted );
        last_left[1] = FindSplit( xSorted );
        last_left[2] = FindSplit( xSorted );

        // First element in the right bounding volume
        std::vector<BBoxAA*>::iterator first_right[3];
        first_right[0] = last_left[0] + 1;
        first_right[1] = last_left[1] + 1;
        first_right[2] = last_left[2] + 1;

        // TODO: Case where we are at end of splitting

        // Find the extents of the different options we have for bounding volumes
        BBoxAA* leftX  = BBoxAA::newBBoxAA( xSorted.front()->GetMin(), (*lastLeftX)->GetMax() );
        BBoxAA* rightX = BBoxAA::newBBoxAA( (*firstRightX)->GetMin(),  xSorted.back()->GetMax() );

        BBoxAA* leftY  = BBoxAA::newBBoxAA( ySorted.front()->GetMin(), (*lastLeftX)->GetMax() );
        BBoxAA* rightY = BBoxAA::newBBoxAA( (*firstRightY)->GetMin(),  xSorted.back()->GetMax() );

        BBoxAA* leftZ  = BBoxAA::newBBoxAA( zSorted.front()->GetMin(), (*lastLeftZ)->GetMax() );
        BBoxAA* rightZ = BBoxAA::newBBoxAA( (*firstRightZ)->GetMin(),  zSorted.back()->GetMax() );

        // Find surface areas of the potential bounding volumes
        const float sizeLeftX  = leftX->GetSurfaceArea();
        const float sizeRightX = rightX->GetSurfaceArea();

        const float sizeLeftY  = leftY->GetSurfaceArea();
        const float sizeRightY = rightY->GetSurfaceArea();

        const float sizeLeftZ  = leftZ->GetSurfaceArea();
        const float sizeRightZ = rightZ->GetSurfaceArea();

        const float box_cost = options::global::bvh_box_cost;
        const float obj_cost = options::global::bvh_obj_cost;

        // Find the sizes of the possible bounding boxes
        float costX = box_cost * ( sizeLeftX + sizeRightX ) + obj_cost;
        float costY = box_cost * ( sizeLeftY + sizeRightY ) + obj_cost;
        float costZ = box_cost * ( sizeLeftZ + sizeRightZ ) + obj_cost;

        // Find the best axis to split on
        uint8 axis;
        if( costX < costY ) {
            axis = (costX < costZ) ? 0 : 2;
        } else {
            axis = (costY < costZ) ? 1 : 2;
        }

        // TODO: do actual split
        // TODO: what if not splitting is better?
    }
}

bool CreateBVHNode( BVHNode& node, std::vector<BBoxAA*>& xSorted, std::vector<BBoxAA*>& ySorted, std::vector<BBoxAA*>& zSorted ) {
    

}

std::vector<BBoxAA*>::iterator FindSplit( std::vector<BBoxAA*> sorted ) {
    if( sorted.size() < 2 ) return sorted.end();
    
    BBoxAA left, right;
    std::vector<BBoxAA*>::iterator split = sorted.end();

    left.SetMin( sorted.front()->GetMin() );
    right.SetMax( sorted.back()->GetMax() );
    
    // For all possible split points, compute the cost; finding the minimum
    float min_cost = FLT_MAX;
    std::vector<BBoxAA*>::iterator curr = sorted.begin();
    std::vector<BBoxAA*>::iterator next = curr + 1;
    do {
        left.SetMax(  (*curr)->GetMax() );
        right.SetMin( (*curr)->GetMin() );

        float cost = box_cost * ( left.GetSurfaceArea() + right.GetSurfaceArea() ) + obj_cost;
        if( cost < min_cost ) {
            min_cost = cost;
            split = curr;
        }

    } while( next != sorted.end() );

    return curr;
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
