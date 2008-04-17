/////////////////////////////////////////////////////////////////////////////
// Class : bvh.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_BVH_H
#define RAWRAY_RAWRAY_BVH_H
#include "stdafx.h"
#include "object.h"
#include "hit_info.h"
#include "ray.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport BVH : public Object
{
public:
    BVH(std::vector<Object*>* objects) : Object(NULL), objects_(objects) { }
    virtual ~BVH() { }

    void Rebuild(std::vector<Object*>* objects);

    virtual void PreCalc();
    virtual void RenderGL();
    virtual bool Intersect(HitInfo& hit, const Ray& ray, float minDistance = 0.0f, float maxDistance = MAX_DISTANCE);

private:
    std::vector<Object*>* objects_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(BVH);

}; // class BVH

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_BVH_H
