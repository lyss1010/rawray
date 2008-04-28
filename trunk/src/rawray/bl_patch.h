/////////////////////////////////////////////////////////////////////////////
// Class : bl_patch.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_BL_PATCH_H
#define RAWRAY_RAWRAY_BL_PATCH_H
#include "stdafx.h"
#include "object.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class Material;

class DllExport BLPatch : public Object
{
// Temporary data required for patch intersection computations
private:
struct BLPatchData {
	BLPatchData() { }

	BLPatchData(float A1, float B1, float C1, float D1, float A2, float B2, float C2, float D2)
		: A1(A1), B1(B1), C1(C1), D1(D1), A2(A2), B2(B2), C2(C2), D2(D2) { }

    float A1, B1, C1, D1;
    float A2, B2, C2, D2;
};


public:
    BLPatch(Material* material) : Object(material), uMin_(0.5f), uMax_(0.5f), vMin_(0.5f), vMax_(0.5f) { }
    virtual ~BLPatch() { }

    void SetUConstraint(float min, float max) { uMin_=min; uMax_=max; }
    void SetVConstraint(float min, float max) { vMin_=min; vMax_=max; }

    void SetP00(const Vector3& v) { P00_ = v; }
    void SetP01(const Vector3& v) { P01_ = v; }
    void SetP10(const Vector3& v) { P10_ = v; }
    void SetP11(const Vector3& v) { P11_ = v; }

	virtual void deleteObject() { delete this; }
    virtual void RenderGL();
    virtual void PreCalc();

    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

protected:
    Vector3 P00_, P01_, P10_, P11_;
    float uMin_, uMax_;
    float vMin_, vMax_;

private:
    int ComputeV(float* out1, float* out2, float a, float b, float c);
    float ComputeT(const Ray& ray, const Vector3& point);
    float ComputeU(float v, const BLPatchData& patch);
    bool IsValid(float u, float v);
    Vector3 Eval(float u, float v);

    DISALLOW_COPY_CONSTRUCTORS(BLPatch);

}; // class BLPatch

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_BL_PATCH_H
