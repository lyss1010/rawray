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
    std::vector<BBoxAA*> sorted[3];
    for( std::vector<Object*>::iterator iter = objects->begin(); iter != objects->end(); ++iter ) {
        Object* obj = (*iter);
        BBoxAA* box = BBoxAA::newBBoxAA(obj);

        sorted[0].push_back( box );
        sorted[1].push_back( box );
        sorted[2].push_back( box );
    }

    // Sort forrests by each axis
    std::sort( sorted[0].begin(), sorted[0].end(), BBoxAA::GreaterX );
    std::sort( sorted[1].begin(), sorted[1].end(), BBoxAA::GreaterY );
    std::sort( sorted[2].begin(), sorted[2].end(), BBoxAA::GreaterZ );

    // TODO: loop end condition
    // Continually find appropriate split points
    while( true ) {
        std::vector<BBoxAA*>::iterator split;
        int8 axis = DetermineSplit( split, sorted[0], sorted[1], sorted[2] );

        if( axis < 0 ) {
            // We are not splitting
            

        } else {
            // We are splitting
            

        }

    }


    // Clean up our temporary sorted data
    for( int i=0; i<3; ++i ) {
        std::vector<BBoxAA*>::iterator iter = sorted[i].begin();
        while( iter != sorted[i].end() ) {
            BBoxAA* box = (*iter);
            ++iter;
            
            box->deleteObject();
        }
    }
}

uint8 DetermineSplit( std::vector<BBoxAA*>::iterator split, std::vector<BBoxAA*>& xSorted, std::vector<BBoxAA*>& ySorted, std::vector<BBoxAA*>& zSorted ) {
    // assume all vectors are same size
    if( xSorted.size() < 2 ) return -1;

    // Last element in the left bounding volume [x,y,z]
    std::vector<BBoxAA*>::iterator last_left[3];
    last_left[0] = FindSplit( xSorted );
    last_left[1] = FindSplit( ySorted );
    last_left[2] = FindSplit( zSorted );

    // First element in the right bounding volume [x,y,z]
    std::vector<BBoxAA*>::iterator first_right[3];
    first_right[0] = last_left[0] + 1;
    first_right[1] = last_left[1] + 1;
    first_right[2] = last_left[2] + 1;

    // Find surface areas of the potential bounding volumes
    float size_left[3];
    size_left[0] = BBoxAA::SurfaceArea( (*lastLeftX)->GetMax() - xSorted.front()->GetMin() );
    size_left[1] = BBoxAA::SurfaceArea( (*lastLeftY)->GetMax() - ySorted.front()->GetMin() );
    size_left[2] = BBoxAA::SurfaceArea( (*lastLeftZ)->GetMax() - zSorted.front()->GetMin() );

    float size_right[3];
    size_right[0] = BBoxAA::SurfaceArea( xSorted.back()->GetMax() - (*firstRightX)->GetMin() );
    size_right[1] = BBoxAA::SurfaceArea( ySorted.back()->GetMax() - (*firstRightY)->GetMin() );
    size_right[2] = BBoxAA::SurfaceArea( zSorted.back()->GetMax() - (*firstRightZ)->GetMin() );

    const float box_cost = options::global::bvh_box_cost;
    const float obj_cost = options::global::bvh_obj_cost;

    // Find the costs of the possible bounding boxes
    float cost[3];
    float cost[0] = box_cost * ( sizeLeftX + sizeRightX ) + obj_cost;
    float cost[1] = box_cost * ( sizeLeftY + sizeRightY ) + obj_cost;
    float cost[2] = box_cost * ( sizeLeftZ + sizeRightZ ) + obj_cost;

    // Find the best axis to split on
    uint8 axis;
    if( cost[0] < cost[1] ) {
        axis = (cost[0] < cost[2]) ? 0 : 2;
    } else {
        axis = (cost[1] < cost[2]) ? 1 : 2;
    }
 
    // Find the elements on the left and right
    split = last_left[axis];
    return axis;
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
