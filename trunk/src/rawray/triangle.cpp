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

/////////////////////////////////////////////////////////////////////////////

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

void Triangle::Interpolate(HitInfo& hit, float alpha, float beta, float gamma) {
    const Tuple3I normalIndices = mesh_.GetNormalIndices()[ index_ ];
    hit.normal = alpha * mesh_.GetNormals()[ normalIndices.x ] +
                 beta  * mesh_.GetNormals()[ normalIndices.y ] +
                 gamma * mesh_.GetNormals()[ normalIndices.z ];

    if( mesh_.GetTexCoordIndices() != NULL ) {
        const Tuple3I texCoordIndices = mesh_.GetTexCoordIndices()[ index_ ];
        hit.texCoord = alpha * mesh_.GetTexCoords()[ texCoordIndices.x ] +
                       beta  * mesh_.GetTexCoords()[ texCoordIndices.y ] +
                       gamma * mesh_.GetTexCoords()[ texCoordIndices.z ];
    } else
        hit.texCoord = Vector2();
}

} // namespace rawray
