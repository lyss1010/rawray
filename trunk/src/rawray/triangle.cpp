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

void Triangle::PreCalc() {
    const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];

    n_ = math::Cross( v1-v0, v2-v0 ).Normalize();
}

bool Triangle::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    switch( options::global::triangle_intersection_algorithm )
    {
    case options::BARYCENTRIC:
        return Barycentric(hit, ray, minDistance, maxDistance);

    case options::BARYCENTRIC_PROJECTION:
        return BarycentricProjection(hit, ray, minDistance, maxDistance);

    case options::MOLLER:
        return Moller(hit, ray, minDistance, maxDistance);

    case options::PLUCKER:
        return Plucker(hit, ray, minDistance, maxDistance);

    default:
        return false;
    }
}

bool Triangle::Barycentric(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
	const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];

    // Normal of the plane which the triangle is on (may not be equivilent to individual triangle normals)
    const Vector3& e1 = v1 - v0;
    const Vector3& e2 = v2 - v0;

    // See if we are exactly lined up with the plane
    register float denominator = math::Dot( ray.direction, n_ );
    if( denominator < options::epsilon ) return false;

    // Compute the point on the plane where we intersect
    const float distance = - math::Dot( ray.origin - v0, n_ ) / denominator;
    if( distance < minDistance || distance > maxDistance ) return false;
    const Vector3& h = (ray.direction * distance) + ray.origin;

    // Compute barycentric coords
    // See: http://www.cimec.org.ar/twiki/pub/Cimec/ComputacionGrafica/triangle_intersection.pdf
    denominator = math::Dot( math::Cross(e1,e2), n_ );
    if( denominator == 0.0f ) return false;
    
    const float alpha = math::Dot( math::Cross( v2-v1, h-v1 ), n_ ) / denominator;
    if( alpha < 0.0f ) return false;

    const float beta = math::Dot( math::Cross( v0-v2, h-v2 ), n_ ) / denominator;
    if( beta < 0.0f ) return false;
    if( alpha+beta > 1.0f ) return false;

    // Copy values we computed earlier for hit point and distance
    hit.point = h;
    hit.distance = distance;
    hit.material = material_;
    Interpolate(hit, alpha, beta);

    return true;
}

bool Triangle::BarycentricProjection(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
	const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];

    // Normal of the plane which the triangle is on (may not be equivilent to individual triangle normals)
    const Vector3& c = v2 - v0;
    const Vector3& b = v1 - v0;

    // See if we are exactly lined up with the plane (or a back face of a triangle)
    register float denominator = math::Dot( ray.direction, n_ );
    if( denominator < options::epsilon ) return false;

    // Compute distance to the plane along the ray
    const float distance = math::Dot( v0 - ray.origin, n_ ) / denominator;
    if( distance < minDistance || distance > maxDistance ) return false;

    // Optimized barycentric projection test
    // See: http://www.mpi-inf.mpg.de/~wald/PhD/wald_phd.pdf

    // Determine dominant axis
    const float absNX = abs(n_.x);
    const float absNY = abs(n_.y);
    const float absNZ = abs(n_.z);

    uint8 axis; // 0=x, 1=y, 2=z
    if( absNX > absNY )
        axis = (absNX > absNZ) ? 0 : 2;
    else
        axis = (absNY > absNZ) ? 1 : 2;

    const uint8 u = (axis+1)%3;
    const uint8 v = (axis+2)%3;

    // Compute the point on the plane where we intersect
    const Vector3& h = (ray.direction * distance) + ray.origin;

    denominator = b[u] * c[v] - b[v] * c[u];
    if( denominator == 0.0f ) return false;
    denominator = 1.0f / denominator;

    const float beta = (b[u] * h[v] - b[v] * h[u]) * denominator;
    if( beta < 0.0f ) return false;

    const float gamma = (c[v] * h[v] - c[u] * h[v]) * denominator;
    if( gamma < 0.0f ) return false;
    if( beta+gamma > 1.0f ) return false;

    // Copy values we computed earlier for hit point and distance
    hit.point = h;
    hit.distance = distance;
    hit.material = material_;
    Interpolate(hit, 1-beta-gamma, beta);

    return true;
}

bool Triangle::Moller(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    UNREFERENCED_PARAMETER(hit);
    UNREFERENCED_PARAMETER(ray);
    UNREFERENCED_PARAMETER(minDistance);
    UNREFERENCED_PARAMETER(maxDistance);
    
    // TODO: Write algorithm
    return false;
}

bool Triangle::Plucker(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    UNREFERENCED_PARAMETER(hit);
    UNREFERENCED_PARAMETER(ray);
    UNREFERENCED_PARAMETER(minDistance);
    UNREFERENCED_PARAMETER(maxDistance);

    // TODO: Write algorithm
    // http://www.flipcode.com/archives/Introduction_To_Plcker_Coordinates.shtml
    return false;
}

void Triangle::Interpolate(HitInfo& hit, float alpha, float beta) {
    const float gamma = 1 - alpha - beta;

    const Tuple3I normalIndices = mesh_.GetNormalIndices()[ index_ ];
	const Vector3& n0 = alpha * mesh_.GetNormals()[ normalIndices.x ];
    const Vector3& n1 = beta * mesh_.GetNormals()[ normalIndices.y ];
    const Vector3& n2 = gamma * mesh_.GetNormals()[ normalIndices.z ];

    hit.normal.x = n0.x + n1.x + n2.x;
    hit.normal.y = n0.y + n1.y + n2.y;
    hit.normal.z = n0.z + n1.z + n2.z;

    if( mesh_.GetTexCoordIndices() != NULL ) {
        const Tuple3I texCoordIndices = mesh_.GetTexCoordIndices()[ index_ ];
        const Vector2& t0 = alpha * mesh_.GetTexCoords()[ texCoordIndices.x ];
        const Vector2& t1 = beta * mesh_.GetTexCoords()[ texCoordIndices.y ];
        const Vector2& t2 = gamma * mesh_.GetTexCoords()[ texCoordIndices.z ];

        hit.texCoord.x = t0.x + t1.x + t2.x;
        hit.texCoord.y = t0.y + t1.y + t2.y;
    } else
        hit.texCoord = Vector2();
}

} // namespace rawray
