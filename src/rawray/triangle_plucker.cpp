/////////////////////////////////////////////////////////////////////////////
// triangle_plucker.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "triangle_plucker.h"
#include "math/tuple3.h"
#include "material.h"

namespace rawray {

void TrianglePlucker::PreCalc() {
    const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];
    
    // Compute the plucker coords of the 3 lines representing edges
    pluckA_ = PluckerCoord( v2-v1, v1 );
    pluckB_ = PluckerCoord( v0-v2, v2 );
    pluckC_ = PluckerCoord( v1-v0, v0 );
}

// Plucker coordinate triangle intersection test
// See: http://tog.acm.org/resources/RTNews/html/rtnv10n3.html#art11
// See: http://tog.acm.org/resources/RTNews/html/rtnv11n1.html#art3
// See: http://www.flipcode.com/archives/Plcker_Coordinates_for_the_Rest_of_Us-Part_4_Applications.shtml
bool TrianglePlucker::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    PluckerCoord pluckRay( ray.direction, ray.origin );
    
    const float dirA = pluckA_.GetOrientation( pluckRay );
    const float dirB = pluckB_.GetOrientation( pluckRay );
    float dirC;

    // Favor larger code for less redundant operations
    // Perform directionality tests as soon as possible and only if nesecary
    // We will assume a dir == 0 is the same as dir > 0
    if( dirA >= 0.0f ) { 
        // Orientations must be positive
        if( dirB < 0.0f ) return false;

        dirC = pluckC_.GetOrientation( pluckRay );
        if( dirC < 0.0f ) return false;

    } else if( dirA < 0.0f ) { 
        // Orientations must be negative
        if( dirB >= 0.0f ) return false;

        dirC = pluckC_.GetOrientation( pluckRay );
        if( dirC >= 0.0f ) return false;
    }
    
    // Our orientations are also unnormalized barycentric coordinates
    const float norm = 1.0f / (dirA + dirB + dirC);
    const float alpha = dirA * norm;
    const float beta =  dirB * norm;
    const float gamma = dirC * norm;

    // Compute the hit point by interpolation based by our barycentric coords
    const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    hit.point = alpha * mesh_.GetVertices()[ vertexIndices.x ] + 
                beta  * mesh_.GetVertices()[ vertexIndices.y ] + 
                gamma * mesh_.GetVertices()[ vertexIndices.z ];

    // Assuming ray.direction is normalized, dot prodcut will give us length of (hit.point - ray.origin)
    hit.distance = math::Dot( (hit.point - ray.origin), ray.direction );
    if( hit.distance < minDistance || hit.distance > maxDistance )
        return false;

    hit.material = material_;
    Interpolate(hit, alpha, beta, gamma);

    return true;
}

} // namespace rayray
