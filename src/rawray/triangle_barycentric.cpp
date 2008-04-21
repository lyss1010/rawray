/////////////////////////////////////////////////////////////////////////////
// triangle_barycentric.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "triangle_barycentric.h"
#include "math/tuple3.h"
#include "material.h"
#include <xmmintrin.h>

namespace rawray {

void TriangleBarycentric::PreCalc() { }

// Ray-Plane intersection with barycentric coordinate test
// See: Fundamentals of Computer Graphics, Peter Shirley p206
// Moller test with the determinants computed out by hand
bool TriangleBarycentric::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
#ifdef SSE
	const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const float* v0 = mesh_.GetVertices()[ vertexIndices.x ].vec;
    const float* v1 = mesh_.GetVertices()[ vertexIndices.y ].vec;
    const float* v2 = mesh_.GetVertices()[ vertexIndices.z ].vec;
    const float* ray_origin = ray.origin.vec;
    const float* ray_direction = ray.direction.vec;
    __m128 zero;
    memset( &zero, 0, sizeof(zero) );

    // Compute temporay values for computing determinants
    __asm {
        // a = v0[0] - v1[0];
        // b = v0[1] - v1[1];
        // c = v0[2] - v1[2];
        mov    eax,  v0;
        mov    esi,  v1;
        movaps xmm0, [eax];
        subps  xmm0, [esi];

        // d = v0[0] - v2[0];
        // e = v0[1] - v2[1];
        // f = v0[2] - v2[2];
        mov    esi,  v2;
        movaps xmm1, [eax];
        subps  xmm1, [esi];

        // g = -ray.direction.x
	    // h = -ray.direction.y
	    // i = -ray.direction.z
        mov    esi,  ray_direction;
        movaps xmm2, zero;
        subps  xmm2, [esi];

        // j = v0[0] - ray.origin.x;
        // k = v0[1] - ray.origin.y;
        // l = v0[2] - ray.origin.z;
        mov    esi,  ray_origin;
        movaps xmm3, [eax];
        subps  xmm3, [esi];

        // xmm4 = [ f d  e  .]
        // xmm4 = [gf dh ei .]
        movaps xmm4, xmm1;
        shufps xmm4, xmm4, 210; // 11:01:00:10
        mulps  xmm4, xmm2;

        // xmm5 = [e   f d .]
        // xmm5 = [eg hf di .]
        movaps xmm5, xmm1;
        shufps xmm5, xmm5, 201; // 11:00:10:01
        mulps  xmm5, xmm2;

        // xmm5 = [di eg hf]
        // xmm4 = [gf-di dh-eg ei-hf]
        shufps xmm5, xmm5, 210; // 11:01:00:10
        subps  xmm4, xmm5;

        // xmm5 = [ k  l  j .]
        // xmm5 = [ak bl cj .]
        movaps xmm5, xmm3;
        shufps xmm5, xmm5, 201; // 11:00:10:01
        mulps  xmm5, xmm0;

        // xmm6 = [b  c  a  .]
        // xmm6 = [bj ck al .]
        movaps xmm6, xmm0;
        shufps xmm6, xmm6, 201; // 11:00:10:01
        mulps  xmm6, xmm3;

        // xmm5 = [ak-bj bl-ck cj-al]
        subps xmm5, xmm6;
    }

    // xmm0 = [a     b     c     .]
    // xmm1 = [d     e     f     .]
    // xmm2 = [g     h     i     .]
    // xmm3 = [j     k     l     .]
    // xmm4 = [gf-di dh-eg ei-hf .]
    // xmm5 = [ak-bj bl-ck cj-al .]

    // Compute denominator determinent
    __asm {
        // xmm0 = [b c a .]
        // xmm0 = [b*(gf-di) c*(dh-eg) a*(ei-hf) .]
        shufps xmm0, xmm0, 201; // 11:00:10:01
        mulps  xmm0, xmm4;

        // Calculate the inverse denominator (inv_den)
        // xmm6[0] = c*(dh-eg)
        // xmm7[0] = a*(ei-hf)
        // xmm0[0] = 1.0f / (b*(gf-di) + c*(dh-eg) + a*(ei-hf))
        movaps xmm6, xmm0;
        movaps xmm7, xmm0;
        shufps xmm6, xmm6,  85; // 01:01:01:01
        shufps xmm7, xmm7, 170; // 10:10:10:10

        addss  xmm0, xmm6;
        addss  xmm0, xmm7;
        rcpss  xmm0, xmm0;
    }

    // Compute distance
    __m128 distance;
    __asm {
        // xmm1 = [f d e .]
        // xmm1 = [f*(ak-bj) d*(bl-ck) e*(cj-al) .]
        shufps xmm1, xmm1, 210; // 11:01:00:10
        mulps  xmm1, xmm5;

        // xmm6[0] = d*(bl-ck)
        // xmm7[0] = e*(cj-al)
        // xmm1[0] = inv_den * (f*(ak-bj) + d*(bl-ck) + e*(cj-al))
        movaps xmm6, xmm1;
        movaps xmm7, xmm1;
        shufps xmm6, xmm6,  85; // 01:01:01:01
        shufps xmm7, xmm7, 170; // 10:10:10:10

        addss  xmm1, xmm6;
        addss  xmm1, xmm7;
        mulss  xmm1, xmm0;

        // Export xmm1[0] which is the distance
        movaps distance, xmm1;
    }
    if( distance.m128_f32[0] < minDistance || distance.m128_f32[0] > maxDistance )
        return false;

    // Compute gamma
    __m128 gamma;
    __asm {
        // xmm2 = [i g h .]
        // xmm2 = [i*(ak-bj) g*(bl-ck) h*(cj-al) .]
        shufps xmm2, xmm2, 210; // 11:01:00:10
        mulps  xmm2, xmm5;

        // calculate gamma
        // xmm6[0] = g*(bl-ck)
        // xmm7[0] = h*(cj-al)
        // xmm2[0] = inv_den * (i*(ak-bj) + g*(bl-ck) + h*(cj-al))
        movaps xmm6, xmm2;
        movaps xmm7, xmm2;
        shufps xmm6, xmm6,  85; // 01:01:01:01
        shufps xmm7, xmm7, 170; // 10:10:10:10

        addss  xmm2, xmm6;
        addss  xmm2, xmm7;
        mulss  xmm2, xmm0;

        // Export xmm2[0] which is gamma
        movaps gamma, xmm2;
    }
    if( gamma.m128_f32[0] < 0.0f || gamma.m128_f32[0] > 1.0f ) 
        return false;


    // Compute beta
    __m128 beta;
    __asm {
        // xmm3 = [k l j .]
        // xmm3 = [k*(gf-di) l*(dh-eg) j*(ei-hf) .]
        shufps xmm3, xmm3, 201; // 11:00:10:01
        mulps  xmm3, xmm4;

        // calculate beta
        // xmm6[0] = l*(dh-eg)
        // xmm7[0] = j*(ei-hf)
        // xmm3[0] = inv_den * (k*(gf-di) l*(dh-eg) j*(ei-hf))
        movaps xmm6, xmm3;
        movaps xmm7, xmm3;
        shufps xmm6, xmm6,  85; // 01:01:01:01
        shufps xmm7, xmm7, 170; // 10:10:10:10

        addss  xmm3, xmm6;
        addss  xmm3, xmm7;
        mulss  xmm3, xmm0;

        // Export xmm3[0] which is beta
        movaps beta, xmm3;
    }

    const float beta_plus_gamma = beta.m128_f32[0] + gamma.m128_f32[0];
    if( beta.m128_f32[0] < 0.0f || beta_plus_gamma > 1.0f )
        return false;

    hit.point = ray.origin + distance.m128_f32[0] * ray.direction;
    hit.distance = distance.m128_f32[0];
    hit.material = material_;
    Interpolate( hit, 1-beta_plus_gamma, beta.m128_f32[0], gamma.m128_f32[0] );

    return true;

#else // SSE

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
    //                      g = -ray.direction.x
    //                      h = -ray.direction.y
    //                      i = -ray.direction.z
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

#endif // SSE

}

} // namespace rayray
