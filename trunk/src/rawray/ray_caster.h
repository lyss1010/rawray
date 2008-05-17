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
    RayCaster(const Camera& cam, int aax, int aay) : cam_(cam), aax_(aax), aay_(aay), hitpacks_(NULL), numpacks_(0) { }
    ~RayCaster() { SAFE_DELETE_ARRAY(hitpacks_); }

    void GenerateRays(int xmin, int xmax, int ymin, int ymax, int width, int height);

    int GetNumPacks() { return numpacks_; }
    HitPack* GetHitPacks() { return hitpacks_; }

protected:
    const Camera& cam_;
    HitPack* hitpacks_;
    int numpacks_;
    int aax_;
    int aay_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(RayCaster);

}; // class RayCaster

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_RAY_CASTER_H
