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
    BBoxAA() : Object(NULL), child_(NULL) { }

    static BBoxAA* newBBoxAA();
    static BBoxAA* newBBoxAA(Object* child);
    static BBoxAA* newBBoxAA(const Vector3& min, const Vector3& max);

    void SetMin(const Vector3& min) { bounds_[0] = min; CalcMidpoint(); }
    void SetMax(const Vector3& max) { bounds_[1] = max; CalcMidpoint(); }
    void SetBounds(const Vector3& min, const Vector3& max) { bounds_[0] = min; bounds_[1] = max; CalcMidpoint(); }
    void SetObject(Object* child) { child_ = child; }

    virtual Vector3 GetMin() { return bounds_[0]; }
    virtual Vector3 GetMax() { return bounds_[1]; }
    Vector3 GetMid() { return bounds_[2]; }

    float GetSurfaceArea();
    float GetVolume();

    virtual ~BBoxAA() { }

	virtual void deleteObject();
    virtual void RenderGL() { }
    virtual void PreCalc() { }

    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

    static bool GreaterX(BBoxAA* a, BBoxAA* b) { return a->GetMid().x > b->GetMid().x; }
    static bool GreaterY(BBoxAA* a, BBoxAA* b) { return a->GetMid().y > b->GetMid().y; }
    static bool GreaterZ(BBoxAA* a, BBoxAA* b) { return a->GetMid().z > b->GetMid().z; }

    static float SurfaceArea(const Vector3& size);
    static float Volume(const Vector3& size);

private:
    BBoxAA(Object* child) : Object(NULL), child_(child) {
        SetBounds( child->GetMin(), child->GetMax() );
    }

    BBoxAA(const Vector3& min, const Vector3& max) {
        SetBounds( min, max );
    }

    void CalcMidpoint() { bounds_[2] = GetMin() + 0.5 * ( GetMax() - GetMin() ); }

    SSE_ALIGN Vector3 bounds_[3]; // { min, max, mid }
    Object* child_;

    DISALLOW_COPY_CONSTRUCTORS(BBoxAA);

}; // class BBoxAA

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_BBOX_AA_H
