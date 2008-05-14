#include "stdafx.h"
#include "options.h"
#include "float.h"
#include "math/constants.h"

namespace rawray {
namespace options {

float epsilon;

namespace global {
    int win_width;
    int win_height;
    int win_posX;
    int win_posY;

    math::Vector3 img_fg_color;
    math::Vector3 img_bg_color;
    math::Vector3 gl_bg_color;
    int  gl_sphere_sections;
	bool gl_render_lights;
    bool gl_render_bbox;
    bool gl_render_objects;
    bool headless;

    TriangleIntersection triangle_intersection_algorithm;

    int num_threads;
    int render_x_block;
    int render_y_block;
    int render_handler_sleep;
    int render_thread_sleep;
    int render_spinlock_sleep;

    float gaussian_blur_max;
    float gaussian_blur_sigma;

    float bvh_box_cost;
    float bvh_obj_cost;

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
	 int spiral_num_spheres;
	 float spiral_radius;

	 float lorenz_dt;
	 float lorenz_min_distance;
	 float lorenz_max_distance;
	 float lorenz_sigma;
	 float lorenz_rho;
	 float lorenz_beta;
	 float lorenz_radius;
	 int lorenz_num_spheres;
	 math::Vector3 lorenz_start;

} // namespace p0



// A DLL can't initialize non-primitive static data
void init() {
    epsilon = 0.00001f;

    global::triangle_intersection_algorithm = BARYCENTRIC;
    global::img_fg_color = Vector3(1);
    global::img_bg_color = Vector3(0);
    global::gl_bg_color = Vector3(0);
    global::win_width  = 800;
    global::win_height = 800;
    global::win_posX   = 100;
    global::win_posY   = 100;

    global::num_threads = 4;
    global::render_x_block = 32;
    global::render_y_block = 32;
    global::render_handler_sleep = 256;
    global::render_thread_sleep = 256;
    global::render_spinlock_sleep = 256;

    global::bvh_box_cost = 1.0f;
    global::bvh_obj_cost = 75.0f;

    global::gaussian_blur_max = 2.0f;
	global::gaussian_blur_sigma = 1.0f;
	global::gl_sphere_sections = 8;
	global::gl_render_lights = false;
    global::gl_render_bbox = false;
    global::headless = false;

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
