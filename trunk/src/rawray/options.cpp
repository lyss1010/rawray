#include "stdafx.h"
#include "options.h"
#include "float.h"
#include "math/constants.h"

namespace rawray {
namespace options {

float epsilon;

TriangleIntersection triangle_intersection_algorithm;
Vector3 bg_color;
Vector3 gl_bg_color;

Vector3 cam_eye;
Vector3 cam_view;
Vector3 cam_up;
Vector3 cam_lookat;

float cam_fov;
float cam_aspect;
float cam_minDraw;
float cam_maxDraw;

std::string win_name;
uint32 win_width;
uint32 win_height;
uint32 win_posX;
uint32 win_posY;

uint32 num_threads;
uint32 render_x_block;
uint32 render_y_block;
uint32 render_handler_sleep;
uint32 render_thread_sleep;
uint32 render_spin_lock_sleep;
float gaussian_blur_max;

// A DLL can't initialize non-primitive static data
void init() {
    epsilon = 0.00001f;

    triangle_intersection_algorithm = BARYCENTRIC;

    bg_color = Vector3(1.0f, 1.0f, 1.0f);
    gl_bg_color = Vector3(0.0f, 0.0f, 0.0f);
    cam_eye = Vector3(0.0f, 0.0f, 0.0f);
    cam_view = Vector3(0.0f, 0.0f, -1.0f);
    cam_up = Vector3(0.0f, 1.0f, 0.0f);
    cam_lookat = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);

    cam_fov = 45.0f * 180.0f * math::PI;
    cam_aspect = 640.0f / 480.0f;
    cam_minDraw = 0.01f;
    cam_maxDraw = 10000.0f;

    win_name = std::string("RawRay");
    win_width = 640;
    win_height = 480;
    win_posX = 100;
    win_posY = 100;

    num_threads = 2;
    render_x_block = 64;
    render_y_block = 64;
    render_handler_sleep = 50;
    render_thread_sleep = 10;
    render_spin_lock_sleep = 10;

    gaussian_blur_max = 2.0f;
}

} // namespace rawray::options
} // namespace rawray
