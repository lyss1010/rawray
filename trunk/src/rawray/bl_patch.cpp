/////////////////////////////////////////////////////////////////////////////
// bl_patch.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "bl_patch.h"

namespace rawray {



void BLPatch::RenderGL() {
}

void BLPatch::PreCalc() {
}

// See: http://www.cs.utah.edu/~kpotter/pubs/bilinear.pdf
bool BLPatch::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    UNREFERENCED_PARAMETER(hit);
    UNREFERENCED_PARAMETER(ray);
    UNREFERENCED_PARAMETER(minDistance);
    UNREFERENCED_PARAMETER(maxDistance);

    const Vector3& a = verts_[3] - verts_[2] - verts_[1] + verts_[0];
    const Vector3& b = verts_[2] - verts_[0];
    const Vector3& c = verts_[1] - verts_[0];
    const Vector3& d = verts_[0];
    const Vector3& q = ray.origin;
    const Vector3& r = ray.direction;

    // Manually solving: r + t*q = uv*a + u*b + v*c + d
    BLPatch::BLPatchData patch;
    patch.a1 = a.x*q.z - a.z*q.x;
    patch.b1 = b.x*q.z - b.z*q.x;
    patch.c1 = c.x*q.z - c.z*q.x;
    patch.d1 = (d.x-r.x)*q.z - (d.z-r.z)*q.x;

    patch.a2 = a.y*q.z - a.z*q.y;
    patch.b2 = b.y*q.z - b.z*q.y;
    patch.c2 = c.y*q.z - c.z*q.y;
    patch.d2 = (d.y-r.y)*q.z - (d.z-r.z)*q.y;

    // Solve this quadratic equation
    // 0 = v^2(A2C1-A1C2) + v(A2D1-A1D2+B2C1-B1C2) + (B2D1-B1D2)
    float v1, v2;
    int numRoots = math::SolveQuadratic( &v1, &v2, 
                        (patch.a2*patch.c1 - patch.a1*patch.c2), 
                        (patch.a2*patch.d1 - patch.a1*patch.d2 + patch.b2*patch.c1 - patch.b1*patch.c2),
                        (patch.b2*patch.d1 - patch.b1*patch.d2) );

    if( numRoots < 1 ) return false;

    // A point on the plane
    Vector3 p;

    // The interpolation coordinates of the point
    float u, v, t;
    const Vector3 absQ( fabs(q.x), fabs(q.y), fabs(q.z) );

    if( numRoots == 1 ) {
        v = v1;
        u = ComputeU(v, patch);
        p = u*v*a + u*b + u*c + d;
        t = ComputeT(ray, p, absQ);
    } else {
        float u1 = ComputeU(v1, patch);
        float u2 = ComputeU(v2, patch);
        Vector3 p1( u1*v1*a + u1*b + u1*c + d );
        Vector3 p2( u2*v2*a + u2*b + u2*c + d );
        float t1 = ComputeT(ray, p1, absQ);
        float t2 = ComputeT(ray, p1, absQ);

        // Closest non negative distance
        // We will check t2 for negativeness later
        if( t1 < 0.0f || t2 < t1 ) {
            t = t2;
            u = u2;
            v = v2;
            p = p2;
        } else {
            t = t1;
            u = u1;
            v = v1;
            p = p1;
        }
    }
    
    if( t < 0.0f ) return false;

    hit.distance = t;
    hit.point = p;
    hit.material = material_;
    hit.texCoord.x = u;
    hit.texCoord.y = v;
    hit.normal = Vector3(0,1,0); // TODO: Compute 2 lines of u,v and cross them
    
    return false;
}

float BLPatch::ComputeU(float v, const BLPatch::BLPatchData& patch) {
    const float divisor_a = v*patch.a2 + patch.b2;
    const float divisor_b = v*(patch.a2-patch.a1) + patch.b2 - patch.b1;

    if( fabs(divisor_b) > fabs(divisor_a) )
        return (v*(patch.c1-patch.c2) + patch.d1 - patch.d2) / divisor_b;
    else
        return (-v*patch.c2 - patch.d2) / divisor_a;
}

float BLPatch::ComputeT(const Ray& ray, const Vector3& p, const Vector3& absQ) {
    if( absQ.x >= absQ.y && absQ.x >= absQ.z )
        return (p.x - ray.direction.x)/ray.origin.x;
    else if( absQ.y >= absQ.z )
        return (p.y - ray.direction.y)/ray.origin.y;
    else
        return (p.z - ray.direction.z)/ray.origin.z;
}

} // namespace rawray
