/////////////////////////////////////////////////////////////////////////////
// Class : sphere.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_SPHERE_H
#define RAWRAY_RAWRAY_SPHERE_H
#include "stdafx.h"
#include "math/vector3.h"
#include "object.h"
#include "hit_info.h"
#include "ray.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport Sphere : public Object
{
public:
    Sphere(const Vector3& center, float radius, const Material* material) :
        Object(material), center_(center), radius_(radius) { }

    virtual ~Sphere() { }

    void SetCenter(const Vector3& center) { center_=center; }
    void SetRadius(float radius) { radius_=radius; }

    const Vector3& GetCenter() const { return center_; }
    float GetRadius() const { return radius_; }

    virtual void RenderGL();
    virtual void PreCalc() { }

    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

private:
    Vector3 center_;
    float radius_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(Sphere);

}; // class Sphere


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_SPHERE_H
