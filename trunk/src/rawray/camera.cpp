/////////////////////////////////////////////////////////////////////////////
// camera.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "camera.h"
#include "float.h"
#include "stats.h"

namespace rawray {

Camera::Camera() : eye_(options::camera::eye), viewDir_(options::camera::view),
    up_(options::camera::up), fov_(options::camera::fov),
    aspect_(options::camera::aspect), minDraw_(options::camera::min_draw), 
    maxDraw_(options::camera::max_draw), redrawImage_(true)
{
}

void Camera::Resize(int width, int height) {
	if( height > 0 && width > 0 )
		aspect_ = float(width) / height;
}

void Camera::RenderGL() {
    glDrawBuffer( GL_BACK );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // set up the screen with our camera parameters
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov_, aspect_, minDraw_, maxDraw_);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Vector3 center = eye_ + viewDir_;
    gluLookAt(eye_.x, eye_.y, eye_.z,
              center.x, center.y, center.z,
              up_.x, up_.y, up_.z);
}

void Camera::RenderImage() {
    glDrawBuffer( GL_FRONT );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}


Ray Camera::EyeRay(int x, int y, float xOffset, float yOffset, int width, int height) const {
#ifdef _DEBUG
    stats::primaryRays++;
#endif

    // Compute camera coordinate system
    Vector3 wDir(viewDir_);
    wDir.Negate();
    wDir.Normalize();

    Vector3 uDir(up_);
    uDir.Cross(wDir);
    uDir.Normalize();

    Vector3 vDir(wDir);
    vDir.Cross(uDir);

    // Find corners of image plane in camera space
    const float aspect = float(width)/float(height);
    const float top = tanf( fov_ * math::HALF_DEG_TO_RAD );
    const float right = aspect*top;
    const float bottom = -top;
    const float left = -right;

    // transform x and y to camera space (into the center of the pixel)
    const float uPos = left + (right-left) * (x+xOffset) / float(width);
    const float vPos = bottom + (top-bottom) * (y+yOffset) / float(height);

    Vector3 rayDirection = Vector3( uPos*uDir + vPos*vDir );
    rayDirection -= wDir;

    return Ray( eye_, rayDirection.Normalize() );
}

} // namespace rawray
