/////////////////////////////////////////////////////////////////////////////
// Class : triangle.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_TRIANGLE_H
#define RAWRAY_RAWRAY_TRIANGLE_H
#include "stdafx.h"
#include "object.h"
#include "triangle_mesh.h"
#include "hit_info.h"
#include "ray.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class PluckerCoord {
public:
    PluckerCoord() { }
    PluckerCoord(const Vector3& direction, const Vector3& point);

    float GetOrientation(const PluckerCoord& p);

private:
    Vector3 u_, v_;
};

class DllExport Triangle : public Object
{
public:
	virtual ~Triangle() { }

    TriangleMesh& GetMesh() { return mesh_; }
    int GetIndex() const { return index_; }

    void SetMesh(TriangleMesh& mesh) { mesh_=mesh; }
    void SetIndex(int index) { index_=index; }

    virtual void RenderGL();
    virtual void PreCalc()=0;

    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance)=0;
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

	Vector3 ComputeBarycentric(const Vector3& point) const;

protected:
	Triangle(TriangleMesh& mesh, int index, const Material* material)
		: Object(material), mesh_(mesh), index_(index) { }
	
    void Interpolate(HitInfo& hit, float alpha, float beta, float gamma);

	TriangleMesh& mesh_;
    int index_;

private:
	DISALLOW_IMPLICIT_CONSTRUCTORS(Triangle);

}; // class Triangle


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_H
