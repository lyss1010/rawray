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
    
    // Edge A corresponds to the edge opposite of vertex A (v0)
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
    float dirA = pluckA_.GetOrientation( pluckRay );
    float dirB = pluckB_.GetOrientation( pluckRay );
    float dirC = pluckC_.GetOrientation( pluckRay );

	// We treat hits on the exact edge as misses
	if( dirA == 0.0f || dirB == 0.0f || dirC == 0.0f )
		return false;

	// Make sure all orientations are the same direction
	if( dirA < 0.0f ) {
		if( dirB > 0.0f || dirC > 0.0f )
			return false;
	} else {
		if( dirB < 0.0f || dirC < 0.0f )
			return false;
	}

    // Our orientations are also unnormalized barycentric coordinates
    const float norm = 1.0f / (dirA + dirB + dirC);
    const float alpha = dirA*norm;
    const float beta = dirB*norm;
    const float gamma = dirC*norm;

    // Compute the hit point by interpolation based by our barycentric coords
    const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    hit.point = alpha*mesh_.GetVertices()[ vertexIndices.x ] + 
                beta*mesh_.GetVertices()[ vertexIndices.y ] + 
                gamma*mesh_.GetVertices()[ vertexIndices.z ];

    hit.distance = (hit.point - ray.origin).Length();
    if( hit.distance < minDistance || hit.distance > maxDistance )
        return false;

    hit.material = material_;
    Interpolate(hit, alpha, beta, gamma);

    return true;
}

} // namespace rayray