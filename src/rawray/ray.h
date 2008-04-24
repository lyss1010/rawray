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

// struct means default public access, but don't change direction or abs!
struct DllExport Ray
{
    ALIGN16 Vector3 origin;
    ALIGN16 Vector3 direction;

    Ray() 
		: origin(), 
		direction( Vector3(1, 0, 0) ) { }

    Ray(const Vector3& origin, const Vector3& direction) : origin(origin), direction(direction) {
        this->direction.Normalize();
	}

    Ray(const Ray& r) 
		: origin(r.origin), 
		direction(r.direction) { }

}; // struct Ray

//typedef Ray[4] RayPack;

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_RAY_H
