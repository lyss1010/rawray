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
	Material(float weight=1.0f) : weight_(weight) { }
	virtual ~Material() {}

	virtual void PreCalc() {}
    virtual Vector3 Shade(HitInfo& hit, Scene& scene) const;
	virtual void ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector3& shadedColor) const=0;
	virtual Vector3 BaseColor() const=0;
	virtual float GetTranslucency() const=0;

	void SetWeight(float weight) { weight_=weight; }
	float GetWeight() { return weight_; }

protected:
	float weight_;

}; // class Material


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_MATERIAL_H
