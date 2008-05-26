/////////////////////////////////////////////////////////////////////////////
// Class : diffuse.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_DIFFUSE_H
#define RAWRAY_RAWRAY_DIFFUSE_H
#include "stdafx.h"
#include "material.h"
#include "ray.h"
#include "hit_info.h"
#include "scene.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport Diffuse : public Material
{
public:
    Diffuse(const Vector3& color = Vector3(1.0f)) : Material(), color_(color) { }

    virtual ~Diffuse() { }

    void SetColor(const Vector3& color) { color_=color; }
    const Vector3& GetColor() const { return color_; }

    virtual void PreCalc() { }
    
    //virtual Vector3 Shade(HitInfo& hit, Scene& scene) const;
	virtual void ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector3& shadedColor) const;
	virtual Vector3 BaseColor() const { return color_; }
	virtual float GetTranslucency() const { return 0.0f; }

protected:
    Vector3 color_;

private:
    DISALLOW_COPY_CONSTRUCTORS(Diffuse);

}; // class Diffuse


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_DIFFUSE_H
