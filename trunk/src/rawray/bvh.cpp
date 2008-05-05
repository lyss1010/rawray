/////////////////////////////////////////////////////////////////////////////
// bvh.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "bvh.h"
#include "bbox_aa.h"
#include "float.h"

namespace rawray {

BVH::~BVH() {
    // TODO: Cleanup
}

void BVH::Rebuild(std::vector<Object*>* objects) {
    // Create a forest of bounding boxes around all objects
    std::cout << "Creating BVH of " << objects->size() << " objects" << std::endl;

    std::vector<BBoxAA*> forest;
    for( std::vector<Object*>::iterator iter = objects->begin(); iter != objects->end(); ++iter )
        forest.push_back( BBoxAA::newBBoxAA( (*iter) ) );

    root_.BuildBVH( forest );
}

void BVHNode::BuildBVH( std::vector<BBoxAA*>& forest ) {
    // TODO: Cleanup old data

    // If there is only 1 box, we can not split it further
    if( forest.size() == 1 ) {
        isLeaf = true;
        bbox = forest[0];
        return;
    }

    // We must split into left and right bounding volumes
    isLeaf = false;
    children = new BVHNode[2];
        
    // Create sorted forests
    std::vector<BBoxAA*> sorted[3] = { 
        std::vector<BBoxAA*>( forest.begin(), forest.end() ), 
        std::vector<BBoxAA*>( forest.begin(), forest.end() ), 
        std::vector<BBoxAA*>( forest.begin(), forest.end() ) };

    std::sort( sorted[0].begin(), sorted[0].end(), BBoxAA::GreaterX );
    std::sort( sorted[1].begin(), sorted[1].end(), BBoxAA::GreaterY );
    std::sort( sorted[2].begin(), sorted[2].end(), BBoxAA::GreaterZ );

    size_t splitIndex;
    int8 axis = Split( splitIndex, sorted );
    assert( axis >= 0 );

	// The left forest will contain the split index and all before it
	std::vector<BBoxAA*>::iterator split = sorted[axis].begin() + splitIndex + 1;

	// Split forrest into left and right sections
    std::vector<BBoxAA*> left(  sorted[axis].begin(), split );
    std::vector<BBoxAA*> right( split, sorted[axis].end() );

    // Recursively build left and right sub nodes
    children[0].BuildBVH( left );
    children[1].BuildBVH( right );
}

int8 BVHNode::Split( size_t& splitIndex, std::vector<BBoxAA*>* sorted ) {
    // assume all vectors are same size
    if( sorted[0].size() < 2 ) return -1;

    // Compute the best cost we can find for each axis
    float cost[3];
    size_t last_left[3];
    for( int i=0; i<3; ++i ) {
		std::vector<BBoxAA*>& forest = sorted[i];

        // Find the best way to split the objects along this axis
        last_left[i] = FindSplittingPlane( forest );

		// Make sure there is at least 1 element in the left section
		assert( last_left[i] >= 0 );

		// Make sure there is at least 1 element in the right section
		assert( last_left[i]+1 < forest.size() );

        // Find surface areas of the potential bounding volumes
        BBoxAA* left_max  = forest[ last_left[i] ];
        BBoxAA* left_min = forest[ 0 ];

        BBoxAA* right_max  = forest[ sorted[i].size() - 1 ];
        BBoxAA* right_min = forest[ last_left[i] + 1 ];

        float size_left = BBoxAA::SurfaceArea( left_max->GetMax() - left_min->GetMin() );
        float size_right = BBoxAA::SurfaceArea( right_max->GetMax() - right_min->GetMin() );

        // Compute the cost of the bounding volumes of this split
        cost[i] = Cost( size_left, size_right );
    }

    // Find the best axis to split on
    uint8 axis;
    if( cost[0] < cost[1] ) {
        axis = (cost[0] < cost[2]) ? 0 : 2;
    } else {
        axis = (cost[1] < cost[2]) ? 1 : 2;
    }
 
    // Find the elements on the left and right
    splitIndex = last_left[axis];
    return axis;
}

size_t BVHNode::FindSplittingPlane( std::vector<BBoxAA*>& sorted ) {
    assert( sorted.size() >= 2 );

    BBoxAA left, right;
    left.SetMin( sorted.front()->GetMin() );
    right.SetMax( sorted.back()->GetMax() );
    float min_cost = FLT_MAX;
	size_t splitIndex = 0;
    
    // For all possible split points, compute the cost; finding the minimum
	for( size_t i=0; i<sorted.size()-1; ++i ) {
        left.SetMax(  sorted[i]->GetMax() );
        right.SetMin( sorted[i+1]->GetMin() );

        float cost = Cost( left.GetSurfaceArea(), right.GetSurfaceArea() );
        if( cost < min_cost ) {
            min_cost = cost;
            splitIndex = i;
        }

    }

    return splitIndex;
}

float BVHNode::Cost(float areaLeft, float areaRight) {
    return areaLeft + areaRight;
}

void BVH::PreCalc() {
    Rebuild(objects_);
}

void BVH::RenderGL() {
}

bool BVHNode::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
    if( isLeaf ) {
        return bbox->Intersect(hit, minDistance, maxDistance);
    } else {
        if( children[0].Intersect(hit, minDistance, maxDistance) ) {
            // We hit the left node, check if a right hit would be closer
            HitInfo hit2 = hit;
            if( children[1].Intersect(hit2, minDistance, maxDistance) ) {
                // Check which hit is closer
                if( hit2.distance < hit.distance )
                    hit = hit2;
            }
            return true;
        } else {
            // We did not hit the left node, only possible hit is on right
            return children[1].Intersect(hit, minDistance, maxDistance);
        }
    }
}

void BVHNode::IntersectPack(HitPack& hitpack, float minDistance, float maxDistance) {
    // TODO: Write me
    return;
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
    return root_.Intersect(hit, minDistance, maxDistance);
}

} // namespace rawray
