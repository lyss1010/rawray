/////////////////////////////////////////////////////////////////////////////
// Class : stone_bump.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_STONE_BUMP_H
#define RAWRAY_RAWRAY_STONE_BUMP_H
#include "stdafx.h"
#include "material.h"
#include "ray.h"
#include "hit_info.h"
#include "scene.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport StoneBump : public Material
{
public:
	StoneBump(float amplitude = 0.1f) : Material(), amplitude_(amplitude) { }
    virtual ~StoneBump() { }

    virtual void PreCalc() { }
    
    //virtual Vector4 Shade(HitInfo& hit, Scene& scene) const;
	virtual void ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector4& shadedColor) const;
	virtual Vector4 BaseColor() const { return Vector4(1); }
	virtual float GetTranslucency() const { return 0.0f; }

	void SetAmplitude(float amplitude) { amplitude_ = amplitude; }

protected:
	float amplitude_;

private:
    DISALLOW_COPY_CONSTRUCTORS(StoneBump);

}; // class StoneBump


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_STONE_BUMP_H
