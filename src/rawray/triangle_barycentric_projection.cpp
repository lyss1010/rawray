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

    const Vector3& b = v2 - v0;
    const Vector3& c = v1 - v0;

    n_ = math::Cross(b, c);

    // denominator = b[u] * c[v] - b[v] * c[u];
    // .x = x component removed, .y = y component removed etc...
    det2d_.x = (b.y)*(c.z) - (b.z)*(c.y);
	det2d_.y = (b.z)*(c.x) - (b.x)*(c.z);
	det2d_.z = (b.x)*(c.y) - (b.y)*(c.x);

    det2d_.x = math::FloatZero(det2d_.x, options::epsilon) ? 0.0f : 1.0f / det2d_.x;
    det2d_.y = math::FloatZero(det2d_.y, options::epsilon) ? 0.0f : 1.0f / det2d_.y;
    det2d_.z = math::FloatZero(det2d_.z, options::epsilon) ? 0.0f : 1.0f / det2d_.z;
}

// Optimized Barycentric 2d projection test
// See: http://www.mpi-inf.mpg.de/~wald/PhD/wald_phd.pdf p91
bool TriangleBarycentricProjection::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
	const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];

	// Edges of triangle
    const Vector3& b = v2 - v0;
    const Vector3& c = v1 - v0;

    // See if we are exactly lined up with the plane (or a back face of a triangle)
    register float denominator = math::Dot( ray.direction, n_ );
    if( denominator == 0.0f ) return false;

    // Compute distance to the plane along the ray
    const float t = -math::Dot( ray.origin-v0, n_ ) / denominator;
    if( t < minDistance || t > maxDistance ) return false;

    const float absNX = fabs(n_.x);
    const float absNY = fabs(n_.y);
    const float absNZ = fabs(n_.z);

    // Determine dominant axis
    uint8 axis; // 0=x, 1=y, 2=z
    if( absNX > absNY )
        axis = (absNX > absNZ) ? 0 : 2;
    else
        axis = (absNY > absNZ) ? 1 : 2;

    // Grab the precomputed inverse determinant based on which axis we're on
    if( det2d_[axis] == 0.0f ) return false;
    const uint8 u = (axis+1)%3;
    const uint8 v = (axis+2)%3;

    // Compute the point on the plane where we intersect minus the first vertex
    hit.point = (ray.direction * t) + ray.origin;
    
    // Compute the 2d determinant get barycentric coordinates
    const float hv = (hit.point[v]-v0[v]);
    const float hu = (hit.point[u]-v0[u]);
    const float beta = (hv * b[u] - hu * b[v]) * det2d_[axis];
    if( beta < 0.0f ) return false;

    const float gamma = (hu * c[v] - hv * c[u]) * det2d_[axis];
    if( gamma < 0.0f ) return false;
    if( beta+gamma > 1.0f ) return false;

    hit.distance = t;
    hit.material = material_;
    Interpolate(hit, 1-beta-gamma, beta, gamma);
    
    return true;
}

} // namespace rayray
