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

enum BVHNodeType { SPLIT_NODE=0, SINGLE_LEAF=1, MULTI_LEAF=2 };

struct BVHNode {
    BVHNodeType type;
	BoxAA box;
	
    union {
        BBoxAA*  leaf;
        BVHNode* children; // [left, right]
    };
	
	void RenderGL(const Vector3& color);

	bool Hit(const Ray& ray, float minDistance, float maxDistance) const;
    bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

    void BuildBVH( std::vector<BBoxAA*>::iterator begin, std::vector<BBoxAA*>::iterator end, float boxCost, float objCost );
	void DestroyBVH();

private:
    int8 Split( size_t& splitIndex, float& splitCost, std::vector<BBoxAA*>* sorted, float boxCost, float objCost, float areaParent );
    size_t FindSplittingPlane( std::vector<BBoxAA*>& sorted, float boxCost, float objCost );
    float Cost(float boxCost, float objCost, float areaParent, float areaLeft, float areaRight, int numLeft, int numRight);
};

class DllExport BVH : public Object
{
public:
    BVH(std::vector<Object*>* objects) : Object(NULL), objects_(objects), 
		objCost_(options::global::bvh_obj_cost), boxCost_(options::global::bvh_box_cost) { }

    virtual ~BVH();

    void Rebuild(std::vector<Object*>* objects);
	void SetObjCost(float cost) { objCost_ = cost; }
	void SetBoxCost(float cost) { boxCost_ = cost; }

    virtual void PreCalc();
    virtual void RenderGL();

    virtual Vector3 GetMin() { return root_.box[0]; }
    virtual Vector3 GetMax() { return root_.box[1]; }

	virtual bool Hit(const Ray& ray, float minDistance, float maxDistance) const;
    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

private:
    BVHNode root_;
    float objCost_, boxCost_;
    std::vector<Object*>* objects_;
	std::vector<BBoxAA*> forest_;
    
	void ClearBVH();
	void ClearForest();
    DISALLOW_COPY_CONSTRUCTORS(BVH);

}; // class BVH

} // namespace rawray
/////////////////////////////////////////////////////////////////////////////


#endif // RAWRAY_RAWRAY_BVH_H
