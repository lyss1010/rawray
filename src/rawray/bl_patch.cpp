/////////////////////////////////////////////////////////////////////////////
// bl_patch.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "bl_patch.h"
#include "material.h"
#include <math.h>

namespace rawray {

void BLPatch::RenderGL() {
    const Vector3& color = material_ ? material_->BaseColor() : Vector3(1);

    // Draw the lines around the perimeter 
    glBegin(GL_LINE_STRIP);
        glColor3f( color.x, color.y, color.z );

        glVertex3f(P00_.x, P00_.y, P00_.z);
        glVertex3f(P01_.x, P01_.y, P01_.z);
        glVertex3f(P11_.x, P11_.y, P11_.z);
        glVertex3f(P10_.x, P10_.y, P10_.z);
        glVertex3f(P00_.x, P00_.y, P00_.z);
    glEnd();
}

void BLPatch::PreCalc() {
}

float BLPatch::ComputeU(float v, const BLPatchData& patch) {
    float denom_a = v*(patch.A1 - patch.A2) + patch.B1 - patch.B2;
    float denom_b = v*(patch.A1           ) + patch.B1;

    if( fabs(denom_a) > fabs(denom_b) )
        return (v*(patch.C2 - patch.C1) + patch.D2 - patch.D1)/denom_a;

    return -(v*patch.C1 + patch.D1)/denom_b;
}

bool BLPatch::IsValid(float u, float v) {
    if( u < 0.0f || u > 1.0f || v < 0.0f || v > 1.0f )
        return false;

    return (u < uMin_ || u > uMax_) || (v < uMin_ || v > uMax_);
}

bool BLPatch::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
    Vector3 x1 = P11_; x1 -= P10_; x1 -= P01_; x1 += P00_;
    const Ray& ray = hit.eyeRay;
    const Vector3& x2 = P10_ - P00_;
    const Vector3& x3 = P01_ - P00_;
    const Vector3& x4 = P00_ - ray.origin;

    BLPatchData patch;
    patch.A1 = x1.x*ray.direction.z - x1.z*ray.direction.x;
    patch.B1 = x2.x*ray.direction.z - x2.z*ray.direction.x;
    patch.C1 = x3.x*ray.direction.z - x3.z*ray.direction.x;
    patch.D1 = x4.x*ray.direction.z - x4.z*ray.direction.x;

    patch.A2 = x1.y*ray.direction.z - x1.z*ray.direction.y;
    patch.B2 = x2.y*ray.direction.z - x2.z*ray.direction.y;
    patch.C2 = x3.y*ray.direction.z - x3.z*ray.direction.y;
    patch.D2 = x4.y*ray.direction.z - x4.z*ray.direction.y;

    float A = patch.A2*patch.C1 - patch.A1*patch.C2;
    float B = patch.A2*patch.D1 - patch.A1*patch.D2 + patch.B2*patch.C1 - patch.B1*patch.C2;
    float C = patch.B2*patch.D1 - patch.B1*patch.D2;

    float v1, v2;
    int roots = ComputeV( &v1, &v2, A, B, C );
    uint8 axis = ray.direction.GetDominantAxis( );

    float u = 0.0f;
    float v = 0.0f;
    switch( roots ) {
    case 0:
        return false;
    case 1:
        // There is only 1 root, so only 1 possible hit
        v = v1;
        u = ComputeU(v, patch);
        hit.point = Eval(u, v);
        hit.distance = ( hit.point[axis] - ray.origin[axis] ) / ray.direction[axis];

        if( !IsValid(u, v) || hit.distance < minDistance || hit.distance > maxDistance )
            return false;

        break;

    case 2:
        // There are 2 roots, so we need to know which hit to use
        v = v1;
        u = ComputeU(v, patch);
        hit.point = Eval(u, v);
        hit.distance = ( hit.point[axis] - ray.origin[axis] ) / ray.direction[axis];

        // Check for any way hit1 can be invalid
        if( !IsValid(u, v) || hit.distance < minDistance || hit.distance > maxDistance )
        {
            // hit 2 is the only possible valid hit
            v = v2;
            u = ComputeU(v, patch);
            if( !IsValid(u, v) )
                return false;

            hit.point = Eval(u, v);
            hit.distance = ( hit.point[axis] - ray.origin[axis] ) / ray.direction[axis];
            if( hit.distance < minDistance || hit.distance > maxDistance )
                return false;

        } else {
            // both are possibly valid
            const float u2 = u = ComputeU(v2, patch);
            if( !IsValid(u2, v2) )
                break; // hit1 is the only valid one

            const Vector3& hit2 = Eval(u2, v2);
            const float t2 = ( hit2[axis] - ray.origin[axis] ) / ray.direction[axis];
            if( t2 < minDistance || t2 > maxDistance )
                break; // hit1 is the only valid one

            // Both are perfectly valid hits, see which one comes first
            // We already know t2 is a positive number
            if( t2 < hit.distance ) {
                u = u2;
                v = v2;
                hit.point = hit2;
                hit.distance = t2;
            }
        }

        break;
    }

    hit.texCoord.x = u;
    hit.texCoord.y = v;
    hit.material = material_;

    // Compute the normal by getting the partial derivatives (tangents) of each line
    Vector3 du =  (1-v) * (P10_-P00_);
            du +=    v  * (P11_-P01_);

    Vector3 dv =  (1-u) * (P01_-P00_);
            dv +=    u  * (P11_-P10_);

    math::Cross( du, dv, hit.normal );
    hit.normal.Normalize();

    return true;
}

int BLPatch::ComputeV(float* out1, float* out2,
             float a, float b, float c)
{
    int numRoots = math::SolveQuadratic(out1, out2, a, b, c);

    switch( numRoots ) {
    case 1:
        if( *out1 < 0.0f || *out1 > 1.0f )
            numRoots--;
    case 2:
        if( *out1 < 0.0f || *out1 > 1.0f )
        {
            // out1 is invald, use out2 as our only possible valid one
            numRoots--;
            *out1 = *out2;

            // check if out2 is invalid
            if( *out2 < 0.0f || *out2 > 1.0f )
                numRoots--;
        } else {
            // out1 was valid, check if out2 is valid also
            if( *out2 < 0.0f || *out2 > 1.0f )
                numRoots--;
        }
    }

    return numRoots;
}

// What is the x,y,z position of a point at params u and v?
Vector3 BLPatch::Eval(float u, float v) {
    Vector3 p = (1-u) * (1-v) * P00_;
    p += (1-u) * ( v ) * P01_;
    p += ( u ) * (1-v) * P10_;
    p += ( u ) * ( v ) * P11_;

    return p;
}

} // namespace rawray
