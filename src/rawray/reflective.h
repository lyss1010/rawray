/////////////////////////////////////////////////////////////////////////////
// Class : reflective.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_REFLECTIVE_H
#define RAWRAY_RAWRAY_REFLECTIVE_H
#include "stdafx.h"
#include "material.h"
#include "ray.h"
#include "hit_info.h"
#include "scene.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport Reflective : public Material
{
public:
    Reflective() : Material() { }
    virtual ~Reflective() { }
    virtual void PreCalc() { }
    
    //virtual Vector4 Shade(HitInfo& hit, Scene& scene) const;
	virtual void ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector4& shadedColor) const;
	virtual Vector4 BaseColor() const { return Vector4(1); }
	virtual float GetTranslucency() const { return 0.0f; }

private:
    DISALLOW_COPY_CONSTRUCTORS(Reflective);

}; // class Reflective


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_REFLECTIVE_H
