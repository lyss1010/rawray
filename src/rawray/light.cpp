/////////////////////////////////////////////////////////////////////////////
// light.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "light.h"

namespace rawray {

void Light::RenderGL() {
    glColor3f( color_.x, color_.y, color_.z );

    glPushMatrix();
    glTranslatef( position_.x, position_.y, position_.z );
    glutWireSphere( 0.6f, 10, 10 );
    glPopMatrix();
}

} // namespace rawray
