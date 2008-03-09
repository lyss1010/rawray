/////////////////////////////////////////////////////////////////////////////
// triangle.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "triangle.h"
#include "math/tuple3.h"

namespace rawray {

    void Triangle::RenderGL() {
        Tuple3I indicies = mesh_.GetVertexIndices()[ index_ ];

        const Vector3 & v0 = mesh_.GetVertices()[ indicies.x ];
        const Vector3 & v1 = mesh_.GetVertices()[ indicies.y ];
        const Vector3 & v2 = mesh_.GetVertices()[ indicies.z ];

        //glBegin(GL_TRIANGLES);
        //    glVertex3f(v0.x, v0.y, v0.z);
        //    glVertex3f(v1.x, v1.y, v1.z);
        //    glVertex3f(v2.x, v2.y, v2.z);
        //glEnd();
    }

    bool Triangle::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
        switch( options::triangle_intersection_algorithm )
        {
        case options::BARYCENTRIC:
            return Barycentric(hit, ray, minDistance, maxDistance);

        case options::MOLLER:
            return Moller(hit, ray, minDistance, maxDistance);

        case options::PLUCKER:
            return Plucker(hit, ray, minDistance, maxDistance);

        default:
            return false;
        }
    }

    bool Triangle::Barycentric(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
        // TODO: Write algorithm
        return false;
    }

    bool Triangle::Moller(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
        // TODO: Write algorithm
        return false;
    }

    bool Triangle::Plucker(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
        // TODO: Write algorithm
        return false;
    }

} // namespace rawray
