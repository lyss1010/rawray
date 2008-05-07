/////////////////////////////////////////////////////////////////////////////
// bvh.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "bvh.h"
#include "bbox_aa.h"
#include "float.h"

namespace rawray {

BVH::~BVH() {
	ClearForest();
}

void BVH::ClearForest() {
	for( std::vector<BBoxAA*>::iterator iter = forest_.begin(); iter != forest_.end(); ++iter ) {
		BBoxAA* box = (*iter);
		box->deleteObject();
	}
	forest_.clear();
}

void BVH::Rebuild(std::vector<Object*>* objects) {
    // Create a forest of bounding boxes around all objects
    std::cout << "Creating BVH of " << objects->size() << " objects" << std::endl;

	ClearForest();
    for( std::vector<Object*>::iterator iter = objects->begin(); iter != objects->end(); ++iter )
        forest_.push_back( BBoxAA::newBBoxAA( (*iter) ) );

    root_.BuildBVH( forest_ );

    std::cout << "Done creating BVH of " << objects->size() << "objects" << std::endl;
}

void BVHNode::BuildBVH( std::vector<BBoxAA*>& forest ) {
    // If there is only 1 box, we can not split it further
    if( forest.size() == 1 ) {
        isLeaf = true;
        leaf = forest[0];
		box.SetBounds( leaf->GetMin(), leaf->GetMax() );

        return;
    }

    // We must split into left and right bounding volumes
    isLeaf = false;
    children = new BVHNode[2];

    // Create sorted forests
    std::vector<BBoxAA*> sorted[6] = { 
        std::vector<BBoxAA*>( forest.begin(), forest.end() ), 
        std::vector<BBoxAA*>( forest.begin(), forest.end() ), 
        std::vector<BBoxAA*>( forest.begin(), forest.end() ),
        std::vector<BBoxAA*>( forest.begin(), forest.end() ), 
        std::vector<BBoxAA*>( forest.begin(), forest.end() ), 
        std::vector<BBoxAA*>( forest.begin(), forest.end() )
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
    int8 axis = Split( splitIndex, sorted );
    assert( axis >= 0 );

	// The left forest will contain the split index and all before it
	std::vector<BBoxAA*>::iterator split = sorted[axis].begin() + splitIndex + 1;

	// Split forest into left and right sections
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
        float size_left  = BoxAA::SurfaceArea( leftVolume[1] - leftVolume[0] );
        float size_right = BoxAA::SurfaceArea( rightVolume[1] - rightVolume[0] );

        // Compute the cost of the bounding volumes of this split
        cost[i] = Cost( size_left, size_right, last_left[i]+1, forest.size()-last_left[i]-1 );
    }

    // Find the best axis to split on
    uint8 axis;
    if( cost[0] < cost[1] ) {
        axis = (cost[0] < cost[2]) ? 0 : 2;
    } else {
        axis = (cost[1] < cost[2]) ? 1 : 2;
    }

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
	int numLeft = 1;
	int numRight = sorted.size()-1;
	for( size_t i=0; i<sorted.size()-1; ++i ) {
        left.SetMax(  sorted[i]->GetMax() );
        right.SetMin( sorted[i+1]->GetMin() );

        float cost = Cost( left.GetSurfaceArea(), right.GetSurfaceArea(), numLeft++, numRight-- );
        if( cost < min_cost ) {
            min_cost = cost;
            splitIndex = i;
        }
    }

    return splitIndex;
}

float BVHNode::Cost(float areaLeft, float areaRight, int numLeft, int numRight) {
    return (numLeft * areaLeft) + (numRight * areaRight);
}

void BVH::PreCalc() {
    Rebuild(objects_);
}

void BVH::RenderGL() {
	if( !options::global::gl_render_bbox )
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
	if( !isLeaf ) {
		const Vector3 newColor( 0.9 * color );
		children[0].RenderGL( newColor );
		children[1].RenderGL( newColor );
	}
}

bool BVHNode::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
    if( isLeaf ) {
        return leaf->Intersect(hit, minDistance, maxDistance);
    } else {
		if( !box.Intersect(hit, minDistance, maxDistance) )
			return false;

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

} // namespace rawray
