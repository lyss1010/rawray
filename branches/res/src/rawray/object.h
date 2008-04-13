/////////////////////////////////////////////////////////////////////////////
// Class : object.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_OBJECT_H
#define RAWRAY_RAWRAY_OBJECT_H
#include "stdafx.h"
#include "hit_info.h"
#include "ray.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class Material;

class DllExport Object
{
public:
    Object(const Material* material) : material_(material) { }
    virtual ~Object() { }

    virtual void RenderGL()=0;
    virtual void PreCalc()=0;

    virtual bool Intersect(HitInfo& hit, const Ray& ray, float minDistance = 0.0f, float maxDistance = MAX_DISTANCE)=0;

protected:
    const Material* material_;

private:
    DISALLOW_IMPLICIT_CONSTRUCTORS(Object);

}; // class Object


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_H