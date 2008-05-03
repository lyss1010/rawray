/////////////////////////////////////////////////////////////////////////////
// bbox_aa.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "bbox_aa.h"
#include "material.h"
#include "ray.h"
#include <new>

namespace rawray {

BBoxAA* BBoxAA::newBBoxAA() {
    uint8* memory = static_cast<uint8*>(
        _aligned_malloc( sizeof(BBoxAA), ALIGNMENT ));

    if( !memory ) return NULL;

    // Call constructor with placement new
    return new (memory) BBoxAA();
}

BBoxAA* BBoxAA::newBBoxAA(Object* child) {
    uint8* memory = static_cast<uint8*>(
        _aligned_malloc( sizeof(BBoxAA), ALIGNMENT ));

    if( !memory ) return NULL;

    // Call constructor with placement new
    return new (memory) BBoxAA(child);
}

BBoxAA* BBoxAA::newBBoxAA(const Vector3& min, const Vector3& max) {
    uint8* memory = static_cast<uint8*>(
        _aligned_malloc( sizeof(BBoxAA), ALIGNMENT ));

    if( !memory ) return NULL;

    // Call constructor with placement new
    return new (memory) BBoxAA(min, max);
}

void BBoxAA::deleteObject() {
	this->~BBoxAA();
	_aligned_free( this );
}


void BBoxAA::IntersectPack(HitPack& hitpack, float minDistance, float maxDistance) {
    hitpack.hit_result[0] = Intersect( hitpack.hits[0], minDistance, maxDistance );
    hitpack.hit_result[1] = Intersect( hitpack.hits[1], minDistance, maxDistance );
    hitpack.hit_result[2] = Intersect( hitpack.hits[2], minDistance, maxDistance );
    hitpack.hit_result[3] = Intersect( hitpack.hits[3], minDistance, maxDistance );
}



/*
 * Ray class, for use with the optimized ray-box intersection test
 * described in:
 *
 *      Amy Williams, Steve Barrus, R. Keith Morley, and Peter Shirley
 *      "An Efficient and Robust Ray-Box Intersection Algorithm"
 *      Journal of graphics tools, 10(1):49-54, 2005
 * 
 */
bool BBoxAA::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
    float txmin, txmax, tymin, tymax, tzmin, tzmax;
    const Ray& r = hit.eyeRay;

    txmin = ( bounds_[     r.sign[0] ].x - r.origin.x ) * r.inv_direction.x;
    txmax = ( bounds_[ 1 - r.sign[0] ].x - r.origin.x ) * r.inv_direction.x;

    tymin = ( bounds_[     r.sign[1] ].y - r.origin.y ) * r.inv_direction.y;
    tymax = ( bounds_[ 1 - r.sign[1] ].y - r.origin.y ) * r.inv_direction.y;

    if( (txmin > tymax) || (tymin > txmax) )
        return false;

    // Compute the 'real' min/max values of both x&y combined
    if( tymax > txmin )
        txmin = tymin;
    if( tymax < txmax )
        txmax = tymax;

    tzmin = ( bounds_[     r.sign[2] ].z - r.origin.z ) * r.inv_direction.z;
    tzmax = ( bounds_[ 1 - r.sign[2] ].z - r.origin.z ) * r.inv_direction.z;

    if( (txmin > tzmax) || (tzmin > txmax) )
        return false;

    // Compute the 'real' min/max values of x&y&z combined
    if( tzmin > txmin )
        txmin = tzmin;
    if( tzmax < txmax )
        txmax = tzmax;

    if( txmin > maxDistance || txmax < minDistance )
        return false;

    // We had a hit with the box, intersect with our child
    return child_->Intersect( hit, minDistance, maxDistance );
}

float BBoxAA::GetSurfaceArea() {
    const float l = bounds_[1].x - bounds_[0].x;
    const float h = bounds_[1].y - bounds_[0].y;
    const float w = bounds_[1].z - bounds_[0].z;

    return 2*h*w + 2*l*w + 2*h*l;
}

float BBoxAA::GetVolume() {
    const float l = bounds_[1].x - bounds_[0].x;
    const float h = bounds_[1].y - bounds_[0].y;
    const float w = bounds_[1].z - bounds_[0].z;

    return l*w*h;
}

} // namespace rawray
