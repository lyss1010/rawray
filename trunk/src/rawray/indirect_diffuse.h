/////////////////////////////////////////////////////////////////////////////
// Class : indirect_diffuse.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_INDIRECT_DIFFUSE_H
#define RAWRAY_RAWRAY_INDIRECT_DIFFUSE_H
#include "stdafx.h"
#include "material.h"
#include "ray.h"
#include "hit_info.h"
#include "scene.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport IndirectDiffuse : public Material
{
public:
    IndirectDiffuse(float weight = 1.0f) : Material(), weight_(weight) { }
    virtual ~IndirectDiffuse() { }

    virtual void PreCalc() { }
    
    //virtual Vector3 Shade(HitInfo& hit, Scene& scene) const;
	virtual void ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector3& shadedColor) const;
	virtual Vector3 BaseColor() const { return Vector3(1); }

	void SetWeight(float weight) { weight_=weight; }

protected:
	float weight_;

private:
    DISALLOW_COPY_CONSTRUCTORS(IndirectDiffuse);

}; // class IndirectDiffuse


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_INDIRECT_DIFFUSE_H
