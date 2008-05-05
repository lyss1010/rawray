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

    PointLight(const Vector3& position, const Vector3& color, float wattage) 
		: Light(position, color, wattage) { }

    //virtual void RenderGL();
	virtual void PreCalc() { }
	virtual float Falloff(const Vector3& direction);

private:
    DISALLOW_COPY_CONSTRUCTORS(PointLight);

}; // class PointLight

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_POINT_LIGHT_H