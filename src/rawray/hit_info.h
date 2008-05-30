/////////////////////////////////////////////////////////////////////////////
// Class : hit_info.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_HIT_INFO_H
#define RAWRAY_RAWRAY_HIT_INFO_H
#include "stdafx.h"
#include "math/vector3.h"
#include "math/vector2.h"
#include "math/tuple2.h"
#include "ray.h"

#define IOR_AIR 1.00029

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class Material;

class DllExport HitInfo
{
public:
    Ray eyeRay;
    Vector3 point;
    Vector3 normal;
    Vector2 texCoord;
    Tuple2I imgCoord;
    float distance;
    Material* material;
	float ior;
	int ior_bounce;
	int diffuse_bounce;
	float weight;

    HitInfo() : material(NULL), ior(IOR_AIR), ior_bounce(0), diffuse_bounce(0), weight(1) { }

    HitInfo(const HitInfo& hit)
        : eyeRay(hit.eyeRay), point(hit.point), normal(hit.normal),
        texCoord(hit.texCoord), imgCoord(hit.imgCoord), distance(hit.distance),
		material(hit.material), ior(hit.ior), ior_bounce(hit.ior_bounce),
        diffuse_bounce(hit.diffuse_bounce), weight(hit.weight) { }

}; // class HitInfo

// Packet of 4 hits used for SSE optimizations
class SSE_ALIGN DllExport HitPack {
public:
    SSE_ALIGN HitInfo hits[4];
    SSE_ALIGN float hit_result[4];

    // Special formatting of the eye rays for SSE optimized code
#ifdef SSE
    __m128 ray_d_x;
    __m128 ray_d_y;
    __m128 ray_d_z;

    __m128 ray_o_x;
    __m128 ray_o_y;
    __m128 ray_o_z;
#endif // SSE

    void PackData() {
#ifdef SSE
        for( int i=0; i<4; ++i ) {
            ray_o_x.m128_f32[i] = hits[i].eyeRay.origin.x;
            ray_o_y.m128_f32[i] = hits[i].eyeRay.origin.y;
            ray_o_z.m128_f32[i] = hits[i].eyeRay.origin.z;

            ray_d_x.m128_f32[i] = hits[i].eyeRay.direction.x;
            ray_d_y.m128_f32[i] = hits[i].eyeRay.direction.y;
            ray_d_z.m128_f32[i] = hits[i].eyeRay.direction.z;
        }
#endif // SSE
    }
};

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_HIT_INFO_H
