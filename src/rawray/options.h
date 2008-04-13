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
    extern uint32 win_width;
    extern uint32 win_height;
    extern uint32 win_posX;
    extern uint32 win_posY;

    extern math::Vector3 img_fg_color;
    extern math::Vector3 img_bg_color;
    extern math::Vector3 gl_bg_color;
    extern uint32 gl_sphere_sections;
	extern bool gl_render_lights;
    extern bool headless;

    extern TriangleIntersection triangle_intersection_algorithm;

    extern uint32 num_threads;
    extern uint32 render_x_block;
    extern uint32 render_y_block;
    extern uint32 render_handler_sleep;
    extern uint32 render_thread_sleep;
    extern uint32 render_spinlock_sleep;

    extern float gaussian_blur_max;
    extern float gaussian_blur_sigma;

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
	extern uint32 spiral_num_spheres;
	extern float spiral_radius;

	extern float lorenz_dt;
	extern float lorenz_min_distance;
	extern float lorenz_max_distance;
	extern float lorenz_sigma;
	extern float lorenz_rho;
	extern float lorenz_beta;
	extern float lorenz_radius;
	extern uint32 lorenz_num_spheres;
	extern math::Vector3 lorenz_start;

} // namespace p0


    DllExport void init();
} // namespace rawray::options
} // namespace rawray

#endif // RAWRAY_RAWRAY_OPTIONS_H
