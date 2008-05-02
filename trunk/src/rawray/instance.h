/////////////////////////////////////////////////////////////////////////////
// Class : bbox_aa.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_INSTANCE_H
#define RAWRAY_RAWRAY_INSTANCE_H
#include "stdafx.h"
#include "object.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class Material;

class DllExport Instance : public Object
{
public:
    Instance(Material* material) : Object(material) { }
    Instance(Material* material, Object* instancedObject) : Object(material), instancedObject_(instancedObject) { }

    // TODO: Take into account matrix rotations on min/max
    virtual Vector3 GetMin() { return instancedObject_->GetMin(); }
    virtual Vector3 GetMax() { return instancedObject_->GetMax(); }

    virtual ~Instance() { }

	virtual void deleteObject();
    virtual void RenderGL();
    virtual void PreCalc();

    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

private:
    Object* instancedObject_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(Instance);

}; // class Instance

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_INSTANCE_H
