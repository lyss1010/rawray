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
    void SetPosition(const Vector3& position) { position_=position; }
    void SetColor(const Vector3& color) { color_=color; }
    void SetWattage(float wattage) { wattage_=wattage; }

    float GetWattage() { return wattage_; }
    const Vector3& GetColor() const { return color_; }
    const Vector3& GetPosition() const { return position_; }

    virtual void PreCalc();

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
