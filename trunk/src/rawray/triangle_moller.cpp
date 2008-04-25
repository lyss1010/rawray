/////////////////////////////////////////////////////////////////////////////
// triangle_moller.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "triangle_moller.h"
#include "math/tuple3.h"
#include "material.h"
#include <xmmintrin.h>

namespace rawray {

void TriangleMoller::PreCalc() {
    const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];

    math::Cross(v2 - v0, v1 - v0, n_);
}

//
//// SSE Enhanced intersection of 4x rays simultaneously
//#ifdef SSE
//void TriangleMoller::IntersectPack(HitPack& hitpack, float minDistance, float maxDistance) {
//    const HitInfo& hit1 = hitpack.hits[0];
//    const HitInfo& hit2 = hitpack.hits[1];
//    const HitInfo& hit3 = hitpack.hits[2];
//    const HitInfo& hit4 = hitpack.hits[3];
//
//    __m128 ray_dir_x, ray_dir_y, ray_dir_z;
//    ray_dir_x.m128_f32[0] = hit1.eyeRay.direction.x;
//    ray_dir_x.m128_f32[1] = hitpack.hits[1].eyeRay.direction.x;
//    ray_dir_x.m128_f32[2] = hitpack.hits[2].eyeRay.direction.x;
//    ray_dir_x.m128_f32[3] = hitpack.hits[3].eyeRay.direction.x;
//
//    ray_dir_y.m128_f32[0] = hit1.eyeRay.direction.y;
//    ray_dir_y.m128_f32[1] = hitpack.hits[1].eyeRay.direction.y;
//    ray_dir_y.m128_f32[2] = hitpack.hits[2].eyeRay.direction.y;
//    ray_dir_y.m128_f32[3] = hitpack.hits[3].eyeRay.direction.y;
//
//    ray_dir_z.m128_f32[0] = hit1.eyeRay.direction.z;
//    ray_dir_z.m128_f32[1] = hitpack.hits[1].eyeRay.direction.z;
//    ray_dir_z.m128_f32[2] = hitpack.hits[2].eyeRay.direction.z;
//    ray_dir_z.m128_f32[3] = hitpack.hits[3].eyeRay.direction.z;
//
//    const float* v0 = &mesh_.GetVertices()[ vertexIndices.x ].x;
//    const float* v1 = &mesh_.GetVertices()[ vertexIndices.y ].x;
//    const float* v2 = &mesh_.GetVertices()[ vertexIndices.z ].x;
//    const float* n  = &n_.x;
//
//    __asm { 
//        // Load vertex 0
//        mov    edx,  v0;
//        movaps xmm0, [edx];
//        movaps xmm1, xmm0;
//        movaps xmm2, xmm0;
//
//        // xmm0 = [ v0.x v0.x v0.x v0.x ]
//        // xmm1 = [ v0.y v0.y v0.y v0.y ]
//        // xmm2 = [ v0.z v0.z v0.z v0.z ]
//        shufps xmm0, xmm0, 0;   // 00:00:00:00
//        shufps xmm1, xmm1, 85;  // 01:01:01:01
//        shufps xmm2, xmm2, 170; // 10:10:10:10
//
//        // xmm3 = ray.direction.x - v0.x 
//        movaps xmm3, ray_dir_x;
//        subps  xmm3, xmm0;
//
//        // xmm4 = ray.direction.y - v0.y
//        movaps xmm4, ray_dir_y;
//        subps  xmm4, xmm1;
//
//        // xmm5 = ray.direction.z - v0.z 
//        movaps xmm5, ray_dir_z;
//        subps  xmm5, xmm2;
//        
//        // Load precomputed normal
//        mov    edx,  n;
//        movaps xmm0, [edx];
//        movaps xmm1, xmm0;
//        movaps xmm2, xmm0;
//
//        // xmm0 = [ n.x n.x n.x n.x ]
//        // xmm1 = [ n.y n.y n.y n.y ]
//        // xmm2 = [ n.z n.z n.z n.z ]
//        shufps xmm0, xmm0, 0;   // 00:00:00:00
//        shufps xmm1, xmm1, 85;  // 01:01:01:01
//        shufps xmm2, xmm2, 170; // 10:10:10:10
//
//        // Compute n DOT ray.direction
//
//        // xmm0 = n.x * (ray.direction.x - v0.x)
//        mulps  xmm0, xmm3;
//
//        // xmm1 = n.y * (ray.direction.y - v0.y)
//        mulps  xmm1, xmm4;
//
//        // xmm2 = n.z * (ray.direction.z - v0.z)
//        mulps  xmm2, xmm5;
//
//
//    }
//}
//#endif // SSE


// Moller triangle intersection test
// See: http://ompf.org/forum/viewtopic.php?t=165
// See: Fundamentals of Computer Graphics, Peter Shirley p206
bool TriangleMoller::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
    const Ray& ray = hit.eyeRay;
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






    //__asm {
    //    // xmm0 = v0
    //    mov    edx,  v0;
    //    movaps xmm0, [edx];

    //    // xmm1 = v1 - v0
    //    mov    edx, v1;
    //    movaps xmm1, [edx];
    //    subps  xmm1, xmm0;

    //    // xmm2 = v2 - v0
    //    mov    edx, v1;
    //    movaps xmm2, [edx];
    //    subps  xmm2, xmm0;
    //}

    //__m128 origin_
    //__asm {

    //}