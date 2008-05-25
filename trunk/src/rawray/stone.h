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
	Stone(const Vector3& colorA = Vector3(1), const Vector3& colorB = Vector3(0.5f)) : Material(), colorA_(colorA), colorB_(colorB) { }
    virtual ~Stone() { }

    virtual void PreCalc() { }
    
    //virtual Vector3 Shade(HitInfo& hit, Scene& scene) const;
	virtual void ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector3& shadedColor) const;
	virtual Vector3 BaseColor() const { return Vector3(1); }

	void SetColorA(const Vector3& colorA) { colorA_ = colorA; }
	void SetColorB(const Vector3& colorB) { colorB_ = colorB; }

protected:
	Vector3 colorA_, colorB_;

private:
    DISALLOW_COPY_CONSTRUCTORS(Stone);

}; // class Stone


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_STONE_H
