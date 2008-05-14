/////////////////////////////////////////////////////////////////////////////
// bvh.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "bvh.h"
#include "bbox_aa.h"
#include "float.h"
#include "time.h"

#include "stats.h"
#include <list>

namespace rawray {

BVH::~BVH() {
	ClearForest();
	root_.DestroyBVH();
}

void BVH::ClearForest() {
	for( std::vector<BBoxAA*>::iterator iter = forest_.begin(); iter != forest_.end(); ++iter ) {
		BBoxAA* box = (*iter);
		box->deleteObject();
	}
	forest_.clear();
}

void BVHNode::DestroyBVH() {
	switch( type ) {
	case SPLIT_NODE:
		children[0].DestroyBVH();
		children[1].DestroyBVH();
		delete [] children;
		break;

	case SINGLE_LEAF:
		// we take care of these deletes in ClearForest()
		break;

	case MULTI_LEAF:
		leaf->deleteObject();
		break;

	default:
		break;
	}
}

void BVH::Rebuild(std::vector<Object*>* objects) {
    // Create a forest of bounding boxes around all objects
    std::cout << "Creating BVH of " << objects->size() << " objects" << std::endl;

	ClearForest();
    for( std::vector<Object*>::iterator iter = objects->begin(); iter != objects->end(); ++iter )
        forest_.push_back( BBoxAA::newBBoxAA( (*iter) ) );

    clock_t startTime = clock();
	if( forest_.size() < 1 ) {
		std::cout << "" << std::endl;

		// No objects for our bvh, make sure bounds are set so nothing can intersect
		root_.type = INVALID_NODE;
		root_.box[0] = Vector3(0);
		root_.box[1] = Vector3(0);
		root_.box[2] = Vector3(0);
		root_.children = NULL;
	} else {
		// Create the bvh using the entire forest of objects
		root_.BuildBVH( forest_.begin(), forest_.end(), boxCost_, objCost_ );
	}
    clock_t endTime = clock();

    std::cout << "Done creating BVH of " << objects->size() << "objects in " << (endTime-startTime)/CLOCKS_PER_SEC << " seconds" << std::endl;
}

void BVHNode::BuildBVH( std::vector<BBoxAA*>::iterator begin, std::vector<BBoxAA*>::iterator end, float boxCost, float objCost ) {
    // If there is only 1 box, we can not split it further
    if( begin+1 == end ) {
		stats::bvhLeaves++;
		type = SINGLE_LEAF;
        leaf = *begin;
		box.SetBounds( leaf->GetMin(), leaf->GetMax() );

        return;
    }

    // Create sorted forests
    std::vector<BBoxAA*> sorted[6] = { 
        std::vector<BBoxAA*>( begin, end ), 
        std::vector<BBoxAA*>( begin, end ), 
        std::vector<BBoxAA*>( begin, end ),
        std::vector<BBoxAA*>( begin, end ), 
        std::vector<BBoxAA*>( begin, end ), 
        std::vector<BBoxAA*>( begin, end )
    };

    // Sort on every axis based on the min coordinate in that axis
    std::sort( sorted[0].begin(), sorted[0].end(), BBoxAA_Alg::min_lt_x );
    std::sort( sorted[1].begin(), sorted[1].end(), BBoxAA_Alg::min_lt_y );
    std::sort( sorted[2].begin(), sorted[2].end(), BBoxAA_Alg::min_lt_z );

    // Sort on every axis based on the max coordinate in that axis
    std::sort( sorted[3].begin(), sorted[3].end(), BBoxAA_Alg::max_lt_x );
    std::sort( sorted[4].begin(), sorted[4].end(), BBoxAA_Alg::max_lt_y );
    std::sort( sorted[5].begin(), sorted[5].end(), BBoxAA_Alg::max_lt_z );

	// Set the bounding volume now that we have everything sorted
	const Vector3 min( sorted[0].front()->GetMin().x, sorted[1].front()->GetMin().y, sorted[2].front()->GetMin().z );
	const Vector3 max( sorted[3].back()->GetMax().x,  sorted[4].back()->GetMax().y,  sorted[5].back()->GetMax().z );
	box.SetBounds( min, max );

    size_t splitIndex;
	float splitCost;
    int8 axis = Split( splitIndex, splitCost, sorted, boxCost, objCost, BoxAA::SurfaceArea( box[1] - box[0] ) );
    assert( axis >= 0 );

	// Compute cost of not splitting this forest and decide on if we should split or not
    // This cost is some made up number, if you just do size*objects it puts too many in the same box
	float leafCost = boxCost + sorted[0].size() * sorted[0].size() * objCost;
	if( leafCost < splitCost ) {
		stats::bvhLeaves++;
		type = MULTI_LEAF;
		leaf = BBoxAA::newBBoxAA( box[0], box[1] );

        // Add all boxes in forest to this box directly
        int leafSize = 0;
        std::vector<BBoxAA*>::iterator iter = begin;
        while( iter != end ) {
			((BBoxAA*)leaf)->AddObject( (*iter++) );
            ++leafSize;
        }
    } else {
	    stats::bvhSplits++;
	    type = SPLIT_NODE;
	    children = new BVHNode[2];

        // The left forest will contain the split index and all before it
	    // Recursively build left and right sub nodes
        std::vector<BBoxAA*>::iterator split = sorted[axis].begin() + splitIndex + 1;
	    children[0].BuildBVH( sorted[axis].begin(), split, boxCost, objCost );
	    children[1].BuildBVH( split, sorted[axis].end(), boxCost, objCost );
    }
}


int8 BVHNode::Split( size_t& splitIndex, float& splitCost, std::vector<BBoxAA*>* sorted, float boxCost, float objCost, float areaParent ) {
    // assume all vectors are same size
    if( sorted[0].size() < 2 ) return -1;

    // Compute the best cost we can find for each axis
    float cost[6];
    size_t last_left[6];
    for( int i=0; i<6; ++i ) {
		std::vector<BBoxAA*>& forest = sorted[i];

        // Find the best way to split the objects along this axis
        last_left[i] = FindSplittingPlane( forest );
		std::vector<BBoxAA*>::iterator split = sorted[i].begin() + last_left[i] + 1;

		// Make sure there is at least 1 element in the left section and right section
		assert( last_left[i] >= 0 && last_left[i]+1 < forest.size() );

		// Create left and right sections
		std::vector<BBoxAA*> leftForest(  sorted[i].begin(), split );
		std::vector<BBoxAA*> rightForest( split, sorted[i].end() );
		size_t lastIndexLeft  = leftForest.size() - 1;
		size_t lastIndexRight = rightForest.size() - 1;

		// Compute min/max values of the bounding volume around each forest
		BoxAA leftVolume, rightVolume;

		std::sort( leftForest.begin(),  leftForest.end(),  BBoxAA_Alg::min_lt_x );
		std::sort( rightForest.begin(), rightForest.end(), BBoxAA_Alg::min_lt_x );
		leftVolume[0].x  = leftForest[0]->GetMin().x;
		rightVolume[0].x = rightForest[0]->GetMin().x;

        std::sort( leftForest.begin(),  leftForest.end(),  BBoxAA_Alg::max_lt_x );
		std::sort( rightForest.begin(), rightForest.end(), BBoxAA_Alg::max_lt_x );
        leftVolume[1].x  = leftForest[lastIndexLeft]->GetMax().x;
		rightVolume[1].x = rightForest[lastIndexRight]->GetMax().x;

        std::sort( leftForest.begin(),  leftForest.end(),  BBoxAA_Alg::min_lt_y );
		std::sort( rightForest.begin(), rightForest.end(), BBoxAA_Alg::min_lt_y );
		leftVolume[0].y  = leftForest[0]->GetMin().y;
		rightVolume[0].y = rightForest[0]->GetMin().y;

        std::sort( leftForest.begin(),  leftForest.end(),  BBoxAA_Alg::max_lt_y );
		std::sort( rightForest.begin(), rightForest.end(), BBoxAA_Alg::max_lt_y );
        leftVolume[1].y  = leftForest[lastIndexLeft]->GetMax().y;
		rightVolume[1].y = rightForest[lastIndexRight]->GetMax().y;

        std::sort( leftForest.begin(),  leftForest.end(),  BBoxAA_Alg::min_lt_z );
		std::sort( rightForest.begin(), rightForest.end(), BBoxAA_Alg::min_lt_z );
		leftVolume[0].z  = leftForest[0]->GetMin().z;
		rightVolume[0].z = rightForest[0]->GetMin().z;

        std::sort( leftForest.begin(),  leftForest.end(),  BBoxAA_Alg::max_lt_z );
		std::sort( rightForest.begin(), rightForest.end(), BBoxAA_Alg::max_lt_z );
        leftVolume[1].z  = leftForest[lastIndexLeft]->GetMax().z;
		rightVolume[1].z = rightForest[lastIndexRight]->GetMax().z;

        // Find surface areas of the potential bounding volumes
        float size_total = 1.0f / BoxAA::SurfaceArea( rightVolume[1] - leftVolume[0] );
		float size_left  = size_total * BoxAA::SurfaceArea( leftVolume[1] - leftVolume[0] );
        float size_right = size_total * BoxAA::SurfaceArea( rightVolume[1] - rightVolume[0] );
		
        // Compute the cost of the bounding volumes of this split
        cost[i] = Cost( boxCost, objCost, areaParent, size_left, size_right, last_left[i]+1, forest.size()-last_left[i]-1 );
    }

    // Find the best axis to split on
    uint8 axisEven;
    if( cost[0] < cost[2] ) {
        axisEven = (cost[0] < cost[4]) ? 0 : 4;
    } else {
        axisEven = (cost[2] < cost[4]) ? 2 : 4;
    }

	uint8 axisOdd;
    if( cost[1] < cost[3] ) {
        axisOdd = (cost[1] < cost[5]) ? 1 : 5;
    } else {
        axisOdd = (cost[3] < cost[5]) ? 3 : 5;
    }

	if( cost[axisEven] < cost[axisOdd] ) {
		splitIndex = last_left[axisEven];
		splitCost = cost[axisEven];
		return axisEven;
	} else {
		splitIndex = last_left[axisOdd];
		splitCost = cost[axisOdd];
		return axisOdd;
	}
}

size_t BVHNode::FindSplittingPlane( std::vector<BBoxAA*>& sorted ) {
    assert( sorted.size() >= 2 );

    BBoxAA left, right;
    left.SetMin( sorted.front()->GetMin() );
    right.SetMax( sorted.back()->GetMax() );
    float min_cost = FLT_MAX;
	size_t splitIndex = 0;

    // If the input is large, we want to skip some computations
	int numLeft = 1;
	int numRight = sorted.size()-1;

    // For all possible split points, compute the cost; finding the minimum
	for( size_t i=0; i<sorted.size()-1; i++ ) {
        left.SetMax(  sorted[i]->GetMax() );
        right.SetMin( sorted[i+1]->GetMin() );

        // We do not need to minimize the actual cost, just the left/right local costs
        const float cost = left.GetSurfaceArea() * (numLeft++) + right.GetSurfaceArea() * (numRight--);
        if( cost < min_cost ) {
            min_cost = cost;
            splitIndex = i;
        }
    }

    return splitIndex;
}

float BVHNode::Cost(float boxCost, float objCost, float areaParent, float areaLeft, float areaRight, int numLeft, int numRight) {
    const float normalize = 1.0f / areaParent;

    // Probability of hitting each section times how costly it is to hit that section
    return boxCost + normalize * ( objCost * (areaLeft*numLeft + areaRight*numRight) );
}

void BVH::PreCalc() {
	// TODO: Only create BVH on the fly from config file instead of having it as a part of the scene
	boxCost_ = options::global::bvh_box_cost;
	objCost_ = options::global::bvh_obj_cost;

    Rebuild(objects_);
}

void BVH::RenderGL() {
	if( !options::global::gl_render_bbox || objects_->size() < 1 )
		return;
 
	root_.RenderGL( Vector3( 0.0f, 1.0f, 0.0f ) );
}

void BVHNode::RenderGL(const Vector3& color) {

    const Vector3 p1( box[0].x, box[0].y, box[0].z );
    const Vector3 p2( box[0].x, box[1].y, box[0].z );
    const Vector3 p3( box[1].x, box[1].y, box[0].z );
    const Vector3 p4( box[1].x, box[0].y, box[0].z );

    const Vector3 p5( box[0].x, box[0].y, box[1].z );
    const Vector3 p6( box[0].x, box[1].y, box[1].z );
    const Vector3 p7( box[1].x, box[1].y, box[1].z );
    const Vector3 p8( box[1].x, box[0].y, box[1].z );

	glBegin( GL_QUADS );
	glColor3f( color.x, color.y, color.z );

    // Back plane
    glVertex3f( p1.x, p1.y, p1.z );
    glVertex3f( p2.x, p2.y, p2.z );
    glVertex3f( p3.x, p3.y, p3.z );
    glVertex3f( p4.x, p4.y, p4.z );

    // Front plane
    glVertex3f( p5.x, p5.y, p5.z );
    glVertex3f( p8.x, p8.y, p8.z );
    glVertex3f( p7.x, p7.y, p7.z );
    glVertex3f( p6.x, p6.y, p6.z );

    // Bottom plane
    glVertex3f( p1.x, p1.y, p1.z );
    glVertex3f( p4.x, p4.y, p4.z );
    glVertex3f( p8.x, p8.y, p8.z );
    glVertex3f( p5.x, p5.y, p5.z );

    // Top plane
    glVertex3f( p2.x, p2.y, p2.z );
    glVertex3f( p6.x, p6.y, p6.z );
    glVertex3f( p7.x, p7.y, p7.z );
    glVertex3f( p3.x, p3.y, p3.z );

    // Right plane
    glVertex3f( p7.x, p7.y, p7.z );
    glVertex3f( p8.x, p8.y, p8.z );
    glVertex3f( p4.x, p4.y, p4.z );
    glVertex3f( p3.x, p3.y, p3.z );

    // Left plane
    glVertex3f( p1.x, p1.y, p1.z );
    glVertex3f( p5.x, p5.y, p5.z );
    glVertex3f( p6.x, p6.y, p6.z );
    glVertex3f( p2.x, p2.y, p2.z );

	glEnd();

	// Render children
	if( type != SPLIT_NODE ) {
		const Vector3 newColor( 0.9 * color );
		children[0].RenderGL( newColor );
		children[1].RenderGL( newColor );
	}
}

bool BVHNode::Hit(const Ray& ray, float minDistance, float maxDistance) const {
    if( type != SPLIT_NODE ) {
        return leaf->Hit(ray, minDistance, maxDistance);
    } else {
		if( !box.Hit(ray, minDistance, maxDistance) )
			return false;
		
		HitInfo hit;
		hit.eyeRay = ray;
		
		// TODO: Fix problem where using Hit() will cause all false
		//bool intersect0 = children[0].Intersect(hit, minDistance, maxDistance);
		//bool intersect1 = children[1].Intersect(hit, minDistance, maxDistance);
		//bool hit0 = children[0].Hit(ray, minDistance, maxDistance);
		//bool hit1 = children[1].Hit(ray, minDistance, maxDistance);

		//if( intersect0 != hit0 ) {
		//	children[0].Intersect(hit, minDistance, maxDistance);
		//	children[0].Hit(ray, minDistance, maxDistance);
		//}

		//if( intersect1 != hit1 ) {
		//	children[1].Intersect(hit, minDistance, maxDistance);
		//	children[1].Hit(ray, minDistance, maxDistance);
		//}

		return ( children[0].Intersect(hit, minDistance, maxDistance) || children[1].Intersect(hit, minDistance, maxDistance) );
    }
}

bool BVHNode::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
    if( type != SPLIT_NODE ) {
        return leaf->Intersect(hit, minDistance, maxDistance);
    } else {
		if( !box.Hit(hit.eyeRay, minDistance, maxDistance) ) {
			return false;
		}

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
            if( children[1].Intersect(hit, minDistance, maxDistance) )
				return true;
			return false;
        }
    }
}

void BVHNode::IntersectPack(HitPack& hitpack, float minDistance, float maxDistance) {
	for( int i=0; i<4; ++i ) {
		hitpack.hit_result[i] = Intersect( hitpack.hits[i], minDistance, maxDistance );
	}

	// TODO: Write raypack intersection

    //HitPack tempHitpack = hitpack;

    //tempHitpack.hits[0].distance = MAX_DISTANCE;
    //tempHitpack.hits[1].distance = MAX_DISTANCE;
    //tempHitpack.hits[2].distance = MAX_DISTANCE;
    //tempHitpack.hits[3].distance = MAX_DISTANCE;

    //for( size_t i=0; i< objects_->size(); ++i ) {
    //    (*objects_)[i]->IntersectPack( tempHitpack, minDistance, maxDistance );

    //    if( tempHitpack.hit_result[0] && tempHitpack.hits[0].distance < hitpack.hits[0].distance ) {
    //        hitpack.hits[0] = tempHitpack.hits[0];
    //        hitpack.hit_result[0] = tempHitpack.hit_result[0];
    //    }

    //    if( tempHitpack.hit_result[1] && tempHitpack.hits[1].distance < hitpack.hits[1].distance ) {
    //        hitpack.hits[1] = tempHitpack.hits[1];
    //        hitpack.hit_result[1] = tempHitpack.hit_result[1];
    //    }

    //    if( tempHitpack.hit_result[2] && tempHitpack.hits[2].distance < hitpack.hits[2].distance ) {
    //        hitpack.hits[2] = tempHitpack.hits[2];
    //        hitpack.hit_result[2] = tempHitpack.hit_result[2];
    //    }

    //    if( tempHitpack.hit_result[3] && tempHitpack.hits[3].distance < hitpack.hits[3].distance ) {
    //        hitpack.hits[3] = tempHitpack.hits[3];
    //        hitpack.hit_result[3] = tempHitpack.hit_result[3];
    //    }
    //}

    return;
}

void BVH::IntersectPack(HitPack& hitpack, float minDistance, float maxDistance) {
	return root_.IntersectPack(hitpack, minDistance, maxDistance);
}

bool BVH::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
    return root_.Intersect(hit, minDistance, maxDistance);
}

bool BVH::Hit(const Ray& ray, float minDistance, float maxDistance) const {
	return root_.Hit(ray, minDistance, maxDistance);
}

} // namespace rawray
