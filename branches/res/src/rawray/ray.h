/////////////////////////////////////////////////////////////////////////////
// Class : ray.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_RAY_H
#define RAWRAY_RAWRAY_RAY_H
#include "stdafx.h"
#include "math/vector3.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport Ray
{
public:
    Vector3 origin;
    Vector3 direction;

    Ray() : origin(), direction( Vector3(0.0f, 0.0f, 1.0f) ) { }
    Ray(const Vector3& origin, const Vector3& direction) : origin(origin), direction(direction) { }
    Ray(const Ray& r) : origin(r.origin), direction(r.direction) { }

private:

}; // class Ray

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_RAY_H
