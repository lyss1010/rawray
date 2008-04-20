/////////////////////////////////////////////////////////////////////////////
// Class : triangle_plucker.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_TRIANGLE_PLUCKER_H
#define RAWRAY_RAWRAY_TRIANGLE_PLUCKER_H
#include "stdafx.h"
#include "triangle.h"
#include "triangle_mesh.h"
#include "hit_info.h"
#include "ray.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport TrianglePlucker : public Triangle
{
public:
    TrianglePlucker(TriangleMesh& mesh, int index, const Material* material)
		: Triangle(mesh, index, material) { }

	virtual ~TrianglePlucker() { }

    //virtual void RenderGL();
    virtual void PreCalc();

    virtual bool Intersect(HitInfo& hit, const Ray& ray, float minDistance = 0.0f, float maxDistance = MAX_DISTANCE);

private:
    PluckerCoord pluckA_;
    PluckerCoord pluckB_;
    PluckerCoord pluckC_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(TrianglePlucker);

}; // class TrianglePlucker


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_PLUCKER_H
