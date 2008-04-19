/////////////////////////////////////////////////////////////////////////////
// Class : hit_info.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_HIT_INFO_H
#define RAWRAY_RAWRAY_HIT_INFO_H
#include "stdafx.h"
#include "math/vector3.h"
#include "math/vector2.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class Material;

class DllExport HitInfo
{
public:
    float distance;
    Vector3 point;
    Vector3 normal;
    Vector2 texCoord;
	Vector3 barycentric;

    const Material* material;

    HitInfo(const HitInfo& hit) : distance(hit.distance), point(hit.point), normal(hit.normal), material(hit.material) { }
    explicit HitInfo(float distance = 0.0f, 
                     const Vector3& point = Vector3(),
                     const Vector3& normal = Vector3(0.0f, 1.0f, 0.0f),
                     const Vector2& texCoord = Vector2(0.0f, 0.0f),
					 const Vector2& barycentric = Vector3(1.0f, 0.0f, 0.0f),
                     const Material* material = NULL) :
        distance(distance), point(point), normal(normal), 
		texCoord(texCoord), barycentric(barycentric), material(material) { }

}; // class HitInfo

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_HIT_INFO_H
