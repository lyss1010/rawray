/////////////////////////////////////////////////////////////////////////////
// custom_scenes.cpp --> (extension of glut_window.cpp)
//
/////////////////////////////////////////////////////////////////////////////
#include "glut_window.h"
#include "light.h"
#include "sphere.h"
#include "triangle_mesh.h"
#include "triangle.h"
#include "float.h"
#include "parser.h"

namespace rawray {

void GlutWindow::MakeScene(int* argc, char* argv[]) {
	int numArgs = *argc;

    for(int i=1; i<numArgs; ++i ) {
		char* filename = argv[i];
		if( filename ) {
			std::cout << "Loading config file '" << filename << "'..." << std::endl;
			ConfigParser( filename );
		}
	}

	DoneParsing();
}

//
//void GlutWindow::MakeSpiralScene() {
//	std::cout << "Loading config file './../res/scenes/spiral.cfg'..." << std::endl;
//    if( !ConfigParser( "./../res/scenes/spiral.cfg" ) )
//		std::cout << "FAILED" << std::endl;
//	else
//		std::cout << "SUCCESS" << std::endl;
//
//	DoneParsing();
//	
//    const float dt = 1.0f / options::p0::spiral_num_spheres;
//    const float a = options::p0::spiral_radius;
//    for (int i=0; i<options::p0::spiral_num_spheres; ++i ) {
//        const float t = i * dt;
//        const float theta = 4 * math::PI * t;
//        const float r = a*theta;
//
//        const float x = r*cos(theta);
//        const float y = r*sin(theta);
//        const float z = 2 * ( 2 * math::PI * a - r);
//
//        const float red = 0.20f*(exp(r-x*x+abs(y)));
//        const float green = 0.12f*( abs(tan(z)) + abs(tan(-z) ) ) ;
//        const float blue = 0.55f;
//
//		Material* mat = scene_.AddMaterial( new Diffuse( Vector3(red,green,blue) ) );
//        rawray::Sphere* sphere = new Sphere( Vector3(x,y,z), r/10, mat );
//        scene_.AddObject(sphere);
//    }
//}
//
//void GlutWindow::MakeLorenzScene() {
//	std::cout << "Loading config file './../res/scenes/lorenz.cfg'..." << std::endl;
//    if( !ConfigParser( "./../res/scenes/lorenz.cfg" ) )
//		std::cout << "FAILED" << std::endl;
//	else
//		std::cout << "SUCCESS" << std::endl;
//
//	DoneParsing();
//
//    float base_dt = options::p0::lorenz_dt;
//	float min_dist = options::p0::lorenz_min_distance;
//	float max_dist = options::p0::lorenz_max_distance;
//
//	const float r = options::p0::lorenz_radius;
//	const float sigma = options::p0::lorenz_sigma;
//	const float rho = options::p0::lorenz_rho;
//	const float beta = options::p0::lorenz_beta;
//	Vector3 delta, l( options::p0::lorenz_start );
//
//	if( base_dt > 0.0f ) {
//		min_dist = FLT_MIN;
//		max_dist = FLT_MAX;
//	} else {
//		base_dt = 0.0001f;
//	}
//
//	// MIN == -16.35  -25.50  00.00
//	// MAX ==  18.90   31.80  58.20
//    for (int i=0; i<options::p0::lorenz_num_spheres; ++i ) {
//		float dt = base_dt;
//        uint8 num_tries = 0;
//
//		do {
//			delta.x = sigma * ( l.y - l.x );
//			delta.y = l.x * (rho - l.z) - l.y;
//			delta.z = (l.x * l.y) - (beta * l.z);
//			delta *= dt;
//
//			float length = delta.Length();
//            if( length < min_dist )
//				dt *= 1.5f;
//			else if( length > max_dist )
//				dt /= 1.5f;
//			else
//				break;
//		} while( num_tries++ < 8 );
//
//		l += delta;
//
//		const float red = 0.3f + (l.Dot( Vector3(0.5f,0,1) )) / 250;
//        const float green = 0.3f + (l.Dot( Vector3(1,1,1) )) / 300;
//		const float blue = 0.4f + (l.Dot( Vector3(1,1,0) )) / 100;
//
//		Material* mat = scene_.AddMaterial( new Diffuse( Vector3(red,green,blue), 0.4*Vector3(red,green,blue) ) );
//        rawray::Sphere* sphere = new Sphere( l, r, mat );
//        scene_.AddObject(sphere);
//    }
//}

} // namespace rawray
