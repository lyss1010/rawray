/////////////////////////////////////////////////////////////////////////////
// Class : triangle_moller.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_TRIANGLE_MOLLER_H
#define RAWRAY_RAWRAY_TRIANGLE_MOLLER_H
#include "stdafx.h"
#include "triangle.h"
#include "triangle_mesh.h"
#include "hit_info.h"
#include "ray.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class DllExport TriangleMoller : public Triangle
{
public:
    TriangleMoller(TriangleMesh& mesh, int index, const Material* material)
		: Triangle(mesh, index, material) { }

	virtual ~TriangleMoller() { }

    //virtual void RenderGL();
    virtual void PreCalc();

    virtual bool Intersect(HitInfo& hit, const Ray& ray, float minDistance = 0.0f, float maxDistance = MAX_DISTANCE);

private:
	Vector3 n_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(TriangleMoller);

}; // class TriangleMoller


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_MOLLER_H
