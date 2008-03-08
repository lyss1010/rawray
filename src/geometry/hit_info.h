/////////////////////////////////////////////////////////////////////////////
// Class : hit_info.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_GEOMETRY_HIT_INFO_H
#define RAWRAY_GEOMETRY_HIT_INFO_H
#include "stdafx.h"
#include "vector3.h"

/////////////////////////////////////////////////////////////////////////////
namespace geometry {

class Material;

class DllExport HitInfo
{
public:
    float distance;
    math::Vector3 point;
    math::Vector3 normal;
    const Material* material; // TODO: Make this a reference and create a "blank" material to assign to it

    HitInfo() { }
    //HitInfo(float d = 0.0f,
    //                 const Vector3& point = Vector3(),
    //                 const Vector3& normal = Vector3(0.0f, 1.0f, 0.0f),
    //                 const Material* material = NULL) :
    //distance(d), point(point), normal(normal), material(material) { }

private:
    DISALLOW_COPY_CONSTRUCTORS(HitInfo);

}; // class HitInfo

} // namespace geometry
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_GEOMETRY_HIT_INFO_H
