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

class DllExport TriangleBarycentric : public Triangle
{
public:
	TriangleBarycentric(TriangleMesh& mesh, int index, const Material* material)
		: Triangle(mesh, index, material) { }

	virtual ~TriangleBarycentric() { }

    //virtual void RenderGL();
    virtual void PreCalc();
    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    //virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

private:
    DISALLOW_IMPLICIT_CONSTRUCTORS(TriangleBarycentric);

}; // class TriangleBarycentric


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_BARYCENTRIC_H
