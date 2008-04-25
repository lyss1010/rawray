/////////////////////////////////////////////////////////////////////////////
// Class : colorful.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_COLORFUL_H
#define RAWRAY_RAWRAY_COLORFUL_H
#include "stdafx.h"
#include "material.h"
#include "ray.h"
#include "hit_info.h"
#include "scene.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport Colorful : public Material
{
public:
    Colorful() { }
    virtual ~Colorful() { }

    virtual void PreCalc() { }
    
    virtual Vector3 Shade(const HitInfo& hit, const Scene&) const;

private:
    DISALLOW_COPY_CONSTRUCTORS(Colorful);

}; // class Colorful


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_COLORFUL_H
