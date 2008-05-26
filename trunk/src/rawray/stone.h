/////////////////////////////////////////////////////////////////////////////
// Class : stone.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_STONE_H
#define RAWRAY_RAWRAY_STONE_H
#include "stdafx.h"
#include "material.h"
#include "ray.h"
#include "hit_info.h"
#include "scene.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport Stone : public Material
{
public:
	Stone(const Vector4& colorA = Vector4(1), 
		  const Vector4& colorB = Vector4(0) ) 
		: Material(), colorA_(colorA), colorB_(colorB) { }

    virtual ~Stone() { }

    virtual void PreCalc() { }
    
    //virtual Vector4 Shade(HitInfo& hit, Scene& scene) const;
	virtual void ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector4& shadedColor) const;
	virtual Vector4 BaseColor() const { return Vector4(1); }
	virtual float GetTranslucency() const { return 0.0f; }

	void SetColorA(const Vector4& colorA) { colorA_ = colorA; }
	void SetColorB(const Vector4& colorB) { colorB_ = colorB; }

protected:
	Vector4 colorA_, colorB_;

private:
    DISALLOW_COPY_CONSTRUCTORS(Stone);

}; // class Stone


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_STONE_H
