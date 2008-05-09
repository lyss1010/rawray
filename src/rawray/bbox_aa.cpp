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


/*      Amy Williams, Steve Barrus, R. Keith Morley, and Peter Shirley
 *      "An Efficient and Robust Ray-Box Intersection Algorithm"
 */
bool BoxAA::Hit(const Ray& ray, float minDistance, float maxDistance) const {
	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	tmin  = (bounds_[ ray.sign[0]   ].x - ray.origin.x) * ray.inv_direction.x;
	tmax  = (bounds_[ 1-ray.sign[0] ].x - ray.origin.x) * ray.inv_direction.x;
	tymin = (bounds_[ ray.sign[1]   ].y - ray.origin.y) * ray.inv_direction.y;
	tymax = (bounds_[ 1-ray.sign[1] ].y - ray.origin.y) * ray.inv_direction.y;

	if ( (tmin > tymax) || (tymin > tmax) )
		return false;

	if (tymin > tmin) tmin = tymin;
	if (tymax < tmax) tmax = tymax;

	tzmin = (bounds_[ ray.sign[2]   ].z - ray.origin.z) * ray.inv_direction.z;
	tzmax = (bounds_[ 1-ray.sign[2] ].z - ray.origin.z) * ray.inv_direction.z;

	if ( (tmin > tzmax) || (tzmin > tmax) )
		return false;

	if (tzmin > tmin) tmin = tzmin;
	if (tzmax < tmax) tmax = tzmax;
	
	// If either is true we have a valid hit, if we required both to be true we would
	// miss intersections where the camera starts out inside the box
	return ( (tmin > minDistance) || (tmax < maxDistance) );
}

bool BBoxAA::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
	if( box_.Hit(hit.eyeRay, minDistance, maxDistance) )
		return child_->Intersect(hit, minDistance, maxDistance);

	return false;
}

bool BBoxAA::Hit(const Ray& ray, float minDistance, float maxDistance) const {
	return box_.Hit( ray, minDistance, maxDistance );
}

float BoxAA::SurfaceArea(const Vector3& size) {
    //           2 * ( height*width  + length*width  + height*length )
    return fabs( 2 * ( size.y*size.z + size.x*size.z + size.y*size.x ) );
}

float BoxAA::Volume(const Vector3& size) {
    //           length * width  * height
    return fabs( size.x * size.y * size.z );
}

float BBoxAA::GetSurfaceArea() {
	return BoxAA::SurfaceArea( box_[1] - box_[0] );
}

float BBoxAA::GetVolume() {
    return BoxAA::Volume( box_[1] - box_[0] );
}


namespace BBoxAA_Alg {
    bool min_lt_x(BBoxAA* a, BBoxAA* b) { return a->GetMin().x < b->GetMin().x; }
    bool min_lt_y(BBoxAA* a, BBoxAA* b) { return a->GetMin().y < b->GetMin().y; }
    bool min_lt_z(BBoxAA* a, BBoxAA* b) { return a->GetMin().z < b->GetMin().z; }
    bool max_lt_x(BBoxAA* a, BBoxAA* b) { return a->GetMax().x < b->GetMax().x; }
    bool max_lt_y(BBoxAA* a, BBoxAA* b) { return a->GetMax().y < b->GetMax().y; }
    bool max_lt_z(BBoxAA* a, BBoxAA* b) { return a->GetMax().z < b->GetMax().z; }
    bool mid_lt_x(BBoxAA* a, BBoxAA* b) { return a->GetMid().x < b->GetMid().x; }
    bool mid_lt_y(BBoxAA* a, BBoxAA* b) { return a->GetMid().y < b->GetMid().y; }
    bool mid_lt_z(BBoxAA* a, BBoxAA* b) { return a->GetMid().z < b->GetMid().z; }
} // namespace BBoxAA_Alg


} // namespace rawray
