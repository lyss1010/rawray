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

class SSE_ALIGN BoxAA {
public:
	BoxAA() { }
	BoxAA(const Vector3& min, const Vector3& max) { bounds_[0]=min; bounds_[1]=max; CalcMidpoint(); }

	void SetMin(const Vector3& min) { bounds_[0] = min; CalcMidpoint(); }
	void SetMax(const Vector3& max) { bounds_[1] = max; CalcMidpoint(); }
	void SetBounds(const Vector3& min, const Vector3& max) { bounds_[0] = min; bounds_[1] = max; CalcMidpoint(); }

	void CalcMidpoint() { bounds_[2] = bounds_[0] + 0.5 * ( bounds_[1] - bounds_[0] ); }

	bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

	static float SurfaceArea(const Vector3& size);
    static float Volume(const Vector3& size);

	Vector3& operator[](int i) { assert( i>=0 && i<=3 ); return bounds_[i]; }
	const Vector3& operator[](int i) const { assert( i>=0 && i<=3 ); return bounds_[i]; }

private:
	SSE_ALIGN Vector3 bounds_[3]; // { min, max, mid }

	DISALLOW_COPY_CONSTRUCTORS( BoxAA );
};


class SSE_ALIGN DllExport BBoxAA : public Object
{
public:
    BBoxAA() : Object(NULL), child_(NULL) { }

    static BBoxAA* newBBoxAA();
    static BBoxAA* newBBoxAA(Object* child);
    static BBoxAA* newBBoxAA(const Vector3& min, const Vector3& max);

    void SetMin(const Vector3& min) { box_[0] = min; box_.CalcMidpoint(); }
    void SetMax(const Vector3& max) { box_[1] = max; box_.CalcMidpoint(); }
    void SetBounds(const Vector3& min, const Vector3& max) { box_[0] = min; box_[1] = max; box_.CalcMidpoint(); }
    void SetObject(Object* child) { child_ = child; }

    virtual Vector3 GetMin() { return box_[0]; }
    virtual Vector3 GetMax() { return box_[1]; }
    Vector3 GetMid() { return box_[2]; }

    float GetSurfaceArea();
    float GetVolume();

    virtual ~BBoxAA() { }

	virtual void deleteObject();
    virtual void RenderGL() { }
    virtual void PreCalc() { }

    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

	static bool GreaterX(BBoxAA* a, BBoxAA* b) { return a->box_[2].x > b->box_[2].x; }
    static bool GreaterY(BBoxAA* a, BBoxAA* b) { return a->box_[2].y > b->box_[2].y; }
    static bool GreaterZ(BBoxAA* a, BBoxAA* b) { return a->box_[2].z > b->box_[2].z; }

private:
    BBoxAA(Object* child) : Object(NULL), child_(child) {
        SetBounds( child->GetMin(), child->GetMax() );
    }

    BBoxAA(const Vector3& min, const Vector3& max) : Object(NULL), child_(NULL) {
        SetBounds( min, max );
    }

    BoxAA   box_;
    Object* child_;

    DISALLOW_COPY_CONSTRUCTORS(BBoxAA);

}; // class BBoxAA

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_BBOX_AA_H
