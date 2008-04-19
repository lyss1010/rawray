/////////////////////////////////////////////////////////////////////////////
// bl_patch.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "bl_patch.h"
#include "material.h"

namespace rawray {

void BLPatch::RenderGL() {
    const Vector3& color = material_ ? material_->BaseColor() : Vector3(1);

    // Draw 2 triangles so we can see something at least in GL
    glBegin(GL_TRIANGLES);
        glColor3f( color.x, color.y, color.z );

        glVertex3f(verts_[0].x, verts_[0].y, verts_[0].z);
        glVertex3f(verts_[2].x, verts_[2].y, verts_[2].z);
        glVertex3f(verts_[1].x, verts_[1].y, verts_[1].z);

        glVertex3f(verts_[3].x, verts_[3].y, verts_[3].z);
        glVertex3f(verts_[2].x, verts_[2].y, verts_[2].z);
        glVertex3f(verts_[1].x, verts_[1].y, verts_[1].z);
    glEnd();
}

void BLPatch::PreCalc() {
}

// See: http://www.cs.utah.edu/~kpotter/pubs/bilinear.pdf
bool BLPatch::Intersect(HitInfo& hit, const Ray& ray, float minDistance, float maxDistance) {
    const Vector3& x1 = verts_[3] - verts_[2] - verts_[1] + verts_[0];
    const Vector3& x2 = verts_[2] - verts_[0];
    const Vector3& x3 = verts_[1] - verts_[0];
    const Vector3& x4 = verts_[0];

    // Manually solve: r + t*d = uv*x1 + u*x2 + v*x3 + x4
	// t.i = (1/d.i) * (uv*x1.i + u*x2.i + v*x3.i + x4.i - r.i)
    BLPatch::BLPatchData p;

	// setting tx*dx*dz = tz*dz*dx where tx=tz=t and substituting the above equation
	p.A1 = x1.x * ray.direction.z - x1.z * ray.direction.x;
	p.B1 = x2.x * ray.direction.z - x2.z * ray.direction.x;
	p.C1 = x3.x * ray.direction.z - x3.z * ray.direction.x;
	p.D1 = ray.direction.z * (x4.x - ray.origin.x) - ray.direction.x * (x4.z - ray.origin.z);

	// and then using ty*dy*dz = tz*dz*dy
	p.A2 = x1.y * ray.direction.z - x1.z * ray.direction.y;
	p.B2 = x2.y * ray.direction.z - x2.z * ray.direction.y;
	p.C2 = x3.y * ray.direction.z - x3.z * ray.direction.y;
	p.D2 = ray.direction.z * (x4.y - ray.origin.y) - ray.direction.y * (x4.z - ray.origin.z);

    // Set the following two equations equal to each other, you get back a quadratic
    // 0 = uvA1 + uB1 + vC1 + D1 = uvA2 + uB2 + vC2 + D2
    // 0 = v^2(A2C1 - A1C2) + v(A2D1 - A1D2 + B2C1 - B1C2) + (B2D1 - B1D2)
    float v1, v2;
    const int numRoots = math::SolveQuadratic( &v1, &v2,
                            ( p.A2*p.C1 - p.A1*p.C2 ),
                            ( p.A2*p.D1 - p.A1*p.D2 + p.B2*p.C1 - p.B1*p.C2 ),
                            ( p.B2*p.D1 - p.B1*p.D2 ) );

    if( numRoots < 1 ) return false;
    
    // Determine dominant axis, this is to ensure no div by 0 when we compute t
    uint8 axis; // 0=x, 1=y, 2=z
    if( ray.abs.x > ray.abs.y )
        axis = (ray.abs.x > ray.abs.z) ? 0 : 2;
    else
        axis = (ray.abs.y > ray.abs.z) ? 1 : 2;
    
    float t, u, v;
    if( numRoots == 1 ) {
		v = v1;
		u = ComputeU( v, p );
		hit.point = u*v*x1 + u*x2 + v*x3 + x4;
		t = (hit.point[axis] - ray.origin[axis]) / ray.direction[axis];

		if( !IsValid( t, u, v, minDistance, maxDistance, 0.5, 0.5 ) )
			return false;
    } else {
        const float u1 = ComputeU( v1, p );
        const float u2 = ComputeU( v2, p );
        
        Vector3 hit1 = u1*v1*x1 + u1*x2 + v1*x3 + x4;
        Vector3 hit2 = u2*v2*x1 + u2*x2 + v2*x3 + x4;

        const float inv_dir = 1.0f / ray.direction[axis];
        const float t1 = (hit1[axis] - ray.origin[axis]) * inv_dir;
        const float t2 = (hit2[axis] - ray.origin[axis]) * inv_dir;

		const bool hit_1_valid = IsValid( t1, u1, v1, minDistance, maxDistance, 0.5, 0.5 );
		const bool hit_2_valid = IsValid( t2, u2, v2, minDistance, maxDistance, 0.5, 0.5 );
		bool choose_hit_1 = true;

		if( hit_1_valid ) {
			if( hit_2_valid && t2 < t1)
				choose_hit_1 = false;
		} else {
			if( hit_2_valid )
				choose_hit_1 = false;
			else
				return false;
		}

		if( choose_hit_1 ) {
			t = t1;
			u = u1;
			v = v1;
			hit.point = hit1;
		} else {
			t = t2;
			u = u2;
			v = v2;
			hit.point = hit2;
		}
    }

	hit.distance = t;
    hit.texCoord.x = u;
    hit.texCoord.y = v;
    hit.material = material_;

    // Compute the normal by using the partial derivitive w/ respect to u and v individually
    hit.normal = math::Cross( ( (1-v)*(verts_[2]-verts_[0]) + v*(verts_[3]-verts_[1]) ), 
                              ( (1-u)*(verts_[1]-verts_[0]) + u*(verts_[3]-verts_[2]) ) );

    return true;
}

bool BLPatch::IsValid(float t, float u, float v, float min, float max, float mid1, float mid2) {
	if( t < min || t > max ) return false;
	if( u < 0.0f || u > 1.0f || v < 0.0f || v > 1.0f ) return false;

	if( (u <= mid1 || u >= mid2) || (v <= mid1 || v >= mid2) )
		return true;

	return false;
}

float BLPatch::ComputeU(float v, const BLPatch::BLPatchData& p) {
    const float divisor_a = v * (p.A2 + p.B2);
    const float divisor_b = v * (p.A2 - p.A1) + p.B2 - p.B1;

    // Choose the largest divisor for numerical stability
    if( fabs(divisor_b) > fabs(divisor_a) )
        return ( v*(p.C1 - p.C2) + p.D1 - p.D2 ) / divisor_b;

	return -(v*p.C2 + p.D2) / divisor_a;
}

} // namespace rawray
