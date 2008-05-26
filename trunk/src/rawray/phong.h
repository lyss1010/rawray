/////////////////////////////////////////////////////////////////////////////
// Class : phong.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_PHONG_H
#define RAWRAY_RAWRAY_PHONG_H
#include "stdafx.h"
#include "material.h"
#include "ray.h"
#include "hit_info.h"
#include "scene.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport Phong : public Material
{
public:
    Phong(const Vector3& color = Vector3(1.0f), float n=1.0f) : Material(), color_(color), n_(n) { }
    virtual ~Phong() { }

    void SetColor(const Vector3& color) { color_=color; }
	void SetN(float n) { n_=n; }
    const Vector3& GetColor() const { return color_; }
	float GetN() const { return n_; }

    virtual void PreCalc() { }
    
    //virtual Vector3 Shade(HitInfo& hit, Scene& scene) const;
	virtual void ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector3& shadedColor) const;
	virtual Vector3 BaseColor() const { return color_; }
	virtual float GetTranslucency() const { return 0.0f; }

protected:
    Vector3 color_;
	float n_;

private:
    DISALLOW_COPY_CONSTRUCTORS(Phong);

}; // class Phong


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_PHONG_H
