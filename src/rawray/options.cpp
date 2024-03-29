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
	int aax;
	int aay;
	int max_ior_bounce;
	int max_diffuse_bounce;

    math::Vector4 img_fg_color;
    math::Vector4 img_bg_color;
    math::Vector4 gl_bg_color;
    int  gl_sphere_sections;
	bool gl_render_lights;
    bool gl_render_bbox;
    bool gl_render_objects;
    bool headless;

    TriangleIntersection triangle_intersection_algorithm;

    int num_threads;
    int thread_job_size_x;
	int thread_job_size_y;
    int render_handler_sleep;
    int render_thread_sleep;
    int render_spinlock_sleep;

    float gaussian_blur_max;
    float gaussian_blur_sigma;

    float bvh_box_cost;
    float bvh_obj_cost;
	float hdr_bloom_power;
	float hdr_bloom_radius;

	float bcspline_b;
	float bcspline_c;

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
    global::img_fg_color = Vector4(1);
    global::img_bg_color = Vector4(0);
    global::gl_bg_color = Vector4(0);
    global::win_width  = 800;
    global::win_height = 800;
    global::win_posX   = 100;
    global::win_posY   = 100;
	global::aax	       = 1;
	global::aay        = 1;
	global::max_ior_bounce = 4;
	global::max_diffuse_bounce = 1;

    global::num_threads = 4;
    global::thread_job_size_x = 64;
	global::thread_job_size_y = 64;
    global::render_handler_sleep = 256;
    global::render_thread_sleep = 256;
    global::render_spinlock_sleep = 256;

    global::bvh_box_cost = 1.0f;
    global::bvh_obj_cost = 640.0f;
	global::hdr_bloom_power = 0.5f;
	global::hdr_bloom_radius = 6.0f;

	global::bcspline_b = 0.35f;
	global::bcspline_c = 0.35f;

    global::gaussian_blur_max = 2.0f;
	global::gaussian_blur_sigma = 1.0f;
	global::gl_sphere_sections = 8;
	global::gl_render_lights = true;
    global::gl_render_bbox = false;
    global::headless = true;

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
