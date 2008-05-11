/////////////////////////////////////////////////////////////////////////////
// Class : bbox_aa.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_BBOX_AA_H
#define RAWRAY_RAWRAY_BBOX_AA_H
#include "stdafx.h"
#include "object.h"
#include <list>

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

	bool Hit(const Ray& ray, float minDistance, float maxDistance) const;

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
    BBoxAA() : Object(NULL) { }

    static BBoxAA* newBBoxAA();
    static BBoxAA* newBBoxAA(Object* child);
    static BBoxAA* newBBoxAA(const Vector3& min, const Vector3& max);

    void SetMin(const Vector3& min) { box_[0] = min; box_.CalcMidpoint(); }
    void SetMax(const Vector3& max) { box_[1] = max; box_.CalcMidpoint(); }
    void SetBounds(const Vector3& min, const Vector3& max) { box_[0] = min; box_[1] = max; box_.CalcMidpoint(); }
    void AddObject(Object* child) { children_.push_back(child); }

    virtual Vector3 GetMin() { return box_[0]; }
    virtual Vector3 GetMax() { return box_[1]; }
    Vector3 GetMid() { return box_[2]; }
	std::list<Object*>& GetObjects() { return children_; }

    float GetSurfaceArea();
    float GetVolume();

    virtual ~BBoxAA() { }

	virtual void deleteObject();
    virtual void RenderGL() { }
    virtual void PreCalc() { }

	virtual bool Hit(const Ray& ray, float minDistance, float maxDistance) const;
    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

private:
    BBoxAA(Object* child) : Object(NULL) {
		children_.push_back( child );
        SetBounds( child->GetMin(), child->GetMax() );
    }

    BBoxAA(const Vector3& min, const Vector3& max) : Object(NULL) {
        SetBounds( min, max );
    }

    BoxAA   box_;
	std::list<Object*> children_;

    DISALLOW_COPY_CONSTRUCTORS(BBoxAA);

}; // class BBoxAA


namespace BBoxAA_Alg {
    bool min_lt_x(BBoxAA* a, BBoxAA* b);
    bool min_lt_y(BBoxAA* a, BBoxAA* b);
    bool min_lt_z(BBoxAA* a, BBoxAA* b);
    bool max_lt_x(BBoxAA* a, BBoxAA* b);
    bool max_lt_y(BBoxAA* a, BBoxAA* b);
    bool max_lt_z(BBoxAA* a, BBoxAA* b);
    bool mid_lt_x(BBoxAA* a, BBoxAA* b);
    bool mid_lt_y(BBoxAA* a, BBoxAA* b);
    bool mid_lt_z(BBoxAA* a, BBoxAA* b);
} // namespace BBoxAA_Alg


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_BBOX_AA_H
