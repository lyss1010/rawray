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
	math::Cross(direction,point,v_);
}

float PluckerCoord::GetOrientation(const PluckerCoord& p) {
	return u_.Dot(p.v_) + v_.Dot(p.u_);
}

/////////////////////////////////////////////////////////////////////////////

void Triangle::RenderGL() {
    Tuple3I indicies = mesh_->GetVertexIndices()[ index_ ];

    const Vector3& v0 = mesh_->GetVertices()[ indicies.x ];
    const Vector3& v1 = mesh_->GetVertices()[ indicies.y ];
    const Vector3& v2 = mesh_->GetVertices()[ indicies.z ];

	indicies = mesh_->GetNormalIndices()[ index_ ];
	const Vector3& n0 = mesh_->GetNormals()[ indicies.x ];
	const Vector3& n1 = mesh_->GetNormals()[ indicies.y ];
	const Vector3& n2 = mesh_->GetNormals()[ indicies.z ];

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

void Triangle::IntersectPack(HitPack& hitpack, float minDistance, float maxDistance) {
    hitpack.hit_result[0] = Intersect( hitpack.hits[0], minDistance, maxDistance );
    hitpack.hit_result[1] = Intersect( hitpack.hits[1], minDistance, maxDistance );
    hitpack.hit_result[2] = Intersect( hitpack.hits[2], minDistance, maxDistance );
    hitpack.hit_result[3] = Intersect( hitpack.hits[3], minDistance, maxDistance );
}

void Triangle::Interpolate(HitInfo& hit, float alpha, float beta, float gamma) {
    const Tuple3I normalIndices = mesh_->GetNormalIndices()[ index_ ];
    hit.normal = alpha * mesh_->GetNormals()[ normalIndices.x ] +
                 beta  * mesh_->GetNormals()[ normalIndices.y ] +
                 gamma * mesh_->GetNormals()[ normalIndices.z ];

	hit.normal.Normalize();

    if( mesh_->GetTexCoordIndices() != NULL ) {
        const Tuple3I texCoordIndices = mesh_->GetTexCoordIndices()[ index_ ];
        hit.texCoord = alpha * mesh_->GetTexCoords()[ texCoordIndices.x ] +
                       beta  * mesh_->GetTexCoords()[ texCoordIndices.y ] +
                       gamma * mesh_->GetTexCoords()[ texCoordIndices.z ];
    } else
        hit.texCoord = Vector2();
}

// Do not use in intersection tests, it doesn't bail out at first sign of miss
// See: http://en.wikipedia.org/wiki/Barycentric_coordinates_(mathematics)
Vector3 Triangle::ComputeBarycentric(const Vector3& point) const {
	const Tuple3I vertexIndices = mesh_->GetVertexIndices()[ index_ ];
    const Vector3& v0 = mesh_->GetVertices()[ vertexIndices.x ];
    const Vector3& v1 = mesh_->GetVertices()[ vertexIndices.y ];
    const Vector3& v2 = mesh_->GetVertices()[ vertexIndices.z ];

	const float a = v0.x - v2.x;
	const float b = v1.x - v2.x;
	const float c = v2.x - point.x;
	const float d = v0.y - v2.y;
	const float e = v1.y - v2.y;
	const float f = v2.y - point.y;
	const float g = v0.z - v2.z;
	const float h = v1.z - v2.z;
	const float i = v2.z - point.z;

	float alpha, beta;
	if( math::FloatZero(a, options::epsilon) && math::FloatZero(b, options::epsilon) ) {
		const float ci = c+i;
		const float bh = b+h;
		const float ag = a+g;
		const float div = 1.0f / (d*bh-e*ag);

		alpha = (e*ci-f*bh) *  div;
		beta =  (d*ci-f*ag) * -div;
	} else {
		const float fi = f+i;
		const float eh = e+h;
		const float dg = d+g;
		const float div = 1.0f / (a*eh-b*dg);

		alpha = (b*fi-c*eh) *  div;
		beta =  (a*fi-c*dg) * -div;
	}
	
	return Vector3( alpha, beta, 1-alpha-beta );
}

} // namespace rawray
