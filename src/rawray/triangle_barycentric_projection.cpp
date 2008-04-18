/////////////////////////////////////////////////////////////////////////////
// triangle_barycentric_projection.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "triangle_barycentric_projection.h"
#include "math/tuple3.h"
#include "material.h"

namespace rawray {

void TriangleBarycentricProjection::PreCalc() {
    const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];

    b_ = v2 - v0;
    c_ = v1 - v0;
    n_ = math::Cross(b_, c_);

	const float absNX = fabs(n_.x);
    const float absNY = fabs(n_.y);
    const float absNZ = fabs(n_.z);

    // Determine dominant axis:  0=x, 1=y, 2=z
    if( absNX > absNY )
        axis_ = (absNX > absNZ) ? 0 : 2;
    else
        axis_ = (absNY > absNZ) ? 1 : 2;

	// The two non-dominant axis we will use
	u_ = (axis_ + 1)%3;
    v_ = (axis_ + 2)%3;

    // Calculate determinant of 2d projection
	det2d_ = b_[u_] * c_[v_] - b_[v_] * c_[u_];
	det2d_ = math::FloatZero( det2d_, options::epsilon ) ? 0.0f : (1.0f / det2d_);
}

// Optimized Barycentric 2d projection test
// See: http://www.mpi-inf.mpg.de/~wald/PhD/wald_phd.pdf p91
bool TriangleBarycentricProjection::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
	if( det2d_ == 0.0f ) return false;

    // See if we are exactly lined up with the plane (or a back face of a triangle)
    const float denominator = math::Dot( ray.direction, n_ );
    if( denominator == 0.0f ) return false;

    // Compute distance to the plane along the ray
	const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const float t = -math::Dot( ray.origin-v0, n_ ) / denominator;
    if( t < minDistance || t > maxDistance ) return false;

    // Compute the point on the plane where we intersect minus the first vertex
    hit.point = (ray.direction * t) + ray.origin;
    
    // Compute the 2d determinant get barycentric coordinates
    const float hv = (hit.point[v_] - v0[v_]);
    const float hu = (hit.point[u_] - v0[u_]);
    const float beta = (hv * b_[u_] - hu * b_[v_]) * det2d_;
    if( beta < 0.0f ) return false;

    const float gamma = (hu * c_[v_] - hv * c_[u_]) * det2d_;
    if( gamma < 0.0f ) return false;
    if( beta+gamma > 1.0f ) return false;

    hit.distance = t;
    hit.material = material_;
    Interpolate(hit, 1-beta-gamma, beta, gamma);
    
    return true;
}

} // namespace rayray
