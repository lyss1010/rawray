/////////////////////////////////////////////////////////////////////////////
// Class : light.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_LIGHT_H
#define RAWRAY_RAWRAY_LIGHT_H
#include "stdafx.h"
#include "math/vector3.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport Light
{
public:
    ~Light() { }
    Light() : position_(Vector3()), color_(Vector3()), wattage_(0) { }
    Light(const Vector3& position, const Vector3& color, float wattage) : position_(position), color_(color), wattage_(wattage) { }

    void SetPosition(const Vector3& position) { position_=position; }
    void SetColor(const Vector3& color) { color_=color; }
    void SetWattage(float wattage) { wattage_=wattage; }

    float GetWattage() const { return wattage_; }
    const Vector3& GetColor() const { return color_; }
    const Vector3& GetPosition() const { return position_; }

    virtual void RenderGL();
    virtual void PreCalc()=0;
	virtual float Falloff(float distance2)=0;

protected:
    Vector3 position_;
    Vector3 color_;
    float wattage_;

private:
    DISALLOW_COPY_CONSTRUCTORS(Light);

}; // class Light

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_LIGHT_H
