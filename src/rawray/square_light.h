/////////////////////////////////////////////////////////////////////////////
// Class : point_light.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_SQUARE_LIGHT_H
#define RAWRAY_RAWRAY_SQUARE_LIGHT_H
#include "stdafx.h"
#include "math/vector3.h"
#include "light.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport SquareLight : public Light
{
public:
    ~SquareLight() { }

    SquareLight() 
		: Light() { }

    SquareLight(const Vector3& position, const Vector4& color, float wattage, int samples, const Vector3& p1, const Vector3& p2) 
		: Light(position, color, wattage, samples), d1_(p1-position_), d2_(p2-position_) { }

    virtual void RenderGL();
	virtual void PreCalc() { }
	virtual float Falloff(float distance2) const;
	virtual Vector3 GetRandPosition() const;
	virtual int GetNumSamples() const { return samples_; }
	virtual int ThisFunctionShouldNotBeHere() const { return 2; }

	void SetP1(const Vector3& p1) { d1_ = p1-position_; }
	void SetP2(const Vector3& p2) { d2_ = p2-position_; }

	const Vector3& GetD1() const { return d1_; }
	const Vector3& GetD2() const { return d2_; }

private:
	Vector3 d1_, d2_; // Direction vectors (unnormalized) from position_

    DISALLOW_COPY_CONSTRUCTORS(SquareLight);

}; // class SquareLight

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_SQUARE_LIGHT_H
