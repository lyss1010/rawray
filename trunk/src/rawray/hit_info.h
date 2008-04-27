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
    const Material* material;

    HitInfo() : material(NULL) { }

    HitInfo(const HitInfo& hit)
        : eyeRay(hit.eyeRay), point(hit.point), normal(hit.normal),
        texCoord(hit.texCoord), imgCoord(hit.imgCoord), distance(hit.distance),
        material(hit.material) { }


}; // class HitInfo

// Packet of 4 hits used for SSE optimizations
class ALIGN16 DllExport HitPack {
public:
    ALIGN16 HitInfo hits[4];
    ALIGN16 float hit_result[4];

    // Special formatting of the eye rays for SSE optimized code
#ifdef SSE
    ALIGN16 float ray_d_x[4];
    ALIGN16 float ray_d_y[4];
    ALIGN16 float ray_d_z[4];

    ALIGN16 float ray_o_x[4];
    ALIGN16 float ray_o_y[4];
    ALIGN16 float ray_o_z[4];
#endif

    void PackData() {
        for( int i=0; i<4; ++i ) {
            ray_o_x[i] = hits[i].eyeRay.origin.x;
            ray_o_y[i] = hits[i].eyeRay.origin.y;
            ray_o_z[i] = hits[i].eyeRay.origin.z;
            ray_d_x[i] = hits[i].eyeRay.direction.x;
            ray_d_y[i] = hits[i].eyeRay.direction.y;
            ray_d_z[i] = hits[i].eyeRay.direction.z;
        }
    }
};

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_HIT_INFO_H
