/////////////////////////////////////////////////////////////////////////////
// square_light.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "square_light.h"

namespace rawray {

float SquareLight::Falloff(float distance2) const {
	// Inverse square falloff
	return 1.0f / distance2;
}

Vector3 SquareLight::GetRandPosition() const {
	const float rand1 = rand() / float(RAND_MAX);
	const float rand2 = rand() / float(RAND_MAX);

	return position_ + d1_ * rand1 + d2_ * rand2;
}

void SquareLight::RenderGL() {
	if( options::global::gl_render_lights ) {
		Vector3 p1 = position_ + d1_;
		Vector3 p2 = position_ + d2_;
		Vector3 p3 = position_ + d1_ + d2_;

		glBegin( GL_QUADS );

			glColor3f( color_.x, color_.y, color_.z );
			
			// Forward
			glVertex3f(p1.x, p1.y, p1.z);
			glVertex3f(p3.x, p3.y, p3.z);
			glVertex3f(p2.x, p2.y, p2.z);
			glVertex3f(position_.x, position_.y, position_.z);

			// Backward
			glVertex3f(position_.x, position_.y, position_.z);
			glVertex3f(p2.x, p2.y, p2.z);
			glVertex3f(p3.x, p3.y, p3.z);
			glVertex3f(p1.x, p1.y, p1.z);

		glEnd();
	}
}

} // namespace rawray
