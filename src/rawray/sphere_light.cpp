/////////////////////////////////////////////////////////////////////////////
// sphere_light.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "sphere_light.h"
#include "sphere.h"
#include "emitter.h"

namespace rawray {

float SphereLight::Falloff(float distance2) const {
	// Inverse square falloff
	return 1.0f / distance2;
}

Vector3 SphereLight::GetRandPosition() const {
	// Take the center and move out in each direction from 0-radius
	// NOTE: Not uniform over volume
	return Vector3(	position_.x + radius_ * rand()/float(RAND_MAX),
					position_.y + radius_ * rand()/float(RAND_MAX),
					position_.z + radius_ * rand()/float(RAND_MAX) );
}

void SphereLight::RenderGL() {
	if( options::global::gl_render_lights ) {
		glColor3f( color_.x, color_.y, color_.z );

		glPushMatrix();
		glTranslatef( position_.x, position_.y, position_.z );
		glutWireSphere( radius_, 5, 5 ); // magic number to scale down lights based on wattage
		glPopMatrix();
	}
}

} // namespace rawray
