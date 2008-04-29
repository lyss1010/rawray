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

class SSE_ALIGN DllExport BBoxAA : public Object
{
public:
    static BBoxAA* newBBoxAA(Material* material);
    static BBoxAA* newBBoxAA(Material* material, const Vector3& min, const Vector3& max);

    void SetMin(const Vector3& v) { bounds_[0] = v; }
    void SetMax(const Vector3& v) { bounds_[1] = v; }

    virtual Vector3 GetMin() { return bounds_[0]; }
    virtual Vector3 GetMax() { return bounds_[1]; }
    float GetSurfaceArea();
    float GetVolume();

    virtual ~BBoxAA() { }

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
