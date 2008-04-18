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
    Vector3 origin;
    Vector3 direction;
	Vector3 abs;		// Absolute value of the direction

    Ray() 
		: origin(), 
		direction( Vector3(0, 0, 1) ), 
		abs( Vector3(0, 0, 1) ) { }

    Ray(const Vector3& origin, const Vector3& direction) : origin(origin), direction(direction) {
		this->direction.Normalize();
		abs = Vector3( fabs(this->direction.x), fabs(this->direction.y), fabs(this->direction.z) );
	}

    Ray(const Ray& r) 
		: origin(r.origin), 
		direction(r.direction), 
		abs(r.abs) { }

}; // struct Ray

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_RAY_H
