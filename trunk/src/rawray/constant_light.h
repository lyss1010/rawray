/////////////////////////////////////////////////////////////////////////////
// Class : point_light.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_CONSTANT_LIGHT_H
#define RAWRAY_RAWRAY_CONSTANT_LIGHT_H
#include "stdafx.h"
#include "math/vector3.h"
#include "light.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport ConstantLight : public Light
{
public:
    ~ConstantLight() { }

    ConstantLight() 
		: Light() { }

    ConstantLight(const Vector3& position, const Vector3& color, float wattage) 
		: Light(position, color, wattage) { }

    //virtual void RenderGL();
	virtual void PreCalc() { }
	virtual float Falloff(const Vector3& direction);

private:
    DISALLOW_COPY_CONSTRUCTORS(ConstantLight);

}; // class ConstantLight

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_CONSTANT_LIGHT_H
