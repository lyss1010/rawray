/////////////////////////////////////////////////////////////////////////////
// Class : sphere.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_GEOMETRY_SPHERE_H
#define RAWRAY_GEOMETRY_SPHERE_H
#include "stdafx.h"
#include "object.h"
#include "hit_info.h"
#include "ray.h"

/////////////////////////////////////////////////////////////////////////////
namespace geometry {

class DllExport Sphere : public Object
{
public:
    virtual ~Sphere() { }

    virtual void RenderGL();
    virtual bool Intersect(HitInfo& hit, const Ray& ray, float minDistance = 0.0f, float maxDistance = MAX_DISTANCE);

private:

    DISALLOW_COPY_CONSTRUCTORS(Sphere);

}; // class Sphere


} // namespace geometry
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_GEOMETRY_SPHERE_H
