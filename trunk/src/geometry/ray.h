/////////////////////////////////////////////////////////////////////////////
// Class : ray.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_GEOMETRY_RAY_H
#define RAWRAY_GEOMETRY_RAY_H
#include "stdafx.h"
#include "vector3.h"

/////////////////////////////////////////////////////////////////////////////
namespace geometry {

struct DllExport Ray
{
public:
    math::Vector3 origin;
    math::Vector3 direction;

    Ray() : origin(), direction( math::Vector3(0.0f, 0.0f, 1.0f) ) { }
    Ray(const math::Vector3& origin, const math::Vector3& direction) : origin(origin), direction(direction) { }

private:
    DISALLOW_COPY_CONSTRUCTORS(Ray);

}; // class Ray

} // namespace geometry
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_GEOMETRY_RAY_H
