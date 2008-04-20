/////////////////////////////////////////////////////////////////////////////
// triangle_barycentric.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "triangle_barycentric.h"
#include "math/tuple3.h"
#include "material.h"

namespace rawray {

void TriangleBarycentric::PreCalc() { }

// Ray-Plane intersection with barycentric coordinate test
// See: Fundamentals of Computer Graphics, Peter Shirley p206
// Moller test with the determinants computed out by hand
bool TriangleBarycentric::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
	const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];

    // Manually compute determinants to avoid redundant calculations
    // See Moller intersection for cleaner (slower) code which does the same test
    const float a = v0.x - v1.x;
    const float b = v0.y - v1.y;
    const float c = v0.z - v1.z;
    const float d = v0.x - v2.x;
    const float e = v0.y - v2.y;
    const float f = v0.z - v2.z;
	//			g = -ray.direction.x
	//			h = -ray.direction.y
	//			i = -ray.direction.z
    const float j = v0.x - ray.origin.x;
    const float k = v0.y - ray.origin.y;
    const float l = v0.z - ray.origin.z;

    const float ei_minus_hf = ray.direction.y*f - e*ray.direction.z;
    const float gf_minus_di = d*ray.direction.z - ray.direction.x*f;
    const float dh_minus_eg = e*ray.direction.x - d*ray.direction.y;
    const float ak_minus_jb = a*k - j*b;
    const float jc_minux_al = j*c - a*l;
    const float bl_minux_kc = b*l - k*c;

    // NOTE: We will allow division by zero which will give us infinity and fail the distance test
    const float inv_den = 1.0f / (a*ei_minus_hf + b*gf_minus_di + c*dh_minus_eg);
    const float t = (f*ak_minus_jb + e*jc_minux_al + d*bl_minux_kc) * inv_den ;
    if( t < minDistance || t > maxDistance ) return false;

    const float gamma = (-ray.direction.z*ak_minus_jb - ray.direction.y*jc_minux_al - ray.direction.x*bl_minux_kc) * inv_den;
    if( gamma < 0.0f || gamma > 1.0f ) return false;

    const float beta = (j*ei_minus_hf + k*gf_minus_di + l*dh_minus_eg) * inv_den;
    if( beta < 0.0f || beta + gamma > 1.0f ) return false;

    hit.point = ray.origin + t * ray.direction;
    hit.distance = t;
    hit.material = material_;
    Interpolate(hit, 1-beta-gamma, beta, gamma);

    return true;
}

} // namespace rayray
