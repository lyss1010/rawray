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
    bool isLeaf;
	
    union {
        BBoxAA*  bbox;
        BVHNode* children; // [left, right]
    };
	
    bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);
    void BuildBVH( std::vector<BBoxAA*>& forrset );

private:
    int8 Split( size_t& splitIndex, std::vector<BBoxAA*>* sorted );
    size_t FindSplittingPlane( std::vector<BBoxAA*>& sorted );
    float Cost(float areaLeft, float areaRight);
};

class DllExport BVH : public Object
{
public:
    BVH(std::vector<Object*>* objects) : Object(NULL), objects_(objects) { }
    virtual ~BVH();

    void Rebuild(std::vector<Object*>* objects);

    virtual void PreCalc();
    virtual void RenderGL();

    // TODO: Write me
    virtual Vector3 GetMin() { return Vector3(-MAX_DISTANCE); }
    virtual Vector3 GetMax() { return Vector3( MAX_DISTANCE); }

    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

private:
    BVHNode root_;
    float ojb_cost, box_cost;
    std::vector<Object*>* objects_;
    
    DISALLOW_COPY_CONSTRUCTORS(BVH);

}; // class BVH

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_BVH_H
