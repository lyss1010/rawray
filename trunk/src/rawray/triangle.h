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

class Triangle;
typedef bool (Triangle::*TriangleIntersectFunc)(HitInfo&, const Ray&, float, float);
typedef void (Triangle::*TrianglePreCalcFunc)();

class PluckerCoord {
public:
    PluckerCoord(const Vector3& direction, const Vector3& point);
    float GetOrientation(const PluckerCoord& p);

private:
    Vector3 u_, v_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(PluckerCoord);
};

class DllExport Triangle : public Object
{
public:
    Triangle(TriangleMesh& mesh, uint32 index, const Material* material);
    virtual ~Triangle();

    TriangleMesh& GetMesh() { return mesh_; }
    uint32 GetIndex() const { return index_; }

    void SetMesh(TriangleMesh& mesh) { mesh_=mesh; }
    void SetIndex(uint32 index) { index_=index; }

    virtual void RenderGL();
    virtual void PreCalc();

    virtual bool Intersect(HitInfo& hit, const Ray& ray, float minDistance = 0.0f, float maxDistance = MAX_DISTANCE);

private:
    // Supported intersection algorithms
    bool IntersectBarycentric(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance);
    bool IntersectBarycentricProjection(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance);
    bool IntersectMoller(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance);
    bool IntersectPlucker(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance);

    // Precalc for each intersection algorithm
    void PreCalcBarycentric();
    void PreCalcBarycentricProjection();
    void PreCalcMoller();
    void PreCalcPlucker();

    void Interpolate(HitInfo& hit, float alpha, float beta, float gamma);

    TriangleIntersectFunc intersect_;
    TrianglePreCalcFunc preCalc_;

    TriangleMesh& mesh_;
    uint32 index_;

    // Defined only if using BarycentricProjection or Moller intersections (NOTE: Unnormaized)
    Vector3* n_;

    // Defined only if using BarycentricProjection
    Vector3* det2d_;

    // Defined only if using Plucker intersections
    PluckerCoord* pluckA_;
    PluckerCoord* pluckB_;
    PluckerCoord* pluckC_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(Triangle);

}; // class Triangle


} // namespace rawray
/////////////////////////////////////////////////////////////////////////////

#endif // RAWRAY_RAWRAY_TRIANGLE_H
