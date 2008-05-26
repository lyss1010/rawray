/////////////////////////////////////////////////////////////////////////////
// Class : sphere_light.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_SPHERE_LIGHT_H
#define RAWRAY_RAWRAY_SPHERE_LIGHT_H
#include "stdafx.h"
#include "math/vector3.h"
#include "light.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport SphereLight : public Light
{
public:
    ~SphereLight() { }

    SphereLight() 
		: Light(), radius_(1.0f) { }

    SphereLight(const Vector3& position, const Vector4& color, float wattage, int samples, float radius) 
		: Light(position, color, wattage, samples), radius_(radius) { }

    virtual void RenderGL();
	virtual void PreCalc() { }
	virtual float Falloff(float distance2) const;
	virtual Vector3 GetRandPosition() const;
	virtual int GetNumSamples() const { return samples_; }

	void SetRadius(float radius) { radius_ = radius; }
	float GetRadius() { return radius_; }

private:
	float radius_;

    DISALLOW_COPY_CONSTRUCTORS(SphereLight);

}; // class SphereLight

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_SPHERE_LIGHT_H
