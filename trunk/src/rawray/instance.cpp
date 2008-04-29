/////////////////////////////////////////////////////////////////////////////
// bbox_aa.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "bbox_aa.h"
#include "material.h"
#include "ray.h"
#include <new>

namespace rawray {

BBoxAA* BBoxAA::newBBoxAA(Material* material) {
    uint8* memory = static_cast<uint8*>(
        _aligned_malloc( sizeof(BBoxAA), ALIGNMENT ));

    if( !memory ) return NULL;

    // Call constructor with placement new
    return new (memory) BBoxAA(material);
}

BBoxAA* BBoxAA::newBBoxAA(Material* material, const Vector3& min, const Vector3& max) {
    uint8* memory = static_cast<uint8*>(
        _aligned_malloc( sizeof(BBoxAA), ALIGNMENT ));

    if( !memory ) return NULL;

    // Call constructor with placement new
    return new (memory) BBoxAA(material, min, max);
}

void BBoxAA::deleteObject() {
	this->~BBoxAA();
	_aligned_free( this );
}

void BBoxAA::RenderGL() {
    if( !options::global::gl_render_bbox )
        return;

    const Vector3& color = material_ ? material_->BaseColor() : Vector3(1);

    const Vector3 p1( bounds_[0].x, bounds_[0].y, bounds_[0].z );
    const Vector3 p2( bounds_[0].x, bounds_[1].y, bounds_[0].z );
    const Vector3 p3( bounds_[1].x, bounds_[1].y, bounds_[0].z );
    const Vector3 p4( bounds_[1].x, bounds_[0].y, bounds_[0].z );

    const Vector3 p5( bounds_[0].x, bounds_[0].y, bounds_[1].z );
    const Vector3 p6( bounds_[0].x, bounds_[1].y, bounds_[1].z );
    const Vector3 p7( bounds_[1].x, bounds_[1].y, bounds_[1].z );
    const Vector3 p8( bounds_[1].x, bounds_[0].y, bounds_[1].z );

    // Draw the bounding box
    glBegin(GL_QUADS);
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
}

void BBoxAA::PreCalc() {
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

    // We had a hit with the box, intersect with all elements inside
    uint32 numHits = 0;
    HitInfo tempHit = hit;
    
    hit.distance = MAX_DISTANCE;
    tempHit.distance = MAX_DISTANCE;
    for (size_t i = 0; i < objects_.size(); ++i)
    {
        if( objects_[i]->Intersect( tempHit, minDistance, maxDistance) ) {
            ++numHits;
            if( tempHit.distance < hit.distance )
                hit = tempHit;
        }
    }
    
    return numHits > 0;
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
