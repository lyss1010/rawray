/////////////////////////////////////////////////////////////////////////////
// triangle.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "triangle.h"
#include "math/tuple3.h"
#include "material.h"

namespace rawray {

PluckerCoord::PluckerCoord(const Vector3& direction, const Vector3& point) {
    u_ = direction;
    v_ = direction; v_.Cross(point);
}

float PluckerCoord::GetOrientation(const PluckerCoord& p) {
    //        L1*M6      -    L2*M5      +     L3*M4     +    L4*M3      -    L5*M2      +    L6*M1
    return (u_.x*p.v_.z) - (u_.y*p.v_.y) + (u_.z*p.v_.x) + (v_.x*p.u_.z) - (v_.y*p.u_.y) + (v_.z*p.u_.x);
}

Triangle::Triangle(TriangleMesh& mesh, uint32 index, const Material* material)
            : Object(material), mesh_(mesh), index_(index),
            n_(NULL), pluckA_(NULL), pluckB_(NULL), pluckC_(NULL)
{
    // Choose which algorithm we will use to intersect with
    // This will save us the switch in the intersect function
    switch( options::global::triangle_intersection_algorithm ) {
    case options::BARYCENTRIC:
        intersect_ = &Triangle::IntersectBarycentric;
        preCalc_ = &Triangle::PreCalcBarycentric;
        break;

    case options::BARYCENTRIC_PROJECTION:
        intersect_ = &Triangle::IntersectBarycentricProjection;
        preCalc_ = &Triangle::PreCalcBarycentricProjection;
        break;

    case options::MOLLER:
        intersect_ = &Triangle::IntersectMoller;
        preCalc_ = &Triangle::PreCalcMoller;
        break;

    default:
    case options::PLUCKER:
        intersect_ = &Triangle::IntersectPlucker;
        preCalc_ = &Triangle::PreCalcPlucker;
        break;
    }
}

Triangle::~Triangle() {
    delete n_;
    delete pluckA_;
    delete pluckB_;
    delete pluckC_;
}

void Triangle::RenderGL() {
    Tuple3I indicies = mesh_.GetVertexIndices()[ index_ ];

    const Vector3& v0 = mesh_.GetVertices()[ indicies.x ];
    const Vector3& v1 = mesh_.GetVertices()[ indicies.y ];
    const Vector3& v2 = mesh_.GetVertices()[ indicies.z ];
    const Vector3& color = material_ ? material_->BaseColor() : Vector3(1);

    glBegin(GL_TRIANGLES);
        glColor3f( color.x, color.y, color.z );
        glVertex3f(v0.x, v0.y, v0.z);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
    glEnd();
}

void Triangle::PreCalc() {
    return ((*this).*preCalc_)();
}

bool Triangle::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    return ((*this).*intersect_)(hit, ray, minDistance, maxDistance);
}

// Ray-Plane intersection with barycentric coordinate test
// See: Fundamentals of Computer Graphics, Peter Shirley p206
void Triangle::PreCalcBarycentric() { }
bool Triangle::IntersectBarycentric(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
	const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];

    const float a = v0.x - v1.x;
    const float b = v0.y - v1.y;
    const float c = v0.z - v1.z;
    const float d = v0.x - v2.x;
    const float e = v0.y - v2.y;
    const float f = v0.z - v2.z;
    const float g = -ray.direction.x;
    const float h = -ray.direction.y;
    const float i = -ray.direction.z;
    const float j = v0.x - ray.origin.x;
    const float k = v0.y - ray.origin.y;
    const float l = v0.z - ray.origin.z;

    const float ei_minus_hf = e*i - h*f;
    const float gf_minus_di = g*f - d*i;
    const float dh_minus_eg = d*h - e*g;

    const float denominator = a*ei_minus_hf + b*gf_minus_di + c*dh_minus_eg;
    if( denominator == 0.0f ) return false;
    
    const float denominatorMul = 1.0f / denominator;
    const float ak_minus_jb = a*k - j*b;
    const float jc_minux_al = j*c - a*l;
    const float bl_minux_kc = b*l - k*c;

    const float t = (f*ak_minus_jb + e*jc_minux_al + d*bl_minux_kc) * denominatorMul;
    if( t < minDistance || t > maxDistance ) return false;

    const float gamma = (i*ak_minus_jb + h*jc_minux_al + g*bl_minux_kc) * denominatorMul;
    if( gamma < 0.0f || gamma > 1.0f ) return false;

    const float beta = (j*ei_minus_hf + k*gf_minus_di + l*dh_minus_eg) * denominatorMul;
    if( beta < 0.0f || beta > 1.0f - gamma ) return false;

    // Copy values we computed earlier for hit point and distance
    hit.point = ray.origin + t * ray.direction;
    hit.distance = t;
    hit.material = material_;
    Interpolate(hit, 1-beta-gamma, beta, gamma);

    return true;
}

// Optimized Barycentric 2d projection test
// See: http://www.mpi-inf.mpg.de/~wald/PhD/wald_phd.pdf p91
void Triangle::PreCalcBarycentricProjection() {
    const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];

    SAFE_DELETE(n_);
    n_ = new Vector3( math::Cross( v1-v0, v2-v0 ).Normalize() );
}

// TODO: This seems to translate the triangles by some amount =(
bool Triangle::IntersectBarycentricProjection(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    assert( n_ );
	const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];

    // Edges of triangle
    const Vector3& b = v2 - v0;
    const Vector3& c = v1 - v0;

    // See if we are exactly lined up with the plane (or a back face of a triangle)
    register float denominator = math::Dot( ray.direction, *n_ );
    if( denominator == 0.0f ) return false;

    // Compute distance to the plane along the ray
    const float distance = -math::Dot( ray.origin-v0, *n_ ) / denominator;
    if( distance < minDistance || distance > maxDistance ) return false;

    // Determine dominant axis
    const float absNX = abs(n_->x);
    const float absNY = abs(n_->y);
    const float absNZ = abs(n_->z);

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

    const float gamma = (c[v] * h[u] - c[u] * h[v]) * denominator;
    if( gamma < 0.0f ) return false;
    if( beta+gamma > 1.0f ) return false;

    // Copy values we computed earlier for hit point and distance
    hit.point = h;
    hit.distance = distance;
    hit.material = material_;
    Interpolate(hit, 1-beta-gamma, beta, gamma);

    return true;
}


// Moller triangle intersection test
void Triangle::PreCalcMoller() { }
bool Triangle::IntersectMoller(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    UNREFERENCED_PARAMETER(hit);
    UNREFERENCED_PARAMETER(ray);
    UNREFERENCED_PARAMETER(minDistance);
    UNREFERENCED_PARAMETER(maxDistance);
    
    // TODO: Write algorithm
    return false;
}


// Plucker coordinate triangle intersection test
// See: http://tog.acm.org/resources/RTNews/html/rtnv10n3.html#art11
// See: http://tog.acm.org/resources/RTNews/html/rtnv11n1.html#art3
// See: http://www.flipcode.com/archives/Plcker_Coordinates_for_the_Rest_of_Us-Part_4_Applications.shtml
void Triangle::PreCalcPlucker() {
    const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];
    
    SAFE_DELETE(pluckA_);
    SAFE_DELETE(pluckB_);
    SAFE_DELETE(pluckC_);

    // Edge A corresponds to the edge opposite of vertex A (v0)
    pluckA_ = new PluckerCoord( v1-v2, v2 );
    pluckB_ = new PluckerCoord( v2-v0, v0 );
    pluckC_ = new PluckerCoord( v0-v1, v1 );
}

// TODO: This seems to rotate the triangles by some amount =(
bool Triangle::IntersectPlucker(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    assert(pluckA_);
    assert(pluckB_);
    assert(pluckC_);

    PluckerCoord pluckRay( ray.direction, ray.origin );
    float dirA = pluckA_->GetOrientation( pluckRay );
    float dirB = pluckB_->GetOrientation( pluckRay );
    float dirC = pluckC_->GetOrientation( pluckRay );

    // TODO: Intersection directly with edge = failure?
    if( dirA == 0.0f || dirB == 0.0f || dirC == 0.0f )
        return false;

    if( dirA < 0.0f ) {
        if( dirB > 0.0f || dirC > 0.0f )
            return false;
    } else { // if( dirA > 0.0f )
        if( dirB < 0.0f || dirC < 0.0f )
            return false;
    }

    const float norm = 1.0f / (dirA + dirB + dirC);
    const float alpha = dirA*norm;
    const float beta = dirB*norm;
    const float gamma = dirC*norm;

    const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];

    HitInfo hit2;
    IntersectBarycentric(hit2, ray, minDistance, maxDistance);

    // Use the computed orientation data as unnormalized barycentric coords
    hit.point = alpha*v0 + beta*v1 + gamma*v2;
    hit.distance = (hit.point - ray.origin).Length();
    if( hit.distance < minDistance || hit.distance > maxDistance )
        return false;

    hit.material = material_;

    Interpolate(hit, beta, gamma, alpha);

    return true;
}

void Triangle::Interpolate(HitInfo& hit, float alpha, float beta, float gamma) {
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
