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

    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance)=0;
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance)=0;

protected:
    const Material* material_;

private:
    DISALLOW_IMPLICIT_CONSTRUCTORS(Object);

}; // class Object


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_H
