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
    Phong(const Vector4& color = Vector4(1), 
			float n=1.0f) 
		: Material(), color_(color), n_(n) { }

    virtual ~Phong() { }

    void SetColor(const Vector4& color) { color_=color; }
	void SetN(float n) { n_=n; }
    const Vector4& GetColor() const { return color_; }
	float GetN() const { return n_; }

    virtual void PreCalc() { }
    
    //virtual Vector4 Shade(HitInfo& hit, Scene& scene) const;
	virtual void ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector4& shadedColor) const;
	virtual Vector4 BaseColor() const { return color_; }
	virtual float GetTranslucency() const { return 0.0f; }

protected:
    Vector4 color_;
	float n_;

private:
    DISALLOW_COPY_CONSTRUCTORS(Phong);

}; // class Phong


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_PHONG_H
