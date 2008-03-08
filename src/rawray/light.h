/////////////////////////////////////////////////////////////////////////////
// Class : light.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_LIGHT_H
#define RAWRAY_RAWRAY_LIGHT_H
#include "stdafx.h"
#include "vector3.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

struct DllExport Light
{
public:
    void SetPosition(const math::Vector3& position) { position_=position; }
    void SetColor(const math::Vector3& color) { color_=color; }
    void SetWattage(float wattage) { wattage_=wattage; }

    float GetWattage() { return wattage_; }
    const math::Vector3& GetColor() const { return color_; }
    const math::Vector3& GetPosition() const { return position_; }

    virtual void PreCalc();

protected:
    math::Vector3 position_;
    math::Vector3 color_;
    float wattage_;

private:
    DISALLOW_COPY_CONSTRUCTORS(Light);

}; // class Light

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_LIGHT_H
