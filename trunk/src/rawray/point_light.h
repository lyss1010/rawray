/////////////////////////////////////////////////////////////////////////////
// Class : point_light.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_POINT_LIGHT_H
#define RAWRAY_RAWRAY_POINT_LIGHT_H
#include "stdafx.h"
#include "math/vector3.h"
#include "light.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport PointLight : public Light
{
public:
    ~PointLight() { }

    PointLight() 
		: Light() { }

    PointLight(const Vector3& position, const Vector4& color, float wattage, int samples) 
		: Light(position, color, wattage, samples) { }

    virtual void RenderGL();
	virtual void PreCalc() { }
	virtual float Falloff(float distance2) const;
	virtual Vector3 GetRandPosition() const { return position_; }
	virtual int GetNumSamples() const { return 1; }

private:
    DISALLOW_COPY_CONSTRUCTORS(PointLight);

}; // class PointLight

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_POINT_LIGHT_H
