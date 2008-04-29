/////////////////////////////////////////////////////////////////////////////
// Class : bbox_aa.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_BBOX_AA_H
#define RAWRAY_RAWRAY_BBOX_AA_H
#include "stdafx.h"
#include "object.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class Material;

class DllExport Instance : public Object
{
public:
    Instance(Material* material) : Object(material) { }
    Instance(Material* material, Object* parent) : Object(material) parent_(parent) { }

    // TODO: Take into account matrix rotations on min/max
    virtual Vector3 GetMin() { return object_->GetMin(); }
    virtual Vector3 GetMax() { return object_->GetMax(); }

    virtual ~Instance() { }

	virtual void deleteObject();
    virtual void RenderGL();
    virtual void PreCalc();

    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

private:
    BBoxAA(Material* material) : Object(material) { }

    BBoxAA(Material* material, const Vector3& min, const Vector3& max) : Object(material) {
        bounds_[0] = min;
        bounds_[1] = max;
    }

    SSE_ALIGN Vector3 bounds_[2]; // { min, max }
    std::vector<Object*> objects_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(BBoxAA);

}; // class BBoxAA

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_BBOX_AA_H
