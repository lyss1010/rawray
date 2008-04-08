#include "stdafx.h"
#include "options.h"
#include "float.h"
#include "math/constants.h"

namespace rawray {
namespace options {

float epsilon;

namespace global {
    uint32 win_width;
    uint32 win_height;
    uint32 win_posX;
    uint32 win_posY;

    math::Vector3 img_bg_color;
    math::Vector3 gl_bg_color;
    uint32 gl_sphere_sections;
	bool gl_render_lights;

    TriangleIntersection triangle_intersection_algorithm;

    uint32 num_threads;
    uint32 render_x_block;
    uint32 render_y_block;
    uint32 render_handler_sleep;
    uint32 render_thread_sleep;
    uint32 render_spinlock_sleep;

    float gaussian_blur_max;
    float gaussian_blur_sigma;

} // namespace global


namespace camera {
     math::Vector3 eye;
     math::Vector3 view;
     math::Vector3 up;
     math::Vector3 lookat;

     float fov;
     float aspect;
     float min_draw;
     float max_draw;

} // namespace camera

namespace p0 {
	 uint32 spiral_num_spheres;
	 float spiral_radius;

	 float lorenz_dt;
	 float lorenz_min_distance;
	 float lorenz_max_distance;
	 float lorenz_sigma;
	 float lorenz_rho;
	 float lorenz_beta;
	 float lorenz_radius;
	 uint32 lorenz_num_spheres;
	 math::Vector3 lorenz_start;

} // namespace p0



// A DLL can't initialize non-primitive static data
void init() {
    epsilon = 0.00001f;

    global::triangle_intersection_algorithm = BARYCENTRIC;
    global::img_bg_color = Vector3(1);
    global::gl_bg_color = Vector3(0);
    global::win_width  = 800;
    global::win_height = 800;
    global::win_posX   = 100;
    global::win_posY   = 100;

    global::num_threads = 4;
    global::render_x_block = 32;
    global::render_y_block = 32;
    global::render_handler_sleep = 50;
    global::render_thread_sleep = 10;
    global::render_spinlock_sleep = 10;

    global::gaussian_blur_max = 2.0f;
	global::gaussian_blur_sigma = 1.0f;
	global::gl_sphere_sections = 8;
	global::gl_render_lights = false;

    camera::eye = Vector3(0);
    camera::view = Vector3(0.0f, 0.0f, -1.0f);
    camera::up = Vector3(0.0f, 1.0f, 0.0f);
    camera::lookat = Vector3(FLT_MAX);
    camera::fov = 45.0f;
    camera::aspect = 1.0f;
    camera::min_draw = 0.01f;
    camera::max_draw = 10000.0f;
}

} // namespace rawray::options
} // namespace rawray
