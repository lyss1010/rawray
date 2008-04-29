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
struct SSE_ALIGN DllExport Ray
{
    Vector3 origin;
    Vector3 direction;
    Vector3 inv_direction;
    int sign[4];

    Ray() 
		: origin(), 
		direction( Vector3(1, 0, 0) ) { PreCalc(); }

    Ray(const Vector3& origin, const Vector3& direction) : origin(origin), direction(direction) {
        this->direction.Normalize();
        PreCalc();
	}

    Ray(const Ray& r) 
		: origin(r.origin), 
		direction(r.direction) { PreCalc(); }

private:
    void PreCalc() {
        inv_direction = 1.0f / direction;
        sign[0] = inv_direction[0] < 0;
        sign[1] = inv_direction[1] < 0;
        sign[2] = inv_direction[2] < 0;
        sign[3] = inv_direction[3] < 0;
    }

}; // struct Ray

// Packet of 4 rays used for SSE optimizations
class SSE_ALIGN DllExport RayPack {
public:
    Ray rays[4];
};

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_RAY_H
