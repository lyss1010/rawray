/////////////////////////////////////////////////////////////////////////////
// Class : triangle_barycentric_projection.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_TRIANGLE_BARYCENTRIC_PROJECTION_H
#define RAWRAY_RAWRAY_TRIANGLE_BARYCENTRIC_PROJECTION_H
#include "stdafx.h"
#include "triangle.h"
#include "triangle_mesh.h"
#include "hit_info.h"
#include "ray.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport TriangleBarycentricProjection : public Triangle
{
public:
    TriangleBarycentricProjection(TriangleMesh& mesh, int index, const Material* material)
		: Triangle(mesh, index, material) { }

	virtual ~TriangleBarycentricProjection() { }

    //virtual void RenderGL();
    virtual void PreCalc();

    virtual bool Intersect(HitInfo& hit, float minDistance = 0.0f, float maxDistance = MAX_DISTANCE);

private:
	Vector3 n_, b_, c_;
	float det2d_;
	uint8 axis_, u_, v_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(TriangleBarycentricProjection);

}; // class TriangleBarycentricProjection


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_BARYCENTRIC_PROJECTION_H
