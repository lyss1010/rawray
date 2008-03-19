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

class DllExport Triangle : public Object
{
public:
    Triangle(TriangleMesh& mesh, uint32 index, const Material* material)
            : Object(material), mesh_(mesh), index_(index) { }

    virtual ~Triangle() { }

    TriangleMesh& GetMesh() { return mesh_; }
    uint32 GetIndex() const { return index_; }

    void SetMesh(TriangleMesh& mesh) { mesh_=mesh; }
    void SetIndex(uint32 index) { index_=index; }

    virtual void RenderGL();
    virtual void PreCalc();

    virtual bool Intersect(HitInfo& hit, const Ray& ray, float minDistance = 0.0f, float maxDistance = MAX_DISTANCE);

private:
    // Supported intersection algorithms
    bool Barycentric(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance);
    bool BarycentricProjection(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance);
    bool Moller(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance);
    bool Plucker(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance);

    void Interpolate(HitInfo& hit, float alpha, float beta);

    TriangleMesh& mesh_;
    uint32 index_;

    // Precomputed data
    Vector3 n_;         // Normal of the plane this triangle lines on
    

    DISALLOW_IMPLICIT_CONSTRUCTORS(Triangle);

}; // class Triangle


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_H
