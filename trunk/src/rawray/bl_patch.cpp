/////////////////////////////////////////////////////////////////////////////
// bl_patch.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "bl_patch.h"
#include "material.h"

namespace rawray {

void BLPatch::RenderGL() {
    const Vector3& color = material_ ? material_->BaseColor() : Vector3(1);

    const Vector3& e0 = verts_[1] - verts_[0];
    const Vector3& e1 = verts_[3] - verts_[0];
    const Vector3& e2 = verts_[1] - verts_[2];
    const Vector3& e3 = verts_[3] - verts_[2];

    const Vector3& n1 = math::Cross(e0,e1);
    const Vector3& n2 = math::Cross(e2,e3);

    // Draw 2 triangles so we can see something at least in GL
    glBegin(GL_TRIANGLES);
        glColor3f( color.x, color.y, color.z );

		glNormal3f(n1.x, n1.y, n1.z);
        glVertex3f(verts_[0].x, verts_[0].y, verts_[0].z);
        glVertex3f(verts_[1].x, verts_[1].y, verts_[1].z);
        glVertex3f(verts_[3].x, verts_[3].y, verts_[3].z);

		glNormal3f(n2.x, n2.y, n2.z);
        glVertex3f(verts_[2].x, verts_[2].y, verts_[2].z);
        glVertex3f(verts_[3].x, verts_[3].y, verts_[3].z);
        glVertex3f(verts_[0].x, verts_[0].y, verts_[0].z);
    glEnd();
}

void BLPatch::PreCalc() {
}

// See: http://www.cs.utah.edu/~kpotter/pubs/bilinear.pdf
bool BLPatch::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    return false;

    //const Vector3& x1 = verts_[3] - verts_[2] - verts_[1] + verts_[0];
    //const Vector3& x2 = verts_[2] - verts_[0];
    //const Vector3& x3 = verts_[1] - verts_[0];
    //const Vector3& x4 = verts_[0];

    //// Manually solve: r + t*d = uv*x1 + u*x2 + v*x3 + x4
    //// We will use a the BLPatchData struct to hold temp values
    //BLPatch::BLPatchData p;

    //// where i is either x,y,z
    //// t.i = (1/d.i) * (uv*x1.i + u*x2.i + v*x3.i + x4.i - r.i)
    //// setting tx*dx*dz = tz*dz*dx where tx=tz=t and substituting the above equation
    //p.A1 = x1.x * ray.direction.z - x1.z * ray.direction.x;
    //p.B1 = x2.x * ray.direction.z - x2.z * ray.direction.x;
    //p.C1 = x3.x * ray.direction.z - x3.z * ray.direction.x;
    //p.D1 = ray.direction.z * (x4.x - ray.origin.x) - ray.direction.x * (x4.z - ray.origin.z);

    //// the same as above but using ty*dy*dz = tz*dz*dy
    //p.A1 = x1.y * ray.direction.z - x1.z * ray.direction.y;
    //p.B1 = x2.y * ray.direction.z - x2.z * ray.direction.y;
    //p.C1 = x3.y * ray.direction.z - x3.z * ray.direction.y;
    //p.D1 = ray.direction.z * (x4.y - ray.origin.y) - ray.direction.y * (x4.z - ray.origin.z);

    //// Set the following two equations equal to each other, you get back a quadratic
    //// 0 = uvA1 + uB1 + vC1 + D1 = uvA2 + uB2 + vC2 + D2
    //// 0 = v^2(A2C1 - A1C2) + v(A2D1 - A1D2 + B2C1 - B1C2) + (B2D1 - B1D2)
    //float v1, v2;
    //const int numRoots = math::SolveQuadratic( &v1, &v2,
    //                        ( p.A2*p.C1 - p.A1*p.C2 ),
    //                        ( p.A2*p.D1 - p.A1*p.D2 + p.B2*p.C1 - p.B1*p.C2 ),
    //                        ( p.B2*p.D1 - p.B1*p.D2 ) );

    //if( numRoots < 1 ) return false;
    //
    //const float absDX = fabs(ray.direction.x);
    //const float absDY = fabs(ray.direction.y);
    //const float absDZ = fabs(ray.direction.z);

    //// Determine dominant axis, this is to ensure no div by 0 when we compute t
    //uint8 axis; // 0=x, 1=y, 2=z
    //if( absDX > absDY )
    //    axis = (absDX > absDZ) ? 0 : 2;
    //else
    //    axis = (absDY > absDZ) ? 1 : 2;
    //
    //float u, v;
    //if( numRoots == 1 ) {
    //    if( v1 < 0.0f || v1 > 1.0f ) return false;
    //    
    //    v = v1;
    //    u = ComputeU( v, p );
    //    if( u < 0.0f || u > 1.0f ) return false;

    //    hit.point = u*v*x1 + u*x2 + v*x3 + x4;
    //    hit.distance = (p[axis] - ray.origin.[axis]) / ray.direction[axis];
    //} else {
    //    const float u1 = 0;//ComputeU( v1, p );
    //    const float u2 = 0;//ComputeU( v1, p );
    //    const Vector3 p1;// = u1*v1*x1 + u1*x2 + v1*x3 + x4;
    //    const Vector3 p2;// = u2*v2*x1 + u2*x2 + v2*x3 + x4;

    //    const float inv_dir = 1.0f;// / ray.direction[axis];
    //    const float t1 = 0;//(p1[axis] - ray.origin[axis]) * inv_dir;
    //    const float t2 = 0;//(p2[axis] - ray.origin[axis]) * inv_dir;

        // TODO: Take care of u,v out of bounds here
        // Find the closest non-negative distance from the two t values
        // We leave the check for t2 negativeness for afterwards
        //if( t1 < 0.0f || t2 < t1 ) {
        //    hit.distance = t2;
        //    hit.point = p2;
        //    u = u2;
        //    v = v2;
        //} else {
        //    hit.distance = t1;
        //    hit.point = p1;
        //    u = u1;
        //    v = v1;
        //}
    //}

    //if( hit.distance < minDistance || hit.distance > maxDistance ) return false;
    //hit.material = material_;

    //// Correct texture coordinates?
    //hit.texCoord.x = u;
    //hit.texCoord.y = v;

    //// Compute the normal by using the partial derivitive w/ respect to u and v individually
    //hit.normal = math::Cross( ( (1-v)*(verts_[2]-verts_[0]) + v*(verts_[3]-verts_[1]) ), 
    //                          ( (1-u)*(verts_[1]-verts_[0]) + u*(verts_[3]-verts_[2]) ) );

    //return true;
    return false;
}

float BLPatch::ComputeU(float v, const BLPatch::BLPatchData& patch) {
    //const float divisor_a = v * (patch.A2 + patch.A2);
    //const float divisor_b = v * (patch.A2 - patch.A1) + patch.B2 - patch.B1;

    //// Choose the largest divisor for numerical stability
    //if( fabs(divisor_b) > fabs(divisor_a) )
    //    return ( v*(patch.C1 - patch.C2) + patch.D1 - patch.D2) / divisor_b;
    //else
    //    return (-v * patch.C2 - patch.D2) / divisor_a;
    return 0;
}

} // namespace rawray
