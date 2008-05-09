/////////////////////////////////////////////////////////////////////////////
// Class : triangle_barycentric.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_TRIANGLE_BARYCENTRIC_H
#define RAWRAY_RAWRAY_TRIANGLE_BARYCENTRIC_H
#include "stdafx.h"
#include "triangle.h"
#include "triangle_mesh.h"
#include "hit_info.h"
#include "ray.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class SSE_ALIGN DllExport TriangleBarycentric : public Triangle
{
public:
    static TriangleBarycentric* newTriangle(TriangleMesh* mesh, int index, Material* material);

	virtual void deleteObject();
    //virtual void RenderGL();
    virtual void PreCalc();
    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    //virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);
	virtual bool Hit(const Ray& ray, float minDistance, float maxDistance) const;

protected:
    TriangleBarycentric(TriangleMesh* mesh, int index, Material* material)
		: Triangle(mesh, index, material) { }

	virtual ~TriangleBarycentric() { }

private:
    DISALLOW_IMPLICIT_CONSTRUCTORS(TriangleBarycentric);
    
}; // class TriangleBarycentric


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_BARYCENTRIC_H
