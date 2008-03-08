/////////////////////////////////////////////////////////////////////////////
// Class : triangle.h
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_GEOMETRY_TRIANGLE_H
#define RAWRAY_GEOMETRY_TRIANGLE_H
#include "stdafx.h"
#include "object.h"
#include "triangle_mesh.h"
#include "hit_info.h"
#include "ray.h"

/////////////////////////////////////////////////////////////////////////////
namespace geometry {

class DllExport Triangle : public Object
{
public:
    Triangle(TriangleMesh& mesh, uint32 index)
            : mesh_(mesh), index_(index) { }

    virtual ~Triangle() { }

    TriangleMesh& GetMesh() { return mesh_; }
    uint32 GetIndex() const { return index_; }

    void SetMesh(TriangleMesh& mesh) { mesh_=mesh; }
    void SetIndex(uint32 index) { index_=index; }

    virtual void RenderGL();
    virtual bool Intersect(HitInfo& hit, const Ray& ray, float minDistance = 0.0f, float maxDistance = MAX_DISTANCE);

private:
    TriangleMesh& mesh_;
    uint32 index_;

    DISALLOW_COPY_CONSTRUCTORS(Triangle);

}; // class Triangle


} // namespace geometry
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_GEOMETRY_TRIANGLE_H
