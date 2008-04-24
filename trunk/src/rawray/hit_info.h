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

//typedef HitInfo[4] HitInfoPack;

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_HIT_INFO_H
