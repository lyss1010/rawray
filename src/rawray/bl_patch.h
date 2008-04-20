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
    BLPatch(Material* material) : Object(material) { }
    virtual ~BLPatch() { }

    void SetP00(const Vector3& v) { P00 = v; }
    void SetP01(const Vector3& v) { P01 = v; }
    void SetP10(const Vector3& v) { P10 = v; }
    void SetP11(const Vector3& v) { P11 = v; }

    virtual void RenderGL();
    virtual void PreCalc();

    virtual bool Intersect(HitInfo& hit, const Ray& ray, float minDistance = 0.0f, float maxDistance = MAX_DISTANCE);

protected:
    Vector3 P00, P01, P10, P11;

private:
    int ComputeV(float* out1, float* out2, 
                 float a, float b, float c, 
                 float min, float max, 
                 float mid1, float mid2);

    //float ComputeU(float v, const BLPatch::BLPatchData& patch);
	//bool IsValid(float t, float u, float v, float min, float max, float mid1, float mid2);

    bool RayPatchIntersection(const Vector3& r, const Vector3& q, Vector3& uv);
    Vector3 SrfEval(double u, double v);
    Vector3 TanU(double v);
    Vector3 TanV(double u);
    Vector3 Normal(double u, double v);

    DISALLOW_COPY_CONSTRUCTORS(BLPatch);

}; // class BLPatch

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_BL_PATCH_H
