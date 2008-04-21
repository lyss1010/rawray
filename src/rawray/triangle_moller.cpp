/////////////////////////////////////////////////////////////////////////////
// triangle_moller.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "triangle_moller.h"
#include "math/tuple3.h"
#include "material.h"

namespace rawray {

void TriangleMoller::PreCalc() {
    const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];

    math::Cross(v2 - v0, v1 - v0, n_);
}

// Moller triangle intersection test
// See: http://ompf.org/forum/viewtopic.php?t=165
// See: Fundamentals of Computer Graphics, Peter Shirley p206
bool TriangleMoller::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
	const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];

	const Vector3& b = v1 - v0;
	const Vector3& c = v2 - v0;
    const Vector3& o = ray.origin - v0;

    // Solve 3x3 linear system using Cramer's rule
    // NOTE: We will allow division by zero which will get us an infinite direction
    const float neg_inv_det = -1.0f / n_.Dot(ray.direction);
    const float t = n_.Dot(o) * neg_inv_det;
    if( t < minDistance || t > maxDistance ) return false;

    Vector3 v; math::Cross(o,c,v);

    const float beta = v.Dot(ray.direction) * neg_inv_det;
    if( beta < 0.0f ) return false;

    math::Cross(b,o,v);
    const float gamma = v.Dot(ray.direction) * neg_inv_det;
    if( gamma < 0.0f || beta+gamma > 1.0f ) return false;

    hit.distance = t;
    hit.material = material_;
    hit.point = ray.origin + ray.direction * t;
    Interpolate(hit, 1-beta-gamma, beta, gamma);

    return true;
}

} // namespace rayray
