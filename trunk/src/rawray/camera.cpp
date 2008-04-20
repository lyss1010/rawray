/////////////////////////////////////////////////////////////////////////////
// camera.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "camera.h"
#include "float.h"


namespace rawray {

Camera::Camera() : eye_(options::camera::eye), viewDir_(options::camera::view),
    up_(options::camera::up), lookAt_(options::camera::up), fov_(options::camera::fov),
    aspect_(options::camera::aspect), minDraw_(options::camera::min_draw), 
    maxDraw_(options::camera::max_draw), redrawImage_(true)
{
    CalcLookAt();
}

void Camera::Resize(int width, int height) {
	if( height > 0 && width > 0 )
		aspect_ = float(width) / height;
}

void Camera::RenderGL() {
    CalcLookAt();
    
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
    CalcLookAt(); // NOTE: Shouldn't need to recalc this when rendering an image, camera is fixed

    glDrawBuffer( GL_FRONT );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void Camera::CalcLookAt() {
    // Check if there was a value loaded from a config file
    if( lookAt_.x != FLT_MAX ) {
        viewDir_ = lookAt_;
        viewDir_ -= eye_;

        lookAt_ = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
    }
}

Ray Camera::EyeRay(int x, int y, float xOffset, float yOffset, int width, int height) const {
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
