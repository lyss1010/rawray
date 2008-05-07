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
bool BoxAA::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
    const Ray& r = hit.eyeRay;
    float tmin, tmax, tymin, tymax, tzmin, tzmax;

	tmin  = (bounds_[ r.sign[0]   ].x - r.origin.x) * r.inv_direction.x;
	tmax  = (bounds_[ 1-r.sign[0] ].x - r.origin.x) * r.inv_direction.x;
	tymin = (bounds_[ r.sign[1]   ].y - r.origin.y) * r.inv_direction.y;
	tymax = (bounds_[ 1-r.sign[1] ].y - r.origin.y) * r.inv_direction.y;

	if ( (tmin > tymax) || (tymin > tmax) )
		return false;

	if (tymin > tmin) tmin = tymin;
	if (tymax < tmax) tmax = tymax;

	tzmin = (bounds_[ r.sign[2]   ].z - r.origin.z) * r.inv_direction.z;
	tzmax = (bounds_[ 1-r.sign[2] ].z - r.origin.z) * r.inv_direction.z;

	if ( (tmin > tzmax) || (tzmin > tmax) )
		return false;

	if (tzmin > tmin) tmin = tzmin;
	if (tzmax < tmax) tmax = tzmax;
	
	return ( (tmin > minDistance) && (tmax < maxDistance) );
}

bool BBoxAA::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
	if( box_.Intersect(hit, minDistance, maxDistance) )
		return child_->Intersect(hit, minDistance, maxDistance);

	return false;
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

} // namespace rawray
