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
    Light() : position_(Vector3()), color_(Vector3()), wattage_(0), samples_(1) { }
    Light(const Vector3& position, const Vector3& color, float wattage, int samples) : position_(position), color_(color), wattage_(wattage), samples_(samples) { }

    void SetPosition(const Vector3& position) { position_=position; }
    void SetColor(const Vector3& color) { color_=color; }
    void SetWattage(float wattage) { wattage_=wattage; }
	void SetNumSamples(int samples) { samples_=samples; }

    float GetWattage() const { return wattage_; }
    const Vector3& GetColor() const { return color_; }
    const Vector3& GetPosition() const { return position_; }

    virtual void RenderGL()=0;
    virtual void PreCalc()=0;
	virtual float Falloff(float distance2) const=0;
	virtual Vector3 GetRandPosition() const=0;
	virtual int GetNumSamples() const=0;

protected:
    Vector3 position_;
    Vector3 color_;
    float wattage_;
	int samples_;

private:
    DISALLOW_COPY_CONSTRUCTORS(Light);

}; // class Light

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_LIGHT_H
