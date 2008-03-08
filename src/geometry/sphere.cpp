/////////////////////////////////////////////////////////////////////////////
// sphere.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "sphere.h"

namespace geometry {

    void Sphere::RenderGL() {
        //TriangleMesh::TupleI3 ti3 = m_mesh->vIndices()[m_index];
        //const Vector3 & v0 = m_mesh->vertices()[ti3.x]; //vertex a of triangle
        //const Vector3 & v1 = m_mesh->vertices()[ti3.y]; //vertex b of triangle
        //const Vector3 & v2 = m_mesh->vertices()[ti3.z]; //vertex c of triangle

        //glBegin(GL_TRIANGLES);
        //    glVertex3f(v0.x, v0.y, v0.z);
        //    glVertex3f(v1.x, v1.y, v1.z);
        //    glVertex3f(v2.x, v2.y, v2.z);
        //glEnd();
    }

    bool Sphere::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
        UNREFERENCED_PARAMETER(hit);
        UNREFERENCED_PARAMETER(ray);
        UNREFERENCED_PARAMETER(minDistance);
        UNREFERENCED_PARAMETER(maxDistance);
        return false;
    }

} // namespace geometry
