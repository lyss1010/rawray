/////////////////////////////////////////////////////////////////////////////
// Class : material.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_MATERIAL_H
#define RAWRAY_RAWRAY_MATERIAL_H
#include "stdafx.h"
#include "ray.h"
#include "hit_info.h"
#include "scene.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport Material
{
public:
    Material() { }
    virtual ~Material() { }

    virtual void PreCalc() { }
    virtual Vector3 Shade(const Ray&, const HitInfo& hit, const Scene&) const;

}; // class Material


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_MATERIAL_H
