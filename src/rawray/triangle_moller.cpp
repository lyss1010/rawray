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

	// TODO: See if that's any faster than shufps
	// If we are using ray packs, we want 4x copies of each element of the normal to work on
#ifdef SSE
	nx_ = Vector4( n_.x );
	ny_ = Vector4( n_.y );
	nz_ = Vector4( n_.z );
#endif
}


// SSE Enhanced intersection of 4x rays simultaneously
// Operate on 4x incoming rays in parallel
#ifdef SSE
void TriangleMoller::IntersectPack(HitPack& hitpack, float minDistance, float maxDistance) {
    const HitInfo& hit1 = hitpack.hits[0];
    const HitInfo& hit2 = hitpack.hits[1];
    const HitInfo& hit3 = hitpack.hits[2];
    const HitInfo& hit4 = hitpack.hits[3];
	
    __m128 ray_d_x, ray_d_y, ray_d_z;
    ray_d_x.m128_f32[0] = hit1.eyeRay.direction.x;
	ray_d_y.m128_f32[0] = hit1.eyeRay.direction.y;
	ray_d_z.m128_f32[0] = hit1.eyeRay.direction.z;
	ray_d_x.m128_f32[1] = hit2.eyeRay.direction.x;
    ray_d_y.m128_f32[1] = hit2.eyeRay.direction.y;
	ray_d_z.m128_f32[1] = hit2.eyeRay.direction.z;
	ray_d_x.m128_f32[2] = hit3.eyeRay.direction.x;
	ray_d_y.m128_f32[2] = hit3.eyeRay.direction.y;
	ray_d_z.m128_f32[2] = hit3.eyeRay.direction.z;
    ray_d_x.m128_f32[3] = hit4.eyeRay.direction.x;
    ray_d_y.m128_f32[3] = hit4.eyeRay.direction.y;
    ray_d_z.m128_f32[3] = hit4.eyeRay.direction.z;

	__m128 ray__x, ray_o_y, ray_o_z;
	ray_o_x.m128_f32[0] = hit1.eyeRay.origin.x;
	ray_o_y.m128_f32[0] = hit1.eyeRay.origin.y;
	ray_o_z.m128_f32[0] = hit1.eyeRay.origin.z;
	ray_o_x.m128_f32[1] = hit2.eyeRay.origin.x;
    ray_o_y.m128_f32[1] = hit2.eyeRay.origin.y;
	ray_o_z.m128_f32[1] = hit2.eyeRay.origin.z;
	ray_o_x.m128_f32[2] = hit3.eyeRay.origin.x;
	ray_o_y.m128_f32[2] = hit3.eyeRay.origin.y;
	ray_o_z.m128_f32[2] = hit3.eyeRay.origin.z;
    ray_o_x.m128_f32[3] = hit4.eyeRay.origin.x;
    ray_o_y.m128_f32[3] = hit4.eyeRay.origin.y;
    ray_o_z.m128_f32[3] = hit4.eyeRay.origin.z;
	
    const float* v0 = &mesh_.GetVertices()[ vertexIndices.x ].x;
    const float* v1 = &mesh_.GetVertices()[ vertexIndices.y ].x;
    const float* v2 = &mesh_.GetVertices()[ vertexIndices.z ].x;
    const float* nx = &nx_.x;
	const float* ny = &ny_.x;
	const float* nz = &nz_.x;
	
	__m128 zero = {0};

	// xmm0 = n.(o - v0)
    __asm { 
        // Load v0
        mov    edx,  v0;
        movaps xmm0, [edx];
        movaps xmm1, xmm0;
        movaps xmm2, xmm0;

        // xmm0 = [ v0.x v0.x v0.x v0.x ]
        // xmm1 = [ v0.y v0.y v0.y v0.y ]
        // xmm2 = [ v0.z v0.z v0.z v0.z ]
        shufps xmm0, xmm0, 0;   // 00:00:00:00
        shufps xmm1, xmm1, 85;  // 01:01:01:01
        shufps xmm2, xmm2, 170; // 10:10:10:10

        // xmm3 = o.x - v0.x 
        movaps xmm3, ray_o_x;
        subps  xmm3, xmm0;

        // xmm4 = o.y - v0.y
        movaps xmm4, ray_o_y;
        subps  xmm4, xmm1;

        // xmm5 = o.z - v0.z 
        movaps xmm5, ray_o_z;
        subps  xmm5, xmm2;
        
        // Load precomputed normal
        mov    edx,  n;
        movaps xmm0, [edx];
        movaps xmm1, xmm0;
        movaps xmm2, xmm0;

        // xmm0 = [ n.x n.x n.x n.x ]
        // xmm1 = [ n.y n.y n.y n.y ]
        // xmm2 = [ n.z n.z n.z n.z ]
        shufps xmm0, xmm0, 0;   // 00:00:00:00
        shufps xmm1, xmm1, 85;  // 01:01:01:01
        shufps xmm2, xmm2, 170; // 10:10:10:10
        
        mulps  xmm0, xmm3;	// xmm0 = n.x * (d.x - v0.x)
        mulps  xmm1, xmm4;	// xmm1 = n.y * (d.y - v0.y)
        mulps  xmm2, xmm5;	// xmm2 = n.z * (d.z - v0.z)

        // xmm0 = n.(o - v0)
		addps  xmm0, xmm1;
		addps  xmm0, xmm2;
	}

	// xmm1 = 1 / n.d
	__asm {
		// Load Ray direction
		movaps xmm4, ray_d_x;
		movaps xmm5, ray_d_y;
		movaps xmm6, ray_d_z;

		// Load precomputed normal into xmm1, xmm2, xmm3
        mov    edx,  n;
        movaps xmm1, [edx];
        movaps xmm2, xmm1;
        movaps xmm3, xmm1;

        // xmm1 = [ n.x n.x n.x n.x ]
        // xmm2 = [ n.y n.y n.y n.y ]
        // xmm3 = [ n.z n.z n.z n.z ]
        shufps xmm1, xmm1, 0;   // 00:00:00:00
        shufps xmm2, xmm2, 85;  // 01:01:01:01
        shufps xmm3, xmm3, 170; // 10:10:10:10
        
        mulps  xmm1, xmm4;	// xmm1 = n.x * d.x
        mulps  xmm2, xmm5;	// xmm2 = n.y * d.y
        mulps  xmm3, xmm6;	// xmm3 = n.z * d.z

		// xmm1 = n.d
		addps xmm1, xmm2;
		addps xmm1, xmm3;

		// xmm2 = -n.d
		movaps xmm2, zero;
		subps  xmm2, xmm1;

		// xmm1 = -1 / n.d
		rcpps  xmm1, xmm2;
    }

	// Now we currently have:
	// xmm0 = n.(o - v0)
	// xmm1 = -1 / n.d

	// Compute distance t = - n.(o-v0) / n.d
	__m128 t;
	__asm {
		mulps  xmm0, xmm1;
		movaps t, xmm0;
	}

	// 
}
#endif // SSE


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