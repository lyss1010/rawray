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
uint32 sphere_sections;

uint32 spiral_num_sphere;
float spiral_radius;

float lorenz_dt;
float lorenz_min_distance;
float lorenz_max_distance;
float lorenz_sigma;
float lorenz_rho;
float lorenz_beta;
float lorenz_radius;
uint32 lorenz_num_sphere;
Vector3 lorenz_start;

// A DLL can't initialize non-primitive static data
void init() {
    epsilon = 0.00001f;

    triangle_intersection_algorithm = BARYCENTRIC;

    bg_color = Vector3(1);
    gl_bg_color = Vector3(0);
    cam_eye = Vector3(0);
    cam_view = Vector3(0.0f, 0.0f, -1.0f);
    cam_up = Vector3(0.0f, 1.0f, 0.0f);
    cam_lookat = Vector3(FLT_MAX);

	win_width = 800;
    win_height = 800;
    win_posX = 100;
    win_posY = 100;

    cam_fov = 45.0f * 180.0f * math::PI;
    cam_aspect = float(win_width) / win_height;
    cam_minDraw = 0.01f;
    cam_maxDraw = 10000.0f;

    num_threads = 4;
    render_x_block = 32;
    render_y_block = 32;
    render_handler_sleep = 50;
    render_thread_sleep = 10;
    render_spin_lock_sleep = 10;

    gaussian_blur_max = 2.0f;
	sphere_sections = 4;

	spiral_num_sphere = 100;
	spiral_radius = 0.15f;

	lorenz_dt = 0.0040f;
	lorenz_min_distance = 0.35f;
	lorenz_max_distance = 2.5f;
	lorenz_sigma = 5.7f;
	lorenz_rho = 32;
	lorenz_beta = 2.0f;
	lorenz_radius = 0.10f;
	lorenz_num_sphere = 3000;
	lorenz_start = Vector3(0.0f, 1.0f, 0.0f);
}

} // namespace rawray::options
} // namespace rawray
