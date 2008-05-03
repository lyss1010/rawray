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

class BBoxAA;

struct BVHNode {
    Vector3 min, max;

    union {
        BBoxAA*  bbox;
        BVHNode* children; // [left, right]
    };
};

class DllExport BVH : public Object
{
public:
    BVH(std::vector<Object*>* objects) : Object(NULL), singleton_(NULL) { }
    virtual ~BVH() { }

    void Rebuild(std::vector<Object*>* objects);

    virtual void PreCalc();
    virtual void RenderGL();

    // TODO: Write me
    virtual Vector3 GetMin() { return Vector3(-MAX_DISTANCE); }
    virtual Vector3 GetMax() { return Vector3( MAX_DISTANCE); }

    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

private:
    Object* singleton_; // 

    std::vector<BBoxAA*>::iterator FindSplit( std::vector<BBoxAA*> sorted );

    DISALLOW_IMPLICIT_CONSTRUCTORS(BVH);

}; // class BVH

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_BVH_H
