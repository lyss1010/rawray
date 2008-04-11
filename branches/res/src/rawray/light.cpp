/////////////////////////////////////////////////////////////////////////////
// light.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "light.h"

namespace rawray {

void Light::RenderGL() {
	if( options::global::gl_render_lights ) {
		glColor3f( color_.x, color_.y, color_.z );

		glPushMatrix();
		glTranslatef( position_.x, position_.y, position_.z );
		glutWireSphere( wattage_*0.001f, 2, 2 ); // magic number to scale down lights based on wattage
		glPopMatrix();
	}
}

} // namespace rawray
