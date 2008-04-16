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
	v_ = math::Cross(direction,point);
}

float PluckerCoord::GetOrientation(const PluckerCoord& p) {
	return u_.Dot(p.v_) + v_.Dot(p.u_);
}

Triangle::Triangle(TriangleMesh& mesh, uint32 index, const Material* material)
            : Object(material), mesh_(mesh), index_(index),
            n_(NULL), det2d_(NULL), pluckA_(NULL), pluckB_(NULL), pluckC_(NULL)
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

	indicies = mesh_.GetNormalIndices()[ index_ ];
	const Vector3& n0 = mesh_.GetNormals()[ indicies.x ];
	const Vector3& n1 = mesh_.GetNormals()[ indicies.y ];
	const Vector3& n2 = mesh_.GetNormals()[ indicies.z ];

    const Vector3& color = material_ ? material_->BaseColor() : Vector3(1);

    glBegin(GL_TRIANGLES);
        glColor3f( color.x, color.y, color.z );
		glNormal3f(n0.x, n0.y, n0.z);
        glVertex3f(v0.x, v0.y, v0.z);

		glNormal3f(n0.x, n1.y, n1.z);
        glVertex3f(v1.x, v1.y, v1.z);

		glNormal3f(n2.x, n2.y, n2.z);
        glVertex3f(v2.x, v2.y, v2.z);
    glEnd();
}

void Triangle::PreCalc() {
    ((*this).*preCalc_)();
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
	//			g = -ray.direction.x
	//			h = -ray.direction.y
	//			i = -ray.direction.z
    const float j = v0.x - ray.origin.x;
    const float k = v0.y - ray.origin.y;
    const float l = v0.z - ray.origin.z;

    const float ei_minus_hf = ray.direction.y*f - e*ray.direction.z;
    const float gf_minus_di = d*ray.direction.z - ray.direction.x*f;
    const float dh_minus_eg = e*ray.direction.x - d*ray.direction.y;

    const float denominator = a*ei_minus_hf + b*gf_minus_di + c*dh_minus_eg;
    if( denominator == 0.0f ) return false;
    
    const float inv_den = 1.0f / denominator;
    const float ak_minus_jb = a*k - j*b;
    const float jc_minux_al = j*c - a*l;
    const float bl_minux_kc = b*l - k*c;

    const float t = (f*ak_minus_jb + e*jc_minux_al + d*bl_minux_kc) * inv_den;
    if( t < minDistance || t > maxDistance ) return false;

    const float gamma = (-ray.direction.z*ak_minus_jb - ray.direction.y*jc_minux_al - ray.direction.x*bl_minux_kc) * inv_den;
    if( gamma < 0.0f || gamma > 1.0f ) return false;

    const float beta = (j*ei_minus_hf + k*gf_minus_di + l*dh_minus_eg) * inv_den;
    if( beta < 0.0f || beta > 1.0f - gamma ) return false;

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

    const Vector3& b = v2 - v0;
    const Vector3& c = v1 - v0;

    SAFE_DELETE(n_);
    n_ = new Vector3( math::Cross(b, c) );

    // denominator = b[u] * c[v] - b[v] * c[u];
    // .x = x component removed, .y = y component removed etc...
    SAFE_DELETE(det2d_);
    det2d_ = new Vector3( (b.y)*(c.z) - (b.z)*(c.y),
                          (b.z)*(c.x) - (b.x)*(c.z),
                          (b.x)*(c.y) - (b.y)*(c.x) );

    det2d_->x = math::FloatZero(det2d_->x, options::epsilon) ? 0.0f : 1.0f / det2d_->x;
    det2d_->y = math::FloatZero(det2d_->y, options::epsilon) ? 0.0f : 1.0f / det2d_->y;
    det2d_->z = math::FloatZero(det2d_->z, options::epsilon) ? 0.0f : 1.0f / det2d_->z;
}

bool Triangle::IntersectBarycentricProjection(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    assert( n_ );
    assert( det2d_ );
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
    const float t = -math::Dot( ray.origin-v0, *n_ ) / denominator;
    if( t < minDistance || t > maxDistance ) return false;

    // Determine dominant axis
    const float absNX = fabs(n_->x);
    const float absNY = fabs(n_->y);
    const float absNZ = fabs(n_->z);

    uint8 axis; // 0=x, 1=y, 2=z
    if( absNX > absNY )
        axis = (absNX > absNZ) ? 0 : 2;
    else
        axis = (absNY > absNZ) ? 1 : 2;

    // Grab the precomputed inverse determinant based on which axis we're on
    const float inv_det = det2d_->operator [](axis);
    if( inv_det == 0.0f ) return false;
    const uint8 u = (axis+1)%3;
    const uint8 v = (axis+2)%3;

    IntersectBarycentric(hit, ray, minDistance, maxDistance);

    // Compute the point on the plane where we intersect minus the first vertex
    hit.point = (ray.direction * t) + ray.origin;
    
    const float hv = (hit.point[v]-v0[v]);
    const float hu = (hit.point[u]-v0[u]);
    const float beta = (hv * b[u] - hu * b[v]) * inv_det;
    if( beta < 0.0f ) return false;

    const float gamma = (hu * c[v] - hv * c[u]) * inv_det;
    if( gamma < 0.0f ) return false;
    if( beta+gamma > 1.0f ) return false;

    hit.distance = t;
    hit.material = material_;
    Interpolate(hit, 1-beta-gamma, beta, gamma);
    
    return true;
}


// Moller triangle intersection test
// See: http://ompf.org/forum/viewtopic.php?t=165
// TODO: Write me
void Triangle::PreCalcMoller() {
    const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];

    const Vector3& b = v2 - v0;
    const Vector3& c = v1 - v0;

    SAFE_DELETE(n_);
    n_ = new Vector3( math::Cross(b, c) );
}

bool Triangle::IntersectMoller(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
	assert( n_ );
    const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_.GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_.GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_.GetVertices()[ vertexIndices.z ];

	const Vector3& b = v1 - v0;
	const Vector3& c = v2 - v0;
    const Vector3& o = ray.origin - v0;

    const float det = n_->Dot(ray.direction);
    if( det == 0.0f ) return false;
    const float inv_det = -1.0f / det;

    const float t = n_->Dot(o) * inv_det;
    if( t < minDistance || t > maxDistance ) return false;

    const float beta = math::Cross(o,c).Dot(ray.direction) * inv_det;
    if( beta < 0.0f ) return false;

    const float gamma = math::Cross(b,o).Dot(ray.direction) * inv_det;
    if( gamma < 0.0f ) return false;
    if( beta+gamma > 1.0f ) return false;

    hit.distance = t;
    hit.material = material_;
    hit.point = ray.origin + ray.direction * t;
    Interpolate(hit, 1-beta-gamma, beta, gamma);

    return true;
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
    pluckA_ = new PluckerCoord( v2-v1, v1 );
    pluckB_ = new PluckerCoord( v0-v2, v2 );
    pluckC_ = new PluckerCoord( v1-v0, v0 );
}

bool Triangle::IntersectPlucker(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    assert(pluckA_); assert(pluckB_); assert(pluckC_);

    PluckerCoord pluckRay( ray.direction, ray.origin );
    float dirA = pluckA_->GetOrientation( pluckRay );
    float dirB = pluckB_->GetOrientation( pluckRay );
    float dirC = pluckC_->GetOrientation( pluckRay );

	// We treat hits on the exact edge as misses
	if( dirA == 0.0f || dirB == 0.0f || dirC == 0.0f )
		return false;

	// Make sure all orientations are the same direction
	if( dirA < 0.0f ) {
		if( dirB > 0.0f || dirC > 0.0f )
			return false;
	} else {
		if( dirB < 0.0f || dirC < 0.0f )
			return false;
	}

    const float norm = 1.0f / (dirA + dirB + dirC);
    const float alpha = dirA*norm;
    const float beta = dirB*norm;
    const float gamma = dirC*norm;

    // Compute the hit point by interpolation based by our barycentric coords
    const Tuple3I vertexIndices = mesh_.GetVertexIndices()[ index_ ];
    hit.point = alpha*mesh_.GetVertices()[ vertexIndices.x ] + 
                beta*mesh_.GetVertices()[ vertexIndices.y ] + 
                gamma*mesh_.GetVertices()[ vertexIndices.z ];

    hit.distance = (hit.point - ray.origin).Length();
    if( hit.distance < minDistance || hit.distance > maxDistance )
        return false;

    hit.material = material_;
    Interpolate(hit, alpha, beta, gamma);

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

