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
#include "bbox_aa.h"

/////////////////////////////////////////////////////////////////////////////
namespace rawray {

struct BVHNode {
    bool isLeaf;
	BoxAA box;
	
    union {
        BBoxAA*  leaf;
        BVHNode* children; // [left, right]
    };
	
	void RenderGL(const Vector3& color);

	bool Hit(const Ray& ray, float minDistance, float maxDistance) const;
    bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

    void BuildBVH( std::vector<BBoxAA*>& forrset );

private:
    int8 Split( size_t& splitIndex, std::vector<BBoxAA*>* sorted );
    size_t FindSplittingPlane( std::vector<BBoxAA*>& sorted );
    float Cost(float areaLeft, float areaRight, int numLeft, int numRight);
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
    virtual Vector3 GetMin() { return root_.box[0]; }
    virtual Vector3 GetMax() { return root_.box[1]; }

	virtual bool Hit(const Ray& ray, float minDistance, float maxDistance) const;
    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

private:
    BVHNode root_;
    float ojb_cost, box_cost;
    std::vector<Object*>* objects_;
	std::vector<BBoxAA*> forest_;
    
	void ClearForest();
    DISALLOW_COPY_CONSTRUCTORS(BVH);

}; // class BVH

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_BVH_H
