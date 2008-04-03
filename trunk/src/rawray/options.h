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

    extern TriangleIntersection triangle_intersection_algorithm;
    extern math::Vector3 bg_color;
    extern math::Vector3 gl_bg_color;

    extern math::Vector3 cam_eye;
    extern math::Vector3 cam_view;
    extern math::Vector3 cam_up;
    extern math::Vector3 cam_lookat;

    extern float cam_fov;
    extern float cam_aspect;
    extern float cam_minDraw;
    extern float cam_maxDraw;

    extern std::string win_name;
    extern uint32 win_width;
    extern uint32 win_height;
    extern uint32 win_posX;
    extern uint32 win_posY;
    
    extern uint32 num_threads;
    extern uint32 render_x_block;
    extern uint32 render_y_block;
    extern uint32 render_handler_sleep;
    extern uint32 render_thread_sleep;
    extern uint32 render_spin_lock_sleep;

    extern float gaussian_blur_max;

    DllExport void init();
} // namespace rawray::options
} // namespace rawray

#endif // RAWRAY_RAWRAY_OPTIONS_H
