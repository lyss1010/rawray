/////////////////////////////////////////////////////////////////////////////
// Class : emitter.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_EMITTER_H
#define RAWRAY_RAWRAY_EMITTER_H
#include "stdafx.h"
#include "material.h"
#include "light.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport Emitter : public Material
{
public:
	Emitter(const Vector4& color = Vector4(1,1,1,1))
		: Material(), color_(color) { }

    virtual ~Emitter() { }

	virtual void PreCalc() { }
    virtual Vector4 Shade(HitInfo& hit, Scene& scene) const;
	virtual void ShadeLight(HitInfo& hit, Scene& scene, const Light& light, float intensity, Vector4& shadedColor) const;
	virtual Vector4 BaseColor() const { return color_; }
	virtual float GetTranslucency() const { return 0.0f; }

	void SetColor(const Vector4& color) { color_ = color; }

protected:
	Vector4 color_;

private:
    DISALLOW_COPY_CONSTRUCTORS(Emitter);

}; // class Emitter


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_EMITTER_H
