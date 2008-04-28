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

class SSE_ALIGN DllExport Object
{
public:
    Object(Material* material) : material_(material) { }

    void SetMaterial(Material* material) { material_ = material; }
    Material* GetMaterial() { return material_; }

	virtual void deleteObject() { delete this; }
    virtual void RenderGL()=0;
    virtual void PreCalc()=0;

    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance)=0;
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance)=0;

protected:
    Material* material_;
	virtual ~Object() { }; // Because some objects are memory aligned, we must invoke custom delete functions

private:
    DISALLOW_IMPLICIT_CONSTRUCTORS(Object);

}; // class Object

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_H
