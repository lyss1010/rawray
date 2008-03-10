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

class DllExport BLPatch : Object
{
public:
    BLPatch() : Object(NULL) { }
    virtual ~BLPatch() { }

    Vector3& operator[](uint32 i) { return verts_[i]; }
    const Vector3& operator[](uint32 i) const { return verts_[i]; }

    virtual void RenderGL();
    virtual void PreCalc();

    virtual bool Intersect(HitInfo& hit, const Ray& ray, float minDistance = 0.0f, float maxDistance = MAX_DISTANCE)=0;

protected:
    Vector3 verts_[4];

private:
    DISALLOW_COPY_CONSTRUCTORS(BLPatch);

}; // class BLPatch

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_BL_PATCH_H
