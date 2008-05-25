/////////////////////////////////////////////////////////////////////////////
// Project Options : options.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_OPTIONS_H
#define RAWRAY_RAWRAY_OPTIONS_H
#include "math/vector3.h"

namespace rawray {
namespace options {

enum TriangleIntersection {
    BARYCENTRIC,
    BARYCENTRIC_PROJECTION,
    PLUCKER,
    MOLLER,
};
extern float epsilon;

namespace global {
    extern int win_width;
    extern int win_height;
    extern int win_posX;
    extern int win_posY;
	extern int aax;
	extern int aay;
	extern int max_bounce;

    extern math::Vector3 img_fg_color;
    extern math::Vector3 img_bg_color;
    extern math::Vector3 gl_bg_color;
    extern int  gl_sphere_sections;
	extern bool gl_render_lights;
    extern bool gl_render_bbox;
    extern bool gl_render_objects;
    extern bool headless;

    extern TriangleIntersection triangle_intersection_algorithm;

    extern int num_threads;
    extern int thread_job_size_x;
	extern int thread_job_size_y;
    extern int render_handler_sleep;
    extern int render_thread_sleep;
    extern int render_spinlock_sleep;

    extern float gaussian_blur_max;
    extern float gaussian_blur_sigma;

    extern float bvh_box_cost;
    extern float bvh_obj_cost;

} // namespace global

namespace camera {
    extern math::Vector3 eye;
    extern math::Vector3 view;
    extern math::Vector3 up;
    extern math::Vector3 lookat;

    extern float fov;
    extern float aspect;
    extern float min_draw;
    extern float max_draw;

} // namespace camera

namespace p0 {
	extern int spiral_num_spheres;
	extern float spiral_radius;

	extern float lorenz_dt;
	extern float lorenz_min_distance;
	extern float lorenz_max_distance;
	extern float lorenz_sigma;
	extern float lorenz_rho;
	extern float lorenz_beta;
	extern float lorenz_radius;
	extern int lorenz_num_spheres;
	extern math::Vector3 lorenz_start;

} // namespace p0


    DllExport void init();
} // namespace rawray::options
} // namespace rawray

#endif // RAWRAY_RAWRAY_OPTIONS_H
