/////////////////////////////////////////////////////////////////////////////
// Class : refractive.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_REFRACTIVE_H
#define RAWRAY_RAWRAY_REFRACTIVE_H
#include "stdafx.h"
#include "material.h"
#include "ray.h"
#include "hit_info.h"
#include "scene.h"
#include "float.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport Refractive : public Material
{
public:
    Refractive(float ior = FLT_MAX) : Material(), ior_(ior) { }
    virtual ~Refractive() { }
    virtual void PreCalc() { }
    
    //virtual Vector3 Shade(HitInfo& hit, Scene& scene) const;
	virtual void ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector3& shadedColor) const;
	virtual Vector3 BaseColor() const { return Vector3(1); }

	void SetIOR(float ior) { ior_=ior; }

protected:
	float ior_;

private:
    DISALLOW_COPY_CONSTRUCTORS(Refractive);

}; // class Refractive


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_REFRACTIVE_H
