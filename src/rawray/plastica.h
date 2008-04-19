/////////////////////////////////////////////////////////////////////////////
// Class : plastica.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_PLASTICA_H
#define RAWRAY_RAWRAY_PLASTICA_H
#include "stdafx.h"
#include "material.h"
#include "ray.h"
#include "hit_info.h"
#include "scene.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

// Lambert material that modifies normal to point in direction of incoming ray
class DllExport Plastica : public Material
{
public:
    Plastica(const Vector3& diffuse = Vector3(1.0f),
             const Vector3& ambient = Vector3(0.0f)) : Material(), diffuse_(diffuse), ambient_(ambient) { }

    virtual ~Plastica() { }

    void SetDiffuse(const Vector3& diffuse) { diffuse_=diffuse; }
    void SetAmbient(const Vector3& ambient) { ambient_=ambient; }

    const Vector3& GetDiffuse() { return diffuse_; }
    const Vector3& GetAmbient() { return ambient_; }

    virtual void PreCalc() { }
    
    virtual Vector3 Shade(const Ray&, const HitInfo& hit, const Scene&) const;
	virtual Vector3 BaseColor() const { return diffuse_; }

protected:
    Vector3 diffuse_;
    Vector3 ambient_;

private:
    DISALLOW_COPY_CONSTRUCTORS(Plastica);

}; // class Plastica


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_PLASTICA_H
