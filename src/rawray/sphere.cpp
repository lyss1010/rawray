/////////////////////////////////////////////////////////////////////////////
// sphere.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "sphere.h"
#include "material.h"

namespace rawray {

void Sphere::RenderGL() {
	const Vector4& color4 = material_ ? material_->BaseColor() : Vector4(1);
	const Vector3 color( color4.x, color4.y, color4.z );

	glColor3f( color.x, color.y, color.z );

    glPushMatrix();
    glTranslatef(center_.x, center_.y, center_.z);
    glutWireSphere(radius_, options::global::gl_sphere_sections, options::global::gl_sphere_sections);
    glPopMatrix();
}

void Sphere::IntersectPack(HitPack& hitpack, float minDistance, float maxDistance) {
    hitpack.hit_result[0] = Intersect( hitpack.hits[0], minDistance, maxDistance );
    hitpack.hit_result[1] = Intersect( hitpack.hits[1], minDistance, maxDistance );
    hitpack.hit_result[2] = Intersect( hitpack.hits[2], minDistance, maxDistance );
    hitpack.hit_result[3] = Intersect( hitpack.hits[3], minDistance, maxDistance );
}

bool Sphere::Hit(const Ray& ray, float minDistance, float maxDistance) const {
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
        return true;
    if( root1 > minDistance && root1 < maxDistance )
        return true;

    return false;
}

bool Sphere::Intersect(HitInfo& hit, float minDistance, float maxDistance) {
    const Ray& ray = hit.eyeRay;
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
    hit.normal = hit.point - center_;
    hit.normal.Normalize();
    
    hit.material = material_;
    return true;
}

} // namespace rawray
