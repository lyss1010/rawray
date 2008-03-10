/////////////////////////////////////////////////////////////////////////////
// Class : lambert.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_LAMBERT_H
#define RAWRAY_RAWRAY_LAMBERT_H
#include "stdafx.h"
#include "material.h"
#include "ray.h"
#include "hit_info.h"
#include "scene.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport Lambert : public Material
{
public:
    Lambert(const Vector3& diffuse = Vector3(1.0f),
            const Vector3& ambient = Vector3(0.0f)) : Material(), diffuse_(diffuse), ambient_(ambient) { }

    virtual ~Lambert() { }

    void SetDiffuse(const Vector3& diffuse) { diffuse_=diffuse; }
    void SetAmbient(const Vector3& ambient) { ambient_=ambient; }

    const Vector3& GetDiffuse() { return diffuse_; }
    const Vector3& GetAmbient() { return ambient_; }

    virtual void PreCalc() { }
    
    Vector3 Shade(const Ray&, const HitInfo& hit, const Scene&) const;


protected:
    Vector3 diffuse_;
    Vector3 ambient_;

private:
    DISALLOW_COPY_CONSTRUCTORS(Lambert);

}; // class Lambert


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_LAMBERT_H
