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
	BLPatchData(float A1, float B1, float C1, float D1, float A2, float B2, float C2, float D2)
		: A1(A1), B1(B1), C1(C1), D1(D1), A2(A2), B2(B2), C2(C2), D2(D2) { }

    float A1, B1, C1, D1;
    float A2, B2, C2, D2;
};


public:
    BLPatch(Material* material) : Object(material) { }
    virtual ~BLPatch() { }

    void SetP00(const Vector3& v) { verts_[0] = v; }
    void SetP01(const Vector3& v) { verts_[1] = v; }
    void SetP10(const Vector3& v) { verts_[2] = v; }
    void SetP11(const Vector3& v) { verts_[3] = v; }

    Vector3& operator[](uint32 i) { return verts_[i]; }
    const Vector3& operator[](uint32 i) const { return verts_[i]; }

    virtual void RenderGL();
    virtual void PreCalc();

    virtual bool Intersect(HitInfo& hit, const Ray& ray, float minDistance = 0.0f, float maxDistance = MAX_DISTANCE);

protected:
    Vector3 verts_[4];

private:
    float ComputeU(float v, const BLPatch::BLPatchData& patch);

    DISALLOW_COPY_CONSTRUCTORS(BLPatch);

}; // class BLPatch

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_BL_PATCH_H
