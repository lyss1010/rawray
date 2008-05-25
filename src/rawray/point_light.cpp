/////////////////////////////////////////////////////////////////////////////
// point_light.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "point_light.h"

namespace rawray {

float PointLight::Falloff(float distance2) const {
	// Inverse square falloff
	return 1.0f / distance2;
}

void PointLight::RenderGL() {
	if( options::global::gl_render_lights ) {
		glColor3f( color_.x, color_.y, color_.z );

		glPushMatrix();
		glTranslatef( position_.x, position_.y, position_.z );
		glutWireSphere( 0.1f, 5, 5 ); // magic number size for point lights
		glPopMatrix();
	}
}

} // namespace rawray
