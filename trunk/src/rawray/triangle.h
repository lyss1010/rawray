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
#include "stats.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray {

class SSE_ALIGN PluckerCoord {
public:
    PluckerCoord() { }
    PluckerCoord(const Vector3& direction, const Vector3& point);

    float GetOrientation(const PluckerCoord& p) const;

public:
    Vector3 u_, v_;
};

class DllExport Triangle : public Object
{
public:
    TriangleMesh* GetMesh() { return mesh_; }
    int GetIndex() const { return index_; }

    void SetMesh(TriangleMesh* mesh) { mesh_=mesh; }
    void SetIndex(int index) { index_=index; }
    void Set(TriangleMesh* mesh, int index, Material* material) { mesh_=mesh; index_=index; material_=material; }

	virtual void deleteObject()=0;
    virtual void RenderGL();
    virtual void PreCalc()=0;
    virtual Vector3 GetMin();
    virtual Vector3 GetMax();

	virtual bool Hit(const Ray& ray, float minDistance, float maxDistance) const=0;
    virtual bool Intersect(HitInfo& hit, float minDistance, float maxDistance)=0;
    virtual void IntersectPack(HitPack& hitpack, float minDistance, float maxDistance);

	Vector3 ComputeBarycentric(const Vector3& point) const;

protected:
    void Interpolate(HitInfo& hit, float alpha, float beta, float gamma);

	TriangleMesh* mesh_;
    int index_;

    Triangle(TriangleMesh* mesh, int index, Material* material)
		: Object(material), mesh_(mesh), index_(index) { }

    virtual ~Triangle() { }

private:
	DISALLOW_IMPLICIT_CONSTRUCTORS(Triangle);

}; // class Triangle


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_H
