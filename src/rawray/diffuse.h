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
    Diffuse(const Vector4& color = Vector4(1)) : Material(), color_(color) { }

    virtual ~Diffuse() { }

    void SetColor(const Vector4& color) { color_=color; }
    const Vector4& GetColor() const { return color_; }

    virtual void PreCalc() { }
    
    //virtual Vector4 Shade(HitInfo& hit, Scene& scene) const;
	virtual void ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector4& shadedColor) const;
	virtual Vector4 BaseColor() const { return color_; }
	virtual float GetTranslucency() const { return 0.0f; }

protected:
    Vector4 color_;

private:
    DISALLOW_COPY_CONSTRUCTORS(Diffuse);

}; // class Diffuse


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_DIFFUSE_H
