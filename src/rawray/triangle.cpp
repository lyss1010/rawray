/////////////////////////////////////////////////////////////////////////////
// triangle.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "triangle.h"
#include "math/tuple3.h"

namespace rawray {

void Triangle::RenderGL() {
    Tuple3I indicies = mesh_.GetVertexIndices()[ index_ ];

    const Vector3& v0 = mesh_.GetVertices()[ indicies.x ];
    const Vector3& v1 = mesh_.GetVertices()[ indicies.y ];
    const Vector3& v2 = mesh_.GetVertices()[ indicies.z ];

    glBegin(GL_TRIANGLES);
        glVertex3f(v0.x, v0.y, v0.z);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
    glEnd();
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
    // See: http://www.devmaster.net/wiki/Ray-triangle_intersection
	const Tuple3I indices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ indices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ indices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ indices.z ];
	const Vector3& n = mesh_.GetNormals()[ index_ ];

	// Compute distance from ray origin to triangle plane
	register float divisor = ray.origin.Dot(n);
	if( divisor == 0.0f ) return false;
	hit.distance = -(ray.origin - v0).Dot(n) / divisor;
	if( hit.distance < 0.0f ) return false;
	
	// Early rejection (behind us) failed, compute full barycentric coords
	hit.point = (ray.origin + hit.distance * ray.direction);
	const Vector3 p = hit.point - v0;
	const Vector3 b = v1 - v0;
	const Vector3 c = v2 - v0;

	divisor = b.x * c.x - b.x * c.y;
	if( divisor == 0.0f ) return false;
	const float u = (p.y * c.x - p.x * c.y) / divisor;
	if( u < 0.0f ) return false;

	divisor = c.y * b.x - c.x * b.y;
	if( divisor == 0.0f ) return false;
	const float v = (p.y * b.x - p.x * b.y) / divisor;
	if( v < 0.0f ) return false;

	if( u+v <= 1.0f )
	{
		hit.material = material_;
		hit.normal = n;
		return true;
	}
	
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
