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

class SSE_ALIGN DllExport TrianglePlucker : public Triangle
{
public:
    static TrianglePlucker* newTriangle(TriangleMesh* mesh, int index, Material* material);

    virtual void deleteObject();
	//virtual void RenderGL();
    virtual void PreCalc();
    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance);
    
#ifdef SSE
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);
#endif // SSE

protected:
    TrianglePlucker(TriangleMesh* mesh, int index, Material* material)
		: Triangle(mesh, index, material) { }

	virtual ~TrianglePlucker() { }

private:
    SSE_ALIGN PluckerCoord pluckA_;
    SSE_ALIGN PluckerCoord pluckB_;
    SSE_ALIGN PluckerCoord pluckC_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(TrianglePlucker);

}; // class TrianglePlucker


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_PLUCKER_H
