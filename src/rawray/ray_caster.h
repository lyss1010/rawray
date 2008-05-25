/////////////////////////////////////////////////////////////////////////////
// Class : ray_caster.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_RAY_CASTER_H
#define RAWRAY_RAWRAY_RAY_CASTER_H
#include "stdafx.h"
#include "camera.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class HitPack;

class DllExport RayCaster {
public:
	explicit RayCaster() : hitpacks_(NULL), numpacks_(0), aax_(0), aay_(0), maxRays_(65536) { }
    RayCaster(int aax, int aay) : aax_(aax), aay_(aay), hitpacks_(NULL), numpacks_(0), maxRays_(65536) { }
	RayCaster(const RayCaster& c) : aax_(c.aax_), aay_(c.aay_), hitpacks_(NULL), numpacks_(0), maxRays_(65536) { }
    ~RayCaster() { SAFE_DELETE_ARRAY(hitpacks_); }

    void GenerateRays(const Camera& cam, int xmin, int xmax, int ymin, int ymax, int imgWidth, int imgHeight);

    int GetNumPacks() { return numpacks_; }
    HitPack* GetHitPacks() { return hitpacks_; }
	float GetIncrement() { return 1.0f / (aax_*aay_); }
	int GetNumDivisions(int xPixels, int yPixels);

	void SetMaxRays(int maxRays) { maxRays_=maxRays; }
	void SetAAX(int aax) { aax_=aax; }
	void SetAAY(int aay) { aay_=aay; }

protected:
    HitPack* hitpacks_;
    int numpacks_;
    int aax_;
    int aay_;
	int maxRays_;

}; // class RayCaster

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_RAY_CASTER_H
