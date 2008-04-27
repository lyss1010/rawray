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

// SSE Enhanced intersection of 4x rays simultaneously
// Operate on 4x incoming rays in parallel
#ifdef SSE
void TriangleMoller::IntersectPack(HitPack& hitpack, float minDistance, float maxDistance) {
    const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const float* v0 = &mesh_.GetVertices()[ vertexIndices.x ].x;
    const float* v1 = &mesh_.GetVertices()[ vertexIndices.y ].x;
    const float* v2 = &mesh_.GetVertices()[ vertexIndices.z ].x;

    const float* ray_d_x = hitpack.ray_d_x;
    const float* ray_d_y = hitpack.ray_d_y;
    const float* ray_d_z = hitpack.ray_d_z;
    const float* ray_o_x = hitpack.ray_o_x;
    const float* ray_o_y = hitpack.ray_o_y;
    const float* ray_o_z = hitpack.ray_o_z;
    
    __m128 temp_vec = {0};
    __m128 o_min_v0_x, o_min_v0_y, o_min_v0_z;

    ALIGN16 const float* n = &n_.x;
    
    // Compute edges and distribute values across a 4x packed vector
    register float bx = v1[0] - v0[0]; __m128 b_x[4] = { bx, bx, bx, bx };
    register float by = v1[1] - v0[1]; __m128 b_y[4] = { by, by, by, by };
    register float bz = v1[2] - v0[2]; __m128 b_z[4] = { bz, bz, bz, bz };

    register float cx = v2[0] - v0[0]; __m128 c_x[4] = { cx, cx, cx, cx };
    register float cy = v2[1] - v0[1]; __m128 c_y[4] = { cy, cy, cy, cy };
    register float cz = v2[2] - v0[2]; __m128 c_z[4] = { cz, cz, cz, cz };


	// compute n.(o - v0)
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

        // xmm4 = o.x - v0.x 
        mov    edx,  ray_o_x;
        movaps xmm4, [edx];
        subps  xmm4, xmm0;

        // xmm5 = o.y - v0.y
        mov    edx,  ray_o_y;
        movaps xmm5, [edx];
        subps  xmm5, xmm1;

        // xmm6 = o.z - v0.z 
        mov    edx,  ray_o_z;
        movaps xmm6, [edx];
        subps  xmm6, xmm2;

        // NOTE: We will be reusing (o-v0) later on, so store it away
        movaps o_min_v0_x, xmm4;
        movaps o_min_v0_y, xmm5;
        movaps o_min_v0_z, xmm6;
        
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
        
        mulps  xmm0, xmm5;	// xmm0 = n.x * (d.x - v0.x)
        mulps  xmm1, xmm6;	// xmm1 = n.y * (d.y - v0.y)
        mulps  xmm2, xmm7;	// xmm2 = n.z * (d.z - v0.z)

        // xmm0 = n.(o - v0)
		addps  xmm0, xmm1;
		addps  xmm0, xmm2;
	}

	// compute 1 / -n.d
	__asm {
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

        // xmm1 = n.x * d.x
        mov    edx,  ray_d_x;
        movaps xmm4, [edx];
        mulps  xmm1, xmm4;
        
        // xmm2 = n.y * d.y
        mov    edx,  ray_d_x;
        movaps xmm4, [edx];
        mulps  xmm2, xmm4;

        // xmm3 = n.z * d.z
        mov    edx,  ray_d_z;
        movaps xmm4, [edx];
        mulps  xmm3, xmm4;

		// xmm1 = n.d
		addps xmm1, xmm2;
		addps xmm1, xmm3;

		// xmm2 = -n.d
		movaps xmm2, temp_vec;
		subps  xmm2, xmm1;

		// xmm7 = 1 / -n.d
		rcpps  xmm7, xmm2;
    }

	// Now we currently have: (we want to keep xmm4,5,6,7 w/o recomputing them)
	// xmm0 = n.(o - v0)
    // xmm4 = o.x - v0.x
    // xmm5 = o.y - v0.y
    // xmm6 = o.z - v0.z
    // xmm7 = -1 / n.d

	// Compute distance t = n.(o-v0) / -n.d
	__m128 t, hitpoint;
	__asm {
		mulps  xmm0, xmm7;
		movaps t, xmm0;

        // TODO: Compute hit points
	}

	// beta = ((o-v0) x b).d / -n.d
    __m128 beta;
    __asm {
        // Load the z and y portions of our data to work on for the 1st part of the cross product
        movaps xmm0, o_min_v0_y;
        movaps xmm1, o_min_v0_z;

        movaps xmm2, b_y;
        movaps xmm3, b_z;

        // 1st element of cross product
        mulps  xmm0, xmm3; // ay * bz
        mulps  xmm2, xmm1; // az * by
        subps  xmm0, xmm2; // ay * bz - az * by

        // Load the x portion of our data for the 2nd part of the cross product
        // the values xmm1 and xmm3 are still untouched (the z portions)
        movaps xmm2, o_min_v0_x;
        movaps xmm4, b_x;

        // 2nd element of cross prodcut
        mulps xmm1, xmm4; // az * bz
        mulps xmm3, xmm2; // ax * bz
        subps xmm1, xmm3; // az * bz - ax * bz

        // Load the y portion of our data for the 3rd part of the cross product
        // the values xmm2 and xmm4 are still untouched (the x portions)
        movaps xmm3, o_min_v0_y;
        movaps xmm5, b_y;

        // 3rd element of cross product
        mulps xmm2, xmm5; // ax * by
        mulps xmm4, xmm3; // ay * bx
        subps xmm2, xmm4; // ax * by - ay * bx

        // Compute ((o-v0) x b).d
        mulps xmm0, ray_d_x;
        mulps xmm1, ray_d_y;
        mulps xmm2, ray_d_z;
        addps xmm0, xmm1;
        addps xmm0, xmm2;

        // store beta in xmm6 for later use so we don't need to load from memory
        // beta = ((o-v0) x b).d / -n.d
        mulps  xmm0, xmm7;
        movaps xmm6, xmm0;
        movaps beta, xmm0;
    }

    // gamma = (c x (o-v0)).d / -n.d
    __m128 gamma;
    __asm {
        // Load the z and y portions of our data to work on for the 1st part of the cross product
        movaps xmm0, c_y;
        movaps xmm1, c_z;

        movaps xmm2, o_min_v0_y;
        movaps xmm3, o_min_v0_z;

        // 1st element of cross product
        mulps  xmm0, xmm3; // ay * bz
        mulps  xmm2, xmm1; // az * by
        subps  xmm0, xmm2; // ay * bz - az * by

        // Load the x portion of our data for the 2nd part of the cross product
        // the values xmm1 and xmm3 are still untouched (the z portions)
        movaps xmm2, c_x;
        movaps xmm4, o_min_v0_x;

        // 2nd element of cross prodcut
        mulps xmm1, xmm4; // az * bz
        mulps xmm3, xmm2; // ax * bz
        subps xmm1, xmm3; // az * bz - ax * bz

        // Load the y portion of our data for the 3rd part of the cross product
        // the values xmm2 and xmm4 are still untouched (the x portions)
        movaps xmm3, c_y;
        movaps xmm5, o_min_v0_y;

        // 3rd element of cross product
        mulps xmm2, xmm5; // ax * by
        mulps xmm4, xmm3; // ay * bx
        subps xmm2, xmm4; // ax * by - ay * bx

        // Compute (c x (o-v0)).d
        mulps xmm0, ray_d_x;
        mulps xmm1, ray_d_y;
        mulps xmm2, ray_d_z;
        addps xmm0, xmm1;
        addps xmm0, xmm2;

        // gamma = (c x (o-v0)).d / -n.d
        mulps  xmm0, xmm7;
        movaps gamma, xmm0;
    }
    
    temp_vec.m128_f32[0] = 1.0f;
    temp_vec.m128_f32[1] = 1.0f;
    temp_vec.m128_f32[2] = 1.0f;
    temp_vec.m128_f32[3] = 1.0f;

    // Compute alpha and beta+gamma
    __m128 beta_plus_gamma, alpha;
    __asm {
        // gamma is still in xmm0
        // beta is still in xmm6
        addps  xmm0, xmm6;
        movaps beta_plus_gamma, xmm0;
        
        // alpha = 1 - (beta+gamma) = 1 - beta - gamma
        movaps xmm1, temp_vec;
        subps  xmm1, xmm0;
        movaps alpha, xmm1;
    }


    // ZOMG we're done computing stuff!
    // we now have values of t, beta, gamma for all 4 rays in the pack
    // we can sort through them and find valid/invalid stuff

    // TODO: Less unpackinga and have the outside world use data in its current form
    memset( hitpack.hit_result, 0, sizeof(hitpack.hit_result) );
    for( int i=0; i<4; ++i ) {
        // All the different cases where we leave the hit_result as false
        if( t.m128_f32[i]               < minDistance || 
            t.m128_f32[i]               > maxDistance ||
            beta.m128_f32[i]            < 0.0f ||
            gamma.m128_f32[i]           < 0.0f || 
            beta_plus_gamma.m128_f32[i] > 1.0f )
        {
            break;
        }

        // We had a valid hit, so compute the rest of the interpolation etc...
        // TODO: SSE Interpolation?
        hitpack.hits[i].distance = t.m128_f32[i];
        hitpack.hits[i].material = material_;
        hitpack.hits[i].point = hitpack.hits[i].eyeRay.origin + t.m128_f32[i] * hitpack.hits[i].eyeRay.direction;
        Interpolate( hitpack.hits[i], alpha.m128_f32[i], beta.m128_f32[i], gamma.m128_f32[i] );
    }
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