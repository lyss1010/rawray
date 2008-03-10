/////////////////////////////////////////////////////////////////////////////
// sphere.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "sphere.h"

namespace rawray {

void Sphere::RenderGL() {
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(center_.x, center_.y, center_.z);
    glutWireSphere(radius_, 8, 8);
    glPopMatrix();
}

bool Sphere::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    const Vector3 toCenter = ray.origin - center_;
    
    const float a = ray.direction.Length2();
    const float b = -math::Dot( 2*ray.direction, toCenter );
    const float c = toCenter.Length2() - radius_*radius_;

    const float discrim = b*b - 4.0f*a*c;
    if( discrim < 0 ) // Sqrt would be imaginary
        return false;

    const float sqrt_discrim = sqrtf( discrim );

    // Quadratic formula, because discrim >=0, root0 < root1
    register float divisor = 0.5f / a;
    const float root0 = (b-sqrt_discrim)*divisor;
    const float root1 = (b+sqrt_discrim)*divisor;

    // Return distance closest to us within range
    if( root0 > minDistance && root0 < maxDistance )
        hit.distance = root0;
    else if( root1 > minDistance && root1 < maxDistance )
        hit.distance = root1;
    else
        return false;

    // hit.point = ray.origin + hit.distance * ray.direction
    hit.point = ray.direction;
    hit.point *= hit.distance;
    hit.point += ray.origin;

    // hit.normal = hit.point - center_
    hit.normal = hit.point;
    hit.normal -= center_;
    hit.normal.Normalize();
    
    hit.material = material_;
    return true;
}

} // namespace rawray
